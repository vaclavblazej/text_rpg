#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
#include "creature.h"
#include "subQuest.h"
#include "subQuestPlace.h"

//-----------------------------------------------------------------SubquestPlace
SubquestPlace::SubquestPlace(World *world, Creature *player, int x, int y)
                            :Subquest(world, player), m_X(x), m_Y(y){}
//----------------------------------------------------------------~SubquestPlace
SubquestPlace::~SubquestPlace(){}
//-------------------------------------------------------------------------Check
int  SubquestPlace::Check()
{
  int x, y, l;
  m_Player->GetInfo(x, y, l);
  if ((m_X == x) && (m_Y == y)) return 1;
  return 0;
}
//-----------------------------------------------------------------------GetMark
void SubquestPlace::GetMark(int &x, int &y) const
{
  x = m_X;
  y = m_Y;
}
//-------------------------------------------------------------------------Print
void SubquestPlace::Print(std::ostream &os) const
{
  os << "Get to [" << m_X << ", " << m_Y << "] coordinates." << endl;
}
//--------------------------------------------------------------------------Save
void SubquestPlace::Save(std::ofstream &output) const
{
  output << m_X << " " << m_Y << endl;
}
//--------------------------------------------------------------------------Load
void SubquestPlace::Load(std::ifstream &input)
{
  string line;
  getline(input, line);
  istringstream is(line);
  is >> m_X >> m_Y;
}
