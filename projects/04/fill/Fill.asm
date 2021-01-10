// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.


// init vars
@R0
M = 0

// set screen limit
@SCREEN
D = A
@8192
D = D + A
@R1
M = D

@SCREEN
D = A // load screen addr into data reg
@R0 // pixel offset
M = D // start at screen memory location

(LOOP)
@KBD // check keyboard state
D = M // load kbd state into data reg

@WRITEPIX // load write loc to A
D;JGT // if D (meaning if key is pressed)

@ERASEPIX // load erase loc to A
0;JMP // else jump to erase pix

(WRITEPIX) // write pixel black
@R0 // offset accumulator
D = M
A = D
M = -1
@INCREMENT// inf loop
0;JMP

(ERASEPIX)
@R0 // offset accumulator
D = M
A = D
M = 0 
@INCREMENT
0;JMP

(INCREMENT)
@R1
D = M
@R0
M = M + 1
D = D - M
@RESET
D;JLE

// check for out of bounds
@LOOP // inf loop
0;JMP

(RESET)
@SCREEN
D = A
@R0
M = D

@LOOP
0;JMP

