#include <vector>
#include <iostream>
#include "systemc.h"

#define clockcycle 10 // 10ns = 100MHz
#define maxcycle   1000
#define maxtime    maxcycle*clockcycle

// using namespace std;

SC_MODULE(ADD){

    sc_in<sc_bv<8>> vec1, vec2;
    sc_out<sc_bv<8>> veco;

    void Xor() {
        veco.write( vec1.read() ^ vec2.read());
    }

    SC_CTOR(ADD){
        SC_METHOD(Xor);
        sensitive << vec1 << vec2;
    }
    
};

SC_MODULE(ADD_PIPE){

    sc_in<bool> clk, rst_n;
    sc_in<sc_bv<8>> vec1, vec2;
    sc_out<sc_bv<8>> veco;

    void Xor() {
        if (rst_n.read()) {
            veco.write( vec1.read() ^ vec2.read());
        }
    }

    SC_CTOR(ADD_PIPE){
        SC_METHOD(Xor);
        sensitive << rst_n;
        sensitive << clk.pos();
    }
    
};

SC_MODULE (DFF){
    sc_in<bool> clk, rst_n;
    sc_in<bool> d;
    sc_out<bool> q;

    void flop() {
        if (rst_n.read()) q.write(d.read());
    }

    SC_CTOR (DFF) {
        SC_METHOD(flop);
        sensitive << clk.pos();
    }

};

// SC_MODULE(PE){
//     sc_in<bool> clk, rst_n;
//     sc_in<bool> a, b, p, m_pre; // data
//     sc_in<bool> isMul, toMod; // control
//     sc_signal<bool> w0, w1, w2, w3, w4;
//     sc_out<bool> out;

//     DFF dff0;

//     void calc() {
//         if (rst_n.read()) {
//             w0.write(p.read() & toMod.read());
//             w1.write(a.read() & b.read());
//             if (isMul.read()) {
//                 w2.write(m_pre.read());
//             }
//             else {
//                 w2.write(w4.read());
//             }
//             w3.write(w0.read() ^ w1.read() ^ w2.read());
//             out.write(w4.read());
//         }
//     }
    
//     SC_CTOR(PE) : dff0("DFF0") {
//         dff0.clk(clk);
//         dff0.rst_n(rst_n);
//         dff0.d(w3);
//         dff0.q(w4);
//         SC_METHOD(calc);
//         sensitive << rst_n;
//     }
// };

SC_MODULE(PE){
    sc_in<bool> clk, rst_n;
    sc_in<bool> a, b, p, m_pre; // data
    sc_in<bool> isMul, toMod; // control
    sc_signal<bool> w0, w1, w2, w3, w4;
    sc_out<bool> out;

    void calc() {
        w0.write(p.read() & toMod.read());
        w1.write(a.read() & b.read());
        if (isMul.read()) {
            w2.write(m_pre.read());
        }
        else {
            w2.write(w4.read());
        }
        w3.write(w0.read() ^ w1.read() ^ w2.read());
        out.write(w4.read());
    }
    
    void update() {
        if (rst_n.read()) {
            w4.write(w3.read());
        }
        // else {
        //     w4.write(1);
        // }
    }

    SC_CTOR(PE) {
        SC_METHOD(calc);
        sensitive << a << b << p << m_pre << isMul << toMod << w0 << w1 << w2 << w3 << w4;
        SC_METHOD(update);
        sensitive << rst_n;
        sensitive << clk.pos();
    }

};

SC_MODULE(MULT){

};

SC_MODULE(tb){

	sc_in<bool> clk;
    sc_out<bool> rst_n;
	sc_out<sc_bv<8>> a, b;

    void reset() {
        rst_n.write(true);
        wait();
        rst_n.write(false);
        wait();
        rst_n.write(true);
        wait();
    }

    void tb_input() {
        reset();
        a.write("10101010");
        b.write("11110000");
        wait();
        a.write("11111100");
        b.write("11000000");
        wait();
        wait();
        wait();
        wait();
        wait();
        sc_stop();
    }

    SC_CTOR(tb) {
        SC_THREAD(tb_input);
        sensitive << clk.pos();
    }

};

