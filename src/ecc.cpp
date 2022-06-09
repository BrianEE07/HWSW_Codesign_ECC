#include <iostream>
#include <fstream>

using namespace std;

void print (bool *a, int bitnum) {
    for (int i = bitnum - 1;i >= 0;--i) {
        cout << a[i];
    }
    cout << endl;
}

bool* addition (bool *a, bool *b, int bitnum) {
    bool* c = new bool [bitnum];
    for (int i = 0;i < bitnum;++i) {
        c[i] = a[i] ^ b[i];
    }
    return c;
}

bool* multiplication (bool *a, bool *b, bool *p, int bitnum) {
    bool* c = new bool [bitnum]; // all 0
    bool mod_p = false;
    for (int i = bitnum - 1;i >= 0;--i) {
        c = (a[i]) ? addition(c, b, bitnum) : c;
        if (mod_p) {
            c = addition(c, p, bitnum);
            mod_p = false;
        }
        mod_p = c[bitnum - 1];
        if (i == 0) return c;
        for (int j = bitnum - 1;j >= 1;--j) {
            c[j] = c[j - 1];
        }
        c[0] = 0;
    }
}

bool* inverse () {

}

int main(void) {
    int bitnum = 8;

    // Read Pattern Px, Py
    fstream fin;
    // fin.open("pattern/pattern_163.txt", ios::in);
    fin.open("pattern/pattern_8.txt", ios::in);
    if (!fin) {
        cerr << "Error: Can't open file!\n";
        exit(1);
    }

    string Px_str, Py_str, poly_str;
    fin >> Px_str;
    fin >> Py_str;
    fin >> poly_str;

    bool* Px = new bool [bitnum];
    bool* Py = new bool [bitnum];
    bool* poly = new bool [bitnum];

    for (int i = 0;i < bitnum;++i) {
        Px[bitnum - 1 - i] = bool(Px_str[i] - '0');
        Py[bitnum - 1 - i] = bool(Py_str[i] - '0');
        poly[bitnum - 1 - i] = bool(poly_str[i] - '0');
    }

    // 
    cout << "Px: ";
    print(Px, bitnum);
    cout << "Py: ";
    print(Py, bitnum);
    cout << "poly: ";
    print(poly, bitnum);
    bool* sum = addition(Px, Py, bitnum);
    bool* mul = multiplication(Px, Py, poly, bitnum);
    cout << "sum: ";
    print(sum, bitnum);
    cout << "mul: ";
    print(mul, bitnum);
    // for (int i = 0;i < 256;i = i + 1) {
    //     bool* mul = multiplication(Px, Px, poly, bitnum);
    // }
}
