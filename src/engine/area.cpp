#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
#include "creature.h"
#include "ally.h"
#include "area.h"

//--------------------------------------------------------------------------Area
Area::Area(int areaCode):m_AreaCode(areaCode){}
//-------------------------------------------------------------------------~Area
Area::~Area()
{
  for (Creature* it : m_Creatures)	delete it;
  for (Ally* it : m_Allies)			delete it;
}
//-----------------------------------------------------------------------GetCode
int Area::GetCode() const
{
  return m_AreaCode;
}
//-------------------------------------------------------------------AddCreature
void Area::AddCreature(Creature *mob)
{
  m_Creatures.push_back(mob);
}
//-----------------------------------------------------------------------AddAlly
void Area::AddAlly(Ally *ally)
{
  m_Allies.push_back(ally);
}
//-----------------------------------------------------------------------KillMob
vector <Item*> Area::KillMob(Creature *mod)
{
  for (vector <Creature*>::iterator it = m_Creatures.begin();
       it != m_Creatures.end(); ++it){
    if (mod == *it){
      vector <Item*> items = m_Creatures[it - m_Creatures.begin()]->GetItems();
      m_Creatures.erase(it);
      return items;
    }
  }
  return vector <Item*> ();
}
//--------------------------------------------------------------------------Save
void Area::Save(ofstream &output) const
{
  output << m_AreaCode << " "
         << m_Creatures.size() << " "
         << m_Allies.size() << endl;
  for (Creature* it : m_Creatures){
    it->Save(output);
  }
  for (Ally* it : m_Allies){
    it->Save(output);
  }
}
//--------------------------------------------------------------------------Load
void Area::Load(std::ifstream &input)
{
  int cCrea, cAlly;
  string line;
  getline(input, line);
  istringstream is(line);
  is >> m_AreaCode >> cCrea >> cAlly;
  for (Creature* it : m_Creatures) delete it;
  m_Creatures.clear();
  for (int i = 0; i < cCrea; i++){
    Creature *crea = new Creature;
    crea->Load(input);
    AddCreature(crea);
  }
  for (Ally* it : m_Allies) delete it;
  m_Allies.clear();
  for (int i = 0; i < cAlly; i++){
    Ally *ally = new Ally;
    ally->Load(input);
    AddAlly(ally);
  }
}
//------------------------------------------------------------------GetCreatures
vector <Creature*> Area::GetCreatures()
{
  return m_Creatures;
}
//---------------------------------------------------------------------GetAllies
vector <Ally*> Area::GetAllies()
{
  return m_Allies;
}
