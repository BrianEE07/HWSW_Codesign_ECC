#include <vector>
#include <iostream>
#include "systemc.h"

#define clockcycle 10 // 10ns = 100MHz
#define maxcycle   10000
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
        // cout << "Core: " << state << endl;
        // cout << "CoreFinish: " << finish << endl;
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

SC_MODULE(PN) {
    sc_in<bool> clk, rst_n;
    sc_in<bool> start;
    sc_in<sc_biguint<17>> P;

    sc_biguint<8> Px;
    sc_biguint<8> Py;
    sc_signal<sc_biguint<8>> Px_sig;
    sc_signal<sc_biguint<8>> Py_sig;
    sc_signal<sc_uint<2>> core_mode;
    sc_signal<sc_biguint<8>> core_p;
    sc_signal<bool> core_finish;
    sc_signal<sc_biguint<8>> core_out;

    sc_out<sc_biguint<17>> P_o;
    sc_out<bool> finish;

    CORE core0;
    
    void comb() {
        Px = P.read().range(15, 8);
        Py = P.read().range(7, 0);
        Px_sig.write(Px);
        Py_sig.write(Py);
        core_mode.write(0);
        core_p.write(0);
        if (core_finish.read()) {
            P_o.write((P.read().range(16, 8), core_out.read()));
            finish.write(1);
        }
        else {
            P_o.write(0);
            finish.write(0);
        }
    }

    SC_CTOR(PN) : core0("CORE0") {
        core0.clk(clk);
        core0.rst_n(rst_n);
        core0.start(start);
        core0.mode(core_mode);
        core0.a(Px_sig);
        core0.b(Py_sig);
        core0.p(core_p);
        core0.out(core_out);
        core0.finish(core_finish);

        SC_METHOD(comb);
        sensitive << P << core_out << core_finish;
    }
};

