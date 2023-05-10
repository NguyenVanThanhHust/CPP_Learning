Problem 1:
Calculate sum of all natural numbers that are divisible by 3 or 5 and not bigger than an input from user.

Solution:    
Naive: loop from 1 to input, check if that is divisible by 3 or 5 then sum.   
More optimized:
Count number of numbers that are divisible by 3, give us $$n_{3} = math.ceil({(user input - 3) \over 3}) + 1$$ 

Count number of numbers that are divisible by 5, give us $$n_{5} = math.ceil({(user input - 5) \over 5}) + 1$$

Count number of numbers that are divisible by 15, give us $$n_{15} = math.ceil({(user input - 15) \over 15}) + 1$$

Final sum: $$S = S_3*3 + S_5*5 - S_{15}*15$$

Problem 2:
Find the greatest common divisor of two inputs

Solution: 
Naive:

More Optimized:

Problem 3: Find the least common multiple of given positive integers.

Solution:
