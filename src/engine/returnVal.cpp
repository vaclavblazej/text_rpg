#include "returnVal.h"

ReturnVal::ReturnVal(int arg):ing(arg),str(""){}

ReturnVal::ReturnVal(std::string arg):ing(2147483647),str(arg){}

std::string ReturnVal::getStr()const{
  return str;
}

int ReturnVal::getInt()const{
  return ing;
}

