#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <sstream>
using namespace std;
#include "method.h"
#include "constant.h"
#include "scriptFuncs.h"
#include "scenario.h"
#include "returnVal.h"
#include "word.h"
#include "menu.h"

//--------------------------------------------------------------------------Menu
Menu::Menu(string gameDirectory, string menuDirectory):good(true){
  DIR      = gameDirectory;
  MENU_DIR = menuDirectory;
  m_Scene = new Scenario(gameDirectory);
  string line, tmp;
  string file = DIR;
  file.append("scripts.txt");
  
  ifstream input;
  input.open (file.c_str(), ios::in);
  getline(input, tmp, ';');
  while(input.good()){
    getline(input, line, '=');
    expressions[line];
    getline(input, tmp, ';');
  }
  input.close();
  input.clear();
  
  input.open (file.c_str(), ios::in);
  getline(input, tmp, ';');
  while (true){
    string errMsg;
    bool skip = false;
    Expression* result = NULL;
    string x, strout;
    char next = '\0';
    int len = 0;
    if (!input.good()) break;
    getline(input, tmp, ';');
    tmp.append(" ;");
    istringstream is  ( tmp );
    istringstream iss ( tmp );
    getline(is, line, '=');
    if (line == tmp){
      errMsg = "expected =";
      skip = true;
    }
    if (Reserved(line)){
      errMsg = "Name of a script can not contain reserved word [";
      errMsg.append(line).append("]");
      skip = true;
    }
    iss >> x;
    while (iss.good()){
      strout.append(x).append(" ");
      iss >> x;
    }
    if (!skip){
      result = LoadFunction(is, next, len, errMsg);
      if (next != ';' && result != NULL){
        errMsg = "unexpected character";
        result->Destroy();
        result = NULL;
      }
    }
    if (!skip && result != NULL){
      expressions[line] = result;
      expressions[line]->Create();
    }else{
      good = false;
      len--;
      cout << "> mistake in macro syntax! (" << errMsg << ")" << endl;
      cout << strout << endl;
      for (unsigned int i = 0; i < line.length(); i++) cout << " ";
      cout << setw(len) << "^" << endl;
    }
  }
  input.close();
}
//-------------------------------------------------------------------------~Menu
Menu::~Menu(){
  for (map<string, Expression*>::iterator it = expressions.begin();
       it != expressions.end(); ++it){
    if (it->second != NULL) it->second->Destroy();
  }
  delete m_Scene;
}
//--------------------------------------------------------------------------Good
bool Menu::Good() const{
  return good;
}
//------------------------------------------------------------------LoadFunction
Expression* Menu::LoadFunction(istringstream & is, char &next, int &len, string &errMsg){
  len++;                                                          //cout << "[";
  string dummy, name;
  is >> name;                                                    //cout << name;
  if (is.good() && name.length() > 0 && name[0] == '"'){
    if (name[name.length()-1] != '"' || name.length() == 1){
      getline(is, dummy, '"');
      name.append(dummy);
    }else{
      name = name.substr( 0, name.length() - 1 );
    }
  }
  len += name.length();
  is >> next;                                                      //is.clear();
  len++;
  if (expressions[name] != NULL){                                 //cout << "]";
    return expressions[name];
  }
  vector<Expression*> atrs;
  if (next == '('){                                              //cout << next;
    while (is.good()){                                 //if (next == ')') break;
      Expression *res = LoadFunction(is, next, len, errMsg);
      if (res == NULL){
        for (vector<Expression*>::iterator it = atrs.begin();
             it != atrs.end(); ++it) (*it)->Destroy();
        return NULL;
      }
      atrs.push_back(res);
      res->Create();                                             //cout << next;
      if (next == ')'){
        len++;
        break;
      }
      if (next != ','){
        len += 2;
        errMsg = "expected ',' or ')' character";
        for (vector<Expression*>::iterator it = atrs.begin();
             it != atrs.end(); ++it) (*it)->Destroy();
        return NULL;
      }
    }
    if (next != ')' || !is.good()){
      errMsg = "expected ')' character";
      for (vector<Expression*>::iterator it = atrs.begin(); it != atrs.end(); ++it)
        (*it)->Destroy();
      return NULL;
    }
    is >> next;
  }                                                               //cout << "]";
  Expression* result = LoadMethod(name, atrs);
  if (result != NULL) return result;
  result = m_Scene->LoadMethod(name, atrs);
  if (result != NULL) return result;
  result = addScript(name, atrs);
  if (result != NULL) return result;
  stringstream digit(name);
  int number;
  if (digit >> number){
    result = new Constant(number);
  }else{
    if (name[0] == '"'){
      len++;
      name = name.substr( 1, name.length() - 1 );
      result = new Word(name);
    }else{
      len += 1-name.length();
      errMsg = "unknown function name '";
      errMsg.append(name).append("'");
    }
  }
  if (result && atrs.size() > 0){
    errMsg = "unnecessary arguments";
    delete result;
    result = NULL;
  }
  if (atrs.size() > 0){
    for (vector<Expression*>::iterator it = atrs.begin();
         it != atrs.end(); ++it) (*it)->Destroy();
  }
  return result;
}
//---------------------------------------------------------------------------Run
void Menu::Run(const char * commandFileName){
  string line;
  vector <Expression*> arg;
  arg.push_back(new Word(commandFileName));
	delete LoadPushMenu(arg);//commandFileName
	delete arg[0];
	arg.clear();
	if (expressions["init"]) delete expressions["init"]->getValue();
  bool b_Repeat = true;
  int found;
  while (b_Repeat){
    cout << PWD;
    found = 1;
    cin >> line;
    if (!cin.good()) break;
    if (line != ""){
      for (map<string, Expression*>::iterator it = alias.begin();
           it != alias.end(); ++it){
        if ((*it).first == line){
          found = 0;
          if(alias[line] != NULL) delete alias[line]->getValue();
          else found = 2;
          break;
        }
      }
      if (found == 1){
        cout << "command not known"  << endl;
        Simmilar();
    	}else if (found == 2){
        cout << "ERROR: macro not defined"  << endl;
    	}
    }
  }
  if (cin.eof()) cout << "quit" << endl;
}
//----------------------------------------------------------------------Simmilar
void Menu::Simmilar() const
{
  if (alias.size() > 0){
    cout << "did you mean: ";
    CommandList();
    cout << " ?" << endl;
  }
}
//-------------------------------------------------------------------CommandList
void Menu::CommandList() const
{
  map<string, Expression*>::const_iterator beg = alias.begin();
  map<string, Expression*>::const_iterator end = alias.end();
  map<string, Expression*>::const_iterator fir = (alias.size() > 0)?--alias.end():alias.end();
  map<string, Expression*>::const_iterator sec = (alias.size() > 1)?--(--alias.end()):alias.end();
  map<string, Expression*>::const_iterator it;
  for (it = beg; it != end; it++){
    cout << '[' << (*it).first << ']';
    if (it == sec){
      cout << " or ";
    }else if (it != sec && it != fir){
      cout << ", ";
    }
  }
}
//====================================================================LoadMethod
Expression *Menu::LoadMethod (string name, vector<Expression*> &atrs)
{
  if (name == "commands")  return new Method<Menu>(this, &Menu::Commands,     atrs);
  if (name == "printFile") return new Method<Menu>(this, &Menu::PrintFile,    atrs);
  if (name == "menu")      return new Method<Menu>(this, &Menu::LoadMenu,     atrs);
  if (name == "pushMenu")  return new Method<Menu>(this, &Menu::LoadPushMenu, atrs);
  if (name == "popMenu")   return new Method<Menu>(this, &Menu::ExitMenu,     atrs);
  return NULL;
}
//----------------------------------------------------------------------Commands
ReturnVal *Menu::Commands (vector<Expression*> atr)
{
  CommandList();
  return NULL;
}
//---------------------------------------------------------------------PrintFile
ReturnVal *Menu::PrintFile (vector<Expression*> atr)
{
  if (atr.size() > 0){
    ifstream input;
    string file = DIR;
    ReturnVal *ret = atr[0]->getValue();
    file.append(ret->getStr());
    cout << "opening: " << file << endl;
    input.open (file.c_str(), ios::in);
    delete ret;
    if(input.good()){
      string line;
      getline(input, line);
      while(input.good()){
        cout << line << endl;
        getline(input, line);
      }
      input.close();
      return new ReturnVal(1);
    }else{
      return new ReturnVal(0);
    }
  }
  return NULL;
}
//----------------------------------------------------------------------LoadMenu
ReturnVal *Menu::LoadMenu (vector<Expression*> atr)
{
  ifstream input;
  string line, garbage, attr;
  alias.clear();
  string file = MENU_DIR;
  if (atr.size() > 0){
    ReturnVal *ret = atr[0]->getValue();
    input.open (file.append(ret->getStr()).c_str(), ios::in);
    delete ret;
  }else{
    input.open (file.append("mainmenu").c_str(), ios::in);
  }
  if (!input.good()) return new ReturnVal(0);
  getline(input, PWD);
  PWD.append("$ ");
  getline(input, line, '=');
  input >> attr;
  getline(input, garbage);
  //cout << "Loading commands..." << endl;
  while (input.good()){
    alias.insert(pair<string, Expression*> (line, expressions[attr]));
    getline(input, line, '=');
    input >> attr;
  	getline(input, garbage);
  }
  input.close();
  return new ReturnVal(1);
}
//------------------------------------------------------------------LoadPushMenu
ReturnVal *Menu::LoadPushMenu (vector<Expression*> atr)
{
  ifstream input;
  string line, garbage, attr;
  alias.clear();
  string file = MENU_DIR;
  if (atr.size() > 0){
    ReturnVal *ret = atr[0]->getValue();
    file.append(ret->getStr());
    lifo.push_back(file.c_str());
    input.open    (file.c_str(), ios::in);
    delete ret;
  }else{
    return new ReturnVal(0);
  }
  if (!input.good()) return new ReturnVal(0);
  getline(input, PWD);
  PWD.append("$ ");
  getline(input, line, '=');
  input >> attr;
  getline(input, garbage);
  //cout << "Loading commands..." << endl;
  while (input.good()){
    alias.insert(pair<string, Expression*> (line, expressions[attr]));
    getline(input, line, '=');
    input >> attr;
  	getline(input, garbage);
  }
  input.close();
  return new ReturnVal(1);
}
//----------------------------------------------------------------------ExitMenu
ReturnVal *Menu::ExitMenu (vector<Expression*> atr)
{
  if (lifo.size() > 0){
    lifo.pop_back();
    delete LoadMenu(/*lifo[lifo.size()-1]*/);
  }else{
    cin.setstate(ios::eofbit);
  }
  return new ReturnVal(lifo.size());
}
//----------------------------------------------------------------------Reserved
bool Menu::Reserved(string line)
{
//scenario
  if ((line == "set")         ||
      (line == "increase")    ||
      (line == "resetVars")   ||
      (line == "listSaves")   ||
      (line == "save")        ||
      (line == "load")        ||
      (line == "newWorld")    ||
      (line == "delWorld")    ||
      (line == "printMap")    ||
      (line == "revealMap")   ||
      (line == "newPlayer")   ||
      (line == "delPlayer")   ||
      (line == "stats")       ||
      (line == "coords")      ||
      (line == "move")        ||
      (line == "port")        ||
      (line == "gItemRand")   ||
      (line == "gItemCust")   ||
      (line == "remItem")     ||
      (line == "listItems")   ||
      (line == "delItem")     ||
      (line == "crQuest")     ||
      (line == "listQuest")   ||
      (line == "chckQuest")   ||
      (line == "enc")         ||
      (line == "fightInfo")   ||
      (line == "fight")       ||
      (line == "showLoot")    ||
      (line == "takeLoot")    ||
      (line == "delLoot")     ||
      (line == "goods")       ||
      (line == "pay")         ||
      (line == "buyItem")     ||
      (line == "sellItem")    ||
      (line == "course")      ||
      (line == "quit")        ||
//menu
      (line == "commands")    ||
      (line == "printFile")   ||
      (line == "menu")        ||
      (line == "pushMenu")    ||
      (line == "popMenu")     ||
//scriptFunc
      (line == "eval")        ||
      (line == "max")         ||
      (line == "min")         ||
      (line == "sum")         ||
      (line == "avg")         ||
      (line == "mod")         ||
      (line == "gStr")        ||
      (line == "gInt")        ||
      (line == "if")          ||
      (line == "equal")       ||
      (line == "great")       ||
      (line == "switch")      ||
      (line == "rerand")      ||
      (line == "recust")      ||
      (line == "print")       ||
      (line == "while")       ||
      (line == "repeat")) return true;
  return false;
}












