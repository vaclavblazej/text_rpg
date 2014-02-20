#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "expression.h"
#include "function.h"
#include "returnVal.h"
#include "scriptFuncs.h"

//=====================================================================addScript
Expression* addScript(string name, vector <Expression*> args){
  if (name == "eval")   return new Function(&evaluate,   args);
  if (name == "max")    return new Function(&maximum,    args);
  if (name == "min")    return new Function(&minimum,    args);
  if (name == "sum")    return new Function(&suma,       args);
  if (name == "avg")    return new Function(&average,    args);
  if (name == "mod")    return new Function(&modulo,     args);
  if (name == "gStr")   return new Function(&getString,  args);
  if (name == "gInt")   return new Function(&getInteger, args);
  if (name == "if")     return new Function(&condition,  args);
  if (name == "equal")  return new Function(&equal,      args);
  if (name == "great")  return new Function(&great,      args);
  if (name == "switch") return new Function(&options,    args);
  if (name == "rerand") return new Function(&randomArg,  args);
  if (name == "recust") return new Function(&customArg,  args);
  if (name == "print")  return new Function(&print,      args);
  if (name == "while")  return new Function(&cycle,      args);
  if (name == "repeat") return new Function(&repeat,     args);
  return NULL;
}
//======================================================================FUNTIONS

