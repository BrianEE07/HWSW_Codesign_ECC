#include <vector>
#include <iostream>
#include "systemc.h"

#define clockcycle 10 // 10ns = 100MHz
#define maxcycle   1000
#define maxtime    maxcycle*clockcycle

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
    sc_in<bool> clk, rst_n;
    sc_in<bool> a;
    sc_in<sc_biguint<8>> b, p;
    sc_in<bool> isMul;

    sc_signal<bool> b0, b1, b2, b3, b4, b5, b6, b7;
    sc_signal<bool> p0, p1, p2, p3, p4, p5, p6, p7;
    sc_signal<bool> gnd;
    sc_signal<bool> toMod;
    sc_signal<bool> r_o0, r_o1, r_o2, r_o3, r_o4, r_o5, r_o6, r_o7;
    sc_out<sc_biguint<8>> out;

    PE pe0, pe1, pe2, pe3, pe4, pe5, pe6, pe7;

    void calc() {
        b0.write(b.read()[0]);
        b1.write(b.read()[1]);
        b2.write(b.read()[2]);
        b3.write(b.read()[3]);
        b4.write(b.read()[4]);
        b5.write(b.read()[5]);
        b6.write(b.read()[6]);
        b7.write(b.read()[7]);

        p0.write(p.read()[0]);
        p1.write(p.read()[1]);
        p2.write(p.read()[2]);
        p3.write(p.read()[3]);
        p4.write(p.read()[4]);
        p5.write(p.read()[5]);
        p6.write(p.read()[6]);
        p7.write(p.read()[7]);

        gnd.write(0);
        toMod.write(isMul.read() & r_o7.read());

        out.write((sc_uint<1>(r_o7.read()), sc_uint<1>(r_o6.read()), sc_uint<1>(r_o5.read()), sc_uint<1>(r_o4.read()), sc_uint<1>(r_o3.read()), sc_uint<1>(r_o2.read()), sc_uint<1>(r_o1.read()), sc_uint<1>(r_o0.read())));
    }

    SC_CTOR(MULT) : pe0("PE0"), pe1("PE1"), pe2("PE2"), pe3("PE3"), pe4("PE4"), pe5("PE5"), pe6("PE6"), pe7("PE7") {
        pe0.clk(clk);
        pe0.rst_n(rst_n);
        pe0.a(a);
        pe0.b(b0);
        pe0.p(p0);
        pe0.m_pre(gnd);
        pe0.isMul(isMul);
        pe0.toMod(toMod);
        pe0.out(r_o0);

        pe1.clk(clk);
        pe1.rst_n(rst_n);
        pe1.a(a);
        pe1.b(b1);
        pe1.p(p1);
        pe1.m_pre(r_o0);
        pe1.isMul(isMul);
        pe1.toMod(toMod);
        pe1.out(r_o1);

        pe2.clk(clk);
        pe2.rst_n(rst_n);
        pe2.a(a);
        pe2.b(b2);
        pe2.p(p2);
        pe2.m_pre(r_o1);
        pe2.isMul(isMul);
        pe2.toMod(toMod);
        pe2.out(r_o2);
        
        pe3.clk(clk);
        pe3.rst_n(rst_n);
        pe3.a(a);
        pe3.b(b3);
        pe3.p(p3);
        pe3.m_pre(r_o2);
        pe3.isMul(isMul);
        pe3.toMod(toMod);
        pe3.out(r_o3);
        
        pe4.clk(clk);
        pe4.rst_n(rst_n);
        pe4.a(a);
        pe4.b(b4);
        pe4.p(p4);
        pe4.m_pre(r_o3);
        pe4.isMul(isMul);
        pe4.toMod(toMod);
        pe4.out(r_o4);

        pe5.clk(clk);
        pe5.rst_n(rst_n);
        pe5.a(a);
        pe5.b(b5);
        pe5.p(p5);
        pe5.m_pre(r_o4);
        pe5.isMul(isMul);
        pe5.toMod(toMod);
        pe5.out(r_o5);

        pe6.clk(clk);
        pe6.rst_n(rst_n);
        pe6.a(a);
        pe6.b(b6);
        pe6.p(p6);
        pe6.m_pre(r_o5);
        pe6.isMul(isMul);
        pe6.toMod(toMod);
        pe6.out(r_o6);

        pe7.clk(clk);
        pe7.rst_n(rst_n);
        pe7.a(a);
        pe7.b(b7);
        pe7.p(p7);
        pe7.m_pre(r_o6);
        pe7.isMul(isMul);
        pe7.toMod(toMod);
        pe7.out(r_o7);

        SC_METHOD(calc);
        sensitive << a << b << p << isMul << out;
        sensitive << b0 << b1 << b2 << b3 << b4 << b5 << b6 << b7;
        sensitive << p0 << p1 << p2 << p3 << p4 << p5 << p6 << p7;
        sensitive << gnd << toMod;
        sensitive << r_o0 << r_o1 << r_o2 << r_o3 << r_o4 << r_o5 << r_o6 << r_o7;
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

SC_MODULE(MULT_tb){

	sc_in<bool> clk;
    sc_out<bool> rst_n;
    sc_out<bool> a;
    sc_out<sc_biguint<8>> b, p;
    sc_out<bool> isMul;

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
        wait();
        a.write(0);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        a.write(1);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        a.write(0);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        a.write(1);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        a.write(0);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        a.write(0);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        a.write(1);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        a.write(1);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        wait();
        sc_stop();
    }

    SC_CTOR(MULT_tb) {
        SC_THREAD(tb_input);
        sensitive << clk.pos();
    }

};

