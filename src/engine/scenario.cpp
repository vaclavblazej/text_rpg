#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <sstream>
using namespace std;
#include "item.h"
#include "creature.h"
#include "ally.h"
#include "world.h"
#include "method.h"
#include "returnVal.h"
#include "battle.h"
#include "subQuest.h"
#include "subQuestPlace.h"
#include "container.h"
#include "quest.h"
#include "scenario.h"

//----------------------------------------------------------------------Scenario
Scenario::Scenario(string gameDirectory):m_World(NULL),
                                         m_Character(NULL),
                                         ally(NULL),
                                         m_Width(20),
                                         m_Height(20),
                                         encounter(vector <Creature*>()),
                                         m_Loot(vector <Item*>()),
                                         m_Quests(NULL),
                                         m_Battle(NULL)
{
  string dir = gameDirectory;
  saveDir = dir + "saves/";
  creaDir = dir + "creatures/";
  itemDir = dir + "items/";
  mapsDir = dir + "maps/";
  
  ifstream input;
  input.open ("./src/config.txt", ios::in);
  string command, parameter;
  getline(input, command, '=');
  while (input.good()){
    getline(input, parameter);
    istringstream is(parameter);
    is >> m_Options[command];
    getline(input, command, '=');
  }
  input.close();
  //Recepies
  string tmp = itemDir;
  tmp.append("recepies");
  input.open (tmp.c_str(), ios::in);
  getline(input, command);
  vector<string> from;
  vector<string> to;
  string temp = "";
  while (input.good()){
    from.clear();
    to.clear();
    istringstream is(command);
    is >> temp;
    if (is.good()){
      while (is.good() && temp != "="){
        to.push_back(temp);
        is >> temp;
      }
      while (is.good()){
        is >> temp;
        from.push_back(temp);
      }
      m_Planes.push_back(t_Planes(from, to));
    }
    getline(input, command);
  }
  input.close();
}
//---------------------------------------------------------------------~Scenario
Scenario::~Scenario()
{
  delete m_World;
  delete m_Character;
  delete m_Quests;
  delete m_Battle;
  for (vector <Item*>::const_iterator it = m_Loot.begin();
       it != m_Loot.end(); ++it) (*it)->RemRef();
  m_Loot.clear();
}
//====================================================================LoadMethod
Expression* Scenario::LoadMethod (string name, vector<Expression*> &param)
{
  if (name == "set")       return new Method<Scenario>(this, &Scenario::Set,          param);
  if (name == "increase")  return new Method<Scenario>(this, &Scenario::Increase,     param);
  if (name == "resetVars") return new Method<Scenario>(this, &Scenario::ResetVars,    param);
  if (name == "listSaves") return new Method<Scenario>(this, &Scenario::ListSaves,    param);
  if (name == "save")      return new Method<Scenario>(this, &Scenario::SaveScenario, param);
  if (name == "load")      return new Method<Scenario>(this, &Scenario::LoadScenario, param);
  if (name == "newWorld")  return new Method<Scenario>(this, &Scenario::CreateWorld,  param);
  if (name == "delWorld")  return new Method<Scenario>(this, &Scenario::DestroyWorld, param);
  if (name == "printMap")  return new Method<Scenario>(this, &Scenario::PrintWorld,   param);
  if (name == "revealMap") return new Method<Scenario>(this, &Scenario::DiscoverWorld,param);
  if (name == "newPlayer") return new Method<Scenario>(this, &Scenario::CreateChar,   param);
  if (name == "delPlayer") return new Method<Scenario>(this, &Scenario::DestroyChar,  param);
  if (name == "stats")     return new Method<Scenario>(this, &Scenario::PrintStats,   param);
  if (name == "coords")    return new Method<Scenario>(this, &Scenario::PrintXY,      param);
  if (name == "move")      return new Method<Scenario>(this, &Scenario::MovePlayer,   param);
  if (name == "port")      return new Method<Scenario>(this, &Scenario::PortPlayer,   param);
  if (name == "gItemRand") return new Method<Scenario>(this, &Scenario::GiveItem,     param);
  if (name == "gItemCust") return new Method<Scenario>(this, &Scenario::GiveCustItem, param);
  if (name == "remItem")   return new Method<Scenario>(this, &Scenario::RemoveItem,   param);
  if (name == "listItems") return new Method<Scenario>(this, &Scenario::ListItems,    param);
  if (name == "delItem")   return new Method<Scenario>(this, &Scenario::DelItem,      param);
  if (name == "crQuest")   return new Method<Scenario>(this, &Scenario::CreateQuest,  param);
  if (name == "listQuest") return new Method<Scenario>(this, &Scenario::ListQuest,    param);
  if (name == "chckQuest") return new Method<Scenario>(this, &Scenario::CheckQuests,  param);
  if (name == "enc")       return new Method<Scenario>(this, &Scenario::EnterEnc,     param);
  if (name == "fightInfo") return new Method<Scenario>(this, &Scenario::PrintFight,   param);
  if (name == "fight")     return new Method<Scenario>(this, &Scenario::FightAttack,  param);
  if (name == "showLoot")  return new Method<Scenario>(this, &Scenario::ShowLoot,     param);
  if (name == "takeLoot")  return new Method<Scenario>(this, &Scenario::TakeLoot,     param);
  if (name == "delLoot")   return new Method<Scenario>(this, &Scenario::FlushLoot,    param);
  if (name == "goods")     return new Method<Scenario>(this, &Scenario::Goods,        param);
  if (name == "pay")       return new Method<Scenario>(this, &Scenario::TakeGold,     param);
  if (name == "buyItem")   return new Method<Scenario>(this, &Scenario::Buy,          param);
  if (name == "sellItem")  return new Method<Scenario>(this, &Scenario::Sell,         param);
  if (name == "course")    return new Method<Scenario>(this, &Scenario::FrCourse,     param);
  if (name == "craft")     return new Method<Scenario>(this, &Scenario::Craft,        param);
  if (name == "quit")      return new Method<Scenario>(this, &Scenario::Quit,         param);
  return NULL;
}
//================================================================SCRIPT METHODS

