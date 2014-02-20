#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
#include "creature.h"
#include "area.h"
#include "questAbs.h"
#include "subQuest.h"
#include "subQuestPlace.h"
#include "quest.h"
//-------------------------------------------------------------------------Quest
Quest::Quest(World *world, Creature *player, vector <Subquest*> quests)
            :QuestAbs(world, player),m_Goals(quests){}
//------------------------------------------------------------------------~Quest
Quest::~Quest()
{
  for (vector<Subquest*>::iterator it = m_Goals.begin();
       it != m_Goals.end(); ++it) delete *it;
}
//-----------------------------------------------------------------------GetMark
void Quest::GetMark(int &x, int &y)
{
  (*(m_Goals.begin()))->GetMark(x, y);
}
//-------------------------------------------------------------------------Check
int Quest::Check()
{
  while (m_Goals.size() != 0 && (*(m_Goals.begin()))->Check() == 1){
    delete *m_Goals.begin();
    m_Goals.erase(m_Goals.begin());
  }
  return m_Goals.size();
}
//-------------------------------------------------------------------------Print
void Quest::Print(ostream &os) const
{
  if (m_Goals.size() != 0){
    (*(m_Goals.begin()))->Print(os);
  }
}
//--------------------------------------------------------------------------Save
void Quest::Save(ofstream &output) const
{
  output << m_Goals.size() << endl;
  for (vector <Subquest*>::const_iterator it = m_Goals.begin();
       it != m_Goals.end(); ++it){
    (*it)->Save(output);
  }
}
//--------------------------------------------------------------------------Load
void Quest::Load(std::ifstream &input)
{
  for (vector <Subquest*>::const_iterator it = m_Goals.begin();
       it != m_Goals.end(); ++it) delete *it;
  m_Goals.clear();
  int c_Quests;
  string line;
  getline(input, line);
  istringstream is(line);
  is >> c_Quests;
  for (int i = 0; i < c_Quests; i++){
    Subquest *squest = new SubquestPlace(m_World, m_Player);
    squest->Load(input);
    m_Goals.push_back(squest);
  }
}