//----------------------------------------------------------------------evaluate
ReturnVal *evaluate (vector<Expression*> atr){
  ReturnVal *ret;
  for (unsigned int i = 0; i < atr.size(); i++){
    ret = atr[i]->getValue();
    delete ret;
  }
  return NULL;
}
//-----------------------------------------------------------------------maximum
ReturnVal *maximum (vector<Expression*> atr){
  int max = 0;
  ReturnVal *ret;
  for (unsigned int i = 0; i < atr.size(); i++){
    ret = atr[i]->getValue();
    if (ret != NULL){
      int val = ret->getInt();
      if (max < val)
        max = val;
      delete ret;
    }
  }
  return new ReturnVal(max);
}
//-----------------------------------------------------------------------minimum
ReturnVal *minimum (vector<Expression*> atr){
  if (atr.size() > 0){
    ReturnVal *ret;
    int min = 2147483647;
    for (unsigned int i = 0; i < atr.size(); i++){
      ret = atr[i]->getValue();
      if (ret != NULL){
        int val = ret->getInt();
        if (min > val)
          min = val;
        delete ret;
      }
    }
    return new ReturnVal(min);
  }else
    return new ReturnVal(0);
}
//--------------------------------------------------------------------------suma
ReturnVal *suma (vector<Expression*> atr){
  int sum = 0;
  ReturnVal *ret;
  for (unsigned int i = 0; i < atr.size(); i++){
    ret = atr[i]->getValue();
    if (ret != NULL) sum += ret->getInt();
    delete ret;
  }
  return new ReturnVal(sum);
}
//-----------------------------------------------------------------------average
ReturnVal *average (vector<Expression*> atr){
  int avg = 0;
  ReturnVal *ret;
  for (unsigned int i = 0; i < atr.size(); i++){
    ret = atr[i]->getValue();
    if (ret != NULL) avg += ret->getInt();
    delete ret;
  }
  return new ReturnVal(avg/(atr.size()?atr.size():1));
}
//------------------------------------------------------------------------modulo
ReturnVal *modulo (vector<Expression*> atr){
  int res = 0;
  if (atr.size() > 0){
    ReturnVal *ret;
    ret = atr[0]->getValue();
    if (ret != NULL) res = ret->getInt();
    delete ret;
    for (unsigned int i = 1; i < atr.size(); i++){
      ret = atr[i]->getValue();
      if (ret != NULL) res %= ret->getInt();
      delete ret;
    }
  }
  return new ReturnVal(res);
}
//---------------------------------------------------------------------getString
ReturnVal *getString (vector<Expression*> atr){
  string res;
  cin >> res;
  cin.ignore(1);// repairs double printing PWD issue
  return new ReturnVal(res);
}
//--------------------------------------------------------------------getInteger
ReturnVal *getInteger (vector<Expression*> atr){
  int res;
  cin >> res;
  while(cin.fail()){
    cin.clear();
    cin.ignore(20,'\n');
    cout << "Wrong input (again): ";
    cin >> res;
  }
  cin.ignore(1);// repairs double printing PWD issue
  return new ReturnVal(res);
}
//---------------------------------------------------------------------condition
ReturnVal *condition (vector<Expression*> atr){
  if (atr.size() == 3){
    ReturnVal *tmp = NULL;
    ReturnVal *ret = atr[0]->getValue();
    if (ret != NULL && (ret->getInt() != 2147483647))
      tmp = atr[(ret->getInt())?1:2]->getValue();
    delete ret;
    return tmp;
  }else if (atr.size() == 2){
    ReturnVal *tmp = NULL;
    ReturnVal *ret = atr[0]->getValue();
    if(ret != NULL && (ret->getInt() != 2147483647 && ret->getInt() != 0)){
      tmp = atr[1]->getValue();
    }
    delete ret;
    return tmp;
  }
  return NULL;
}
//-----------------------------------------------------------------------options
ReturnVal *options (vector<Expression*> atr){
  if (atr.size() > 0){
    ReturnVal *ret = atr[0]->getValue();
    if (ret != NULL){
      unsigned int result = ret->getInt() + 1;
      delete ret;
      if (atr.size() > result && atr[result] != NULL){
        ReturnVal *arg = atr[result]->getValue();
        return arg;
      }
    }
  }
  return NULL;
}
//-------------------------------------------------------------------------equal
ReturnVal *equal (vector<Expression*> atr){
  bool res = false;
  if (atr.size() == 2){
    ReturnVal *fir = atr[0]->getValue();
    ReturnVal *sec = atr[1]->getValue();
    if (fir == NULL || sec == NULL){
      delete sec;
      delete fir;
      return new ReturnVal(-1);
    }
    if (fir->getInt() != 2147483647 &&
        fir->getInt() == sec->getInt()) res = true;
    if (fir->getStr() != "" &&
        fir->getStr() == sec->getStr()) res = true;
    delete sec;
    delete fir;
  }
  return new ReturnVal((int)res);
}
//-------------------------------------------------------------------------great
ReturnVal *great (vector<Expression*> atr){
  bool res = false;
  if (atr.size() == 2){
    ReturnVal *fir = atr[0]->getValue();
    ReturnVal *sec = atr[1]->getValue();
    if (fir == NULL || sec == NULL){
      delete sec;
      delete fir;
      return new ReturnVal(-1);
    }
    if (fir->getInt() > sec->getInt()) res = true;
    delete sec;
    delete fir;
  }
  return new ReturnVal((int)res);
}
//---------------------------------------------------------------------randomArg
ReturnVal *randomArg (vector<Expression*> atr){
  if (atr.size() > 0){
    srand(time(NULL));
    int arg = rand()%atr.size();
    return atr[arg]->getValue();
  }
  return NULL;
}
//---------------------------------------------------------------------customArg
ReturnVal *customArg (vector<Expression*> atr){
  if (atr.size() > 0){
    ReturnVal *res = atr[0]->getValue();
    if (res == NULL) return new ReturnVal(-1);
    unsigned int idx = res->getInt();
    delete res;
    ReturnVal *ret = NULL;
    for (unsigned int i = 1; i < atr.size(); i++){
      res = atr[i]->getValue();
      if (idx == i) ret = res;
      else          delete res;
    }
    return ret;
  }
  return NULL;
}
//-------------------------------------------------------------------------print
ReturnVal *print (vector<Expression*> atr)
{
  ReturnVal *ret;
  for (unsigned int i = 0; i < atr.size(); i++){
    ret = atr[i]->getValue();
    if (ret == NULL) return new ReturnVal(-1);
    int intRet    = ret->getInt();
    string strRet = ret->getStr();
    if (intRet != 2147483647) cout << intRet;
    if (strRet != "")         cout << strRet;
    delete ret;
  }
  cout << endl;
  return NULL;
}
//-------------------------------------------------------------------------cycle
ReturnVal *cycle (vector<Expression*> atr)
{
  if (atr.size() > 0){
    int cond = 0;
    int counter = 0;
    ReturnVal *con = atr[0]->getValue();
    if (con == NULL) return new ReturnVal(-1);
    cond = con->getInt();
    delete con;
    while(!cond){
      counter++;
      ReturnVal *con = atr[0]->getValue();
      if (con == NULL) return new ReturnVal(-1);
      cond = con->getInt();
      delete con;
      for (unsigned int i = 1; i < atr.size(); i++){
        delete atr[i]->getValue();
      }
    }
  }
  return NULL;
}
//------------------------------------------------------------------------repeat
ReturnVal *repeat (vector<Expression*> atr)
{
  if (atr.size() > 0){
    ReturnVal *ret = atr[0]->getValue();
    if (ret == NULL) return new ReturnVal(-1);
    int times = ret->getInt();
    delete ret;
    for (int i = 0; i < times; i++){
      for (unsigned int i = 1; i < atr.size(); i++){
        ret = atr[i]->getValue();
        if (ret == NULL) return new ReturnVal(-1);
        delete ret;
      }
    }
    return new ReturnVal(times);
  }
  return NULL;
}