SC_MODULE(PE_tb){

	sc_in<bool> clk;
    sc_out<bool> rst_n;
	sc_out<bool> a, b, p, m_pre, isMul, toMod;

    void reset() {
        rst_n.write(true);
        wait();
        rst_n.write(false);
        wait();
        rst_n.write(true);
        wait();
    }

    void tb_input() {
        reset();
        a.write(1);
        b.write(1);
        p.write(1);
        m_pre.write(0);
        isMul.write(0);
        toMod.write(0);
        wait();
        // a.write(1);
        // b.write(1);
        // p.write(1);
        // m_pre.write(1);
        // isMul.write(0);
        // toMod.write(0);
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        a.write(1);
        b.write(0);
        p.write(1);
        m_pre.write(0);
        isMul.write(1);
        toMod.write(1);
        wait();
        a.write(1);
        b.write(0);
        p.write(0);
        m_pre.write(1);
        isMul.write(1);
        toMod.write(1);
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        sc_stop();
    }

    SC_CTOR(PE_tb) {
        SC_THREAD(tb_input);
        sensitive << clk.pos();
    }

};

SC_MODULE(mon){
    sc_in<bool> clk;
    // sc_in<sc_bv<8>> a, b, c;
    sc_in<bool> a, b, p, m_pre, isMul, toMod, out;

    void monitor() {
        // cout << sc_time_stamp()  << "\t" << a << "\t" << b << "\t" << c <<endl;
        cout << sc_time_stamp()  << "\t" << a << "\t" << b << "\t" << p << "\t" << m_pre << "\t" << isMul << "\t" << toMod << "\t" << out << endl;
    }
  
    SC_CTOR(mon) {
        cout << endl << "time\ta\tb\tp\tm_pre\tisMul\ttoMod\tout" << endl;
        SC_METHOD(monitor);
        sensitive << clk.pos();
        dont_initialize();
    }

};

int sc_main(int argc, char** argv){

    sc_clock clk("CLOCK", clockcycle, SC_NS, 0.5, 0, SC_NS, true);
    sc_signal<bool> rst_n;
    // sc_signal<sc_bv<8>> a, b, c;
    sc_signal<bool> a, b, p, m_pre, isMul, toMod, out;

    // ADD add0("adder");
    // add0.vec1(a);
    // add0.vec2(b);
    // add0.veco(c);
    // // add0.rst_n(rst_n);
    // // add0.clk(clk);

    // ADD_PIPE add0("adder");
    // add0.vec1(a);
    // add0.vec2(b);
    // add0.veco(c);
    // add0.rst_n(rst_n);
    // add0.clk(clk);

    // tb tb0("testbench");
    // tb0.a(a);
    // tb0.b(b);
    // tb0.rst_n(rst_n);
    // tb0.clk(clk);

    PE pe0("PE0");
    pe0.a(a);
    pe0.b(b);
    pe0.p(p);
    pe0.m_pre(m_pre);
    pe0.isMul(isMul);
    pe0.toMod(toMod);
    pe0.out(out);
    pe0.rst_n(rst_n);
    pe0.clk(clk);

    PE_tb tb0("PE_testbench");
    tb0.a(a);
    tb0.b(b);
    tb0.p(p);
    tb0.m_pre(m_pre);
    tb0.isMul(isMul);
    tb0.toMod(toMod);
    tb0.rst_n(rst_n);
    tb0.clk(clk);

    mon monitor0("monitor");
    monitor0.a(a);
    monitor0.b(b);
    monitor0.p(p);
    monitor0.m_pre(m_pre);
    monitor0.isMul(isMul);
    monitor0.toMod(toMod);
    monitor0.out(out);
    monitor0.clk(clk);

    sc_start(maxtime, SC_NS);

    return 0;
};

