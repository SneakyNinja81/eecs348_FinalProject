# User Manual
## Introduction
This reposotority contain the c++ code for a boolean algebra calcualtor. 
The calcualtor takes as input boolean algebra expressions and outputs the expressions truth value table.


To install run `git clone https://github.com/SneakyNinja81/eecs348_FinalProject.git` in the terminal.
Then compile the code with `g++ Project.cpp -o Project.exe` on Linux or Windows and `g++ Project.cpp -std=c++11 -o Projec.exe` on Mac.
Finally you can run the program with `./Project.exe`

## Getting Started
Enter an expression using T to represent True, F to represent False, and the folowing symbols to represent logical operators

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


Remember to use parentheses to choose which parts of the expression to evalute first.

### Example Usage
`(T | F) $ F` will first evaluate True or False which is True and then take the result XOR with F which is True. So the calculator will return True
