#ifndef	__ASIC_H
#define __ASIC_H
#include "systemc.h"
#include <stdio.h>

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

SC_MODULE(PD) {
    sc_in<bool> clk, rst_n;
    sc_in<bool> start;
    sc_in<sc_biguint<17>> P;
    sc_in<sc_biguint<8>> a, p;

    sc_biguint<8> Px, Py;
    sc_signal<sc_biguint<8>> Px_sig, Py_sig;
    sc_signal<bool> eq;
    sc_signal<sc_uint<5>> state;
    sc_signal<sc_uint<2>> core_mode;
    sc_signal<bool> core_start, pn_start;
    sc_signal<bool> core_finish, pn_finish;
    sc_signal<sc_biguint<8>> core_out;
    sc_signal<sc_biguint<17>> pn_P, pn_P_o;

    sc_signal<sc_biguint<17>> P_neg;
    sc_signal<sc_biguint<17>> eq_P, eq_Q;

    sc_signal<sc_biguint<8>> inv_x, temp_lamb, lamb, lamb_2, x_2;
    sc_signal<sc_biguint<8>> tempx0, P_ox, lamb_X;
    sc_signal<sc_biguint<8>> tempy0, P_oy;
    sc_signal<sc_biguint<8>> core_a, core_b, core_p;

    sc_out<sc_biguint<17>> P_o;
    sc_out<bool> finish;

    PN pn0;
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
        // cout << pn_finish << endl;
        // cout << pn_start << endl;
        if (!rst_n.read()) {
            state.write(0);
        }
        else {
            switch(state.read()) { 
                case 0:
                    if (start.read()) {
                        if (pn_finish.read()) {
                            if (eq.read() || P.read()[16] == 1) {
                                state.write(0);    // P_o.is_inf = true;
                            }
                            else {
                                state.write(1);
                            }
                        }
                        else {
                            state.write(0);
                        }
                    }
                    else {
                        state.write(0);
                    }
                    break;
                case 1:                         // calculate inv_x
                    if (core_finish.read()) {
                        state.write(2);
                    }
                    else {
                        state.write(1);
                    }
                    break;
                case 2:                         // calculate temp_lamb
                    if (core_finish.read()) {
                        state.write(3);
                    }
                    else {
                        state.write(2);
                    }
                    break;
                case 3:                         // calculate lamb
                    if (core_finish.read()) {
                        state.write(4);
                    }
                    else {
                        state.write(3);
                    }
                    break;
                case 4:                         // calculate lamb_2
                    if (core_finish.read()) {
                        state.write(5);
                    }
                    else {
                        state.write(4);
                    }
                    break;  
                case 5:                         // calculate x_2
                    if (core_finish.read()) {
                        state.write(6);
                    }
                    else {
                        state.write(5);
                    }
                    break;
                case 6:                         // calculate tempx0
                    if (core_finish.read()) {
                        state.write(7);
                    }
                    else {
                        state.write(6);
                    }
                    break;
                case 7:                         // calculate P_ox
                    if (core_finish.read()) {
                        state.write(8);
                    }
                    else {
                        state.write(7);
                    }
                    break;
                case 8:                         // lamb_X
                    if (core_finish.read()) {
                        state.write(9);
                    }
                    else {
                        state.write(8);
                    }
                    break;
                case 9:                         // calculate tempy0
                    if (core_finish.read()) {
                        state.write(10);
                    }
                    else {
                        state.write(9);
                    }
                    break;
                case 10:                         // calculate P_oy
                    if (core_finish.read()) {
                        state.write(11);
                    }
                    else {
                        state.write(10);
                    }
                    break;
                case 11:                         
                    state.write(0);
                    break;
                default: 
                    break;
            }
        }
    }
    
    void sequ() {
        inv_x.write(inv_x.read());
        temp_lamb.write(temp_lamb.read());
        lamb.write(lamb.read());
        lamb_2.write(lamb_2.read());
        x_2.write(x_2.read());
        tempx0.write(tempx0.read());
        P_ox.write(P_ox.read());
        lamb_X.write(lamb_X.read());
        tempy0.write(tempy0.read());
        P_oy.write(P_oy.read());
        switch(state.read()) { 
            case 1: 
                inv_x.write(core_out.read());
                break;
            case 2: 
                temp_lamb.write(core_out.read());
                break;
            case 3:
                lamb.write(core_out.read());
                break;
            case 4:
                lamb_2.write(core_out.read());
                break;
            case 5:
                x_2.write(core_out.read());
                break;
            case 6:
                tempx0.write(core_out.read());
                break;
            case 7:
                P_ox.write(core_out.read());
                break;
            case 8:
                lamb_X.write(core_out.read());
                break;
            case 9:
                tempy0.write(core_out.read());
                break;
            case 10:
                P_oy.write(core_out.read());
                break;
            default: 
                break;
        }
    }
    
    void comb() {
        Px = P.read().range(15, 8);
        Py = P.read().range(7, 0);
        Px_sig.write(Px);
        Py_sig.write(Py);
        P_o.write(0);
        finish.write(0);
        pn_start.write(0);
        core_start.write(0);
        switch(state.read()) { 
            case 0: 
                if(start.read() == 1) {
                    pn_start.write(1);
                }
                P_neg.write(pn_P_o.read());
                eq_P.write(P.read());
                eq_Q.write(P_neg.read());
                if (pn_finish.read()) {
                    if (eq.read() || P.read()[16] == 1) {
                        P_o.write((1, P.read().range(15, 0)));
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
            case 1:
                core_start.write(1);
                core_mode.write(2);
                core_a.write(Px_sig.read());
                core_b.write(0);
                core_p.write(p.read());
                break;
            case 2: 
                core_start.write(1);
                core_mode.write(1);
                core_a.write(Py_sig.read());
                core_b.write(inv_x.read());
                core_p.write(p.read());
                break;
            case 3: 
                core_start.write(1);
                core_mode.write(0);
                core_a.write(Px_sig.read());
                core_b.write(temp_lamb.read());
                core_p.write(0);
                break;
            case 4: 
                core_start.write(1);
                core_mode.write(1);
                core_a.write(lamb.read());
                core_b.write(lamb.read());
                core_p.write(p.read());
                break;
            case 5: 
                core_start.write(1);
                core_mode.write(1);
                core_a.write(Px_sig.read());
                core_b.write(Px_sig.read());
                core_p.write(p.read());
                break;
            case 6: 
                core_start.write(1);
                core_mode.write(0);
                core_a.write(lamb_2.read());
                core_b.write(lamb.read());
                core_p.write(0);
                break;
            case 7: 
                core_start.write(1);
                core_mode.write(0);
                core_a.write(tempx0.read());
                core_b.write(a.read());
                core_p.write(0);
                break;
            case 8: 
                core_start.write(1);
                core_mode.write(1);
                core_a.write(lamb.read());
                core_b.write(P_ox.read());
                core_p.write(p.read());
                break;
            case 9: 
                core_start.write(1);
                core_mode.write(0);
                core_a.write(x_2.read());
                core_b.write(lamb_X.read());
                core_p.write(0);
                break;
            case 10: 
                core_start.write(1);
                core_mode.write(0);
                core_a.write(tempy0.read());
                core_b.write(P_ox.read());
                core_p.write(0);
                break;
            case 11:
                P_o.write((0, P_ox.read(), P_oy.read()));
                finish.write(1);
                break;
            default: 
                break;
        }
    }
    
    SC_CTOR(PD) : core0("CORE0"), pn0("PN0") {
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
        sensitive << P << P_neg << state << start << p << a;
        sensitive << pn_finish << pn_P_o << eq << Px_sig << Py_sig;
        sensitive << inv_x << temp_lamb;
        sensitive << lamb << lamb_2 << x_2 << lamb_X;
        sensitive << tempx0 << P_ox << tempy0 << P_oy;

        SC_METHOD(sequ);
        sensitive << clk.pos();
        sensitive << rst_n;
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
    sc_signal<bool> core_start, pn_start, pd_start;
    sc_signal<bool> core_finish, pn_finish, pd_finish;
    sc_signal<sc_biguint<8>> core_out;
    sc_signal<sc_biguint<17>> pn_P, pn_P_o, pd_P, pd_P_o;
    sc_signal<sc_biguint<8>> pd_a, pd_p;

    sc_signal<sc_biguint<17>> Q_neg;
    sc_signal<sc_biguint<17>> eq_P, eq_Q;

    sc_signal<sc_biguint<8>> Px_Qx, Py_Qy, inv_Px_Qx, lamb, lamb_2, Px_X, lamb_Px_X;
    sc_signal<sc_biguint<8>> tempx0, tempx1, tempx2, P_ox;
    sc_signal<sc_biguint<8>> tempy0, P_oy;
    sc_signal<sc_biguint<8>> core_a, core_b, core_p;

    sc_out<sc_biguint<17>> P_o;
    sc_out<bool> finish;

    PN pn0;
    PD pd0;
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
        // cout << "eq: " << eq.read() << endl;
        // cout << "P inf : " << (P.read()[16] == 1) << endl;
        // cout << "Q inf : " << (Q.read()[16] == 1) << endl;
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
                case 16:                         // point_doubling 
                    if (pd_finish.read()) {
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
            case 15:
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
        pd_start.write(0);
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
                Q_neg.write(pn_P_o.read());
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
                pd_start.write(1);
                pd_P.write(P.read());
                pd_a.write(a.read());
                pd_p.write(p.read());
                if (pd_finish.read()) {
                    P_o.write(pd_P_o.read());
                    finish.write(1);
                }
                else{
                    P_o.write(0);
                    finish.write(0);
                }
                break;
            default: 
                break;
        }
    }
    
    SC_CTOR(PA) : core0("CORE0"), pn0("PN0"), pd0("PD0") {
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

        pd0.clk(clk);
        pd0.rst_n(rst_n);
        pd0.start(pd_start);
        pd0.P(pd_P);
        pd0.a(pd_a);
        pd0.p(pd_p);
        pd0.P_o(pd_P_o);
        pd0.finish(pd_finish);


        SC_METHOD(equal);
        sensitive << eq_P << eq_Q;

        SC_METHOD(fsm);
        sensitive << clk.pos();
        sensitive << rst_n;

        SC_METHOD(comb);
        sensitive << P << Q << Q_neg << state << start << p << a;
        sensitive << pn_finish << pn_P_o << eq << Px_sig << Py_sig << Qx_sig << Qy_sig;
        sensitive << Px_Qx << Py_Qy << inv_Px_Qx;
        sensitive << lamb << lamb_2 << tempx0 << tempx1 << tempx2;
        sensitive << P_ox << Px_X << lamb_Px_X << tempy0 << P_oy;
        sensitive << pd_finish << pd_P_o;

        SC_METHOD(sequ);
        sensitive << clk.pos();
        sensitive << rst_n;
    }
};

SC_MODULE(SCALAR_MULT){
    sc_in<bool> clk, rst_n;
    sc_in<bool> start;
    sc_in<sc_biguint<8>> n;
    sc_in<sc_biguint<17>> P;
    sc_in<sc_biguint<8>> a, p;

    sc_out<sc_biguint<17>> P_o;
    sc_out<bool> finish;

    sc_signal<sc_biguint<17>> A;
    sc_signal<sc_biguint<17>> R;
    sc_signal<sc_bigint<8>> cnt;
    sc_signal<sc_uint<3>> state;

    sc_signal<bool> pa_start;
    sc_signal<sc_biguint<17>> pa_P, pa_Q;
    sc_signal<sc_biguint<8>> pa_a, pa_p;
    sc_signal<sc_biguint<17>> pa_P_o;
    sc_signal<bool> pa_finish;

    sc_signal<bool> pd_start;
    sc_signal<sc_biguint<17>> pd_P;
    sc_signal<sc_biguint<8>> pd_a, pd_p;
    sc_signal<sc_biguint<17>> pd_P_o;
    sc_signal<bool> pd_finish;

    PA pa0;
    PD pd0;

    void fsm() {
        // cout << state << endl;
        if (!rst_n.read()) {
            state.write(0);
        }
        else {
            if (state.read() == 0) {
                if (start.read() == 1) {
                    if (n.read()[0] == 1) {
                        state.write(1);
                    }
                    else {
                        state.write(2);
                    }
                }
                else {
                    state.write(0);
                }
            }
            else if (state.read() == 1) { // PA
                if (pa_finish.read() == 1) {
                    state.write(2);
                }
                else {
                    state.write(1);
                }
            }
            else if (state.read() == 2) { // PD
                if ((cnt.read() == 1 || cnt.read() == 2) && pd_finish.read() == 1) {
                    state.write(3);
                }
                else if (cnt.read()[1] == 1 && pd_finish.read() == 1) {
                    state.write(1);
                }
                else {
                    state.write(2);
                }
            }
            else {
                state.write(0);
            } 
        }
    }

    void count() {
        // cout << cnt << endl;
        if (!rst_n.read()) {
            cnt.write(0);
        }
        else {
            if (state.read() == 0) {
                if (start.read() == 1) {
                    cnt.write(n.read());
                }
                else {
                    cnt.write(0);
                }
            }
            else if (state.read() == 1) { // PA
                cnt.write(cnt.read());
            }
            else if (state.read() == 2) { // PD
                if ((cnt.read() == 1 || cnt.read() == 2) && pd_finish.read() == 1) {
                    cnt.write(0);
                }
                else if (pd_finish.read() == 1) {
                    cnt.write(cnt.read() >> 1);
                }
                else {
                    cnt.write(cnt.read());
                }
            }
            else {
                cnt.write(0);
            } 
        }
    }

    void done() {
        if (!rst_n.read()) {
            P_o.write(0);
            finish.write(0);
        }
        else {
            if (state.read() == 0) {
                P_o.write(0);
                finish.write(0);
            }
            else if (state.read() == 1) {
                P_o.write(0);
                finish.write(0);
            }
            else if (state.read() == 2) {
                if ((cnt.read() == 1 || cnt.read() == 2) && pd_finish.read() == 1) {
                    P_o.write(R.read());
                    finish.write(1);
                }
                else {
                    P_o.write(0);
                    finish.write(0);
                }
            }
            else {
                P_o.write(0);
                finish.write(0);
            } 
        }
    }

    void sequ() {
        // cout << "pa_finish " << pa_finish << endl;
        // cout << "pd_finish " << pd_finish << endl;
        if (!rst_n.read()) {
            A.write(0);
            R.write(0);
        }
        else {
            if (state.read() == 0) {
                A.write(P.read());
                R.write((1, P.read().range(15, 0)));
            }
            else if (state.read() == 1) {
                if (pa_finish.read() == 1) {
                    A.write(A.read());
                    R.write(pa_P_o.read());
                    // cout << "tmp1: ";
                    // cout << sc_bv<17>(pa_P_o.read()) << endl;
                }
                else {
                    A.write(A.read());
                    R.write(R.read());
                }
            }
            else if (state.read() == 2) {
                if (pd_finish.read() == 1) {
                    A.write(pd_P_o.read());
                    R.write(R.read());
                    // cout << "tmp2: ";
                    // cout << sc_bv<17>(pd_P_o.read()) << endl;
                }
                else {
                    A.write(A.read());
                    R.write(R.read());
                }
            }
            else {
                A.write(0);
                R.write(0);
            } 
        }
    }

    void comb() {
        pa_start.write(0);
        pa_P.write(0);
        pa_Q.write(0);
        pa_a.write(a.read());
        pa_p.write(p.read());
        pd_start.write(0);
        pd_P.write(0);
        pd_a.write(a.read());
        pd_p.write(p.read());
        if (state.read() == 0) {
            if (start.read() == 1) {
                if (n.read()[0] == 1) {
                    pa_start.write(1);
                    pa_P.write((1, P.read().range(15, 0)));
                    pa_Q.write(P.read());
                    pd_start.write(0);
                    pd_P.write(0);
                }
                else {
                    pa_start.write(0);
                    pa_P.write(0);
                    pa_Q.write(0);
                    pd_start.write(1);
                    pd_P.write(P.read());
                }
            }
            else {
                pa_start.write(0);
                pd_start.write(0);
                pa_P.write(0);
                pa_Q.write(0);
                pd_P.write(0);
            }
        }
        else if (state.read() == 1) {
            pa_start.write(1);
            pa_P.write(R.read());
            pa_Q.write(A.read());
            pd_start.write(0);
            pd_P.write(0);
        }
        else if (state.read() == 2) {
            pa_start.write(0);
            pa_P.write(0);
            pa_Q.write(0);
            pd_start.write(1);
            pd_P.write(A.read());
        }
        else {
            pa_start.write(0);
            pa_P.write(0);
            pa_Q.write(0);
            pd_start.write(0);
            pd_P.write(0);
        } 
    }

    SC_CTOR(SCALAR_MULT) : pa0("PA0"), pd0("PD0") {
        pa0.clk(clk);
        pa0.rst_n(rst_n);
        pa0.start(pa_start);
        pa0.P(pa_P);
        pa0.Q(pa_Q);
        pa0.a(pa_a);
        pa0.p(pa_p);
        pa0.P_o(pa_P_o);
        pa0.finish(pa_finish);

        pd0.clk(clk);
        pd0.rst_n(rst_n);
        pd0.start(pd_start);
        pd0.P(pd_P);
        pd0.a(pd_a);
        pd0.p(pd_p);
        pd0.P_o(pd_P_o);
        pd0.finish(pd_finish);

        SC_METHOD(fsm);
        sensitive << clk.pos();
        sensitive << rst_n;
        SC_METHOD(count);
        sensitive << clk.pos();
        sensitive << rst_n;
        SC_METHOD(done);
        sensitive << clk.pos();
        sensitive << rst_n;
        SC_METHOD(sequ);
        sensitive << clk.pos();
        sensitive << rst_n;
        SC_METHOD(comb);
        sensitive << a << p << R << A << state;
    }
};

SC_MODULE(ECC){
    sc_in_clk			   clk;
    sc_in<bool>	           rst_n;
    sc_in<sc_uint<8>>      P0;      // P0: input start signal
    sc_in<sc_uint<8>>      P1;      // P1: input data (n, P, a, p)
    sc_out<sc_uint<8>>     P2;      // P2: output result (P_o)
    sc_out<sc_uint<8>>     P3;      // P3: output valid signal

    sc_signal<bool> sm_start;
    sc_signal<sc_biguint<8>> sm_n;
    sc_signal<sc_biguint<17>> sm_P;
    sc_signal<sc_biguint<8>> sm_a, sm_p;
    sc_signal<sc_biguint<17>> sm_P_o;
    sc_signal<bool> sm_finish;

    sc_signal<sc_biguint<17>> P_o_r;
    sc_signal<sc_uint<8>> result;
    sc_signal<sc_uint<8>> valid;

    sc_signal<sc_uint<3>> state;
    sc_signal<sc_uint<3>> read_cnt;
    sc_signal<sc_uint<3>> write_cnt;

    SCALAR_MULT sm0;
        
    void fsm() {
        // cout << state << endl;
        if (!rst_n.read()) {
            state.write(0);
        }
        else {
            if (state.read() == 0) { // IDLE
                if (P0.read() == 1) {
                    state.write(1);
                }
                else {
                    state.write(0);
                }
            }
            else if (state.read() == 1) { // READ
                if (read_cnt.read() == 5) {
                    state.write(2);
                }
                else {
                    state.write(1);
                }
            }
            else if (state.read() == 2) { // CALC
                if (sm_finish.read() == 1) {
                    state.write(3);
                }
                else {
                    state.write(2);
                }
            }
            else { // WRITE
                if (write_cnt.read() == 2) {
                    state.write(0);
                }
                else {
                    state.write(3);
                }
            }
        }   
    }

    void counter() {
        if (!rst_n.read()) {
            read_cnt.write(0);
            write_cnt.write(0);
        }
        else {
            if (state.read() == 0) { // IDLE
                read_cnt.write(0);
                write_cnt.write(0);
            }
            else if (state.read() == 1) { // READ
                write_cnt.write(0);
                if (read_cnt.read() == 5) {
                    read_cnt.write(0);
                }
                else {
                    read_cnt.write(read_cnt.read() + 1);
                }
            }
            else if (state.read() == 2) { // CALC
                read_cnt.write(0);
                write_cnt.write(0);
            }
            else { // WRITE
                read_cnt.write(0);
                if (write_cnt.read() == 2) {
                    write_cnt.write(0);
                }
                else {
                    write_cnt.write(write_cnt.read() + 1);
                }
            }
        }
    }

    void read_data() {
        sm_start.write(0);
        sm_n.write(sm_n.read());
        sm_P.write(sm_P.read());
        sm_a.write(sm_a.read());
        sm_p.write(sm_p.read());
        if (!rst_n.read()) {
            sm_start.write(0);
            sm_n.write(0);
            sm_P.write(0);
            sm_a.write(0);
            sm_p.write(0);
        }
        else {
            if (state.read() == 1) {
                if (read_cnt.read() == 0) {
                    sm_n.write((P1.read()[7], P1.read().range(6, 0)));
                }
                else if (read_cnt.read() == 1) {
                    sm_P.write((P1.read()[0], sm_P.read().range(15, 0)));
                }
                else if (read_cnt.read() == 2) {
                    sm_P.write((sm_P.read()[16], P1.read(), sm_P.read().range(7, 0)));
                }
                else if (read_cnt.read() == 3) {
                    sm_P.write((sm_P.read().range(16, 8), P1.read()));
                }
                else if (read_cnt.read() == 4) {
                    sm_a.write((P1.read()[7], P1.read().range(6, 0)));
                }
                else if (read_cnt.read() == 5) {
                    sm_p.write((P1.read()[7], P1.read().range(6, 0)));
                    sm_start.write(1);
                }
            }
        }
    }

    void sm_out() {
        if (!rst_n.read()) {
            P_o_r.write(0);
        }
        else {
            if (sm_finish.read() == 1) {
                P_o_r.write(sm_P_o.read());
            }
            else {
                P_o_r.write(P_o_r.read());
            }
        }
    }

    void write_data() {
        result.write(result.read());
        valid.write(0);
        if (!rst_n.read()) {
            result.write(0);
            valid.write(0);
        }
        else {
            if (state.read() == 3) {
                if (write_cnt.read() == 0) {
                    result.write((result.read().range(7, 1), P_o_r.read()[16]));
                    valid.write(1);
                }
                else if (write_cnt.read() == 1) {
                    result.write((P_o_r.read()[15], P_o_r.read().range(14, 8)));
                    valid.write(1);
                }
                else if (write_cnt.read() == 2) {
                    result.write((P_o_r.read()[7], P_o_r.read().range(6, 0)));
                    valid.write(1);
                }
            }
            else {
                result.write(0);
                valid.write(0);
            }
        }    
    }

    void output() {
        P2.write(result.read());
        P3.write(valid.read());
    }

    SC_CTOR(ECC) : sm0("SM0") {
        sm0.clk(clk);
        sm0.rst_n(rst_n);
        sm0.start(sm_start);
        sm0.n(sm_n);
        sm0.P(sm_P);
        sm0.a(sm_a);
        sm0.p(sm_p);
        sm0.P_o(sm_P_o);
        sm0.finish(sm_finish);
        
        SC_METHOD(fsm);
        sensitive << clk.pos();
        sensitive << rst_n;
        SC_METHOD(counter);
        sensitive << clk.pos();
        sensitive << rst_n;
        SC_METHOD(read_data);
        sensitive << clk.pos();
        sensitive << rst_n;
        SC_METHOD(sm_out);
        sensitive << clk.pos();
        sensitive << rst_n;
        SC_METHOD(write_data);
        sensitive << clk.pos();
        sensitive << rst_n;
        SC_METHOD(output);
        sensitive << result << valid;
    }
};

SC_MODULE(ECC_mon){

    sc_in<bool> clk;
    sc_in<bool> rst_n;
    sc_in<sc_uint<8>> P0;
    sc_in<sc_uint<8>> P1;
    sc_in<sc_uint<8>> P2;
    sc_in<sc_uint<8>> P3;

    sc_signal<sc_uint<4>> cnt;
 
    void monitor() {
        if (rst_n == 0) {
            cnt.write(0);
            cout << sc_time_stamp() << "\t" << "RESET" << endl;
        }
        else if (P0 == sc_uint<8>(1) && cnt.read() <= 6) {
            if (cnt.read() == 0) cout << "start input..." << endl;
            cout << sc_time_stamp() << "\t\t" << sc_bv<8>(P0) << "\t" << sc_bv<8>(P1) << "\t" << sc_bv<8>(P2) << "\t" << sc_bv<8>(P3) << endl;
            cnt.write(cnt.read() + 1);
        }
        else if (P3 == sc_uint<8>(1)) {
            if (cnt.read() == 7) cout << "finish, output..." << endl;
            cout << sc_time_stamp() << "\t" << sc_bv<8>(P0) << "\t" << sc_bv<8>(P1) << "\t" << sc_bv<8>(P2) << "\t" << sc_bv<8>(P3) << endl;
            cnt.write(cnt.read() + 1);
            if (cnt.read() == 9) sc_stop();
        }
        else {
            // cout << sc_time_stamp() << "\t" << sc_bv<8>(P0) << "\t" << sc_bv<8>(P1) << "\t" << sc_bv<8>(P2) << "\t" << sc_bv<8>(P3) << endl;
        }
    }
  
    SC_CTOR(ECC_mon) {
        cout << endl << "time\t\tP0(start)\tP1(in_data)\tP2(out_data)\tP3(valid)" << endl;
        SC_METHOD(monitor);
        sensitive << clk.pos();
        dont_initialize();
    }

};



#endif