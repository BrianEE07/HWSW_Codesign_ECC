#include <iostream>
#include <fstream>

using namespace std;

struct point {
    bool *x;
    bool *y;
    bool is_inf;
    point(): is_inf(false) {}
};

void print (bool *a, int bitnum) {
    for (int i = bitnum - 1;i >= 0;--i) {
        cout << a[i];
    }
    cout << endl;
}

void print (point P, int bitnum) {
    cout << "(";
    for (int i = bitnum - 1;i >= 0;--i) {
        cout << P.x[i];
    }
    cout << ", ";
    for (int i = bitnum - 1;i >= 0;--i) {
        cout << P.y[i];
    }
    cout << ")" << endl;
}

// field arithmetic
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
    return c;
}

bool* inverse (bool *a, bool *p, int bitnum) {
    bool* c = multiplication(a, a, p, bitnum);
    bool* sqr = multiplication(a, a, p, bitnum);
    for (int i = 2;i < bitnum;++i) {
        sqr = multiplication(sqr, sqr, p, bitnum);
        c = multiplication(c, sqr, p, bitnum);
    }
    return c;
}

// point arithmetic
bool equal(point P, point Q, int bitnum) {
    bool eq = true;
    if (P.is_inf != Q.is_inf) return false;
    else if (P.is_inf && Q.is_inf) return true;
    else {
        for (int i = 0;i < bitnum;++i) {
            if (P.x[i] != Q.x[i] || P.y[i] != Q.y[i]) {
                eq = false;
                break;
            }
        }
    }
    return eq;
}

point point_negation (point P, int bitnum) {
    point P_o;
    P_o.x = P.x;
    P_o.y = addition(P.x, P.y, bitnum);
    return P_o;
}

point point_doubling (point P, bool *a, bool *p, int bitnum) {
    point P_o = P;
    point P_neg = point_negation(P, bitnum);
    if (equal(P, P_neg, bitnum) || P.is_inf) {
        P_o.is_inf = true;
    }
    else {
        bool *inv_x = inverse(P.x, p, bitnum);
        bool *lamb = addition(P.x, multiplication(P.y, inv_x, p, bitnum), bitnum);
        bool *lamb_2 = multiplication(lamb, lamb, p, bitnum);
        bool *x_2 = multiplication(P.x, P.x, p, bitnum);
        P_o.x = addition(addition(lamb_2, lamb, bitnum), a, bitnum);
        bool *lamb_X = multiplication(lamb, P_o.x, p, bitnum);
        P_o.y = addition(addition(x_2, lamb_X, bitnum), P_o.x, bitnum);
    }
    return P_o;
}

point point_addition (point P, point Q, bool *a, bool *p, int bitnum) {
    point P_o = P;
    point Q_neg = point_negation(Q, bitnum);
    if (!equal(P, Q, bitnum)) {
        if (equal(P, Q_neg, bitnum)) {
            P_o.is_inf = true;
        }
        else if (P.is_inf) {
            P_o = Q;
        }
        else if (Q.is_inf) {
            P_o = P;
        }
        else {
            bool *Px_Qx = addition(P.x, Q.x, bitnum);
            bool *Py_Qy = addition(P.y, Q.y, bitnum);
            bool *inv_Px_Qx = inverse(Px_Qx, p, bitnum);
            bool *lamb = multiplication(Py_Qy, inv_Px_Qx, p, bitnum);
            bool *lamb_2 = multiplication(lamb, lamb, p, bitnum);
            P_o.x = addition(addition(addition(lamb_2, lamb, bitnum), addition(P.x, Q.x, bitnum), bitnum), a, bitnum);
            bool *Px_X = addition(P.x, P_o.x, bitnum);
            bool *lamb_Px_X = multiplication(lamb, Px_X, p, bitnum);
            P_o.y = addition(addition(lamb_Px_X, P_o.x, bitnum), P.y, bitnum);
        }
    }
    else return point_doubling(P, a, p, bitnum);
    return P_o;
}

point scalar_multiplication (int n, point P, bool *a, bool *p, int bitnum) {
    point A = P;
    point R = P;
    R.is_inf = true;
    while (n > 0) {
        if (n % 2 == 1) {
            point tmp1 = point_addition(R, A, a, p, bitnum);
            R = tmp1;
        }
        n >>= 1;
        point tmp2 = point_doubling(A, a, p, bitnum);
        A = tmp2;
    }
    return R;
}


