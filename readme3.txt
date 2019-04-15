COMPILE:
Compile program3.cpp by either running make, make program3, or you can use:
  	g++ -c program3.cpp
  	g++ -g program3.o -o program3

RUN:
Run program3 by using the following command:
  ./program3 <filex.txt> <filey.txt> <output.txt>
Where <filex.txt> is the first file to read, <filey.txt> the second file to
read, and <output.txt> as the output file.

COMPUTATION TIME:
The time the top down (recursive with memoization) version of Longest Common
Subsequence takes a shorter amount of time versus only recursion. This is faster
than program2 because you are filling the matrix in order to achieve constant
time access rather than only recursing for the result. 

CLASSES:
Chroma class to time the algorithm.
FStream to read in and write out to files.
IOStream to print error message and debug.
String to read in file easier.
cstdlib for basic c functions.
