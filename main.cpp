#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include "crypt.h"

using namespace std;

class CrFile {
private:
    vector<lli> bytes;
public:
    CrFile(string name = "foo", string path = "") {
        ifstream input(name, std::ios::binary);

        bytes = vector<lli>(
                (istreambuf_iterator<char>(input)),
                (istreambuf_iterator<char>()));

        input.close();

    }

    CrFile(vector<lli> in) {
        bytes = std::move(in);
    }

    void show() {
        for (auto &i: bytes) {
            cout << i;
        }
    }

    vector<lli> getVector() {
        return bytes;
    }

    int outToFile(string name = "foo") {
        ofstream outputFile(name, ios::binary | ios::out);
        ostream_iterator<char> outputIter(outputFile, "");
        copy(bytes.begin(), bytes.end(), outputIter);
    }


};

lli genPrime(lli min = 4, lli max = 100) {
    lli temp = 4;
    while (!checkSimple(temp)) {
        temp = random(min, max);

    }
    return temp;
}

vector<lli> shamCypher(vector<lli> file, lli pow, lli p) {
    vector<lli> temp = file;
    for (auto &i: temp) {
        i = modPow(i, pow, p);
    }
    return temp;
}

string fileNameSplit(string fN, int part = 0) {
    string temp = "";
    int check = 0;
    for (auto &i: fN) {
        switch (part) {
            case 0:
                if (i == '.') { check = 1; };
                if (!check) { temp += i; };
                break;
            case 1:
                if (i == '.') { check = 1; };
                if (check) { temp += i; };
                break;
            default:
                temp += i;
                break;
        }

    }
    return temp;
}

int shamRun(const string &fileName = "foo.txt") {
    string name, ext;
    int iter=0;
    name = fileNameSplit(fileName, 0);
    ext = fileNameSplit(fileName, 1);
    lli Ca = 0, Da = 0, p;
    lli Cb = 0, Db = 0;
    lli min = pow(10, 1);
    lli max = pow(10, 7);
    p = genPrime(min, max);
    cout << p;
    while ((Ca * Da) % (p - 1) != 1) {
        Ca = random(min, max) % (p - 1);
        Da = random(min, max) % (p - 1);
    }
    while ((Cb * Db) % (p - 1) != 1) {
        Cb = random(min, max) % (p - 1);
        Db = random(min, max) % (p - 1);
    }
    cout << "\n" << Ca << "\n" << Da << "\n" << (Ca * Da) % (p - 1);
    cout << "\n" << Cb << "\n" << Db << "\n" << (Cb * Db) % (p - 1);
    cout << endl;
    CrFile tempFile;
    tempFile = CrFile(fileName);
    tempFile.outToFile(name + to_string(iter) + ext);
    iter++;
    tempFile = CrFile(shamCypher(tempFile.getVector(), Ca, p));
    tempFile.outToFile(name + to_string(iter) + ext);
    iter++;
    tempFile = CrFile(shamCypher(tempFile.getVector(), Cb, p));
    tempFile.outToFile(name + to_string(iter) + ext);
    iter++;
    tempFile = CrFile(shamCypher(tempFile.getVector(), Da, p));
    tempFile.outToFile(name + to_string(iter) + ext);
    iter++;
    tempFile = CrFile(shamCypher(tempFile.getVector(), Db, p));
    tempFile.outToFile(name + to_string(iter) + ext);

    return 0;
}
//lli ElGamalCalc(lli target,lli g,lli k,lli p,lli x,lli y){
//    cout << " Orig =" << target << endl;
//
//    lli b = (target * modPow(y, k, p)) % p;
//    cout << (b * modPow(a, p - 1 - x, p)) % p;
//}
CrFile ElGamalDecrypt(CrFile b,lli p,lli a,lli x){
    vector<lli> m;


    for(auto &i:b.getVector()){
        m.push_back(i * modPow(a, p - 1 - x, p)% p);
    }
    return {m};
}
CrFile ElGamalEncrypt(CrFile target,lli k,lli p,lli y){
    vector<lli> b;


    for(auto &i:target.getVector()){
        b.push_back(i * modPow(y, k, p) % p);
    }
    return {b};
}
lli ElGamalRun(int iSeed = NULL,const string& fileName="foo.txt") {
    string name, ext;
    int iter=0;
    name = fileNameSplit(fileName, 0);
    ext = fileNameSplit(fileName, 1);
    int t = 9;
    if (iSeed != 0) {
        srand(iSeed);
    } else {
        srand(time(NULL));
    }
    lli iQ = 0;
    lli iP = 0;
    lli iG = 0;
    do {
        iQ = rand() % ((lli) pow(10, 9) - 1) + 1;
        iP = 2 * iQ + 1;
    } while (!(checkSimple(iQ) && checkSimple(iP)));
    do {
        iG = rand() % (iP - 2) + 2;
    } while (modPow(iG, iQ, iP) == 1);
//
//
//    nlPrint("G argument");
//    nlPrint(iG);
//    nlPrint("P argument");
//    nlPrint(iP);
    lli iAliceSecKey = rand() % (iP - 1) + 1;
    lli iBobSecKey = rand() % (iP - 1) + 1;
//    nlPrint("Alice secret:");
//    nlPrint(iAliceSecKey);
//    nlPrint("Bob secret:");
//    nlPrint(iBobSecKey);
    lli iAlicePubKey = modPow(iG, iAliceSecKey, iP);
    lli iBobPubKey = modPow(iG, iBobSecKey, iP);
    lli a = modPow(iG, iAliceSecKey, iP)%iP;
    lli iAliceCommKey = modPow(iBobPubKey, iAliceSecKey, iP);
    lli iBobCommKey = modPow(iAlicePubKey, iBobSecKey, iP);
    CrFile orig(fileName);
    CrFile enc= ElGamalEncrypt(orig,iAliceSecKey,iP,iBobPubKey);
    enc.outToFile(name + to_string(iter) + ext);
    CrFile dec=ElGamalDecrypt(enc,iP,a,iBobSecKey);
    dec.outToFile(name + to_string(iter+1) + ext);
    lli b = (t * modPow(iBobPubKey, iAliceSecKey, iP)) % iP;
//    cout<<b<<endl;
//    nlPrint("");
//    nlPrint(orig.getVector());
//    nlPrint(enc.getVector());
//    nlPrint(dec.getVector());
//    nlPrint("");
    cout << (b * modPow(a, iP - 1 - iBobSecKey, iP)) % iP;
}

int main() {
//  cout<<fileNameSplit("foo.bar",0)<<endl;
//    cout<<fileNameSplit("foo.bar",1)<<endl;
//    cout<<fileNameSplit("foo.bar",2)<<endl;
    // shamRun("test.jpg");
    nlPrint("");
    ElGamalRun(NULL,"test.jpg");
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