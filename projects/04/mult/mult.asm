// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

  // init registers
  @R2
  M = 0
  @R3 // use R3 for our accumulation
  M = 0 // set R3 to 0
(LOOP)
  @R1 // load second term
  D = M
  @END
  D ; JLE // jump to END if D = 0
  @R3
  D = M // set data register to R3
  @R0
  D = D + M // increase data register value by R0
  @R3
  M = D // store result back in R3
  @R1
  D = M - 1 // decrement second term
  @R1
  M = D // store decremented second term
  @LOOP
  0 ; JMP // else loop
(END)
  @R3
  D = M
  @R2
  M = D
  @END
  0 ; JMP


