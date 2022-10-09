#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
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
        bytes=in;
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

int main(){
    CrFile temp("test.png");
    vector<char> t=temp.getVector();
    for(auto &i:t){
        i+=2;
    }

    CrFile out(t);

    out.outToFile("test1.png");
    vector<char> t1=out.getVector();
    for(auto &i: t1){
        i-=2;
    }

    CrFile outq(t1);

    outq.outToFile("test2.png");
    return 0;
}