You will have an orthogonal triangle input from a file and you need to find the maximum sum of the numbers according to given rules below;

1. You will start from the top and move downwards to an adjacent number as in below.
2. You are only allowed to walk downwards and diagonally.
3. You can only walk over NON PRIME NUMBERS.
4. You have to reach at the end of the pyramid as much as possible.
5. You have to treat the input as pyramid.

According to above rules the maximum sum of the numbers from top to bottom in below example is 24.

      *1
     *8 4
    2 *6 9
    8 *5 9 3


As you can see this has several paths that fits the rule of NOT PRIME NUMBERS; 1>8>6>9, 1>4>6>9, 1>4>9>9
1 + 8 + 6 + 9 = 24.  As you see 1, 8, 6, 9 are all NOT PRIME NUMBERS and walking over these yields the maximum sum.






How to work: <br />
Compile the core and run it. <br />
the first input that you write # of line that you give. <br /> 
the i'th line take i element of integer. <br />
After giving inputs, max vlue is calculaten and printed. <br />
g++ -o fun fun.cpp <br />
./fun <br />
4 <br />
1 <br />
8 4 <br />
2 6 9 <br />
8 5 9 3 <br />



or  <br />

./fun < inp.txt > out.txt <br />
