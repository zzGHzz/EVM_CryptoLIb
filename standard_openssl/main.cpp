#include "include/secp256k1.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

string bin[16] = {"0000", "0001", "0010", "0011",
                  "0100", "0101", "0110", "0111",
                  "1000", "1001", "1010", "1011",
                  "1100", "1101", "1110", "1111"};

bool check(Secp256k1_point now, string check) {
    return true;
}

int main()
{
    Secp256k1_point g;
    string s = "1";
    const vector<unsigned char> n(s.begin(), s.end());
    g.set_ng(n);
    Secp256k1_point o;
    o.set_O();
    for (int i=2; i<o.ORDER.length(); ++i) {
        string tmp = "";
        tmp += o.ORDER[i];
        int pos = stoi(tmp, nullptr, 16);
        for (int j=0; j<4; ++j) {
            o+=o;
            check(o, ""); // TODO
            if (bin[pos][j] == '1') {
                o+=g;
                check(o, ""); //TODO
            }
        }
    }
    assert(o.is_O());
    return 0;
}