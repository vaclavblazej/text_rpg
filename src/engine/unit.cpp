#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
#include "item.h"
#include "unit.h"
//--------------------------------------------------------------------------Unit
Unit::Unit(string name, int X, int Y, int L, int gold)
                  :m_Name(name), m_X(X), m_Y(Y), m_L(L),
                   m_Gold(gold), m_Items(vector <Item*>()){}
//-------------------------------------------------------------------------~Unit
Unit::~Unit()
{
  for (Item* it : m_Items) it->RemRef();
  m_Items.clear();
}
//----------------------------------------------------------------------GetItems
vector <Item*> Unit::GetItems() const
{
  return m_Items;
}
//-----------------------------------------------------------------------GetInfo
void Unit::GetInfo(int &X, int &Y, int &L) const
{
  X    = m_X;
  Y    = m_Y;
  L    = m_L;
}
//-----------------------------------------------------------------------GetInfo
void Unit::GetInfo(string &name, int &X, int &Y, int &L) const
{
  name = m_Name;
  X    = m_X;
  Y    = m_Y;
  L    = m_L;
}
//--------------------------------------------------------------------PrintItems
void Unit::PrintItems(int cost) const
{
  vector <Item*>::const_iterator it = m_Items.begin();
  for (;it != m_Items.end(); ++it){
    cout << setw(2) << (it-m_Items.begin()+1) << ") ";
    (*it)->PrintCompact(cost);
    cout << endl;
  }
  cout << "gold: " << m_Gold << endl;
}
//----------------------------------------------------------------------HandItem
bool Unit::ChangeGold(int amount)
{
  if (m_Gold+amount >= 0){
    m_Gold += amount;
    return true;
  }
  return false;
}
//------------------------------------------------------------------------IsItem
bool Unit::IsItem(string str)
{
  string name;
  for (Item* it : m_Items){
    it->GetInfo(name);
    if (name == str){
      return true;
    }
  }
  return false;
}
//---------------------------------------------------------------------DelByName
bool Unit::DelByName(string str)
{
  string name;
  for (vector<Item*>::iterator it = m_Items.begin(); it != m_Items.end(); ++it){
    (*it)->GetInfo(name);
    if (name == str){
      (*it)->RemRef();
      m_Items.erase(it);
      return true;
    }
  }
  return false;
}
//----------------------------------------------------------------------GiveItem
int Unit::GiveItem(Item *item)
{
  m_Items.push_back(item);
  return m_Items.size();
}
//----------------------------------------------------------------------HandItem
Item * Unit::HandItem(int which)
{
  if (which > 0 && (unsigned int) which <= m_Items.size()){
    vector <Item*>::iterator it = m_Items.begin() + which - 1;
    Item *item = *it;
    m_Items.erase(it);
    return item;
  }else{
    return NULL;
  }
}
//-----------------------------------------------------------------------DelItem
bool Unit::DelItem(int which)
{
  if (which > 0 && (unsigned int) which <= m_Items.size()){
    vector <Item*>::iterator it = m_Items.begin()+which-1;
    (*it)->RemRef();
    m_Items.erase(it);
    return true;
  }else{
    return false;
  }
}
//--------------------------------------------------------------------------Save
void Unit::Save(ofstream &output) const
{
  output << m_Name.c_str() << " "
         << m_X << " "
         << m_Y << " "
         << m_L << " "
         << m_Gold << " "
         << m_Items.size() << endl;
  for (Item* it : m_Items){
    it->Save(output);
  }
}
//--------------------------------------------------------------------------Load
void Unit::Load(std::ifstream &input)
{
  int count;
  string line;
  getline(input, line);
  istringstream is(line);
  is >> m_Name >> m_X >> m_Y >> m_L >> m_Gold >> count;
  for (int i = 0; i < count; i++){
    Item *item = new Item();
    item->Load(input);
    m_Items.push_back(item);
  }
}
