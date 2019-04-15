#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <chrono>

using namespace std;


//made this function solely to test runtime. I do not return the matrix
//This function finds length of LCS in bottom up fashion
int lenLCS(string linex, string liney, int m, int n){
  int lcs[m+1][n+1]; //matrix of size m+1,n+1. Needs to hold extra row of 0's in both dimensions
  for(int i = 0; i < m+1; i++){ //row
    for(int j = 0; j < n+1; j++){//column
      if(i == 0 || j == 0){
        lcs[i][j] = 0; //initalize lcs[][]
      } else if (linex[i-1] == liney[j-1]){
        lcs[i][j] = lcs[i-1][j-1] + 1; //if chars are the same, add 1 to lcs[i-1][j-1]
      } else {
        lcs[i][j] = max(lcs[i-1][j],lcs[i][j-1]); //if chars not same, pick the max of the row above or column to the left.
      }
    }
  }
  return lcs[m][n];
}

//printLCS takes in two strings, linex and liney, two ints, m (length of linex) and n (length of liney)
//also takes in string out, which is the name of the output file.
//It computes the longest common subsequnce in bottom up fashion
void printLCS(string linex, string liney, int m, int n, string out){
  ofstream outfile; //outfile is file to write to
  outfile.open(out);
  if(outfile.is_open()){
    //find length of longest common subsequnce and time it
    auto start = chrono::high_resolution_clock::now(); //record start time
    int lcs_len = lenLCS(linex, liney, m, n);
    auto end = chrono::high_resolution_clock::now(); //record end time
    auto time = chrono::duration_cast<chrono::microseconds>(end-start); //total amount of time taken in microseconds
    //recreate matrix in order to find a lcs
    int lcs[m+1][n+1]; //matrix of size m+1,n+1. Needs to hold extra row of 0's in both dimensions
    for(int i = 0; i < m+1; i++){ //row
      for(int j = 0; j < n+1; j++){//column
        if(i == 0 || j == 0){
          lcs[i][j] = 0; //initalize lcs[][]
        } else if (linex[i-1] == liney[j-1]){
          lcs[i][j] = lcs[i-1][j-1] + 1; //if chars are the same, add 1 to lcs[i-1][j-1]
        } else {
          lcs[i][j] = max(lcs[i-1][j],lcs[i][j-1]); //if chars not same, pick the max of the row above or column to the left.
        }
        outfile << lcs[i][j]; //write val to file
      }
      outfile << endl; //end line of file
    }
    lcs_len = lcs[m][n]; //length of LCS
    int index = lcs_len; //want to start at back of string first
    int i = m; //i = len(linex)
    int j = n; //j = len(liney)
    char lcs_str[lcs_len+1]; //char array of the least common subsequnce of size lcs_len + 1 for \0
    lcs_str[lcs_len] = '\0'; //set null byte
    //find a lcs by starting at end of string and lcs[m][n] (bottom up)
    while(i > 0 && j > 0){ //while lcs is not at the 0 row/column
      if(linex[i-1] == liney[j-1]){ //if chars are equal
        lcs_str[index-1] = linex[i-1]; //go diagnoal up (subtract 1 from i and j)
        i--;
        j--;
        index--; //next character is in front of previous
      } else if(lcs[i-1][j] >= lcs[i][j-1]){ //if max(lcs[i-1][j],lcs[i][j-1]) == lcs[i-1][j], i--
        i--;
      } else { // if max(lcs[i-1][j],lcs[i][j-1]) == lcs[i][j-1], j--
        j--;
      }
    }
    for(int k = 0; k < lcs_len+1; k++){ //write lcs_str to file
      outfile << lcs_str[k];
    }
    outfile << endl;
    outfile << time.count() << " microseconds."; //write elapsed time
    outfile.close();
  }else {
    cerr << "Could not write to file: " << out << "." << endl;
    cerr << "Exiting." <<endl;
    exit(1);
  }
}

//printLCSOver takes in two strings, linex and liney, two ints, m (length of linex) and n (length of liney)
//also takes in string out, which is the name of the output file
void printLCSOver(string linex, string liney, int m, int n, string out){
  ofstream outfile; //outfile is file to write to
  outfile.open(out);
  if(outfile.is_open()){
    auto start = chrono::high_resolution_clock::now(); //record start time
    int lcs_len = lenLCS(linex, liney, m, n);
    auto end = chrono::high_resolution_clock::now(); //record end time
    auto time = chrono::duration_cast<chrono::microseconds>(end-start); //total amount of time taken in microseconds
    outfile << lcs_len << endl;
    outfile << time.count() << " microseconds."; //write elapsed time
    outfile.close();
  }
  else {
    cerr << "Could not write to file: " << out << "." << endl;
    cerr << "Exiting." <<endl;
    exit(1);
  }
}

//max takes in two ints, a and b, and returns the greater of the two by simple >= comparison
//a and b are assumed to be integers.
int max(int a, int b){
  if(a >= b){
    return a; // a is bigger
  }
  else {
    return b; //b is bigger
  }
}

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
    file.close();
  } else {
    cerr << "Could not open file: " << filex << "." << endl;
    cerr << "Exiting." <<endl;
    exit(1);
  }
  int m = linex.length(); //m = length of string from filex
  file.open(filey);
  string liney; //chars from filey
  if(file.is_open()){
    getline(file, liney);//liney = input from filey
    file.close();
  } else {
    cerr << "Could not open file: " << filey << "." << endl;
    cerr << "Exiting." <<endl;
    exit(1);
  }
  int n = liney.length(); //n = length of string from filey
  if(m <= 10 && n <= 10){
    printLCS(linex, liney, m, n, out); //if length of strings are <= 10, print LCS matrix
  }
  else {
    printLCSOver(linex, liney, m, n, out); // else print only length
  }
}
