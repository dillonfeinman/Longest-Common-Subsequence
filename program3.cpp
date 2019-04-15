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
//This function takes in two strings, linex and liney, and their current indexes, m and n, along with
//The matrix int mat[m][n]
int lcsLen(string linex, string liney, int m, int n, int mat[][100]){
  if(linex[m]=='\0' || liney[n]=='\0'){ //base case, end of string
    return 0;
  } else if(mat[m][n] != -1){ //if the value is already set, return it
    return mat[m][n];
  } else if(linex[m] == liney[n]){//if the characters are the same
    mat[m][n] = 1 + lcsLen(linex, liney, m+1, n+1, mat);//set the value of the matrix by recursing with m-1 and n-1
    return mat[m][n]; //return value
  } else { //characters are different
    mat[m][n] = max(lcsLen(linex, liney, m+1, n, mat), lcsLen(linex, liney, m, n+1, mat));//set value of matrix with the max of the value to the right and the value below
    return mat[m][n]; //return that value
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
  }
  int m = linex.length(); //m = length of string from filex
  file.open(filey);
  string liney; //chars from filey
  if(file.is_open()){
    getline(file, liney);//liney = input from filey
    file.close();
  }
  int n = liney.length(); //n = length of string from filey
  auto start = chrono::high_resolution_clock::now(); //record start time
  int mat[m][100]; //create matrix with the max number of possible characters
  for(int i = 0; i < m; i++){
    for(int j = 0; j < 100; j++){
      mat[i][j] = -1; //initalize all of matrix to -1
    }
  }
  int lcs_len = lcsLen(linex, liney, 0, 0, mat); //get length of lcs by calling with strings, then 0's to serve as a starting point, and the matrix
  auto end = chrono::high_resolution_clock::now(); //record end time
  auto time = chrono::duration_cast<chrono::microseconds>(end-start); //find time of algorithm
  ofstream outfile; //create output stream
  outfile.open(out); //open output file
  if(outfile.is_open()){
    outfile << lcs_len << endl; //write length of lcs
    outfile << time.count() << " microseconds."; //write elapsed time
    outfile.close();
  }
}
