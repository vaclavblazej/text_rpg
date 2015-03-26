#include <vector>
using namespace std;
#include "expression.h"
#include "returnVal.h"
#include "function.h"

Function::Function(funcPtr arg, vector<Expression*> &atrs) {
  func = arg;
  atributes = atrs;
}
Function::~Function() {
  for (auto it = atributes.begin(); it != atributes.end(); ++it){
    (*it)->Destroy();
  }
}
ReturnVal *Function::getValue() const {
  return func(atributes);
}
