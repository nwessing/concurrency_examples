defmodule Concurrency.Process do
  use GenServer

  def start_link(default) do
    GenServer.start_link(__MODULE__, default, name: Counter)
  end

  @impl true
  def init(_) do
    {:ok, 0}
  end

  @impl true
  def handle_cast(:increment, state) do
    {:noreply, state + 1}
  end

  @impl true
  def handle_call(:get_count, _from, state) do
    {:reply, state, state}
  end

  def increment() do
    GenServer.cast(Counter, :increment)
  end

  def get_count() do
    GenServer.call(Counter, :get_count)
  end
end

{:ok, _} = Supervisor.start_link([Concurrency.Process], strategy: :one_for_all)

tasks =
  1..1000
  |> Enum.map(fn _ ->
    Task.async(fn -> Concurrency.Process.increment() end)
  end)

tasks
|> Enum.each(fn task ->
  Task.await(task)
end)

IO.puts("Count is : #{Concurrency.Process.get_count()}")
