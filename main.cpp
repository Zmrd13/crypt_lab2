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
    vector<lli> bytes;
public:
    CrFile(string name="foo",string path=""){
        ifstream input(name, std::ios::binary);

        bytes=vector<lli>(
                (istreambuf_iterator<char>(input)),
                (istreambuf_iterator<char>()));

        input.close();

    }
    CrFile(vector<lli> in){
        bytes=std::move(in);
    }
    void show(){
        for(auto &i:bytes){
            cout<<i;
        }
    }
    vector<lli>getVector(){
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
vector<lli> shamCypher(vector<lli>file,lli pow,lli p){
    vector<lli> temp=file;
    for(auto &i:temp){
        i=modPow(i,pow,p);
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
    CrFile srcFile("test.txt");
vector<lli> temp= shamCypher(srcFile.getVector(),Ca,p);
//    for(auto &i:temp){
//        i= modPow(i,Ca,p);
//    }
    srcFile.outToFile("test1.txt");
    CrFile srcFile1(temp);
    srcFile1.outToFile("test2.txt");
    temp= shamCypher(srcFile1.getVector(),Cb,p);
//    for(auto &i:temp){
//        i= modPow(i,Cb,p);
//    }
    CrFile srcFile2(temp);
    srcFile2.outToFile("test3.txt");
    temp= shamCypher(srcFile2.getVector(),Da,p);
//    for(auto &i:temp){
//        i= modPow(i,Da,p);
//    }
    CrFile srcFile3(temp);
    srcFile3.outToFile("test4.txt");
    temp= shamCypher(srcFile3.getVector(),Db,p);
//    for(auto &i:temp){
//        i= modPow(i,Db,p);
//    }
    CrFile srcFile4(temp);
    srcFile4.outToFile("test5.txt");
    return 0;
}