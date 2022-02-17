============================================================
General description
============================================================

It is expected that you will implement a basic compiler for the 
C0 language, a dialect of the C language developed at Carnegie University 
Mellon University for teaching. The compiler will read C0 source code and generate 
MIPS assembly code.
In addition to this document you should also consult the C0 language reference 
(language reference.pdf that contains detailed descriptions of the syntax and 
semantics (including grammar rules).

============================================================
1. 

a) Check the available files:
   - Makefile : makefile to build the interpreter.
   - scanner.flex : the lexical analyser (scanner) in flex
   - parser.bison: the parser in bison
   - ast.h, ast.c: AST declarations & constructor implementations
   - interpreter.c: the interpreter routines including main
   - example[1234].txt : example files

b) Compile the interpreter by typing "make" in the command line.
   The generated executable file is called "interpreter".

c)  The interpreter recognises a single expression composed 
of single integers or expressions making use
of the '+' operator.  

Execute it for example1.txt and example2.txt, for instance 
type "./interpreter example1.txt". 

============================================================
2. Main objectives

a) Basic types (int, bool) and constants (true, false and integers)
b) Arithmetic expressions: +, -, *, /, %
c) Simple variable declarations and assignments: var = expr
d) Comparison operators: ==, !=, <, <=, >, >=
e) Conditional execution: if(expr) instr / if(expr) instr else instr
f) Instruction blocks: { instr . . . . instr }
g) Cycles: while(expr) instr
h) Definition of functions with arguments and return values
i) Functions to input and output integers: scan_int(), print_int()

3. Extra objectives

It is not necessary to implement all of them to get full quotation.
Quality will be valued more than quantity!

a) Checking type errors
b) Logical operators !, && and || (with short-circuit evaluation)
c) Cycles for
d) Cycle flow control using break and continue
e) string type, constants and a print function: print_str()
f) Arrays of basic types

