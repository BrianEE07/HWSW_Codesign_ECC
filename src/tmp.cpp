#include <vector>
#include <iostream>
#include "systemc.h"

#define clockcycle 10 // 10ns = 100MHz
#define maxcycle   1000
#define maxtime    maxcycle*clockcycle

SC_MODULE(PE){
    sc_in<bool> clk, rst_n;
    sc_in<bool> a, b, p, m_pre; // data
    sc_in<bool> isMul, toMod, clean; // control
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
            if (clean.read()) {
                w4.write(0);
            }
            else {
                w4.write(w3.read());
            }
        }
        else {
            w4.write(0);
        }
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
    sc_in<bool> start;
    sc_in<bool> a;
    sc_in<sc_biguint<8>> b, p;
    sc_in<bool> isMul, clean;

    sc_signal<bool> b0, b1, b2, b3, b4, b5, b6, b7;
    sc_signal<bool> p0, p1, p2, p3, p4, p5, p6, p7;
    sc_signal<bool> gnd;
    sc_signal<bool> toMod;
    sc_signal<bool> r_o0, r_o1, r_o2, r_o3, r_o4, r_o5, r_o6, r_o7;
    sc_signal<sc_uint<8>> counter;
    sc_signal<sc_uint<2>> state;

    sc_out<sc_biguint<8>> out;
    sc_out<bool> finish;

    PE pe0, pe1, pe2, pe3, pe4, pe5, pe6, pe7;

    void fsm() {
        if (!rst_n.read()) {
            state.write(0);
        }
        else {
            if (state.read() == 0) {
                if (start.read()) 
                    state.write(1);
            }
            else if (state.read() == 1){
                if (isMul.read() == 1) {
                    if (counter.read() == 7) 
                       state.write(2);
                }
                else {
                    if (counter.read() == 1) 
                       state.write(2);
                }   
            }
            else {
                state.write(0);
            }
        }
    }

    void done() {
        if (state.read() == 2) {
            finish.write(1);
        }
        else {
            finish.write(0);
        }
    }

    void count() {
        if (!rst_n.read()) {
            counter.write(0);
        }
        else {
            if (state.read() == 1) {
                if (isMul.read() == 1) {
                    if (counter.read() == 7) {
                        counter.write(0);
                    }
                    else {
                        counter.write(counter.read() + 1);
                    }
                }
                else {
                    if (counter.read() == 1) {
                        counter.write(0);
                    }
                    else {
                        counter.write(counter.read() + 1);
                    }
                }
                
            }
            else {
                counter.write(0);
            }
        }
    }

    void calc() {
        if (state.read() == 1) {
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
        else if (state.read() == 2) {
            toMod.write(isMul.read() & r_o7.read());
            out.write((sc_uint<1>(r_o7.read()), sc_uint<1>(r_o6.read()), sc_uint<1>(r_o5.read()), sc_uint<1>(r_o4.read()), sc_uint<1>(r_o3.read()), sc_uint<1>(r_o2.read()), sc_uint<1>(r_o1.read()), sc_uint<1>(r_o0.read())));
        }
        else {
            toMod.write(isMul.read() & r_o7.read());
            out.write(0);
        }
    }

    SC_CTOR(MULT) : pe0("PE0"), pe1("PE1"), pe2("PE2"), pe3("PE3"), pe4("PE4"), pe5("PE5"), pe6("PE6"), pe7("PE7") {
        pe0.clk(clk);
        pe0.rst_n(rst_n);
        pe0.a(a);
        pe0.b(b0);
        pe0.p(p0);
        pe0.m_pre(gnd);
        pe0.isMul(isMul);
        pe0.clean(clean);
        pe0.toMod(toMod);
        pe0.out(r_o0);

        pe1.clk(clk);
        pe1.rst_n(rst_n);
        pe1.a(a);
        pe1.b(b1);
        pe1.p(p1);
        pe1.m_pre(r_o0);
        pe1.isMul(isMul);
        pe1.clean(clean);
        pe1.toMod(toMod);
        pe1.out(r_o1);

        pe2.clk(clk);
        pe2.rst_n(rst_n);
        pe2.a(a);
        pe2.b(b2);
        pe2.p(p2);
        pe2.m_pre(r_o1);
        pe2.isMul(isMul);
        pe2.clean(clean);
        pe2.toMod(toMod);
        pe2.out(r_o2);
        
        pe3.clk(clk);
        pe3.rst_n(rst_n);
        pe3.a(a);
        pe3.b(b3);
        pe3.p(p3);
        pe3.m_pre(r_o2);
        pe3.isMul(isMul);
        pe3.clean(clean);
        pe3.toMod(toMod);
        pe3.out(r_o3);
        
        pe4.clk(clk);
        pe4.rst_n(rst_n);
        pe4.a(a);
        pe4.b(b4);
        pe4.p(p4);
        pe4.m_pre(r_o3);
        pe4.isMul(isMul);
        pe4.clean(clean);
        pe4.toMod(toMod);
        pe4.out(r_o4);

        pe5.clk(clk);
        pe5.rst_n(rst_n);
        pe5.a(a);
        pe5.b(b5);
        pe5.p(p5);
        pe5.m_pre(r_o4);
        pe5.isMul(isMul);
        pe5.clean(clean);
        pe5.toMod(toMod);
        pe5.out(r_o5);

        pe6.clk(clk);
        pe6.rst_n(rst_n);
        pe6.a(a);
        pe6.b(b6);
        pe6.p(p6);
        pe6.m_pre(r_o5);
        pe6.isMul(isMul);
        pe6.clean(clean);
        pe6.toMod(toMod);
        pe6.out(r_o6);

        pe7.clk(clk);
        pe7.rst_n(rst_n);
        pe7.a(a);
        pe7.b(b7);
        pe7.p(p7);
        pe7.m_pre(r_o6);
        pe7.isMul(isMul);
        pe7.clean(clean);
        pe7.toMod(toMod);
        pe7.out(r_o7);

        SC_METHOD(fsm);
        sensitive << clk.pos();
        sensitive << rst_n;
        SC_METHOD(done);
        sensitive << state;
        SC_METHOD(count);
        sensitive << clk.pos();
        sensitive << rst_n;
        SC_METHOD(calc);
        sensitive << a << b << p << isMul << out;
        sensitive << b0 << b1 << b2 << b3 << b4 << b5 << b6 << b7;
        sensitive << p0 << p1 << p2 << p3 << p4 << p5 << p6 << p7;
        sensitive << gnd << state << toMod;
        sensitive << r_o0 << r_o1 << r_o2 << r_o3 << r_o4 << r_o5 << r_o6 << r_o7;
    }
};