SC_MODULE(PA) {
    sc_in<bool> clk, rst_n;
    sc_in<bool> start;
    sc_in<sc_biguint<17>> P, Q;
    sc_in<sc_biguint<8>> a, p;

    sc_biguint<8> Px, Py;
    sc_biguint<8> Qx, Qy;
    sc_signal<sc_biguint<8>> Px_sig, Py_sig;
    sc_signal<sc_biguint<8>> Qx_sig, Qy_sig;
    sc_signal<bool> eq;
    sc_signal<sc_uint<5>> state;
    sc_signal<sc_uint<2>> core_mode;
    sc_signal<bool> core_start, pn_start;
    sc_signal<bool> core_finish, pn_finish;
    sc_signal<sc_biguint<8>> core_out;
    sc_signal<sc_biguint<17>> pn_P, pn_P_o;

    sc_signal<sc_biguint<17>> Q_neg;
    sc_signal<sc_biguint<17>> eq_P, eq_Q;

    sc_signal<sc_biguint<8>> Px_Qx, Py_Qy, inv_Px_Qx, lamb, lamb_2, Px_X, lamb_Px_X;
    sc_signal<sc_biguint<8>> tempx0, tempx1, tempx2, P_ox;
    sc_signal<sc_biguint<8>> tempy0, P_oy;
    sc_signal<sc_biguint<8>> core_a, core_b, core_p;

    sc_out<sc_biguint<17>> P_o;
    sc_out<bool> finish;

    PN pn0;
    // PD pd0;
    CORE core0;

    void equal() {
        if (eq_P.read()[16] != eq_Q.read()[16]) {
            eq.write(false);
        }
        else if (eq_P.read()[16] && eq_Q.read()[16]) {
            eq.write(true);
        }
        else {
            if (eq_P.read().range(15, 0) == eq_Q.read().range(15, 0)) {
                eq.write(true);
            }
            else {
                eq.write(false);
            }
        }  
    }

    void fsm() {
        // cout << state << endl;
        // cout << "Start " << core_start << endl;
        // cout << "Finish " << core_finish << endl;
        if (!rst_n.read()) {
            state.write(0);
        }
        else {
            switch(state.read()) { 
                case 0:
                    if (start.read()) {
                        if (!eq.read()) {
                            state.write(1);
                        }
                        else {
                            state.write(16);    // return PD
                        }
                    }
                    else {
                        state.write(0);
                    }
                    break;
                case 1:                         // calculate Q_neg
                    if (pn_finish.read()) {
                        if (eq.read()) {
                            state.write(0);    // P_o.is_inf = true;
                        }
                        else if (P.read()[16] == 1) {
                            state.write(0);    // P_o = Q;
                        }
                        else if (Q.read()[16] == 1) {
                            state.write(0);    // P_o = P;
                        }
                        else {
                            state.write(2);
                        }
                    }
                    else {
                        state.write(1);
                    }
                    break;
                case 2:                         // calculate Px add Qx
                    if (core_finish.read()) {
                        state.write(3);
                    }
                    else {
                        state.write(2);
                    }
                    break;
                case 3:                         // calculate Py add Qy
                    if (core_finish.read()) {
                        state.write(4);
                    }
                    else {
                        state.write(3);
                    }
                    break;
                case 4:                         // calculate inv (Px add Qx)
                    if (core_finish.read()) {
                        state.write(5);
                    }
                    else {
                        state.write(4);
                    }
                    break;  
                case 5:                         // calculate lamb
                    if (core_finish.read()) {
                        state.write(6);
                    }
                    else {
                        state.write(5);
                    }
                    break;
                case 6:                         // calculate lamb_2
                    if (core_finish.read()) {
                        state.write(7);
                    }
                    else {
                        state.write(6);
                    }
                    break;
                case 7:                         // calculate lamb_2 add lamb
                    if (core_finish.read()) {
                        state.write(8);
                    }
                    else {
                        state.write(7);
                    }
                    break;
                case 8:                         // calculate P.x add Q.x
                    if (core_finish.read()) {
                        state.write(9);
                    }
                    else {
                        state.write(8);
                    }
                    break;
                case 9:                         // calculate P_o.x add 2nd
                    if (core_finish.read()) {
                        state.write(10);
                    }
                    else {
                        state.write(9);
                    }
                    break;
                case 10:                         // calculate P_o.x add 3rd
                    if (core_finish.read()) {
                        state.write(11);
                    }
                    else {
                        state.write(10);
                    }
                    break;
                case 11:                         // calculate Px_X
                    if (core_finish.read()) {
                        state.write(12);
                    }
                    else {
                        state.write(11);
                    }
                    break;
                case 12:                         // calculate lamb_Px_X
                    if (core_finish.read()) {
                        state.write(13);
                    }
                    else {
                        state.write(12);
                    }
                    break;
                case 13:                         // calculate lamb_Px_X add P_o.x
                    if (core_finish.read()) {
                        state.write(14);
                    }
                    else {
                        state.write(13);
                    }
                    break;
                case 14:                         // calculate P_o.y add 2nd
                    if (core_finish.read()) {
                        state.write(15);
                    }
                    else {
                        state.write(14);
                    }
                    break;
                case 15:
                    state.write(0);
                    break;
                case 16:                         // point_doubling !!! is not finished  !!!
                    if (core_finish.read()) {
                        state.write(0);
                    }
                    else {
                        state.write(16);
                    }
                    break;
                default: 
                    break;
            }
        }
    }
    
    void sequ() {
        Px_Qx.write(Px_Qx.read());
        Py_Qy.write(Py_Qy.read());
        inv_Px_Qx.write(inv_Px_Qx.read());
        lamb.write(lamb.read());
        lamb_2.write(lamb_2.read());
        tempx0.write(tempx0.read());
        tempx1.write(tempx1.read());
        tempx2.write(tempx2.read());
        P_ox.write(P_ox.read());
        Px_X.write(Px_X.read());
        lamb_Px_X.write(lamb_Px_X.read());
        tempy0.write(tempy0.read());
        P_oy.write(P_oy.read());
        switch(state.read()) { 
            case 2: 
                Px_Qx.write(core_out.read());
                break;
            case 3:
                Py_Qy.write(core_out.read());
                break;
            case 4:
                inv_Px_Qx.write(core_out.read());
                break;
            case 5:
                lamb.write(core_out.read());
                break;
            case 6:
                lamb_2.write(core_out.read());
                break;
            case 7:
                tempx0.write(core_out.read());
                break;
            case 8:
                tempx1.write(core_out.read());
                break;
            case 9:
                tempx2.write(core_out.read());
                break;
            case 10:
                P_ox.write(core_out.read());
                break;
            case 11:
                Px_X.write(core_out.read());
                break;
            case 12:
                lamb_Px_X.write(core_out.read());
                break;
            case 13:
                tempy0.write(core_out.read());
                break;
            case 14:
                P_oy.write(core_out.read());
                break;
            default: 
                break;
        }
    }
    
    void comb() {
        Px = P.read().range(15, 8);
        Py = P.read().range(7, 0);
        Qx = Q.read().range(15, 8);
        Qy = Q.read().range(7, 0);
        Px_sig.write(Px);
        Py_sig.write(Py);
        Qx_sig.write(Qx);
        Qy_sig.write(Qy);
        P_o.write(0);
        finish.write(0);
        pn_start.write(0);
        core_start.write(0);
        switch(state.read()) { 
            case 0: 
                if (start.read()){
                    pn_start.write(1);
                }
                eq_P.write(P.read());
                eq_Q.write(Q.read());
                break;
            case 1:
                eq_P.write(P.read());
                eq_Q.write(Q_neg.read());
                if (pn_finish.read()) {
                    if (eq.read()) {
                        P_o.write((1, P.read().range(15, 0)));
                        finish.write(1);
                    }
                    else if (P.read()[16] == 1) {
                        P_o.write(Q.read());
                        finish.write(1);
                    }
                    else if (Q.read()[16] == 1) {
                        P_o.write(P.read());
                        finish.write(1);
                    }
                    else {
                        P_o.write(0);
                    }
                }
                else {
                    P_o.write(0);
                }
                break;
            case 2: 
                core_start.write(1);
                core_mode.write(0);
                core_a.write(Px_sig.read());
                core_b.write(Qx_sig.read());
                core_p.write(0);
                break;
            case 3: 
                core_start.write(1);
                core_mode.write(0);
                core_a.write(Py_sig.read());
                core_b.write(Qy_sig.read());
                core_p.write(0);
                break;
            case 4: 
                core_start.write(1);
                core_mode.write(2);
                core_a.write(Px_Qx.read());
                core_b.write(0);
                core_p.write(p.read());
                break;
            case 5: 
                core_start.write(1);
                core_mode.write(1);
                core_a.write(Py_Qy.read());
                core_b.write(inv_Px_Qx.read());
                core_p.write(p.read());
                break;
            case 6: 
                core_start.write(1);
                core_mode.write(1);
                core_a.write(lamb.read());
                core_b.write(lamb.read());
                core_p.write(p.read());
                break;
            case 7: 
                core_start.write(1);
                core_mode.write(0);
                core_a.write(lamb_2.read());
                core_b.write(lamb.read());
                core_p.write(0);
                break;
            case 8: 
                core_start.write(1);
                core_mode.write(0);
                core_a.write(Px_sig.read());
                core_b.write(Qx_sig.read());
                core_p.write(0);
                break;
            case 9: 
                core_start.write(1);
                core_mode.write(0);
                core_a.write(tempx0.read());
                core_b.write(tempx1.read());
                core_p.write(0);
                break;
            case 10: 
                core_start.write(1);
                core_mode.write(0);
                core_a.write(tempx2.read());
                core_b.write(a.read());
                core_p.write(0);
                break;
            case 11: 
                core_start.write(1);
                core_mode.write(0);
                core_a.write(Px_sig.read());
                core_b.write(P_ox.read());
                core_p.write(0);
                break;
            case 12: 
                core_start.write(1);
                core_mode.write(1);
                core_a.write(lamb.read());
                core_b.write(Px_X.read());
                core_p.write(p.read());
                break;
            case 13: 
                core_start.write(1);
                core_mode.write(0);
                core_a.write(lamb_Px_X.read());
                core_b.write(P_ox.read());
                core_p.write(0);
                break;
            case 14: 
                core_start.write(1);
                core_mode.write(0);
                core_a.write(tempy0.read());
                core_b.write(Py_sig.read());
                core_p.write(0);
                break;
            case 15:
                P_o.write((0, P_ox.read(), P_oy.read()));
                finish.write(1);
                break;
            case 16: // todo
                break;
            default: 
                break;
        }
    }
    
    SC_CTOR(PA) : core0("CORE0"), pn0("PN0") {
        core0.clk(clk);
        core0.rst_n(rst_n);
        core0.start(core_start);
        core0.mode(core_mode);
        core0.a(core_a);
        core0.b(core_b);
        core0.p(core_p);
        core0.out(core_out);
        core0.finish(core_finish);

        pn0.clk(clk);
        pn0.rst_n(rst_n);
        pn0.start(pn_start);
        pn0.P(pn_P);
        pn0.P_o(pn_P_o);
        pn0.finish(pn_finish);

        SC_METHOD(equal);
        sensitive << eq_P << eq_Q;

        SC_METHOD(fsm);
        sensitive << clk.pos();
        sensitive << rst_n;

        SC_METHOD(comb);
        sensitive << P << Q << Q_neg << state << start << p;
        sensitive << pn_finish << eq << Px_sig << Py_sig << Qx_sig << Qy_sig;
        sensitive << Px_Qx << Py_Qy << inv_Px_Qx;
        sensitive << lamb << lamb_2 << tempx0 << tempx1 << tempx2;
        sensitive << P_ox << Px_X << lamb_Px_X << tempy0 << P_oy;
        SC_METHOD(sequ);
        sensitive << clk.pos();
        sensitive << rst_n;
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

SC_MODULE(PA_tb){

    sc_in<bool> clk;
    sc_in<bool> finish;
    sc_out<bool> rst_n;
    sc_out<bool> start;
    sc_out<sc_biguint<17>> P, Q;
    sc_out<sc_biguint<8>> a, p;

    void reset() {
        rst_n.write(true);
        wait();
        rst_n.write(false);
        start.write(0);
        P.write(0);
        Q.write(0);
        a.write(0);
        p.write(0);
        wait();
        rst_n.write(true);
        wait();
    }

    void tb_input() {
        reset();
        start.write(1);
        P.write(59082);
        Q.write(43639);
        a.write(170);
        p.write(27);
        while (!finish.read()) {
            wait();
        }
        wait();
        sc_stop();
    }

    SC_CTOR(PA_tb) {
        SC_THREAD(tb_input);
        sensitive << clk.pos();
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

SC_MODULE(PA_mon){
    sc_in<bool> clk;
    sc_in<bool> rst_n;
    sc_in<bool> start;
    sc_in<sc_biguint<17>> P, Q;
    sc_in<sc_biguint<8>> a, p;
    sc_in<sc_biguint<17>> P_o;
    sc_in<bool> finish;

    void monitor() {
        if (rst_n == 0) cout << sc_time_stamp() << "\t" << "RESET" << endl;
        else if (finish == 1) {
            cout << sc_time_stamp() << "\t" << start << "\t" << sc_bv<17>(P) << "\t" << sc_bv<17>(Q) << "\t" << sc_bv<8>(a) << "\t" << sc_bv<8>(p) << "\t" << sc_bv<17>(P_o) << "\t" << finish << endl;
        }
        else {
            // cout << sc_time_stamp() << "\t" << start << "\t" << sc_bv<17>(P) << "\t" << sc_bv<17>(Q) << "\t" << sc_bv<8>(a) << "\t" << sc_bv<8>(p) << "\t" << sc_bv<17>(P_o) << "\t" << finish << endl;
        }
    }
  
    SC_CTOR(PA_mon) {
        cout << endl << "time\tstart\tP\t\t\tQ\t\t\ta\t\tp\t\tP_o\t\t\tfinish" << endl;
        SC_METHOD(monitor);
        sensitive << clk.pos();
        dont_initialize();
    }

};


// point scalar_multiplication (int n, point P, bool *a, bool *p, int bitnum) {
// point A = P;
// point R = P;
// R.is_inf = true;
// while (n > 0) {
//     if (n % 2 == 1) {
//         point tmp1 = point_addition(R, A, a, p, bitnum);
//         R = tmp1;
//     }
//     n >>= 1;
//     point tmp2 = point_doubling(A, a, p, bitnum);
//     A = tmp2;
// }
// return R;}

int sc_main(int argc, char** argv){

    sc_clock clk("CLOCK", clockcycle, SC_NS, 0.5, 0, SC_NS, true);
    sc_signal<bool> rst_n;

    // // for CORE
    // sc_signal<bool> start;
    // sc_signal<sc_uint<2>> mode; // 0: add, 1: mul, 2: inv
    // sc_signal<sc_biguint<8>> a, b, p;
    // sc_signal<sc_biguint<8>> out;
    // sc_signal<bool> finish;
    
    // CORE core0("CORE0");
    // core0.start(start);
    // core0.mode(mode);
    // core0.a(a);
    // core0.b(b);
    // core0.p(p);
    // core0.out(out);
    // core0.finish(finish);
    // core0.rst_n(rst_n);
    // core0.clk(clk);

    // CORE_tb tb0("CORE_testbench");
    // tb0.start(start);
    // tb0.mode(mode);
    // tb0.a(a);
    // tb0.b(b);
    // tb0.p(p);
    // tb0.rst_n(rst_n);
    // tb0.clk(clk);
    // tb0.finish(finish);

    // CORE_mon mon0("CORE_monitor");
    // mon0.start(start);
    // mon0.mode(mode);
    // mon0.a(a);
    // mon0.b(b);
    // mon0.p(p);
    // mon0.out(out);
    // mon0.finish(finish);
    // mon0.clk(clk);
    // mon0.rst_n(rst_n);

    // for PA
    sc_signal<bool> start;
    sc_signal<sc_biguint<17>> P, Q;
    sc_signal<sc_biguint<8>> a, p;

    sc_signal<sc_biguint<17>> P_o;
    sc_signal<bool> finish;

    PA pa0("PA0");
    pa0.start(start);
    pa0.P(P);
    pa0.Q(Q);
    pa0.a(a);
    pa0.p(p);
    pa0.P_o(P_o);
    pa0.finish(finish);
    pa0.rst_n(rst_n);
    pa0.clk(clk);

    PA_tb tb0("PA_testbench");
    tb0.start(start);
    tb0.P(P);
    tb0.Q(Q);
    tb0.a(a);
    tb0.p(p);
    tb0.rst_n(rst_n);
    tb0.clk(clk);
    tb0.finish(finish);

    PA_mon mon0("PA_monitor");
    mon0.start(start);
    mon0.P(P);
    mon0.Q(Q);
    mon0.a(a);
    mon0.p(p);
    mon0.P_o(P_o);
    mon0.finish(finish);
    mon0.rst_n(rst_n);
    mon0.clk(clk);

    sc_start(maxtime, SC_NS);

    return 0;
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