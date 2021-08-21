// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header


/*
* BFS寻找最短路径
* 因为每次只变一个<a1,a2,a3,a4....an> 为字母相同个数一样的序列
* 所以先后顺序没有关系，因为当前都有相同字母相同
* 假设n个相等，最少也需要l-n次
* 所以找到时就为最短路径
*/
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "hashset.h"
#include "stack.h"
#include "queue.h"
using namespace std;

string getFileName();

void process(class HashSet<string>& dic,string filename,string w1,string w2,class stack<string>&);

bool done = false;

int main() {
    // TODO: Finish the program!

    string filename;
    filename = getFileName();

    HashSet<string> dictionary;                //放置所有的词语
    string word1,word2;
    cout << "Word #1 (or Enter to quit):" ;
    cin >> word1;
    cout << "Word #2 (or Enter to quit):" ;
    cin >> word2;

    ifstream input;
    openFile(input,filename);
    string word;
    while(input >> word){
        dictionary.add(word);
    }

    stack<string> ans;
    ans.push(word1);
    process(dictionary,filename,word1,word2,ans);

    cout << "Have a nice day." << endl;
    return 0;
}

string getFileName(){
    ifstream input;
    string name;
    cout << "Dictionary file name?";
    cin >> name;
    while (!fileExists(name)) {
        cout << "Please enter a vaild file name:";
        cin >> name;
    }
    return name;
}

void process(class HashSet<string>& dic,string filename,string w1,string w2,class stack<string>& stack){
    if(w1.length() != w2.length()) {
        cout << "No rout exists." << endl;
        return;
    }

    if(w1 == w2 && !done){
        cout << endl;
        string out = stack.top();
        stack.pop();
        cout << out;
        while(!stack.empty()){
            string out = stack.top();
            stack.pop();
            cout <<"<---"<<out;
        }
        cout << endl;
        done = true;
        return;
    }


    queue<string> q;
    string w3 = w1;
    for(int i=0;i<w2.length();i++){
        if(w1.at(i) != w2.at(i)){
            w3 = w1;
            w3.at(i) = w2.at(i);
            q.push(w3);
        }
    }

    while (!q.empty()) {
        string w = q.front();
        q.pop();
        if(dic.contains(w)){
            stack.push(w);
            process(dic,filename,w,w2,stack);
        }
    }

    return;
}