SC_MODULE(CORE){
    sc_in<bool> clk, rst_n;
    sc_in<bool> start;
    sc_in<sc_uint<2>> mode; // 0: add, 1: mul, 2: inv
    sc_in<sc_biguint<8>> a, b, p;

    sc_signal<sc_uint<8>> cnt_a, cnt_mult;
    sc_signal<sc_biguint<8>> c, sqr;
    sc_signal<bool> add_input_2nd;
    sc_signal<bool> mult_start;
    sc_signal<bool> mult_a;
    sc_signal<bool> mult_isMul;
    sc_signal<sc_biguint<8>> mult_b;
    sc_signal<sc_biguint<8>> mult_p;
    sc_signal<sc_biguint<8>> mult_out;
    sc_signal<bool> mult_finish;
    sc_signal<bool> mult_clean;
    sc_signal<bool> newstart;
    sc_signal<sc_uint<2>> state;

    sc_out<sc_biguint<8>> out;
    sc_out<bool> finish;

    MULT mult0;

    void fsm() {
        if (!rst_n.read()) {
            state.write(0);
        }
        else {
            if (state.read() == 0) { // IDLE , give start sig to mult
                if (start.read() == 1) {
                    state.write(1);
                }
                else {
                    state.write(0);
                }
            }
            else if (state.read() == 1) { // BUSY
                switch(mode.read()) { 
                    case 0: case 1:
                        if (mult_finish.read())
                            state.write(2);
                        break;
                    case 2: 
                        if (cnt_mult.read() == 12 && mult_finish.read())
                            state.write(2);
                        break;
                    default: 
                        break;
                }
            }
            else { // FINISH = 1, OUT = result
                state.write(0);
            }
        }
    }

    void count() {
        if (!rst_n.read()) {
            add_input_2nd.write(0);
            cnt_a.write(7);
            cnt_mult.write(0);
        }
        else {
            if (state.read() == 0) {
                add_input_2nd.write(0);
                cnt_a.write(7);
                cnt_mult.write(0);
            }
            else if (state.read() == 1) {
                add_input_2nd.write(!add_input_2nd.read());
                switch(mode.read()) { 
                    case 0: case 1:
                        if (cnt_a.read() == 0) {
                            cnt_a.write(7);
                        }
                        else {
                            cnt_a.write(cnt_a.read() - 1);
                        }
                        break;
                    case 2:
                        if (cnt_a.read() == 0) {
                            if (newstart.read()) {
                                cnt_a.write(7);
                            }
                            else {
                                cnt_a.write(cnt_a.read());
                            }
                        }
                        else {
                            cnt_a.write(cnt_a.read() - 1);
                        }
                        if (cnt_mult.read() == 12 && mult_finish.read()) {
                            cnt_mult.write(0);
                        }
                        else {
                            if (newstart.read()) {
                                cnt_mult.write(cnt_mult.read() + 1);
                            }
                            else {
                                cnt_mult.write(cnt_mult.read());
                            }
                        }
                        break;
                    default: 
                        break;
                }
            }
            else {
                add_input_2nd.write(0);
                cnt_a.write(7);
                cnt_mult.write(0);
            }
        }
    }

    void done() {
        if (!rst_n.read()) {
            mult_clean.write(1);
            c.write(0);
            sqr.write(0);
            out.write(0);
            finish.write(0);
        }
        else {
            if (state.read() == 0) {
                mult_clean.write(0);
                c.write(0);
                sqr.write(0);
                out.write(0);
                finish.write(0);
            }
            else if (state.read() == 1) {
                switch(mode.read()) { 
                    case 0: case 1:
                        if (mult_finish.read()) {
                            mult_clean.write(1);
                            out.write(mult_out.read());
                            finish.write(1);
                        }
                        break;
                    case 2: 
                        if (cnt_mult.read() == 12 && mult_finish.read()) {
                            mult_clean.write(1);
                            out.write(mult_out.read());
                            finish.write(1);
                        }
                        else if (cnt_mult.read() == 0 && mult_finish.read()) {
                            mult_clean.write(1);
                            c.write(mult_out.read());
                            sqr.write(mult_out.read());
                        }
                        else if (cnt_mult.read()[0] == 1 && mult_finish.read()) {
                            mult_clean.write(1);
                            c.write(c.read());
                            sqr.write(mult_out.read());
                        }
                        else if (mult_finish.read()) {
                            mult_clean.write(1);
                            c.write(mult_out.read());
                            sqr.write(sqr.read());
                        }
                        else {
                            mult_clean.write(0);
                            c.write(c.read());
                            sqr.write(sqr.read());
                        }
                        break;
                    default: 
                        break;
                }
            }
            else {
                mult_clean.write(0);
                c.write(0);
                sqr.write(0);
                out.write(0);
                finish.write(0);
            }
        }
        
    }

    void done_start() {
        if (cnt_mult.read() == 12) {
            newstart.write(0);
        }
        else {
            newstart.write(mult_finish.read());
        }
    }

    void proc() {
        if (state.read() == 0) {
            mult_start.write(start.read());
            mult_a.write(0);
            mult_b.write(0);
            mult_p.write(0);
            mult_isMul.write(0);
        }
        else if (state.read() == 1) {
            switch(mode.read()) { 
                case 0:
                    mult_start.write(0);
                    mult_a.write(1);
                    mult_b.write((add_input_2nd.read()) ? a.read() : b.read());
                    mult_p.write(0);
                    mult_isMul.write(0);
                    break; 
                case 1: 
                    mult_start.write(0);
                    mult_a.write(a.read()[cnt_a.read()]);
                    mult_b.write(b.read());
                    mult_p.write(p.read());
                    mult_isMul.write(1);
                    break; 
                case 2:
                    mult_start.write(newstart.read());
                    mult_p.write(p.read());
                    mult_isMul.write(1);
                    if (cnt_mult.read() == 0) {
                        mult_a.write(a.read()[cnt_a.read()]);
                        mult_b.write(a.read());
                    }
                    else if (cnt_mult.read()[0] == 1) {
                        mult_a.write(sqr.read()[cnt_a.read()]);
                        mult_b.write(sqr.read());
                    }
                    else {
                        mult_a.write(c.read()[cnt_a.read()]);
                        mult_b.write(sqr.read());
                    }
                    break;
                default: 
                    break;
            } 
        }
        else {
            mult_start.write(0);
            mult_a.write(0);
            mult_b.write(0);
            mult_p.write(0);
            mult_isMul.write(0);
        }
    }

    SC_CTOR(CORE) : mult0("MULT0") {
        mult0.clk(clk);
        mult0.rst_n(rst_n);
        mult0.start(mult_start);
        mult0.a(mult_a);
        mult0.b(mult_b);
        mult0.p(mult_p);
        mult0.isMul(mult_isMul);
        mult0.clean(mult_clean);
        mult0.out(mult_out);
        mult0.finish(mult_finish);

        SC_METHOD(fsm);
        sensitive << clk.pos();
        sensitive << rst_n;
        SC_METHOD(count);
        sensitive << clk.pos();
        sensitive << rst_n;
        SC_METHOD(done);
        sensitive << clk.pos();
        sensitive << rst_n;
        SC_METHOD(done_start);
        sensitive << clk.pos();
        sensitive << rst_n;
        SC_METHOD(proc);
        sensitive << mode << state << start << newstart;
        sensitive << a << b << p << c << sqr;
        sensitive << cnt_a << cnt_mult << add_input_2nd;
    }
};

