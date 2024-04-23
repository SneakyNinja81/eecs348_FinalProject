#include <iostream>
using namespace std;


int[] getinsidemostparent(std::string expression) {
  for (int i = 0; i < expression.length(); i++) {
    if (expression[i] == ')') {
      for (int j = i - 1; j >= 0; j--) {
        if (expression[j] == '(') {
          return [j,]
        }
      }
    }
  }
}

int main() {
  std:string expression = "(T | F) $ F";
  // find first ) then go forward to the next (
  // simplify that expression 
  int start = getinsidemostparent(expression)[0];
  int end = getinsidemostparent(expression)[1];

  std:

}
