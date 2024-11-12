# ISA
## Types
Types used in ISA:
- w8 &mdash; 8-bit value
- w16 &mdash; 16-bit value
- w32 &mdash; 32-bit value
- w64 &mdash; 64-bit value
- Label
- Function

Types w8, w16, w32, w64 have the following subtype:
- Value &mdash; represents the data, which can be read
- Dest &mdash; represents the data, which can be written
- DestValue &mdash; represents the data, which can be read and written

## Registers

ISA has 256 registers:
- w8-form with names ```l0```-```l255```
- w16-form with names ```x0```-```x255```
- w32-form with names ```ex0```-```ex255```
- w64-form with names ```rx0```-```rx255```

Register l```<i>``` represents the lower part of register x```<i>```.\
Register x```<i>``` represents the lower part of register ex```<i>```.\
Register ex```<i>``` represents the lower part of register rx```<i>```.

When the lower part of the register is written, the higher part is set to zero.

Registers are the DestValue subtype.

## Constants

Constants should be represented with a decimal integer with an optional ```-``` before it. 

All the constants should be preceded by the type in a brackets (ex. ```(w32) -239```).

Constants are the Value subtype.

## Poinsters

Pointers represents the value from the memory.

All the pointers should be written in the following form: ```(<type>) *rx<i>``` (ex. ```(w16) *rx5```).

Pointers are the DestValue subtype.

## Labels

Labels are the points in a function, which can be jumped to.

All the labels should be written in the following form: ```%<name>``` (ex. ```%foo_lbl```). 

Name of the label should consist of latin letters, digits and ```_```.

Labels with the same name inside the function are forbidden.

Labels with the same name in the different functions are the diffenent labels.

## Functions

Functions are the named blocks of code, which can be executed. 

All the functions should be referred with the following form: ```#<name>(<args_count>)``` (ex. ```#foo_func(5)```).

Name of the function should consist of latin letters, digits and ```_```.

Functions with the same name and the same args count are forbidden.

Functions with the same name and the diffenent args count are the different functions.

Each function should be ended with ```jp```, a call, which will never be exited, or a ```ret``` instruction.

## Comment

Comment is a line started with ```;```. This line will be ignored by the compiler.

## Calling convention

Arguments of the call should be passed through the registers ```rx0```-```rx<n>```, where ```n = args_count - 1```.

All the functions return a value in ```rx0``` register.

Registers ```rx0```-```rx<n>```, but at least ```rx0```, are not guarantied to save their value after the call.

Registers ```rx<n+1>```-```rx255``` are presaved by ```call``` instruction and guarantied not to be changed.

## Instruction Set

- Value operands with type ```t``` are marked as ```<name:t>```
- Dest operands with type ```t``` are marked as ```{name:t}```
- DestValue operands with type ```t``` are marked as ```[name:t]```
- Label operands are marked as ```%lbl```
- Function operands are marked as ```#func(n)```

### add
```add {res:t} <left:t> <right:t>```

Sum ```left``` with ```right``` and write the result to ```res```

### sub
```sub {res:t} <left:t> <right:t>```

Subtract ```right``` from ```left``` and write the result to ```res```

### mul
```mul {res:t} <left:t> <right:t>```

Multiply ```left``` by ```right``` and write the result to ```res```

### div
```div {div:t} {rem:t} <left:t> <right:t>```

Divide ```left``` by ```right``` as signed values and write the quotient to ```div``` and the reminder to ```rem```

### udiv
```udiv {div:t} {rem:t} <left:t> <right:t>```

Divide ```left``` by ```right``` as unsigned values and write the quotient to ```div``` and the reminder to ```rem```

### and
```and {res:t} <left:t> <right:t>```

Compute bitwise AND of ```left``` and ```right``` and write the result to ```res```

### or
```or {res:t} <left:t> <right:t>```

Compute bitwise OR of ```left``` and ```right``` and write the result to ```res```

### xor
```and {res:t} <left:t> <right:t>```

Compute bitwise XOR of ```left``` and ```right``` and write the result to ```res```

### lsh
```and {res:t} <op:t> <sh:t2>```

Shift ```op``` left by ```sh``` and write the result to ```res```

### rshl
```rshl {res:t} <op:t> <sh:t2>```

Shift ```op``` right by ```sh``` logically and write the result to ```res```

### rsha
```rsha {res:t} <op:t> <sh:t2>```

Shift ```op``` right by ```sh``` arithmetically and write the result to ```res```

### eq
```eq {res:t} <left:t2> <right:t2>```

Compare ```left``` with ```right``` and write ```1``` to ```res``` if ```left``` is equal to ```right```, otherwise write  ```0```

### neq
```neq {res:t} <left:t2> <right:t2>```

Compare ```left``` with ```right``` and write ```1``` to ```res``` if ```left``` is not equal to ```right```, otherwise write  ```0```

### lt
```lt {res:t} <left:t2> <right:t2>```

Compare ```left``` with ```right``` as a signed values and write ```1``` to ```res``` if ```left``` is less than ```right```, otherwise write  ```0```

### le
```le {res:t} <left:t2> <right:t2>```

Compare ```left``` with ```right``` as a signed values and write ```1``` to ```res``` if ```left``` is less than or equal to ```right```, otherwise write  ```0```

### ult
```ult {res:t} <left:t2> <right:t2>```

Compare ```left``` with ```right``` as a unsigned values and write ```1``` to ```res``` if ```left``` is less than ```right```, otherwise write  ```0```

### ule
```ule {res:t} <left:t2> <right:t2>```

Compare ```left``` with ```right``` as a unsigned values and write ```1``` to ```res``` if ```left``` is less than or equal to ```right```, otherwise write  ```0```

### mv
```mv {dst:t} <src:t>```

Write ```src``` to ```dst```

### mvc
```mvc <cond:t> {dst:t2} <src:t2>```

Write ```src``` to ```dst``` if ```cond``` is not ```0```

### swp
```swp [left:t] [right:t]```

Swap ```left``` and ```right```

###  drw
```drw <x:w32> <y:w32> <color:w32>```

Set color of pixel (```x```, ```y```) to ```color```

### flsh
```flsh```

Update the screen

### alloc
```alloc {dst:w64} <n:t>```

Allocate ```n``` bytes of memory and write the address of the first byte to ```dst```

### free
```free <src:w64>```

Free the memory. ```src``` should contain the result of ```alloc``` 

### call
```call #func(n)```

Execute the function ```#func(n)```.
See "Calling convention"

### ret
```ret```

Return from the function

### jp
```jp %lbl```

Jump to label ```%lbl```. The label should be in the same function

### jpc
```jpc <cond:t> %lbl```

Jump to label ```%lbl``` if ```cond``` is not ```0```. The label should be in the same function

### nop
```nop```

Do nothing