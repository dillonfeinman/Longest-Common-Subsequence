#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <chrono>

using namespace std;

//max takes in two ints, a and b, and returns the greater of the two by simple >= comparison
//a and b are assumed to be integers.
int max(int a, int b){
  if(a >= b){
    return a; //a is bigger
  }
  else {
    return b; //b is bigger
  }
}

//recLCS takes in the two strings to compare, linex and liney, and the lengths of those strings,
//m and n, respectively. It finds the length of longest common subsequnce recursively.
int recLCS(string linex, string liney, int m, int n){
  if(m==0 || n==0){ //base case, end of string
    return 0; //not a match
  } else if(linex[m-1] == liney[n-1]){ //chars match
    return 1 + recLCS(linex, liney, m-1, n-1); //add 1 and recurse with the previous char
  } else { //chars dont match
    return max(recLCS(linex, liney, m-1, n), recLCS(linex, liney, m, n-1)); //take the larger after recursing
  }                                                                         //with (m-1,n) and (m,n-1)
}                                                                           //(linex[m-2], liney[n-2])

int main(int argc, char * argv[]){ //main requires 3 args (other than ./program) inlcuding 2 input file names and
  fstream file;                    //the output file name.
  if(argc != 4){
    cerr << "Need 3 args! <filex.txt>, <filey.txt>, <output.txt>" << endl; //if not 3 args, exit.
    exit(1);
  }
  string filex = argv[1]; //first input file name
  string filey = argv[2]; //second input file name
  string out = argv[3]; //output file name
  file.open(filex); //getting ready to read filex
  string linex; //chars from filex
  if(file.is_open()){
    getline(file, linex); //linex = input from filex
  } else {
    cerr << "Could not open file: " << filex << "." << endl;
    cerr << "Exiting." <<endl;
    exit(1);
  }
  int m = linex.length(); //m = length of string from filex
  file.close();
  file.open(filey);
  string liney; //chars from filey
  if(file.is_open()){
    getline(file, liney);//liney = input from filey
  } else {
    cerr << "Could not open file: " << filey << "." << endl;
    cerr << "Exiting." <<endl;
    exit(1);
  }
  int n = liney.length(); //n = length of string from filey
  file.close();
  auto start = chrono::high_resolution_clock::now(); //record start time
  int lcs_len = recLCS(linex, liney, m, n); //length of longest common subsequnce by calling recLCS with the
                                            //strings and length of strings
  auto end = chrono::high_resolution_clock::now(); //record end time
  auto time = chrono::duration_cast<chrono::microseconds>(end-start); //get time of algorithm in microseconds
  ofstream outfile; //ofstream to write to file
  outfile.open(out); //open out, name of output file
  if(outfile.is_open()){
    outfile << lcs_len << endl; //write length to outfile
    outfile << time.count() << " microseconds."; //write elapsed time
  } else {
    cerr << "Could not write to file: " << out << "." << endl;
    cerr << "Exiting." <<endl;
    exit(1);
  }
  outfile.close(); //close file
}
