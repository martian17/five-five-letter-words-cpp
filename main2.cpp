#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
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

//pretend this is C for a moment
vector<int> search(vector<int> &searchSpace/*, int max_depth*//*=5*/){
    //mindful of 8mb stack size
    int buff[10000];
    vector<int> results;
    //first copy searchSpace to buff to ensure memory locality
    for(int i = 0; i < searchSpace.size(); i++){
        buff[i] = searchSpace[i];
    }
    int* buffstarts[6];
    int* buffptr[5];
    buffstarts[0] = buff;
    buffstarts[1] = buff+searchSpace.size();
    buffptr[0] = buff;
    int depth = 0;
    while(true){
        //fprintf(stderr,"depth: %d\n",depth);
        if(depth == 4){
            //found result
            for(int* it = buffstarts[4]; it < buffstarts[5]; it++){
                //push back to results
                //fprintf(stderr,"found!\n");
                for(int i = 0; i < 4; i++){
                    results.push_back(*buffptr[i]);
                }
                //push back fifth element
                results.push_back(*it);
            }
            depth = 3;
            buffptr[3]++;
        }

        if(buffptr[depth] == buffstarts[depth+1]){
            if(depth == 0){
                //everything done!
                break;
            }
            buffptr[depth] = buffstarts[depth];
            buffptr[depth-1]++;
            depth--;
            continue;
        }

        int w1 = *buffptr[depth];
        int* buff2ptr = buffstarts[depth+1];
        for(int* it = buffptr[depth]+1; it < buffstarts[depth+1]; it++){
            int w2 = *it;
            if(!(w2 & w1)){
                *buff2ptr = w2;
                buff2ptr++;
            }
        }
        buffptr[depth+1] = buffstarts[depth+1];
        buffstarts[depth+2] = buff2ptr;
        depth++;
    }
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

    vector<int> result = search(numlist);
    cerr << "result size: " << result.size()/5 << endl;
}






