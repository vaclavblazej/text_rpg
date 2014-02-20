#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
#include "item.h"
#include "unit.h"
#include "ally.h"
//--------------------------------------------------------------------------Ally
Ally::Ally(string name, int X, int Y, int L, bool quests)
          :Unit(name, X, Y, L, 0){}
//-------------------------------------------------------------------------~Ally
Ally::~Ally()
{
  for (vector <Item*>::const_iterator it = m_Items.begin();
       it != m_Items.end(); ++it) (*it)->RemRef();
  m_Items.clear();
}
//-------------------------------------------------------------------------Paint
int Ally::Paint() const
{
  return -1;
}
//------------------------------------------------------------------------Course
int Ally::Course() const
{
  return 50;
}
//--------------------------------------------------------------------------Save
void Ally::Save(ofstream &output) const
{
  Unit::Save(output);
}
//--------------------------------------------------------------------------Load
void Ally::Load(std::ifstream &input)
{
  Unit::Load(input);
}
