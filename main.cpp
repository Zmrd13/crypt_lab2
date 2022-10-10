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
        ofstream outputFile(name,ios::binary | ios::out);
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
    lli min=pow(10,1);
    lli max=pow(10,7);
    p=genPrime(min,max);
    cout<<p;
    while((Ca*Da)%(p-1)!=1){
        Ca= random(min,max)%(p-1);
        Da=random(min,max)%(p-1);
    }
    while((Cb*Db)%(p-1)!=1){
        Cb= random(min,max)%(p-1);
        Db=random(min,max)%(p-1);
    }
    cout<<"\n"<<Ca<<"\n"<<Da<<"\n"<<(Ca*Da)%(p-1);
    cout<<"\n"<<Cb<<"\n"<<Db<<"\n"<<(Cb*Db)%(p-1);
    cout<<endl;
    CrFile tempFile;
    tempFile=CrFile("test.jpg");
    tempFile.outToFile("test1.jpg");
    tempFile=CrFile(shamCypher(tempFile.getVector(),Ca,p));
    tempFile.outToFile("test2.jpg");
    tempFile=CrFile(shamCypher(tempFile.getVector(),Cb,p));
    tempFile.outToFile("test3.jpg");
    tempFile=CrFile(shamCypher(tempFile.getVector(),Da,p));
    tempFile.outToFile("test4.jpg");
    tempFile=CrFile(shamCypher(tempFile.getVector(),Db,p));
    tempFile.outToFile("test5.jpg");
//     CrFile srcFile("test.jpg");
// vector<lli> temp= shamCypher(srcFile.getVector(),Ca,p);
// //    for(auto &i:temp){
// //        i= modPow(i,Ca,p);
// //    }
//     srcFile.outToFile("test1.jpg");
//     CrFile srcFile1(temp);
//     srcFile1.outToFile("test2.jpg");
//     temp= shamCypher(srcFile1.getVector(),Cb,p);
// //    for(auto &i:temp){
// //        i= modPow(i,Cb,p);
// //    }
//     CrFile srcFile2(temp);
//     srcFile2.outToFile("test3.jpg");
//     temp= shamCypher(srcFile2.getVector(),Da,p);
// //    for(auto &i:temp){
// //        i= modPow(i,Da,p);
// //    }
//     CrFile srcFile3(temp);
//     srcFile3.outToFile("test4.jpg");
//     temp= shamCypher(srcFile3.getVector(),Db,p);
// //    for(auto &i:temp){
// //        i= modPow(i,Db,p);
// //    }
//     CrFile srcFile4(temp);
//     srcFile4.outToFile("test5.jpg");
    return 0;
}