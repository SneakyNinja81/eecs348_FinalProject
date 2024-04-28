#include <iostream>
#include <string>
using namespace std;

int main() {
  string expr;
  cout << "Type the expression:\n";
  cin >> expr;
  int j = expr.find(")", 0);
  cout << "Found closing parenthesis at index: " + std::to_string(j) << "\n";
  return 0;
}