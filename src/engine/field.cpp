#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
#include "item.h"
#include "creature.h"
#include "ally.h"
#include "area.h"
#include "field.h"

//-------------------------------------------------------------------------Field
Field::Field()
            :m_Height(0),
             m_Discovered(false)
{
  //m_Area.push_back(new Area(fill, color));
}
//------------------------------------------------------------------------~Field
Field::~Field()
{
  for (auto it = m_Area.begin(); it != m_Area.end(); ++it) {
  	delete *it;
  }
}
//-----------------------------------------------------------------------AddArea
void Field::AddArea(Area *area)
{
  m_Area.push_back(area);
}
//------------------------------------------------------------------ChangeHeight
void Field::ChangeHeight(int newHeight)
{
  m_Height += newHeight;
}
//----------------------------------------------------------------------SetBiome
void Field::SetBiome()
{
       if (m_Height > 60) AddArea(new Area(2));
  else if (m_Height > 45) AddArea(new Area(3));
  else if (m_Height > 35) AddArea(new Area(4));
  else if (m_Height > 15) AddArea(new Area(5));
  else if (m_Height > 10) AddArea(new Area(6));
  else                    AddArea(new Area(7));
}
//-----------------------------------------------------------------------GetCode
int Field::GetCode() const
{
  if(m_Discovered){
    return m_Area.back()->GetCode();
  }else{
    return 0;
  }
}
//--------------------------------------------------------------------------Save
void Field::Save(ofstream &output) const
{
  output << m_Discovered << " "
         << m_Height << " "
         << m_Area.size() << endl;
  for (auto it = m_Area.begin(); it != m_Area.end(); ++it){
    (*it)->Save(output);
  }
}
//--------------------------------------------------------------------------Load
void Field::Load(std::ifstream &input)
{
  int count;
  string line;
  getline(input, line);
  istringstream is(line);
  is >> m_Discovered >> m_Height >> count;
  for (auto it = m_Area.begin(); it != m_Area.end(); ++it) {
  	delete *it;
  }
  m_Area.clear();
  for (int i = 0; i < count; i++){
    Area *area = new Area();
    area->Load(input);
    AddArea(area);
  }
}
//-----------------------------------------------------------------------KillMob
vector <Item*> Field::KillMob(Creature *mob, const int &l)
{
  return m_Area[l]->KillMob(mob);
}
//------------------------------------------------------------------GetCreatures
vector <Creature*> Field::GetCreatures()
{
  if (m_Area.size() > 0){
    return m_Area[0]->GetCreatures();
  } else {
    return vector <Creature*> ();
  }
}
//---------------------------------------------------------------------GetAllies
vector <Ally*> Field::GetAllies()
{
  if (m_Area.size() > 0){
    return m_Area[0]->GetAllies();
  } else {
    return vector <Ally*> ();
  }
}
