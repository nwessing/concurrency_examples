defmodule Concurrency.Process do
  def start do
    spawn(&loop/0)
  end

  def loop(state \\ 0) do
    receive do
      {_pid, :increment} ->
        loop(state + 1)

      {pid, :get_count} ->
        send(pid, state)
        loop(state)
    end
  end
end

pid = Concurrency.Process.start()

client_pids =
  1..1000
  |> Enum.map(fn _ ->
    spawn(fn -> send(pid, {self(), :increment}) end)
  end)

client_pids
|> Enum.each(fn client_pid ->
  Process.monitor(client_pid)

  receive do
    {:DOWN, _, :process, _, _} ->
      true
  end
end)

send(pid, {self(), :get_count})

receive do
  count -> IO.puts("Count is : #{count}")
end
