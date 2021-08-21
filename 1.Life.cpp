// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!
/*
*The simulation starts with an initial pattern of cells on the grid and computes successive generations of cells according to the following rules:
A location that has zero or one neighbors will be empty in the next generation. If a cell was there, it dies.
A location with two neighbors is stable. If it had a cell, it still contains a cell. If it was empty, it's still empty.
A location with three neighbors will contain a cell in the next generation. If it was unoccupied before, a new cell is born. If it currently contains a cell, the cell remains.
A location with four or more neighbors will be empty in the next generation. If there was a cell in that location, it dies of overcrowding.
*/

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
using namespace std;

string getFileName();

Grid<char> readFile(int& row,int& col,string& fileName);

void updateGrid(class Grid<char>&);

Grid<char> tUpdate(class Grid<char>&);

int checkNeighbour(class Grid<char>&,int i,int j);

int main() {
    // TODO: Finish the program!
    cout << "Welcome to Game Of Life" << endl;
    cout << "Please input your filename!" << endl;

    string fileName = getFileName();

    int row; int col; Grid<char> g;
    g = readFile(row,col,fileName);

    updateGrid(g);

    return 0;
}

string getFileName(){
    string fileName;
    cin >> fileName;
    while(!fileExists(fileName)){
        cout << "Please input your filename again!" << endl;
        cin >> fileName;
    }
    cout << "The fileName is:" << fileName << "And the getFileName is completed!" << endl;
    return fileName;
}

Grid<char> readFile(int& row,int& col,string& fileName){
    ifstream input;
    openFile(input,fileName);
    string line;
    //read row,col
    getline(input,line);
    row = stringToInteger(line);
    getline(input,line);
    col = stringToInteger(line);

    Grid<char> g(row+2,col+2);
    for(int i =1;i < row+1;i++){
        getline(input,line);
        for(int j=1;j<col+1;j++){
            g[i][j] = line.at(j-1);
        }
    }
    input.close();
    for(int i=0;i<row+2;i++){
        for(int j=0;j<col+2;j++){
            cout << g[i][j];
        }
        cout << endl;
    }
    cout << "read successful!" <<endl;
    return g;
}

void updateGrid(class Grid<char>& g){
    char key;
    while(true){
        cout << "a)nimate, t)ick, q)uit? ";
        cin >> key;
        if(key == 'a'){
            int frame = 0;
            cout << "How many frames? ";
            cin >> frame;
            for(int i=0;i<frame;i++){
                g = tUpdate(g);
                pause(300);
            }
        }else if(key == 't'){
            g = tUpdate(g);
        }else if(key == 'q'){
            break;
        }
    }
}

Grid<char> tUpdate(class Grid<char>& g){
    Grid<char> newG = g;
    for(int i=1;i<g.nRows-1;i++){
        for(int j=1;j<g.nCols-1;j++){
            int neighbour = 0;
            neighbour = checkNeighbour(g,i-1,j-1) + checkNeighbour(g,i-1,j) + checkNeighbour(g,i-1,j+1)
                    + checkNeighbour(g,i,j-1) + checkNeighbour(g,i,j+1)
                    + checkNeighbour(g,i+1,j-1) + checkNeighbour(g,i+1,j) + checkNeighbour(g,i+1,j+1);
            switch (neighbour) {
            case 0:
                newG[i][j] = '-';
                break;
            case 1:
                newG[i][j] = '-';
                break;
            case 2:
                newG[i][j] = '-'?'-':'X';
            case 3:
                newG[i][j] = 'X';
                break;
            default:
                newG[i][j] = '-';
            }

        }
    }
    for(int i=1;i<newG.nRows-1;i++){
        for(int j=1;j<newG.nCols-1;j++){
            cout << newG[i][j];
        }
        cout << endl;
    }
    cout << endl;
    return newG;
}

int checkNeighbour(class Grid<char>& g,int i,int j){
    if(g[i][j] == 'X') return 1;
    else return 0;
}