// void equal() {
//     if (P.read()[16] != Q.read()[16]) {
//         eq.write(false);
//     }
//     else if (P.read()[16] && Q.read()[16]) {
//         eq.write(true);
//     }
//     else {
//         if (P.read()[15:0] == Q.read()[15:0]) {
//             eq.write(true);
//         }
//         else {
//             eq.write(false);
//         }
//     }
// }

// SC_MODULE(PD) {
//     sc_in<bool> clk, rst_n;
//     sc_in<bool> start;
//     sc_in<sc_biguint<17>> P;
//     sc_in<sc_biguint<8>> a;
//     sc_in<sc_biguint<8>> poly;
//     sc_out<sc_biguint<17>> P_o;
//     sc_out<bool> finish;

//     sc_signal<sc_biguint<17>> P_neg;
//     sc_signal<bool> eq;
//     sc_signal<sc_uint<4>> state;

//     PN pn0;
//     CORE core0;

//     void fsm() {

//     }

//     void equal() {
//         if (P.read()[16] != Q.read()[16]) {
//             eq.write(false);
//         }
//         else if (P.read()[16] && Q.read()[16]) {
//             eq.write(true);
//         }
//         else {
//             if (P.read()[15:0] == Q.read()[15:0]) {
//                 eq.write(true);
//             }
//             else {
//                 eq.write(false);
//             }
//         }
//     }