SC_MODULE(PE_mon){
    sc_in<bool> clk;
    sc_in<bool> a, b, p, m_pre, isMul, toMod, out;

    void monitor() {
        cout << sc_time_stamp()  << "\t" << a << "\t" << b << "\t" << p << "\t" << m_pre << "\t" << isMul << "\t" << toMod << "\t" << out << endl;
    }
  
    SC_CTOR(PE_mon) {
        cout << endl << "time\ta\tb\tp\tm_pre\tisMul\ttoMod\tout" << endl;
        SC_METHOD(monitor);
        sensitive << clk.pos();
        dont_initialize();
    }

};

SC_MODULE(MULT_mon){
    sc_in<bool> clk;
    sc_in<bool> a;
    sc_in<sc_biguint<8>> b, p;
    sc_in<bool> isMul;
    sc_in<sc_biguint<8>> out;

    void monitor() {
        cout << sc_time_stamp()  << "\t" << a << "\t" << sc_bv<8>(b) << "\t" << sc_bv<8>(p) << "\t" << isMul << "\t" << sc_bv<8>(out) << endl;
    }
  
    SC_CTOR(MULT_mon) {
        cout << endl << "time\ta\tb\t\tp\t\tisMul\tout" << endl;
        SC_METHOD(monitor);
        sensitive << clk.pos();
        dont_initialize();
    }

};

int sc_main(int argc, char** argv){

    sc_clock clk("CLOCK", clockcycle, SC_NS, 0.5, 0, SC_NS, true);
    sc_signal<bool> rst_n;

    // // for PE
    // sc_signal<bool> a, b, p, m_pre, isMul, toMod, out;

    // PE pe0("PE0");
    // pe0.a(a);
    // pe0.b(b);
    // pe0.p(p);
    // pe0.m_pre(m_pre);
    // pe0.isMul(isMul);
    // pe0.toMod(toMod);
    // pe0.out(out);
    // pe0.rst_n(rst_n);
    // pe0.clk(clk);

    // PE_tb tb0("PE_testbench");
    // tb0.a(a);
    // tb0.b(b);
    // tb0.p(p);
    // tb0.m_pre(m_pre);
    // tb0.isMul(isMul);
    // tb0.toMod(toMod);
    // tb0.rst_n(rst_n);
    // tb0.clk(clk);

    // PE_mon mon0("PE_monitor");
    // mon0.a(a);
    // mon0.b(b);
    // mon0.p(p);
    // mon0.m_pre(m_pre);
    // mon0.isMul(isMul);
    // mon0.toMod(toMod);
    // mon0.out(out);
    // mon0.clk(clk);

    // for MULT
    sc_signal<bool> a;
    sc_signal<sc_biguint<8>> b, p;
    sc_signal<bool> isMul;
    sc_signal<sc_biguint<8>> out;
    
    MULT mult0("MULT0");
    mult0.a(a);
    mult0.b(b);
    mult0.p(p);
    mult0.isMul(isMul);
    mult0.out(out);
    mult0.rst_n(rst_n);
    mult0.clk(clk);

    MULT_tb tb0("MULT_testbench");
    tb0.a(a);
    tb0.b(b);
    tb0.p(p);
    tb0.isMul(isMul);
    tb0.rst_n(rst_n);
    tb0.clk(clk);

    MULT_mon mon0("MULT_monitor");
    mon0.a(a);
    mon0.b(b);
    mon0.p(p);
    mon0.isMul(isMul);
    mon0.out(out);
    mon0.clk(clk);

    sc_start(maxtime, SC_NS);

    return 0;
};

