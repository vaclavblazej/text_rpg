#include "returnVal.h"
#include "constant.h"
//----------------------------------------------------------------------Constant
Constant::Constant(int var):var(var){}
//---------------------------------------------------------------------~Constant
Constant::~Constant(){}
//----------------------------------------------------------------------getValue
ReturnVal *Constant::getValue() const
{
  return new ReturnVal(var);
}
