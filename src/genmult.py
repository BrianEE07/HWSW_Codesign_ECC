
def genPE(i, tail):
    m_pre = f"r_o{i-1}"
    if (tail):
        m_pre = "gnd"
    print(f"        pe{i}.clk(clk);")     
    print(f"        pe{i}.rst_n(rst_n);")  
    print(f"        pe{i}.a(a);")          
    print(f"        pe{i}.b(b{i});")     
    print(f"        pe{i}.p(p{i});")     
    print(f"        pe{i}.m_pre({m_pre});")
    print(f"        pe{i}.isMul(isMul);")  
    print(f"        pe{i}.toMod(toMod);")  
    print(f"        pe{i}.out(r_o{i});")
    print()

if __name__ == "__main__" :
    bitnum = 12

    # dump code
    print("SC_MODULE(MULT){")
    ########
    print(f"    sc_in<bool> clk, rst_n;")
    print(f"    sc_in<bool> a;")
    print(f"    sc_in<sc_biguint<{bitnum}>> b, p;")
    print(f"    sc_in<bool> isMul;")
    print()
    print(f"    sc_signal<bool> b0", end='')
    for i in range(1, bitnum):
        print(f", b{i}", end='')
    print(";")
    print(f"    sc_signal<bool> p0", end='')
    for i in range(1, bitnum):
        print(f", p{i}", end='')
    print(";")
    print(f"    sc_signal<bool> gnd;")
    print(f"    sc_signal<bool> toMod;")
    print(f"    sc_signal<bool> r_o0", end='')
    for i in range(1, bitnum):
        print(f", r_o{i}", end='')
    print(";")
    print()
    print(f"    sc_out<sc_biguint<{bitnum}>> out;")
    print()
    print(f"    PE pe0", end='')
    for i in range(1, bitnum):
        print(f", pe{i}", end='')
    print(";")
    print()
    ########
    print("    void calc() {")
    for i in range(0, bitnum):
        print(f"        b{i}.write(b.read()[{i}]);")
    print()
    for i in range(0, bitnum):
        print(f"        p{i}.write(p.read()[{i}]);")
    print()
    print(f"        gnd.write(0);")
    print(f"        toMod.write(isMul.read() & r_o{bitnum-1}.read());")
    print()
    print(f"        out.write((sc_uint<1>(r_o{bitnum-1}.read())", end='')
    for i in range(bitnum - 2, -1, -1):
        print(f", sc_uint<1>(r_o{i}.read())", end='')
    print("));")
    print("    }")
    print()
    ########
    print(f"    SC_CTOR(MULT) : pe0(\"PE0\")", end='')
    for i in range(1, bitnum):
        print(f", pe{i}(\"PE{i}\")", end='')
    print(" {")
    genPE(0, True)
    for i in range(1, bitnum):
        genPE(i, False)
    print(f"        SC_METHOD(calc);")
    print(f"        sensitive << a << b << p << isMul << out;")
    print(f"        sensitive", end='')
    for i in range(0, bitnum):
        print(f" << b{i}", end='')
    print(";")
    print(f"        sensitive", end='')
    for i in range(0, bitnum):
        print(f" << p{i}", end='')
    print(";")
    print(f"        sensitive << gnd << toMod;")
    print(f"        sensitive", end='')
    for i in range(0, bitnum):
        print(f" << r_o{i}", end='')
    print(";")
    print("    }")
    print("};")
    print()