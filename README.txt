*****INSTRUCTIONS*****

1. This simulator accepts these operators:
- AND
- OR
- NOT
- XOR
- NAND
- NOR

2. Expressions that you enter are limited to 3 operators.

3. Upon launching program you will be given 2 options:

a. Load previously saved expression (program loads prevously saved expression from truth_table.txt if there is none it asks again).

b. Enter new expression.

4. After you enter the expression (or load the old one) programm will produce truth table for the expression.

5. Once this is done you will be given 2 options:

a. Repeat the process

b. Save the table and repeat the process (table will be save in a truth_table.txt)

!!! I couldn't come up with a way to exit the program so it has to be done manually (through task manager or ctrl + c)

Truth table file contents:
- Saved expression
- Operators that have been used explanation
- Generated truth table

*****EXAMPLE USAGE*****

*** BOOLEAN TRUTH TABLE SIMULATOR ***
1) Load previously saved expression
2) Enter new expression
Choose option: 2
Enter Boolean expression (max 3 operators, variables A, B, C): A AND B XOR C

Expression: A AND B XOR C

Operators Detected and Explained:
- AND: Returns true only when both inputs are true. Example: 1 AND 1 = 1, 1 AND 0 = 0.
- XOR: Returns true when inputs are different. Example: 1 XOR 0 = 1, 1 XOR 1 = 0.

Generated Truth Table:
|   A |   B |   C | RESULT |
|-----|-----|-----|--------|
|   0 |   0 |   0 |      0 |
|   0 |   0 |   1 |      1 |
|   0 |   1 |   0 |      0 |
|   0 |   1 |   1 |      1 |
|   1 |   0 |   0 |      0 |
|   1 |   0 |   1 |      1 |
|   1 |   1 |   0 |      1 |
|   1 |   1 |   1 |      0 |

1) Repeat the process
2) Save the table and repeat the process (this will override the old one)
Choose option: 2
Saved to file "truth_table" successfully. Old saved table was overridden.

*****DESIGN DECISIONS*****

My program has one parent class called "BooleanOperator" which is used to define common functions and attributes for all operators.

Using inheritance based on "BooleanOperator" class I have made further classes:

- AndOperator

- OrOperator

- NotOperator

- XorOperator

- NandOperator

- NorOperator

Each operator class responsible for returning:
1. Its own name 
2. Its own precedence
3. Number of operands
4. Logic of evaluation
5. Explanation text

"BooleanExpression" class is responsible for:
1. Finding variables used
2. Finding operators used
3  Returning operator explanations

"TruthTable" class is responsible for:
1. Getting the variables used in expression
2. Generate all possible combinations of 0s and 1s
3. Evaluate for each combination

Initially I thought to include file management in "TruthTable" class but then I thought it would be more convinient to have
as a separate class.

"FileManager" is  responsible for:
1. Saving output produced by the program in "truth_table.txt" file.
2. Loading previously saved expression.

I chose to keep the truth table simple without adding any sub-expressions in the table 
as this makes truth table more comprehensible and readable for the user.

Also, I made it so old truth table is being overwritten by the new as I found this solution simpler to 
develop which saved me some of my time, which was important given that I have not had enough time since I had to do other
coursework and preapare for the exams.



