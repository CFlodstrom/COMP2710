/*
 * Chris Flodstrom
 * Czf0038
 * Project 3
 * 17 Oct 2019
 *
 * Compile with g++
 *
 * Description:  a program that merges the numbers in two files and writes all the numbers into a
 * third file. Your program takes input from two different files and writes its output to a
 * third file.
 *
 * I used assistance from Sam (cant remember last name) in regards to implementing vectors and used the hand
 * out to format my program.
 * I also used StackOverflow for assistance with vectors
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;


bool check_file(string);
vector<int> read_file(string);
void write_file(string, vector<int>);
vector<int> merge(vector<int>, vector<int>);
void to_string(string, vector<int>);


int main() {
ifstream istream;
int data;
int cnt = 0;
vector<int> numb1;
vector<int> numb2;
vector<int> numb3;
string fileName1;
string fileName2;
string fileName3;

    do {
        cout << "*** Welcome to Chris's sorting program ***" << endl ;
        cout << "Enter the first input file name: ";
        cin >> fileName1;
        if (!check_file(fileName1)) {
            cout << "File does not exist" << endl;
            }
        } while (cin.fail() || !check_file(fileName1));
    
   
    numb1 = read_file(fileName1);
   for (int i = 0; i < numb1.size(); i++)
        cnt++;
       cout << "The list of " << cnt << " numbers in file " << fileName1 << " is:" << endl;
       cnt = 0;
   for (int i = 0; i < numb1.size(); i++)
       cout << numb1[i] << endl;
    
    do {
        cout << "\nEnter the second input file name: ";
        cin >> fileName2;
        
        if (!check_file(fileName2)) {
        cout << "File does not exist" << endl;
            }
        } while (cin.fail() || !check_file(fileName2));
    
    

    numb2 = read_file(fileName2);
    for (int i = 0; i < numb2.size(); i++)
        cnt++;
    cout << "The list of " << cnt << " numbers in file " << fileName2 << " is:" << endl;
    cnt = 0;
    for (int i = 0; i < numb2.size(); i++)
    cout << numb2[i] << endl;
   
    
    numb3 = merge(numb1, numb2);
    for (int i = 0; i < numb3.size(); i++)
      cnt++;
    cout << "\nThe sorted list of " << cnt << " numbers is: ";
    cnt = 0;
    for (int i = 0; i < numb3.size(); i++)
      cout << numb3[i] << " ";
      cout << endl;
    
   
    do {
        cout << "Enter the output file name: ";
        cin >> fileName3;
    } while (cin.fail());
    

    write_file(fileName3, numb3);
    
    
   cout << "*** Please check the new file - " << fileName3 << " ***" << endl;
   cout << "*** Goodbye. ***" << endl;
    return 0;
}

bool check_file(string file){

    ifstream strm;

    strm.open(file.c_str());
    if (strm.fail()) {
       return false;
    }
    strm.close();
    return true;
}


vector<int> read_file(string file) {
    ifstream strm;
    vector<int> vec;
    int i;
   strm.open((char*)file.c_str());

   
   if (strm.fail()) {
      cout << "input file opening failed." << endl;
      exit(1);
   }
    
   strm >> i;
    while (strm.good()) {
       vec.push_back(i);
      strm >> i;
    }
    strm.close();
   
    return vec;
}


void write_file(string file, vector<int> vec) {
    ofstream output;
   output.open((char*)file.c_str());
   
   
   for (int i = 0; i < vec.size(); i++) {
      output << vec[i] << endl;
   }
   output.close();
}



vector<int> merge(vector<int> vec1, vector<int> vec2) {
vector<int> mvec;
    
   
//for loops merging vectors
   for (int i = 0; i < vec1.size(); i++) {
      mvec.push_back(vec1[i]);
   }
   for (int i = 0; i < vec2.size(); i++) {
      mvec.push_back(vec2[i]);
   }
   sort(mvec.begin(), mvec.end());
    return mvec;
}

void to_string(string file, vector<int> vec) {
   cout << "The contents of the file " << file << "are: ";
    for (int x = 0; x < vec.size(); x++) {
      cout << vec[x] << " " << endl;
   }
}
