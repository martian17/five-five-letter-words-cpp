#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int toNumbers(string word){
    int n = 0;
    for(char &c: word){
        int v = 1<<((int)c-97);
        //contains duplicate letters
        if(v & n)return -1;
        n |= v;
    }
    return n;
}


//vector<string> fives;
map<int,vector<string>> nummap;
vector<int> numlist;

vector<vector<int>> search(vector<int> currentSet, int n){
    //cerr << n << " " << currentSet.size() << endl;
    vector<vector<int>> results;
    if(n == 1){
        for(int &w: currentSet)
            results.push_back(vector<int>{w});
        return results;
    }
    int cnt = 0;
    for(int i = 0; i < ((int)currentSet.size())-1; i++){
        //if(n == 2)cerr << "wtf " << i << " " << currentSet.size()-1 << endl;
        cnt++;
        int w1 = currentSet[i];
        vector<int> newSet;
        for(int j = i+1; j < currentSet.size(); j++){
            int w2 = currentSet[j];
            //bitwise if no overlap
            if(!(w2 & w1))newSet.push_back(w2);
        }
        vector<vector<int>> r = search(newSet,n-1);
        for(vector<int> &set: r){
            set.push_back(w1);
            results.push_back(set);
        }
        if(n == 5){
            cerr << ((float)(cnt*1000/nummap.size()))/10 << "% complete, searched subset: " << newSet.size() << endl;
        }
    }
    //cerr << "returning " << results.size() << endl;
    return results;
}


int main(){
    ifstream ifs;
    ifs.open ("words_alpha.txt", ifstream::in);

    while (ifs.good()) {
        string word;
        ifs >> word;
        if(word.size() != 5){
            continue;
        }
        int n = toNumbers(word);
        if(n == -1){
            //has duplicate letters
            continue;
        }
        //nummap and numlist
        if(nummap.find(n) == nummap.end()){
            nummap[n] = vector<string>{};
            numlist.push_back(n);
        }
        nummap[n].push_back(word);
        //string push back
        //fives.push_bacl(word);
    }
    cerr << "input size: " <<  numlist.size() << endl;

    vector<vector<int>> result = search(numlist,5);
    cerr << "result size: " << result.size() << endl;
}






