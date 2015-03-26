#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
#include "quest.h"
#include "world.h"
#include "questAbs.h"
#include "subQuest.h"
#include "container.h"
//---------------------------------------------------------------------Container
Container::Container(World *world, Creature *player)
                    :QuestAbs(world, player),
                     m_Active(false){}
//--------------------------------------------------------------------~Container
Container::~Container()
{
  for (auto it = m_Quests.begin(); it != m_Quests.end(); ++it) {
  	delete *it;
  }
}
//-------------------------------------------------------------------CheckQuests
int Container::Check()
{
  int count = 0;
  for (auto it = m_Quests.begin(); it != m_Quests.end(); ++it){
    if ((*it)->Check() == 0){
      delete *it;
      m_Quests.erase(it--);
      count++;
    }
  }
  m_Active = false; // aktualizovat pouze při změně podúkolu
  return count;
}
//-------------------------------------------------------------------------Print
void Container::Print(std::ostream &os) const
{
  for (auto it : m_Quests){
    it->Print(os);
  }
}
//--------------------------------------------------------------------GetChanges
t_ChangeArr &Container::GetChanges()
{
  if (!m_Active){
    int x, y;
    m_Changes.clear();
    for (Quest* it : m_Quests){
      it->GetMark(x, y);
      m_Changes[x][y] = '?';
    }
    m_Active = true;
  }
  return m_Changes;
}
//----------------------------------------------------------------------AddQuest
void Container::AddQuest(Quest *quest)
{
  m_Active = false;
  m_Quests.push_back(quest);
}
//----------------------------------------------------------------------RemQuest
void Container::RemQuest(Quest *quest)
{
  for (auto it = m_Quests.begin(); it != m_Quests.end(); ++it){
    if (&quest == &(*it)){
      delete *it;
      m_Active = false;
      m_Quests.erase(it);
    }
  }
}
//--------------------------------------------------------------------------Save
void Container::Save(ofstream &output) const
{
  output << m_Quests.size() << endl;
  for (Quest* it : m_Quests){
    it->Save(output);
  }
}
//--------------------------------------------------------------------------Load
void Container::Load(ifstream &input)
{
  m_Active = false;
  for (Quest* it : m_Quests) delete it;
  m_Quests.clear();
  int c_Quests;
  string line;
  getline(input, line);
  istringstream is(line);
  is >> c_Quests;
  for (int i = 0; i < c_Quests; i++){
    Quest *quest = new Quest(m_World, m_Player);
    quest->Load(input);
    m_Quests.push_back(quest);
  }
}
