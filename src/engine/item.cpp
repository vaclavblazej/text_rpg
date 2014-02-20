#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
#include "item.h"
//----------------------------------------------------------------------Creature
Item::Item(string name, vector<t_Done> attrs)
           :m_Cost(0),
            m_Name(name),
            m_Ref(1),
            m_Attrs(attrs)
{
  for (vector<t_Done>::const_iterator it = m_Attrs.begin();
       it != m_Attrs.end(); ++it){
    m_Cost += (*it).second;
  }
  m_Cost += 1;
}
//-----------------------------------------------------------------------GetCost
int  Item::GetCost() const
{
  return m_Cost;
}
//-----------------------------------------------------------------------GetInfo
void Item::GetInfo(int &hp) const
{
  hp = 0;
  for (vector<t_Done>::const_iterator it = m_Attrs.begin();
       it != m_Attrs.end(); ++it){
    if((*it).first == "health") hp = (*it).second;
  }
}
//-----------------------------------------------------------------------GetInfo
void Item::GetInfo(bool &range) const
{
  range = false;
  for (vector<t_Done>::const_iterator it = m_Attrs.begin();
       it != m_Attrs.end(); ++it){
    if((*it).first == "range") range = (*it).second;
  }
}
//-----------------------------------------------------------------------GetInfo
void Item::GetInfo(string &name) const
{
  name = m_Name;
}
//-----------------------------------------------------------------------GetInfo
void Item::GetInfo(int &hp, int &str, int &agi, int &inl) const
{
  hp  = 0;
  str = 0;
  agi = 0;
  inl = 0;
  for (vector<t_Done>::const_iterator it = m_Attrs.begin();
       it != m_Attrs.end(); ++it){
    if((*it).first == "health"  ) hp  = (*it).second;
    if((*it).first == "strength") str = (*it).second;
    if((*it).first == "agility" ) agi = (*it).second;
    if((*it).first == "intelect") inl = (*it).second;
  }
}
//-----------------------------------------------------------------------GetInfo
void Item::GetInfo(int &hp, int &str, int &agi, int &inl, bool &range) const
{
  hp  = 0;
  str = 0;
  agi = 0;
  inl = 0;
  range = false;
  for (vector<t_Done>::const_iterator it = m_Attrs.begin();
       it != m_Attrs.end(); ++it){
    if((*it).first == "health"  ) hp    = (*it).second;
    if((*it).first == "strength") str   = (*it).second;
    if((*it).first == "agility" ) agi   = (*it).second;
    if((*it).first == "intelect") inl   = (*it).second;
    if((*it).first == "range"   ) range = (*it).second;
  }
}
//-------------------------------------------------------------------------Print
void Item::Print() const
{
  cout << "Name:      " << m_Name << endl;
  /*if (m_Health)   cout << "+health:   " << m_Health   << endl;
  if (m_Strength) cout << "+strength: " << m_Strength << endl;
  if (m_Agility)  cout << "+agility:  " << m_Agility  << endl;
  if (m_Intelect) cout << "+intelect: " << m_Intelect << endl;
  if (m_Range)    cout << "is ranged"                 << endl;*/
}
//------------------------------------------------------------------PrintCompact
void Item::PrintCompact(int cost) const
{
  cout << showpos
       << setw(10) << m_Name;
       /*<< setw(2)  << m_Health   << " hp, "
       << setw(2)  << m_Strength << " str, "
       << setw(2)  << m_Agility  << " agi, "
       << setw(2)  << m_Intelect << " int";
  cout << endl;*/
  for (vector<t_Done>::const_iterator it = m_Attrs.begin();
       it != m_Attrs.end(); ++it){
    cout << ", ";
    cout << (*it).first << " " << (*it).second;
  }
  cout << noshowpos;
  if (cost) cout << ", "<< setw(2) << int(m_Cost*cost/100.) << " gold";
  //if (m_Range) cout << " (ranged)";
}
//--------------------------------------------------------------------------Save
void Item::Save(ofstream &output) const
{
  output << m_Name << " "
         << m_Cost << " "
         << m_Attrs.size() << endl;
  for (vector<t_Done>::const_iterator it = m_Attrs.begin();
       it != m_Attrs.end(); ++it){
    output << (*it).first << " " << (*it).second << endl;
  }
}
//--------------------------------------------------------------------------Load
void Item::Load(std::ifstream &input)
{
  string line;
  int count;
  string fir;
  int sec;
  m_Attrs.clear();
  getline(input, line);
  istringstream is(line);
  is >> m_Name >> m_Cost >> count;
  for (int i = 0; i < count; i++){
    getline(input, line);
    istringstream is(line);
    is >> fir >> sec;
    m_Attrs.push_back(t_Done(fir, sec));
  }
}


