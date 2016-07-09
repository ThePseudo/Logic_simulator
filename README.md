LS: LOGIC SIMULATOR

------------------------------

Index:

1 Program functionalities and limitations
2 How to start LS
3 The structure file
3.1 How to use gates
4 The input file
5 Credits

------------------------------

1 Program functionalities and limitations

This program allows the user to simulate any logic circuit you want, with some limitation:
- only combinatorial circuits are allowed
- the program does not calculate any critical path

---------------------------------------

2 How to start LS

By default, your input files will be "structure.txt" and "inputs.txt"
You can give some input paramenters to prevent this: the first parameter is the structure file, the second one contains every input series you want to simulate

---------------------------------------

3 The structure file

The structure file is divided into two parts:
- the first one contains the INPUTS, NETS, OUTPUTS (followed by a number) and NAME (optional) directives; this section ends with the word GATES
- the second part contains the gates declarations: you can use AND, OR, XOR, NOT, NAND, NOR, XNOR.

------------------------

3.1 How to use gates

To use a gate, you have to follow the synthax:

GATEN GATE_NAME INPUT_1, INPUT_2, ... INPUT_N, GATE_OUTPUT

Where the "N" in "GATEN" is the number of inputs the gate has to take

Input names are called by I, net ones with the N and output ones with the O charachter followed by a number in the range 0 - N-1 and a comma.
The user will be aknowledged of those errors.

---------------------------------------

4 The input file

The input file provides all the inputs for the simulation in a simple format: you must provide all the inputs you declared in the first part of the file divided by a space
If you do not provide enough inputs, in the last simulation the missing inputs will be substituted by the previous ones:

EX: if you have 3 inputs and you want 3 simulations done, the file should look like this:

0 1 0
1 1 1
0 1 0

It is possible to write every simulation in a single line (in the previous ex: 0 1 0 1 1 1 0 1 0), but we suggest not to.

EX 2: Having 3 inputs:

0 1 0
1 1 1
0

The last simulation will have the inputs set as "0 1 1"

---------------------------------------

5 Credits

Beatrice Bussolino
Andrea Calabrese
