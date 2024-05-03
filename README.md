# User Manual
## Introduction
This repository contain the C++ code for a Boolean algebra calcualtor. 
The calculator takes an input Boolean algebra expression and outputs the expression's truth value.


To install, run `git clone https://github.com/SneakyNinja81/eecs348_FinalProject.git` in the terminal.
Then, compile the code with `g++ Project.cpp -o Project.exe` on Linux or Windows and `g++ Project.cpp -std=c++11 -o Projec.exe` on Mac.
Finally, run the program with `./Project.exe`

## Getting Started
Enter a logical expression using T to represent True, F to represent False, and the following symbols as logical operators.

<table>
   <thead>
      <tr>
         <th>Symbol</th>
         <th>Logical Operation</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>&</td>
         <td>AND</td>
      </tr>
      <tr>
         <td>|</td>
         <td>OR</td>
      </tr>
      <tr>
         <td>!</td>
         <td>NOT</td>
      </tr>
      <tr>
         <td>@</td>
         <td>NAND</td>
      </tr>
      <tr>
         <td>$</td>
         <td>XOR</td>
   </tbody>
</table>


This calculator is programmed to handle parentheses/nested expressions.

### Example Usage
`(T | F) $ F` First, the value of the expression in parentheses is determined to be True. Next, this value is compared to the next Boolean 
in the input using the XOR operator, which evaluates as True. The whole statement has been processed, so the calculator returns True.
