// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

/*
*HashMap<Vector<string>,Vector<string>> map
* randomKey(map)
* randomElements(map[key])
* vec.remove(0)
* vec.add(word)
*/

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "hashmap.h"
#include "filelib.h"
#include "vector.h"
#include "random.h"
using namespace std;

string getFileName(int&);

void generateMap(string fil,int N);

HashMap<Vector<string>,Vector<string>> process(string filename,int N);

void generatePoem(HashMap<Vector<string>,Vector<string>>& map,int N);

int main() {
    // TODO: Finish the program!

    int N;
    string fil = getFileName(N);

    HashMap<Vector<string>,Vector<string>> map = process(fil,N);

    generatePoem(map,N);

    cout << "Exiting." << endl;
    return 0;
}

string getFileName(int& N){
    string name;
    cout << "Input file name?";
    cin >> name;
    while(!fileExists(name)){
        cout << "Input file name?";
        cin >> name;
    }
    cout << "Value of N?";
    cin >> N;

    while(N < 2 || !cin || cin.peek()!='\n' ){
        cin.clear();
        cin.ignore(200,'\n');
        cout << "Invalid input. Try again." << endl;
        cout << "Value of N? ";
        cin >> N;
    }
    return name;
}

HashMap<Vector<string>,Vector<string>> process(string filename,int N){
    HashMap<Vector<string>,Vector<string>> map;
    Vector<string> vec;                            //used to save the n-1 prefix

    ifstream input;
    openFile(input,filename);
    string word;
    for(int i=0;i<N-1;i++){
        input >> word;
        vec.add(word);
    }   //前n-1个项已经收集完成


    while(input >> word){
        if(map.containsKey(vec)){
            map[vec].add(word);
        }else{
            Vector<string> newVec;
            newVec.add(word);
            map.put(vec,newVec);
        }
        vec.remove(0);
        vec.add(word);
    }//此时结尾为最后N个
    input.close();

    openFile(input,filename);
    for(int i=0;i<N-1;i++){
        input >> word;
        if(map.containsKey(vec)){
            map[vec].add(word);
        }else{
            Vector<string> newVec;
            newVec.add(word);
            map.put(vec,newVec);
        }
        vec.remove(0);
        vec.add(word);
    }

    /*for(Vector<string> key:map.keys()){
        cout << "Key:" << key << "value:" << map[key] << endl;
    }*/
    return map;
}

void generatePoem(HashMap<Vector<string>,Vector<string> >& map,int N){
    int total;
    cout << "# of random words to generate (0 to quit)?";
    cin >> total;
    while(total <= N || !cin || cin.peek()!='\n' ){
        cin.clear();
        cin.ignore(200,'\n');
        cout << "Invalid input. Try again." << endl;
        cout << "Value of total? ";
        cin >> total;
    }

    Vector<string> vec = randomKey(map);
    cout << "...";
    for(string w:vec){
        cout << w << " ";
    }
    for(int i=0;i<total-N;i++){
        string word = randomElement(map[vec]);
        cout << word << " ";
        vec.add(word);
        vec.remove(0);
    }
    cout << "..." << endl;
}
