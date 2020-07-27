# Concurrency Examples

Spin up N number of threads, have each thread increment the same variable. The result should be N right? How hard can that be?

## C 
The C example uses illustrates the difficulty of concurrency with true paralleism. The pthreads (POSIX Threads) library is used to demonstrate.

Compile the source with `make`

Run the compiled program with `./program 1000`

The first argument is the number of threads to create, you can specify `-m` after the number of threads to run the mutex version. 

## Ruby
### CRuby
CRuby, or MRI, supports threads, but does not have paralleism. This means only 1 thread is executed at a time. Threads are not interrupted unless they explicitly yield to the runtime (File/Network I/O for example).\

`ruby main.rb`

### JRuby
JRuby does support parallelism and you can see the same pit

`jruby main.rb`

## Javascript
(Web workers enable concurrency in JS, but I am ignoring that for now)

Javascript is single threaded, does not have a threading API, but it does have an event loop. Using `setTimeout` we can schedule work to happen sometime in the future, and kind of fake threading.

`node main.js`