int main(void) {
    int bitnum = 8;

    // Read Pattern Px, Py, poly, a, b
    fstream fin;
    // fin.open("../pattern/pattern_163.txt", ios::in);
    fin.open("../pattern/pattern_8.txt", ios::in);
    if (!fin) {
        cerr << "Error: Can't open file!\n";
        exit(1);
    }

    string Px_str, Py_str, poly_str, a_str, b_str;
    fin >> Px_str;
    fin >> Py_str;
    fin >> poly_str;
    fin >> a_str;
    fin >> b_str;

    bool* Px = new bool [bitnum];
    bool* Py = new bool [bitnum];
    bool* poly = new bool [bitnum];
    bool* a = new bool [bitnum];
    bool* b = new bool [bitnum];

    for (int i = 0;i < bitnum;++i) {
        Px[bitnum - 1 - i] = bool(Px_str[i] - '0');
        Py[bitnum - 1 - i] = bool(Py_str[i] - '0');
        poly[bitnum - 1 - i] = bool(poly_str[i] - '0');
        a[bitnum - 1 - i] = bool(a_str[i] - '0');
        b[bitnum - 1 - i] = bool(b_str[i] - '0');
    }

    //// field arithmetic
    // cout << "Px: ";
    // print(Px, bitnum);
    // cout << "Py: ";
    // print(Py, bitnum);
    // cout << "poly: ";
    // print(poly, bitnum);
    bool* sum = addition(Px, Py, bitnum);
    cout << "sum: ";
    print(sum, bitnum);
    bool* mul = multiplication(Px, Py, poly, bitnum);
    cout << "mul: ";
    print(mul, bitnum);
    bool* inv = inverse(Px, poly, bitnum);
    cout << "inv: ";
    print(inv, bitnum);

    //// point arithmetic
    point P;
    point Q;
    P.x = Px;
    P.y = Py;
    Q.x = a;
    Q.y = b;
    // cout << "POINT NEG" << endl;
    // point P_neg = point_negation(P, bitnum);
    // print(P_neg, bitnum);
    // cout << "POINT DOUBLE" << endl;
    // point P_double = point_doubling(P, a, poly, bitnum);
    // print(P_double, bitnum);
    // cout << "POINT ADD" << endl;
    // point P_add = point_addition(P, P, a, poly, bitnum);
    // print(P_add, bitnum);
    cout << "POINT ADD" << endl;
    point P_add = point_addition(P, Q, a, poly, bitnum);
    print(P_add, bitnum);
    // cout << "POINT SCALARMULT" << endl;
    // point P_sca = scalar_multiplication(10, P, a, poly, bitnum);
    // print(P_sca, bitnum);

    // 密鑰交換
    int ka = 22; // bitnum-bit
    int kb = 77; // bitnum-bit
    cout << endl;
    cout << "ECC GF(2^" << bitnum << ")" << endl;
    cout << "y^3 + xy = x^3 + ax^2 + b" << endl;
    cout << "Px ";
    print(P.x, bitnum);
    cout << "Py ";
    print(P.y, bitnum);
    cout << "Assume Alice choose " << ka << " as private key and send ka*P to Bob as Alice's public key." << endl;
    cout << "Assume Bob choose " << kb << " as private key and send kb*P to Alice as Bob's public key." << endl;
    cout << "Bob received ka*P and apply kb*(ka*P), Alice received kb*P and apply ka*(kb*P)" << endl;
    point ka_P = scalar_multiplication(ka, P, a, poly, bitnum);
    point kb_P = scalar_multiplication(kb, P, a, poly, bitnum);
    point kb_ka_P = scalar_multiplication(kb, ka_P, a, poly, bitnum);
    point ka_kb_P = scalar_multiplication(ka, kb_P, a, poly, bitnum);
    print(kb_ka_P, bitnum);
    print(ka_kb_P, bitnum);
    if (equal(kb_ka_P, ka_kb_P, bitnum)) {
        cout << "Success!!" << endl;
    }
    else {
        cout << "Fail..." << endl;
    }
}
