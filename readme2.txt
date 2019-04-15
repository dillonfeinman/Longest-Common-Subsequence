COMPILE:
Compile program2.cpp by either running make, make program2, or you can use:
  	g++ -c program2.cpp
  	g++ -g program2.o -o program2

RUN:
Run program2 by using the following command:
  ./program2 <filex.txt> <filey.txt> <output.txt>
Where <filex.txt> is the first file to read, <filey.txt> the second file to
read, and <output.txt> as the output file.

COMPUTATION TIME:
The time the recursive (without memoization) version of Longest Common Subsequence
takes longer than program1 and program3. This is due to the fact that there is no
constant time access like there is with the use of the matrix.

CLASSES:
Chroma class to time the algorithm.
FStream to read in and write out to files.
IOStream to print error message and debug.
String to read in file easier.
cstdlib for basic c functions.
