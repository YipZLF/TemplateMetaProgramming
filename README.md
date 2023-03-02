# A Demo of Template Metaprogramming

## Features

- Support types are:
  - Number (rational numbers)
  - Boolean
  - None
  - Pair
  - List
- Support operations:
  - add, sub, mul, div
  - greater, geq, less, leq
  - print
- Support program structure:
  - sequencial
  - branch
  - loop(using branch)

## Demo

see `demo.cpp`

## Compile & Try

Use the following instruction to compile:

```
g++ ./demo.cpp -std=c++14 
-ftemplate-depth=1024 -I. -o demo
```
