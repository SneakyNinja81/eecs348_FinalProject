#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

char NOT(char a) {
    if (a == 'T') {
        return 'F';
    } else {
        return 'T';
    }
}

char AND(char a, char b) {
    if (a == 'T' && b == 'T') {
        return 'T';
    }
    return 'F';
}

char OR(char a, char b) {
    if (a == 'T' || b == 'T') {
        return 'T';
    }
    return 'F';
}

char NAND(char a, char b) {
    if (a == 'T' && b == 'T') {
        return 'F';
    }
    return 'T';
}

char XOR(char a, char b) {
    if ((a == 'T' && b == 'T') || (a == 'F' && b == 'F')) {
        return 'F';
    }
    return 'T';
}

int check_symbols(string expr, int i) {
  if ((expr[i - 1] == 'T' || expr[i - 1] == 'F' || expr[i - 1] == ')' || expr[i - 1] == '!') && (expr[i + 1] == 'T' || expr[i + 1] == 'F' || expr[i + 1] == '(' || expr[i + 1] == '!')){
    return 1;
  } else {
    return 0;
  }
}
// string add_parentheses_to_evaluatenotfirst(string expr) {
//   for (int i = 0; i < expr.length(); ++i) {
//     if (expr[i] == '!') {
//       expr.insert(i, "(");
//       expr.insert(i + 3, ")");
//       i += 2; // move i forward to account for the added characters
//     }
//   }
//   return expr;
// }
std::vector<int> find_inner_parentheses(string expr) {
  std::vector<int> indicies = {-1, -1};
  for (int i = 0; i < expr.length(); ++i) {
    // increase the counter until we reach the first closing parenthesis
    if (expr[i] == ')')
    {
      for (int j = i - 1; j >= 0; --j) {
        if (expr[j] == '(') {
          indicies =  {j, i};
          return indicies;
        }
      }
    }
  }
  return indicies;
}
string evlaute_nots(string expr) {
  // evualte nots from a single expression with parentheses
  for (int i = 0; i < expr.length(); ++i) {
    if (expr[i] == '!') {
      if (expr[i + 1] == 'T') {
        expr[i + 1] = 'F';
      } 
      else if (expr[i + 1] == 'F') {
        expr[i + 1] = 'T';
      }
      else
      {
        cout << "Invalid expression" << endl;
        throw std::invalid_argument("Invalid expression");
      }
      expr.erase(i, 1);
      --i; // decrement i to account for the removed character
    }
  }
  return expr;
}
string parse_expression_without_parentheses(string expr) {
  string ans = expr;
  ans = evlaute_nots(ans);
  cout << "The expression is " << ans << "\n";
  while (ans.length() > 1) {
    cout << "The length of the expression is " << ans.length() << "\n";
    cout << "The expression is " << ans << "\n";
    if ((expr[0] == 'T' || expr[0] == 'F') && (expr[2] == 'T' || expr[2] == 'F')) 
    {
      cout << "The operator is " << expr[1] << "\n";
      switch (expr[1]) {
          case '&':
              ans[1] = AND(expr[0], expr[2]);
              ans.erase(0, 1);
              ans.erase(1, 1);
              break;
          case '|':
              ans[1] = OR(expr[0], expr[2]);
              ans.erase(0, 1);
              ans.erase(1, 1);
              break;
          case '@':
              ans[1] = NAND(expr[0], expr[2]);
              ans.erase(0, 1);
              ans.erase(1, 1);;
              break;
          case '$':
              ans[1] = XOR(expr[0], expr[2]);
              ans.erase(0, 1);
              ans.erase(1, 1);
              break;
          default:
              cout << "Invalid expression" << endl;
              throw std::invalid_argument("Invalid expression");
              break;
        }
    }
    else
    {
      cout << "Invalid expression" << endl;
      throw std::invalid_argument("Invalid expression");
    }
  }
  return ans;
}
string parse_single_operator(string single_expr) {
  std::string ans;
  single_expr = evlaute_nots(single_expr);
  cout << "Single expression is " << single_expr << "\n";
  switch(single_expr.length()) {
    case 1:
      if (single_expr[0] == 'T' || single_expr[0] == 'F') {
        ans.push_back(single_expr[0]);
        return ans;
      }
      else {
        cout << "Invalid expression" << endl;
        throw std::invalid_argument("Invalid expression");
      }
    case 2:
      if (single_expr[0] == '!' && (single_expr[1] == 'F' || single_expr[1] == 'T')) {
        // convert output of not to a string
        ans.push_back(NOT(single_expr[1]));
        return ans;
    }
    case 3:
      switch (single_expr[1]) {
          case '&':
            ans.push_back(AND(single_expr[0], single_expr[2]));
            return ans;
          case '|':
            ans.push_back(OR(single_expr[0], single_expr[2]));
            return ans;
          case '@':
            ans.push_back(NAND(single_expr[0], single_expr[2]));
            return ans;
          case '$':
            ans.push_back(XOR(single_expr[0], single_expr[2]));
            return ans;
      }
    default:
      cout << "Invalid expression" << endl;
      throw std::invalid_argument("Invalid expression");
  }
}
string parse_expression(string expr) {
  // find if there are any sets of parentheses
  std:vector<int> indicies = find_inner_parentheses(expr);
  // if there are no parentheses just evaluate the expression
  if (indicies[0] == -1) {
    cout << "There are no parentheses in the expression" << endl;
    return parse_expression_without_parentheses(expr);
  }
  // otherwise evaluate the inner expression
  cout << "The index of the inner parentheses are " << indicies[0] << " and " << indicies[1] << "\n";
  string inner_expression = expr.substr(indicies[0] + 1, indicies[1] - indicies[0] - 1);
  cout << "The inner expression is " << inner_expression << "\n";
  string subexpression_evaluation = parse_expression(inner_expression);
  string new_expression = expr.substr(0, indicies[0]) + subexpression_evaluation + expr.substr(indicies[1] + 1, expr.length() - 1 - indicies[1]);
  cout << "The new expression is " << new_expression << "\n";
  // if the new expression is only one character return it
  if (new_expression.length() == 1) {
    return new_expression;
  }
  // recursively call this function
  return parse_expression(new_expression);
}
string parse(string expr) {
    string newExpr;
    unordered_set<char> operations =  {'&', '|', '!', '@', '$'};
    for (int i = 0; i < expr.length(); ++i) {
        if (operations.find(expr[i]) != operations.end()) {
          if (!check_symbols(expr, i)) {
            cout << "The expression is " << expr << "\n";
            cerr << "Error: Invalid symbols adjacent to operation.\n";
            return "";
          }
        }
        else {
            switch (expr[i]) {
                case '(':
                    {
                        int j = i + 1;
                        int level = 1;
                        while (j < expr.length() && level > 0) {
                            if (expr[j] == '(') {
                                level++;
                            } else if (expr[j] == ')') {
                                level--;
                            }
                            j++;
                        }
                        if (level > 0) {
                            cerr << "Error: Missing closing parenthesis." << endl;
                            return "";
                        }
                        string subExpr = expr.substr(i + 1, j - i - 2);
                        string parsedSubExpr = parse(subExpr);
                        newExpr += parsedSubExpr;
                        i = j - 1; // Update index to skip the processed substring
                        break;
                    }
                case ')':
                    cerr << "Error: Missing opening parenthesis." << endl;
                    return "";
                default:
                    newExpr += expr[i];
            }
      }
    }
    return newExpr;
}

string remove_spaces(string expr) {
    string newExpr;
    // go through each character if it is not a space add it to the new string
    for (int i = 0; i < expr.length(); ++i) {
        if (expr[i] != ' ') {
            newExpr += expr[i];
        }
    }
    return newExpr;
}
int main() {
    string expr;
    cout << "Type the expression:\n";
    std::getline(std::cin, expr);
    expr = remove_spaces(expr);
    string ans = parse_expression(expr);
    cout << "The expression is\n";
    cout << ans << "\n";
    // string ans = parse(expr);
    // if (ans == "") {
    //     return 1;
    // }
    // cout << "The expression is\n";
    // cout << ans[0] << "\n";
    return 0;
}