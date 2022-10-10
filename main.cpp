#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include "crypt.h"
using namespace std;

class CrFile{
private:
    vector<char> bytes;
public:
    CrFile(string name="foo",string path=""){
        ifstream input(name, std::ios::binary);

        bytes=vector<char>(
                (istreambuf_iterator<char>(input)),
                (istreambuf_iterator<char>()));

        input.close();

    }
    CrFile(vector<char> in){
        bytes=std::move(in);
    }
    void show(){
        for(auto &i:bytes){
            cout<<i;
        }
    }
    vector<char>getVector(){
        return bytes;
    }
    int outToFile(string name="foo"){
        ofstream outputFile(name);
        ostream_iterator<char>outputIter(outputFile,"");
        copy(bytes.begin(),bytes.end(),outputIter);
    }

};
lli genPrime(lli min=4,lli max=100){
    lli temp=4;
    while(!checkSimple(temp)){
        temp= random(min,max);
    }
    return temp;
}

int main(){
    lli Ca=0,Da=0,p;
    lli Cb=0,Db=0;
    lli min=pow(10,7);
    lli max=pow(10,10);
    p=genPrime(min,max);
    cout<<p;
    while((Ca*Da)%(p-1)!=1){
        Ca= random(min,max);
        Da=random(min,max);
    }
    while((Cb*Db)%(p-1)!=1){
        Cb= random(min,max);
        Db=random(min,max);
    }
    cout<<"\n"<<Ca<<"\n"<<Da<<"\n"<<(Ca*Da)%(p-1);
    cout<<"\n"<<Cb<<"\n"<<Db<<"\n"<<(Cb*Db)%(p-1);
    CrFile srcFile("test.jpg");

//    for(auto &i:srcFile.getVector()){
//        i= modPow(i,Ca,p);
//    }
    srcFile.outToFile("test1.jpg");
    return 0;
}