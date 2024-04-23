#include <iostream>
#include <string>
using namespace std;

bool AND (bool a, bool b) {
    return a && b;
}

bool OR (bool a, bool b) {
    return a || b;
}

bool NAND (bool a, bool b) {
    return !(a && b);
}

bool NOR (bool a, bool b) {
    return !(a || b);
}

bool XOR (bool a, bool b) {
    return a ^ b;
}

void main () {
    string expr;
    cout << "Type the expression:\n"
    cin >> expr;
    bool ans = solve(expr);
    cout << "The expression is ", ans;
}

bool solve (string expr) {
    int length = expr.length() - 1;
    for (int i = 0; i < length; i++) {

    }