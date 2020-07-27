#!/usr/bin/ruby
# frozen_string_literal: true

if ARGV.empty?
  puts 'Must call this program with 1 argument, ' \
       'indicating the number of threads'
  return
end

num_threads = Integer(ARGV[0])

result = 0
threads = []
num_threads.times do
  threads << Thread.new { result += 1 }
end

threads.each(&:join)
puts "Result is #{result}"
