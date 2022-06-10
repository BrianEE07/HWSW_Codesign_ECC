#include <vector>
#include <iostream>
#include "systemc.h"

using namespace std;

SC_MODULE(ADD){

    //sc_in<bool> clk, rst_n;
    sc_in<sc_bv<8>> vec1[8], vec2[8];
    sc_out<sc_bv<8>> veco;

    void xor() {
        veco.write( vec1.read() ^ vec2.read());
    }

    SC_CTOR(ADD){
        SC_METHOD(xor);
        sensitive << veco;
    }
    
}

int sc_main(int argc, char** argv){

    sc_signal<sc_bv<8>> a, b;
    ADD add("add");

    a = 10101010;
    b = 11110000;
    add.vec1(a);
    add.vec2(b);
    add.veco(c);

    
    ADD add("add", a, b, 8);
    sc_core::sc_start();
    return 0;
};