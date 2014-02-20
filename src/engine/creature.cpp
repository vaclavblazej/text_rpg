#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
#include "item.h"
#include "unit.h"
#include "creature.h"
//----------------------------------------------------------------------Creature
Creature::Creature(string name, int X, int Y, int L, int m_class,
                   int hp, int str, int agl, int inl, int gold,
                   bool fly, bool hst, bool tpl,
                   bool vig, bool frs)
                  :Unit(name, X, Y, L, gold),
                   m_Class(((m_class%7)+7)%7),
                   m_Health(hp), m_Strength(str),
                   m_Agility(agl), m_Intelect(inl),
                   m_Flying(fly),
                   m_Haste(hst),
                   m_Trample(tpl),
                   m_Vigilance(vig),
                   m_FirstStrike(frs){}
//---------------------------------------------------------------------~Creature
Creature::~Creature()
{
  for (vector <Item*>::const_iterator it = m_Items.begin();
       it != m_Items.end(); ++it) (*it)->RemRef();
  m_Items.clear();
}
//------------------------------------------------------------------------MoveBy
void Creature::MoveBy(int X, int Y, int cutX, int cutY)
{
  m_X = (m_X + X + cutX) % cutX;
  m_Y = (m_Y + Y + cutY) % cutY;
}
//------------------------------------------------------------------------MoveTo
void Creature::MoveTo(int X, int Y)
{
  m_X = X;
  m_Y = Y;
}
//------------------------------------------------------------------GetAbilities
void Creature::GetAbilities(bool &Rng, bool &Fly, bool &Hst,
                            bool &Tpl, bool &Vig, bool &Frs) const
{
  Rng = false;
  for (vector <Item*>::const_iterator it = m_Items.begin();
       it != m_Items.end(); ++it){
    bool tmpRange;
    (*it)->GetInfo(tmpRange);
    Rng = (Rng || tmpRange);
  }
  Fly = m_Flying;
  Hst = m_Haste;
  Tpl = m_Trample;
  Vig = m_Vigilance;
  Frs = m_FirstStrike;
}
//-------------------------------------------------------------------------GetHp
int Creature::GetHp() const
{
  int hp = 0;
  for (vector <Item*>::const_iterator it = m_Items.begin();
       it != m_Items.end(); ++it){
    int tmpHp;
    (*it)->GetInfo(tmpHp);
    hp += tmpHp;
  }
  return hp + m_Health;
}
//------------------------------------------------------------------------GetDmg
int Creature::GetDmg() const
{
  int str = 0, agi = 0, inl = 0;
  for (vector <Item*>::const_iterator it = m_Items.begin();
       it != m_Items.end(); ++it){
    int tmpHp, tmpStr, tmpAgi, tmpInt;
    (*it)->GetInfo(tmpHp, tmpStr, tmpAgi, tmpInt);
    str += tmpStr;
    agi += tmpAgi;
    inl += tmpInt;
  }
  str += m_Strength;
  agi += m_Agility;
  inl += m_Intelect;
  switch (m_Class){
  case 0:
    return str/3 + 1;
  case 1:
    return agi/3 + 1;
  case 2:
    return inl/3 + 1;
  case 3:
    return (str+agi)/6 + 1;
  case 4:
    return (str+inl)/6 + 1;
  case 5:
    return (agi+inl)/6 + 1;
  case 6:
    return (str+agi+inl)/9 + 1;
  default:
    return 0;
  }
}
//----------------------------------------------------------------------GetBlock
int Creature::GetBlock() const
{
  int str = 0, agi = 0, inl = 0;
  for (vector <Item*>::const_iterator it = m_Items.begin();
       it != m_Items.end(); ++it){
    int tmpHp, tmpStr, tmpAgi, tmpInt;
    (*it)->GetInfo(tmpHp, tmpStr, tmpAgi, tmpInt);
    str += tmpStr;
    agi += tmpAgi;
    inl += tmpInt;
  }
  str += m_Strength;
  agi += m_Agility;
  inl += m_Intelect;
  switch (m_Class){
  case 0:
    return str/3 + 1;
  case 1:
    return agi/3 + 1;
  case 2:
    return inl/3 + 1;
  case 3:
    return (str+agi)/6 + 1;
  case 4:
    return (str+inl)/6 + 1;
  case 5:
    return (agi+inl)/6 + 1;
  case 6:
    return (str+agi+inl)/9 + 1;
  default:
    return 0;
  }
}
//--------------------------------------------------------------------PrintStats
void Creature::PrintStats() const
{
  int t_Str = 0, t_Agi = 0, t_Int = 0, t_Hp = 0;
  bool range = false;
  for (vector <Item*>::const_iterator it = m_Items.begin();
       it != m_Items.end(); ++it){
    int tmpHp, tmpStr, tmpAgi, tmpInt;
    bool tmpRange;
    (*it)->GetInfo(tmpHp, tmpStr, tmpAgi, tmpInt, tmpRange);
    t_Hp  += tmpHp;
    t_Str += tmpStr;
    t_Agi += tmpAgi;
    t_Int += tmpInt;
    range = range || tmpRange;
  }
  cout << "name:     " << m_Name.c_str();
  if (range)         cout << " (ranged)";
  if (m_Flying)      cout << " (flying)";
  if (m_Haste)       cout << " (haste)";
  if (m_Trample)     cout << " (trample)";
  if (m_Vigilance)   cout << " (vigilance)";
  if (m_FirstStrike) cout << " (first strike)";
  cout << endl;
  cout << "ødamage:  " << GetDmg()                            << endl
       << "health:   " << m_Health   << " (+" << t_Hp  << ")" << endl
       << "strength: " << m_Strength << " (+" << t_Str << ")" << endl
       << "agility:  " << m_Agility  << " (+" << t_Agi << ")" << endl
       << "intelect: " << m_Intelect << " (+" << t_Int << ")" << endl;
}
//--------------------------------------------------------------------------Save
void Creature::Save(ofstream &output) const
{
  Unit::Save(output);
  output << m_Health << " "
         << m_Strength << " "
         << m_Agility << " "
         << m_Intelect << " "
         << m_Flying << " "
         << m_Haste << " "
         << m_Trample << " "
         << m_Vigilance << " "
         << m_FirstStrike << endl;
}
//--------------------------------------------------------------------------Load
void Creature::Load(std::ifstream &input)
{
  Unit::Load(input);
  string line;
  getline(input, line);
  istringstream is(line);
  is >> m_Health >> m_Strength >> m_Agility >> m_Intelect
     >> m_Flying >> m_Haste    >> m_Trample >> m_Vigilance >> m_FirstStrike;
}
