COMPILE:
Compile program1.cpp by either running make, make program1, or you can use:
  	g++ -c program1.cpp
  	g++ -g program1.o -o program1

RUN:
Run program1 by using the following command:
  ./program1 <filex.txt> <filey.txt> <output.txt>
Where <filex.txt> is the first file to read, <filey.txt> the second file to
read, and <output.txt> as the output file.

COMPUTATION TIME:
The time the bottom up version of Longest Common Subsequence tends to be shorter
than both recursion techniques. This is because the values are always available
in constant time access due to the matrix (no recursion).

CLASSES:
Chroma class to time the algorithm.
FStream to read in and write out to files.
IOStream to print error message and debug.
String to read in file easier.
cstdlib for basic c functions.