//=====================================================================VARIABLES
//---------------------------------------------------------------------------Set
ReturnVal *Scenario::Set (vector<Expression*> atr)
{
  if (atr.size() > 0){
    ReturnVal *ret = atr[0]->getValue();
    if (ret == NULL) return new ReturnVal(-1);
    if (atr.size() > 1){
      ReturnVal *res = atr[1]->getValue();
      if (res != NULL) m_Variables[ret->getStr()] = res->getInt();
      delete res;
    }
    int val = m_Variables[ret->getStr()];
    delete ret;
    return new ReturnVal(val);
  }
  return NULL;
}
//----------------------------------------------------------------------Increase
ReturnVal *Scenario::Increase (vector<Expression*> atr)
{
  if (atr.size() > 0){
    ReturnVal *ret = atr[0]->getValue();
    if (ret == NULL) return new ReturnVal(-1);
    if (atr.size() > 1){
      ReturnVal *res = atr[1]->getValue();
      if (res != NULL) m_Variables[ret->getStr()] += res->getInt();
      delete res;
    }
    int val = m_Variables[ret->getStr()];
    delete ret;
    return new ReturnVal(val);
  }
  return NULL;
}
//---------------------------------------------------------------------ResetVars
ReturnVal *Scenario::ResetVars (vector<Expression*> atr)
{
  m_Variables.clear();
  return NULL;
}
//================================================================LOADING/SAVING
//---------------------------------------------------------------------ListSaves
ReturnVal *Scenario::ListSaves (vector<Expression*> atr)
{
  string commnad = "ls ";
  commnad.append(saveDir);
  system(commnad.c_str());
  return NULL;
}
//------------------------------------------------------------------SaveScenario
ReturnVal *Scenario::SaveScenario (vector<Expression*> atr)
{
  if (m_World  != NULL && m_Character != NULL &&
      m_Quests != NULL && atr.size()  == 1){
    string name, dir = saveDir;
    ReturnVal *ret = atr[0]->getValue();
    if (ret == NULL) return new ReturnVal(-1);
    name = ret->getStr();
    delete ret;
    dir.append(name).append(".txt");
    ofstream output;
    output.open (dir.c_str(), ios::out | ios::trunc);
    output << m_Variables.size() << endl;
    for (map <string, int>::const_iterator it = m_Variables.begin();
         it != m_Variables.end(); ++it){
      output << (*it).first << " " << (*it).second << endl;
    }
    m_Character->Save(output);
    m_World->Save(output);
    m_Quests->Save(output);
    output.close();
    return new ReturnVal(1);
  }else{
    return new ReturnVal(0);
  }
  return NULL;
}
//------------------------------------------------------------------LoadScenario
ReturnVal *Scenario::LoadScenario (vector<Expression*> atr)
{
  if (m_World  == NULL && m_Character == NULL &&
      m_Quests == NULL && atr.size() == 1){
    string dir = saveDir;
    string name;
    ReturnVal *ret = atr[0]->getValue();
    if (ret == NULL) return new ReturnVal(-1);
    name = ret->getStr();
    delete ret;
    dir.append(name);
    dir.append(".txt");
    ifstream input;
    input.open (dir.c_str(), ios::in);
    if (!input.good()) return new ReturnVal(0);
    m_Variables.clear();
    int size;
    input >> size;
    for (int i = 0; i < size; i++){
      string line;
      getline(input, line);
      istringstream is(line);
      int number;
      string name;
      input >> name >> number;
      m_Variables[name] = number;
    }
    string line;
    getline(input, line);
    istringstream iss(line);
    m_Character = new Creature();
    m_Character->Load(input);
    getline(input, line);
    istringstream is(line);
    is.str(line);
    is >> m_Width >> m_Height;
    m_World = new World(m_Width, m_Height, creaDir, itemDir);
    m_World->Load(input);
    m_Quests = new Container(m_World, m_Character);
    m_Quests->Load(input);
    input.close();
    return new ReturnVal(1);
  }
  return NULL;
}
//===========================================================WORLD AND CHARACTER
//-------------------------------------------------------------------CreateWorld
ReturnVal *Scenario::CreateWorld (vector<Expression*> atr)
{
  if (m_World == NULL){
    if (atr.size() == 2 || atr.size() == 3){
      string filename = mapsDir;
      if (atr.size() == 3){
        ReturnVal *retStr = atr[2]->getValue();
        if (retStr == NULL) return new ReturnVal(-1);
        filename.append(retStr->getStr());
        delete retStr;
      }
      ReturnVal *retOne = atr[0]->getValue();
      ReturnVal *retTwo = atr[1]->getValue();
      if (retOne == NULL || retTwo == NULL){
        delete retOne;
        delete retTwo;
        return new ReturnVal(-1);
      }
      m_Width  = retOne->getInt();
      m_Height = retTwo->getInt();
      delete retOne;
      delete retTwo;
      cout << filename << endl;
      ifstream input(filename.c_str());
      string line;
      getline(input, line);
      while (input.good()){
        stringstream ss(line);
        int    num;
        string col;
        char   mark;
        ss >> num >> col >> mark;
        string color = "\033[";
        if (col.length() > 0 && col[0] == 'B'){
          col = col.substr( 1, col.length() - 1 );
          color.append("1");
        }else{
          color.append("0");
        }
        color.append(";");
        if (col.length() > 0 && col[0] == 'Q'){
          col = col.substr( 1, col.length() - 1 );
          color.append("4");
        }else{
          color.append("3");
        }
              if (col == "black" ){ color.append("0");
        }else if (col == "red"   ){ color.append("1");
        }else if (col == "green" ){ color.append("2");
        }else if (col == "yellow"){ color.append("3");
        }else if (col == "blue"  ){ color.append("4");
        }else if (col == "purple"){ color.append("5");
        }else if (col == "azure" ){ color.append("6");
        }else if (col == "gray"  ){ color.append("7");
        }else if (col == "white" ){ color.append("9");
        }
        color.append("m");
        cout << color;
        cout << line;
        cout << "\033[0;39m";
        cout << endl;
        getline(input, line);
      }
      input.close();
      if (m_Width >= 10 && m_Height >= 10){
        m_World  = new World(m_Width, m_Height, creaDir, itemDir);
        m_Quests = new Container(m_World, m_Character);
      }
    }
    return new ReturnVal(1);
  }else{
    return new ReturnVal(0);
  }
}
//------------------------------------------------------------------DestroyWorld
ReturnVal *Scenario::DestroyWorld (vector<Expression*> atr)
{
  if (m_World != NULL && m_Quests != NULL){
    delete m_World;
    m_World = NULL;
    delete m_Quests;
    m_Quests = NULL;
    return new ReturnVal(1);
  }else{
    return new ReturnVal(0);
  }
  return NULL;
}
//--------------------------------------------------------------------PrintWorld
ReturnVal *Scenario::PrintWorld (vector<Expression*> atr)
{
  if (m_World != NULL){
    if (m_Character != NULL){
      string name;
      int x, y, l;
      m_Character->GetInfo(name, x, y, l);
      m_World->Paint(x, y, m_Options["COLOR"], m_Quests->GetChanges());
      return new ReturnVal(1);
    }else{
      m_World->Paint(-1, -1, m_Options["COLOR"], m_Quests->GetChanges());
      return new ReturnVal(-1);
    }
  }else{
    return new ReturnVal(0);
  }
}
//-----------------------------------------------------------------DiscoverWorld
ReturnVal *Scenario::DiscoverWorld (vector<Expression*> atr)
{
  if (m_World != NULL){
    if (atr.size() == 1){
      ReturnVal *rad   = atr[0]->getValue();
      if (rad == NULL) return new ReturnVal(-1);
      string name;
      int x, y, l;
      m_Character->GetInfo(name, x, y, l);
      m_World->Discover(x, y, rad->getInt());
      delete rad;
    }else if (atr.size() == 3){
      ReturnVal *x   = atr[0]->getValue();
      ReturnVal *y   = atr[1]->getValue();
      ReturnVal *rad = atr[2]->getValue();
      if (x == NULL || y == NULL || rad == NULL){
        delete x;
        delete y;
        delete rad;
        return new ReturnVal(-1);
      }
      m_World->Discover(x->getInt(), y->getInt(), rad->getInt());
      delete x;
      delete y;
      delete rad;
    }else if (atr.size() == 0){
      m_World->Discover();
    }
    return new ReturnVal(1);
  }else{
    return new ReturnVal(0);
  }
}
//--------------------------------------------------------------------CreateChar
ReturnVal *Scenario::CreateChar (vector<Expression*> atr)
{
  if (m_Character == NULL){
    if (atr.size() > 4){
      ReturnVal *retName = atr[0]->getValue();
      ReturnVal *retCls  = atr[1]->getValue();
      ReturnVal *retHp   = atr[2]->getValue();
      ReturnVal *retStr  = atr[3]->getValue();
      ReturnVal *retAgi  = atr[4]->getValue();
      ReturnVal *retInt  = atr[5]->getValue();
      bool flag = false;
      if ( retName != NULL && retCls  != NULL && retHp  != NULL && 
           retStr  != NULL && retAgi  != NULL && retInt != NULL){
        m_Character = new Creature(retName->getStr(),
                                   rand()%m_Width, rand()%m_Height, 0,
                                   retCls->getInt(),
                                   retHp->getInt(),
                                   retStr->getInt(),
                                   retAgi->getInt(),
                                   retInt->getInt());
        flag = true;
      }
      delete retName;
      delete retCls;
      delete retHp;
      delete retStr;
      delete retAgi;
      delete retInt;
      if (flag) return new ReturnVal(1);
      return new ReturnVal(-1);
    }
  }else{
    return new ReturnVal(0);
  }
  return NULL;
}
//-------------------------------------------------------------------DestroyChar
ReturnVal *Scenario::DestroyChar (vector<Expression*> atr)
{
  if (m_Character != NULL){
    delete m_Character;
    m_Character = NULL;
    return new ReturnVal(1);
  }else{
    return new ReturnVal(0);
  }
}
//--------------------------------------------------------------------PrintStats
ReturnVal *Scenario::PrintStats (vector<Expression*> atr)
{
  if (m_Character != NULL){
    m_Character->PrintStats();
    return new ReturnVal(1);
  }
  return NULL;
}
//-----------------------------------------------------------------------PrintXY
ReturnVal *Scenario::PrintXY (vector<Expression*> atr)
{
  if (m_Character != NULL){
    string name;
    int x, y, l;
    m_Character->GetInfo(name, x, y, l);
    cout << "[" << x << ", " << y << "]" << endl;
    return NULL;
  }
  return NULL;
}
//======================================================================MOVEMENT
//--------------------------------------------------------------------MovePlayer
ReturnVal *Scenario::MovePlayer (vector<Expression*> atr)
{
  if (atr.size() == 2 && m_World != NULL && m_Character != NULL){
    string name;
    int x, y, l;
    m_Character->GetInfo(name, x, y, l);
    ReturnVal *retX = atr[0]->getValue();
    ReturnVal *retY = atr[1]->getValue();
    if (retX == NULL || retY == NULL) return new ReturnVal(-1);
    x = (x + retX->getInt() + m_Width)  % m_Width;
    y = (y + retY->getInt() + m_Height) % m_Height;
    int code = m_World->GetCode(x, y);
    cout << "kód: " << code << endl;
    if (code != 6 && code != 7){//omezení pohybu
      m_Character->MoveBy(retX->getInt(), retY->getInt(), m_Width, m_Height);
    }
    delete retX;
    delete retY;
    m_Character->GetInfo(name, x, y, l);
    encounter = m_World->GetCreatures(x, y);
    alliesMet = m_World->GetAllies(x, y);
    return new ReturnVal(1);
  }
  return NULL;
}
//--------------------------------------------------------------------PortPlayer
ReturnVal *Scenario::PortPlayer (vector<Expression*> atr)
{
  if (atr.size() == 2 && m_World != NULL){
    ReturnVal *X = atr[0]->getValue();
    ReturnVal *Y = atr[1]->getValue();
    if (X == NULL || Y == NULL){
      delete X;
      delete Y;
      return new ReturnVal(-1);
    }
    int toX = ((X->getInt() % m_Width) + m_Width)  % m_Width;
    int toY = ((Y->getInt() % m_Width) + m_Height) % m_Height;
    m_Character->MoveTo(toX, toY);
    delete X;
    delete Y;
    encounter = m_World->GetCreatures(toX, toY);
    return new ReturnVal(encounter.size());
  }
  return NULL;
}
//=========================================================================ITEMS
//----------------------------------------------------------------------GiveItem
ReturnVal *Scenario::GiveItem (vector<Expression*> atr){
  if (m_Character != NULL){
    m_Character->GiveItem(m_World->CreateItem());
    return new ReturnVal(1);
  }else{
    return new ReturnVal(0);
  }
}
//------------------------------------------------------------------GiveCustItem
ReturnVal *Scenario::GiveCustItem (vector<Expression*> atr){
  if (m_Character != NULL){
    if (atr.size() > 5){
      ReturnVal *retName = atr[0]->getValue();
      ReturnVal *retHp   = atr[1]->getValue();
      ReturnVal *retStr  = atr[2]->getValue();
      ReturnVal *retAgi  = atr[3]->getValue();
      ReturnVal *retInt  = atr[4]->getValue();
      ReturnVal *retRng  = atr[5]->getValue();
      bool flag = false;
      if (retName != NULL && retHp  != NULL && retStr != NULL &&
          retAgi  != NULL && retInt != NULL && retRng != NULL){
        /*m_Character->GiveItem(new Item(retName->getStr(),
                                       retHp->getInt(),
                                       retStr->getInt(),
                                       retAgi->getInt(),
                                       retInt->getInt(),
                                       bool(retRng->getInt())));*/
        flag = true;
      }
      delete retName;
      delete retHp;
      delete retStr;
      delete retAgi;
      delete retInt;
      delete retRng;
      if (flag) return new ReturnVal(1);
      return new ReturnVal(-1);
    }
  }else{
    return new ReturnVal(0);
  }
  return NULL;
}
//--------------------------------------------------------------------RemoveItem
ReturnVal *Scenario::RemoveItem (vector<Expression*> atr){
  if (m_Character != NULL){
    ReturnVal *ret = atr[0]->getValue();
    if (ret == NULL) return new ReturnVal(-1);
    Item *item = m_Character->HandItem(ret->getInt());
    delete ret;
    if (item == NULL) return new ReturnVal(0);
    m_Loot.push_back(item);
    return new ReturnVal(1);
  }
  return NULL;
}
//---------------------------------------------------------------------ListItems
ReturnVal *Scenario::ListItems (vector<Expression*> atr)
{
  int course = 0;
  if (atr.size() == 1) {
    ReturnVal *ret = atr[0]->getValue();
    if (ret == NULL) return new ReturnVal(-1);
    course = ret->getInt();
    delete ret;
  }
  if (m_Character != NULL) m_Character->PrintItems(course);
  return NULL;
}
//-----------------------------------------------------------------------DelItem
ReturnVal *Scenario::DelItem (vector<Expression*> atr)
{
  if (m_Character != NULL && atr.size() == 1) {
    bool res;
    ReturnVal *ret = atr[0]->getValue();
    if (ret == NULL) return new ReturnVal(-1);
    res = m_Character->DelItem(ret->getInt());
    delete ret;
    return new ReturnVal(int(res));
  }
  return NULL;
}
//========================================================================QUESTS
//-------------------------------------------------------------------CreateQuest
ReturnVal *Scenario::CreateQuest (vector<Expression*> atr)
{
  if (m_Quests != NULL && m_World != NULL && m_Character != NULL){
    vector <Subquest*> quests;
    string name;
    int x, y, l;
    m_Character->GetInfo(name, x, y, l);
    quests.push_back(new SubquestPlace(m_World, m_Character,
                                       rand()%m_Width, rand()%m_Height));
    if (rand()%2)quests.push_back(new SubquestPlace(m_World, m_Character, x, y));
    Quest* quest = new Quest(m_World, m_Character, quests);
    m_Quests->AddQuest(quest);
    return new ReturnVal(1);
  }
  return NULL;
}
//---------------------------------------------------------------------ListQuest
ReturnVal *Scenario::ListQuest (vector<Expression*> atr)
{
  if (m_Quests != NULL){
    m_Quests->Print(cout);
    return new ReturnVal(1);
  }
  return NULL;
}
//-------------------------------------------------------------------CheckQuests
ReturnVal *Scenario::CheckQuests (vector<Expression*> atr)
{
  if (m_Quests != NULL){
    return new ReturnVal(m_Quests->Check());
  }
  return NULL;
}
//=========================================================================FIGHT
//----------------------------------------------------------------------EnterEnc
ReturnVal *Scenario::EnterEnc (vector<Expression*> atr)
{
  if (encounter.size() > 0){
    if (m_Battle == NULL) m_Battle = new Battle(m_Character, encounter[0]);
    ally = NULL;
    return new ReturnVal(0);
  }else if(alliesMet.size() > 0){
    ally = alliesMet[0];
    return new ReturnVal(1);
  }
  return NULL;
}
//--------------------------------------------------------------------PrintFight
ReturnVal *Scenario::PrintFight (vector<Expression*> atr)
{
  if (m_Battle != NULL){
    cout << "--You-----------" << endl;
    m_Battle->m_First->PrintStats();
    cout << "--Enemy---------" << endl;
    m_Battle->m_Second->PrintStats();
  }
  return NULL;
}
//-------------------------------------------------------------------FightAttack
ReturnVal *Scenario::FightAttack (vector<Expression*> atr)
{
  if (m_Battle != NULL && atr.size() >= 3){
    bool f = false;
    if (atr.size() >= 4){
      ReturnVal *flee = atr[3]->getValue();
      if (flee == NULL) return new ReturnVal(-1);
      if (flee->getInt()) f = true;
      delete flee;
    }
    ReturnVal *crit  = atr[0]->getValue();
    ReturnVal *block = atr[1]->getValue();
    ReturnVal *dodge = atr[2]->getValue();
    bool flag = false;
    int ret = 0;
    if (crit != NULL && block != NULL && dodge != NULL){
      ret = m_Battle->Fight(crit->getInt(), block->getInt(),
                                dodge->getInt(), f);
      flag = true;
    }
    delete crit;
    delete block;
    delete dodge;
    if (!flag) return new ReturnVal(-1);
    if (ret == 0) return NULL;
    if (ret != 3){
      vector <Item *> tmpLoot = m_World->KillMob(m_Battle->m_Second);
      for (vector <Item *>::iterator it = tmpLoot.begin();
           it != tmpLoot.end(); ++it){
        m_Loot.push_back(*it);
        (*it)->AddRef();
      }
      tmpLoot.clear();
      m_Battle->m_Second = NULL;
      for (vector <Creature*>::const_iterator it = encounter.begin();
           it != encounter.end(); ++it) delete *it;
      encounter.clear();
    }
    delete m_Battle;
    m_Battle = NULL;
    return new ReturnVal(ret-1);
  }
  return NULL;
}
//================================================================LOOT MANAGMENT
//----------------------------------------------------------------------ShowLoot
ReturnVal *Scenario::ShowLoot (vector<Expression*> atr)
{
  for (vector <Item*>::const_iterator it = m_Loot.begin();
       it != m_Loot.end(); ++it){
    cout << it-m_Loot.begin()+1 << ")";
    (*it)->PrintCompact();
    cout << endl;
  }
  return NULL;
}
//----------------------------------------------------------------------TakeLoot
ReturnVal *Scenario::TakeLoot (vector<Expression*> atr)
{
  int res = 0;
  for (vector <Item*>::const_iterator it = m_Loot.begin();
       it != m_Loot.end(); ++it){
    (*it)->AddRef();
    res = m_Character->GiveItem(*it);
  }
  for (vector <Item*>::const_iterator it = m_Loot.begin();
       it != m_Loot.end(); ++it) (*it)->RemRef();
  m_Loot.clear();
  return new ReturnVal(res);
}
//---------------------------------------------------------------------FlushLoot
ReturnVal *Scenario::FlushLoot (vector<Expression*> atr)
{
  for (vector <Item*>::const_iterator it = m_Loot.begin();
       it != m_Loot.end(); ++it) (*it)->RemRef();
  m_Loot.clear();
  return NULL;
}
//=============================================================FRIENDLY CREATURE
//-------------------------------------------------------------------------Goods
ReturnVal *Scenario::Goods (vector<Expression*> atr)
{
  if (ally){
    ally->PrintItems(100);
    return new ReturnVal(1);
  }else{
    return new ReturnVal(0);
  }
}
//----------------------------------------------------------------------TakeGold
ReturnVal *Scenario::TakeGold (vector<Expression*> atr)
{
  if (atr.size() > 0 && m_Character){
    ReturnVal *gld = atr[0]->getValue();
    if (gld == NULL) return new ReturnVal(-1);
    int gold = gld->getInt();
    delete gld;
    if (m_Character->ChangeGold( - int(gold))){
      return new ReturnVal(1);
    }else{
      return new ReturnVal(0);
    }
  }
  return NULL;
}
//---------------------------------------------------------------------------Buy
ReturnVal *Scenario::Buy (vector<Expression*> atr)
{
  if (atr.size() > 0 && ally && m_Character){
    ReturnVal *idx = atr[0]->getValue();
    if (idx == NULL) return new ReturnVal(-1);
    Item *item = ally->HandItem(idx->getInt());
    delete idx;
    if (!item) return new ReturnVal(0);
    int course = 100;
    if (atr.size() > 1){
      ReturnVal *crs = atr[1]->getValue();
      if (crs == NULL) return new ReturnVal(-1);
      course = crs->getInt();
      delete crs;
    }
    if (m_Character->ChangeGold( - int(item->GetCost()*course/100.))){
      m_Character->GiveItem(item);
      return new ReturnVal(1);
    }else{
      ally->GiveItem(item);
      return new ReturnVal(2);
    }
  }
  return NULL;
}
//--------------------------------------------------------------------------Sell
ReturnVal *Scenario::Sell (vector<Expression*> atr)
{
  if (atr.size() > 0 && ally && m_Character){
    ReturnVal *idx = atr[0]->getValue();
    if (idx == NULL) return new ReturnVal(-1);
    Item *item = m_Character->HandItem(idx->getInt());
    delete idx;
    if (!item) return new ReturnVal(0);
    int course = 100;
    if (atr.size() > 1){
      ReturnVal *crs = atr[1]->getValue();
      if (crs == NULL) return new ReturnVal(-1);
      course = crs->getInt();
      delete crs;
    }
    m_Character->ChangeGold(int(item->GetCost()*course/100.));
    ally->GiveItem(item);
    return new ReturnVal(1);
  }
  return NULL;
}
//----------------------------------------------------------------------FrCourse
ReturnVal *Scenario::FrCourse (vector<Expression*> atr)
{
  if (alliesMet.size() > 0){
    return new ReturnVal(ally->Course());
  }
  return NULL;
}
//======================================================================CRAFTING
//-------------------------------------------------------------------------Craft
ReturnVal *Scenario::Craft      (vector<Expression*> atr)
{
  if (atr.size() > 0 && m_Character != NULL && m_World != NULL){
    cout << "recepty:" << endl;
    cout << "0) exit" << endl;
    vector<t_Planes>tmp_Planes;
    for (vector<t_Planes>::const_iterator it = m_Planes.begin();
         it != m_Planes.end(); ++it){
      bool ok = true;
      if (m_Options["COLOR"]){
        vector<string>::const_iterator ii;
        for (ii = (*it).first.begin(); ii != (*it).first.end(); ++ii){
          if (!m_Character->IsItem((*ii))){
            ok = false;
            break;
          }
        }
        if (ok){
          tmp_Planes.push_back(*it);
          cout << "\033[1;32m";
        }else{
          cout << "\033[0;31m";
        }
      }
      if (ok){
        cout << tmp_Planes.size() << ") ";
        for (vector<string>::const_iterator il = (*it).second.begin();
             il != (*it).second.end(); ++il){
          cout << (*il) << " ";
        }
        cout << "= ";
        for (vector<string>::const_iterator il = (*it).first.begin();
             il != (*it).first.end(); ++il){
          cout << (*il) << " ";
        }
        cout << endl;
      }
    }
    if (m_Options["COLOR"]) cout << "\033[0;39m";
    cout << "vyber: ";
    ReturnVal *ret = atr[0]->getValue();
    if (ret == NULL) return new ReturnVal(-1);
    unsigned int choice = ret->getInt()-1;
    delete ret;
    if (choice >= tmp_Planes.size()) return new ReturnVal(0);
    for (vector<string>::const_iterator ia = tmp_Planes[choice].first.begin();
         ia != tmp_Planes[choice].first.end(); ++ia){
      m_Character->DelByName(*ia);
    }
    for (vector<string>::const_iterator ia = tmp_Planes[choice].second.begin();
         ia != tmp_Planes[choice].second.end(); ++ia){
      m_Character->GiveItem(m_World->CreateItem(*ia));
    }
    return new ReturnVal(1);
  }
  return NULL;
}
//=======================================================================GENERAL
//--------------------------------------------------------------------------Quit
ReturnVal *Scenario::Quit       (vector<Expression*> atr)
{
  cin.setstate(ios::eofbit);
  return NULL;
}
