# Brainfuck Interpreter

This program serves to interpret code written in the esoteric programming language Brainfuck. The concept is simple: each Brainfuck program is alloted a default of 30,000 single byte memory cells, and the following symbols are used:

* \+ to increment the current cell's value by 1
* \- to decrement the current cell's value by 1
* . to output the current cell's value as its ASCII mapping
* , to take a single character input
* \> to shift one cell to the right
* < to shift one cell to the left
* [ to begin a while loop, as long as the current cell is != 0
* ] to end a while loop

Generally, all other characters are ignored. For this implementation, only the 8 valid tokens and whitespace are allowed.

You can read more here: https://en.wikipedia.org/wiki/Brainfuck
