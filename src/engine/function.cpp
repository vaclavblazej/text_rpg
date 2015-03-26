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
  for (Expression * it : atributes){
    it->Destroy();
  }
}
ReturnVal *Function::getValue() const {
  return func(atributes);
}
