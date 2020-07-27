#!/usr/bin/env node

let result = 0;

for (let i = 0; i < 1000; i++) {
  setTimeout(() => result++, 0)
}


setTimeout(() => console.log(`Result is ${result}`), 0);