//     void calc() {
//         P_o.write((P.read[16], P.read()[15:8], (P.read()[15:8] ^ P.read()[7:0])));
//     }

//     SC_CTOR(PD) : pn0("PN0") {
//         // todo pn0 connect
//         SC_METHOD(calc);
//         sensitive << P;
//     }

// }

// point point_doubling (point P, bool *a, bool *p, int bitnum) {
//     point P_o = P;
//     point P_neg = point_negation(P, bitnum);
//     if (equal(P, P_neg, bitnum) || P.is_inf) {
//         P_o.is_inf = true;
//     }
//     else {
//         bool *inv_x = inverse(P.x, p, bitnum);
//         bool *lamb = addition(P.x, multiplication(P.y, inv_x, p, bitnum), bitnum);
//         bool *lamb_2 = multiplication(lamb, lamb, p, bitnum);
//         bool *x_2 = multiplication(P.x, P.x, p, bitnum);
//         P_o.x = addition(addition(lamb_2, lamb, bitnum), a, bitnum);
//         bool *lamb_X = multiplication(lamb, P_o.x, p, bitnum);
//         P_o.y = addition(addition(x_2, lamb_X, bitnum), P_o.x, bitnum);
//     }
//     return P_o;
// }

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
    sc_out<bool> start;
    sc_out<bool> a;
    sc_out<sc_biguint<8>> b, p;
    sc_out<bool> isMul;

    void reset() {
        rst_n.write(true);
        wait();
        rst_n.write(false);
        start.write(0);
        a.write(0);
        b.write(0);
        p.write(0);
        isMul.write(0);
        wait();
        rst_n.write(true);
        wait();
    }

    void tb_input() {
        reset();
        wait();
        start.write(1);
        wait();
        start.write(0);
        a.write(0);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        start.write(0);
        a.write(1);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        start.write(0);
        a.write(0);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        start.write(0);
        a.write(1);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        start.write(0);
        a.write(0);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        start.write(0);
        a.write(0);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        start.write(0);
        a.write(1);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        start.write(0);
        a.write(1);
        b.write(202);
        p.write(27);
        isMul.write(1);
        wait();
        wait();
        reset();
        start.write(1);
        wait();
        start.write(0);
        a.write(1);
        b.write(202);
        p.write(27);
        isMul.write(0);
        wait();
        start.write(0);
        a.write(1);
        b.write(83);
        p.write(27);
        isMul.write(0);
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

SC_MODULE(CORE_tb){

    sc_in<bool> clk;
    sc_in<bool> finish;
    sc_out<bool> rst_n;
    sc_out<bool> start;
    sc_out<sc_uint<2>> mode; // 0: add, 1: mul, 2: inv
    sc_out<sc_biguint<8>> a, b, p;

    void reset() {
        rst_n.write(true);
        wait();
        rst_n.write(false);
        start.write(0);
        mode.write(0);
        a.write(0);
        b.write(0);
        p.write(0);
        wait();
        rst_n.write(true);
        wait();
    }

    void tb_input() {
        reset();
        start.write(1);
        mode.write(0);
        a.write(202);
        b.write(83);
        p.write(27);
        while (!finish.read()) {
            wait();
        }
        wait();
        start.write(1);
        mode.write(1);
        a.write(83);
        b.write(202);
        p.write(27);
        while (!finish.read()) {
            wait();
        }
        wait();
        start.write(1);
        mode.write(2);
        a.write(230);
        b.write(83);
        p.write(27);
        while (!finish.read()) {
            wait();
        }
        wait();
        start.write(1);
        mode.write(0);
        a.write(200);
        b.write(11);
        p.write(27);
        while (!finish.read()) {
            wait();
        }
        wait();
        start.write(1);
        mode.write(1);
        a.write(111);
        b.write(1);
        p.write(27);
        while (!finish.read()) {
            wait();
        }
        wait();
        start.write(1);
        mode.write(2);
        a.write(202);
        b.write(83);
        p.write(27);
        while (!finish.read()) {
            wait();
        }
        wait();
        start.write(1);
        mode.write(1);
        a.write(83);
        b.write(0);
        p.write(27);
        while (!finish.read()) {
            wait();
        }
        wait();
        //
        wait();
        wait();
        sc_stop();
    }

    SC_CTOR(CORE_tb) {
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
    sc_in<bool> rst_n;
    sc_in<bool> start;
    sc_in<bool> a;
    sc_in<sc_biguint<8>> b, p;
    sc_in<bool> isMul;
    sc_in<sc_biguint<8>> out;
    sc_in<bool> finish;

    void monitor() {
        if (rst_n == 0) cout << sc_time_stamp() << "\t" << "RESET" << endl;
        else cout << sc_time_stamp() << "\t" << start << "\t" << a << "\t" << sc_bv<8>(b) << "\t" << sc_bv<8>(p) << "\t" << isMul << "\t" << sc_bv<8>(out) << "\t" << finish << endl;
    }
  
    SC_CTOR(MULT_mon) {
        cout << endl << "time\tstart\ta\tb\t\tp\t\tisMul\tout\t\tfinish" << endl;
        SC_METHOD(monitor);
        sensitive << clk.pos();
        dont_initialize();
    }

};

SC_MODULE(CORE_mon){
    sc_in<bool> clk;
    sc_in<bool> rst_n;
    sc_in<bool> start;
    sc_in<sc_uint<2>> mode; // 0: add, 1: mul, 2: inv
    sc_in<sc_biguint<8>> a, b, p;
    sc_in<sc_biguint<8>> out;
    sc_in<bool> finish;

    void monitor() {
        if (rst_n == 0) cout << sc_time_stamp() << "\t" << "RESET" << endl;
        else if (finish == 1) {
            cout << sc_time_stamp() << "\t" << start << "\t" << mode << "\t" << sc_bv<8>(a) << "\t" << sc_bv<8>(b) << "\t" << sc_bv<8>(p) << "\t" << sc_bv<8>(out) << "\t" << finish << endl;
        }
        else if (start == 1) {
            // cout << sc_time_stamp() << "\t" << start << "\t" << mode << "\t" << sc_bv<8>(a) << "\t" << sc_bv<8>(b) << "\t" << sc_bv<8>(p) << "\t" << sc_bv<8>(out) << "\t" << finish << endl;
        }
        else {
            // cout << sc_time_stamp() << "\t" << start << "\t" << mode << "\t" << sc_bv<8>(a) << "\t" << sc_bv<8>(b) << "\t" << sc_bv<8>(p) << "\t" << sc_bv<8>(out) << "\t" << finish << endl;
        }
    }
  
    SC_CTOR(CORE_mon) {
        cout << endl << "time\tstart\tmode\ta\t\tb\t\tp\t\tout\t\tfinish" << endl;
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

    // // for MULT
    // sc_signal<bool> start;
    // sc_signal<bool> a;
    // sc_signal<sc_biguint<8>> b, p;
    // sc_signal<bool> isMul;
    // sc_signal<sc_biguint<8>> out;
    // sc_signal<bool> finish;
    
    // MULT mult0("MULT0");
    // mult0.start(start);
    // mult0.a(a);
    // mult0.b(b);
    // mult0.p(p);
    // mult0.isMul(isMul);
    // mult0.out(out);
    // mult0.finish(finish);
    // mult0.rst_n(rst_n);
    // mult0.clk(clk);

    // MULT_tb tb0("MULT_testbench");
    // tb0.start(start);
    // tb0.a(a);
    // tb0.b(b);
    // tb0.p(p);
    // tb0.isMul(isMul);
    // tb0.rst_n(rst_n);
    // tb0.clk(clk);

    // MULT_mon mon0("MULT_monitor");
    // mon0.start(start);
    // mon0.a(a);
    // mon0.b(b);
    // mon0.p(p);
    // mon0.isMul(isMul);
    // mon0.out(out);
    // mon0.finish(finish);
    // mon0.clk(clk);
    // mon0.rst_n(rst_n);

    // for CORE
    sc_signal<bool> start;
    sc_signal<sc_uint<2>> mode; // 0: add, 1: mul, 2: inv
    sc_signal<sc_biguint<8>> a, b, p;
    sc_signal<sc_biguint<8>> out;
    sc_signal<bool> finish;
    
    CORE core0("CORE0");
    core0.start(start);
    core0.mode(mode);
    core0.a(a);
    core0.b(b);
    core0.p(p);
    core0.out(out);
    core0.finish(finish);
    core0.rst_n(rst_n);
    core0.clk(clk);

    CORE_tb tb0("CORE_testbench");
    tb0.start(start);
    tb0.mode(mode);
    tb0.a(a);
    tb0.b(b);
    tb0.p(p);
    tb0.rst_n(rst_n);
    tb0.clk(clk);
    tb0.finish(finish);

    CORE_mon mon0("CORE_monitor");
    mon0.start(start);
    mon0.mode(mode);
    mon0.a(a);
    mon0.b(b);
    mon0.p(p);
    mon0.out(out);
    mon0.finish(finish);
    mon0.clk(clk);
    mon0.rst_n(rst_n);

    sc_start(maxtime, SC_NS);

    return 0;
};

