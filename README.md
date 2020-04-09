# push_swap  

This project is written in C.
## Project Description  

The project consists of 2 programs which names: push_swap and checker. 
### "Checker" program

This program takes integer arguments and reads instructions on
the standard output. Once read, checker executes them and displays OK if integers
are sorted. Otherwise, it will display KO.  
```
$>./checker 3 2 1 0
rra
pb
sa
rra
pa
OK

$>./checker 3 2 1 0
sa
rra
pb
KO

$>./checker 3 2 one 0
Error
```
### "Push_swap" program

This program calculates and displays on the standard
output the smallest progam using Push_swap instruction language that sorts integer arguments received.
There’s only a few moves you’re allowed to used to manipulate the stacks that we’re going to called “Operations”.
The main goal of this program is to sort Stack A in as few operations as possible.  
```
$>./push_swap 2 1 3 6 5 8
sa
pb
pb
pb
sa
pa
pa
pa

$>./push_swap 0 one 2 3
Error
```  

### How to use these two programs together?  
_Example:_  
`ARG="6 5 7"; ./push_swap $ARG | ./checker $ARG`  

### What's about visualization?  
You can use flag `-v` for a simple visualization of sort process  
_Example:_  
`ARG="6 5 7 1 -1 0"; ./push_swap $ARG | ./checker -v $ARG`



## Rules  
<ul>
  <li>The game is composed of 2 stacks named a and b</li>
  <li>To start with:</li>
    <ul>
      <li>a contains a random number of either positive or negative numbers without any duplicates</li>
      <li>b is empty</li>
   </ul>
  <li>The goal is to sort in ascending order numbers into stack a</li>
  <li>To do this you have few operations at your disposal</li>
</ul>  

|Operation | Instruction | Action |
|----------|:------------|:-------|
|  `sa`    | swap a      |  swap the first 2 elements at the top of stack a|
|  `sb`    | swap b      |  swap the first 2 elements at the top of stack b|
|  `ss`    | swap a + swap b | both `sa` and `sb` |
|  `pa`    | push a      | take the first element at the top of b and put it at the top of a |
|  `pb` | push b | take the first element at the top of a and put it at the top of b |
| `ra` | rotate a | shifts all elements of stack a from bottom to top |
| `rb` | rotate b | shifts all elements of stack b from bottom to top |
| `rr` | rotate a + rotate b | both `ra` and `rb` |
| `rra` | reverse rotate a | shifts all elements of stack a from top to bottom |
| `rrb` | reverse rotate b | shifts all elements of stack b from top to bottom |
| `rrr` | reverse rotate a + reverse rotate b | both `rra` and `rrb` |

