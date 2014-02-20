#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>
#include <sstream>
using namespace std;
#include "ally.h"
#include "creature.h"
#include "creaBP.h"
#include "item.h"
#include "itemBP.h"
#include "area.h"
#include "field.h"
#include "world.h"

//-------------------------------------------------------------------------World
World::World(int width, int height, string creaDir, string itemDir)
            :width(width), height(height)
{
  srandom(time(NULL));
  cout << "Generating map..." << endl;
  grid = new Field**[width];
  for (int i = 0; i < width; i++){
    grid[i] = new Field*[height];
  }
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      grid[i][j] = new Field();
    }
  }
  Mountanize();
  Populate();
  SetBiome();
  // creatures
  for (vector <CreaBP*>::const_iterator it = creatureBlueprints.begin();
       it != creatureBlueprints.end(); ++it){
    delete *it;
    cout << "CREATURE ERROR\n";
  }
  creatureBlueprints.clear();
  cout << "Loading creatures..." << endl;
  string line, meta;
  meta = creaDir;
  meta.append("metadata");
  ifstream file;
  file.open (meta.c_str(), ios::in);
  if (!file.good()){
    cout << "Creatures metadata file not found!" << endl;
  }else{
    getline(file,line);
    while(file.good()){
      creatureBlueprints.push_back(new CreaBP(line, creaDir));
      getline(file,line);
    }
    file.close();
    // items
    for (t_ItemBP::const_iterator it = itemBlueprints.begin();
         it != itemBlueprints.end(); ++it){
      delete (*it).second;
      cout << "ITEMSBP ERROR\n";
    }
    itemBlueprints.clear();
    cout << "Loading items..." << endl;
    meta = itemDir;
    meta.append("recepies");
    file.open (meta.c_str(), ios::in);
    file >> line;
    while(file.good()){
      if (line != "=")
        m_Materials.insert(line);
      file >> line;
    }
    file.close();
    meta = itemDir;
    meta.append("atributes");
    file.open (meta.c_str(), ios::in);
    getline(file, line);
    vector<pair<string, string> > names;
    while(file.good()){
      istringstream iss(line);
      string name, shortname;
      iss >> name >> shortname;
      names.push_back(pair<string, string>(name, shortname));
      getline(file,line);
    }
    for (vector <pair<string, string> >::const_iterator it = names.begin();
         it != names.end(); ++it){
      cout << (*it).first << " " << (*it).second << endl;
    }
    file.close();
    meta = itemDir;
    meta.append("metadata");
    file.open (meta.c_str(), ios::in);
    getline(file,line);
    while(file.good()){
      ifstream sub;
      string name = "UNKNOWN";
      string tmp = itemDir;
      tmp.append(line);
      sub.open (tmp.c_str(), ios::in);
      if (!sub.good()){
        cout << "Error: Item blueprint file not found!" << endl;
      }else{
        string ln, cmd;
        getline(sub, ln);
        while (sub.good()){
          istringstream is(ln);
          getline(is, cmd, '=');
          if (cmd == "name"){
            is >> name;
            break;
          }
          getline(sub, ln);
        }
      }
      itemBlueprints.insert(pair<string, ItemBP*>(name, new ItemBP(name, tmp, names)));
      getline(file,line);
    }
    file.close();
  }
  
  AddMobs();
}
//------------------------------------------------------------------------~World
World::~World(){
  for (vector <CreaBP*>::const_iterator it = creatureBlueprints.begin();
       it != creatureBlueprints.end(); ++it) delete *it;
  creatureBlueprints.clear();
  for (t_ItemBP::const_iterator it = itemBlueprints.begin();
       it != itemBlueprints.end(); ++it)     delete (*it).second;
  itemBlueprints.clear();
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      delete grid[i][j];
    }
  }
  for (int i = 0; i < width; i++){
    delete [] grid[i];
  }
  delete [] grid;
}
//--------------------------------------------------------------------Mountanize
void World::Mountanize()
{
  for (int i = 0; i < (width * height)/32; i++){
    int minRadius = 8;
    int maxRadius = 10;
    int x = random()%width;
    int y = random()%height;
    int radius = random()%(maxRadius - minRadius) + minRadius;
    int tmpX, tmpY;
    for (int j = -radius; j <= radius; j++){
      tmpX = (x + j + width) % width;
      for (int k = -radius; k <= radius; k++){
        tmpY = (y + k + height) % height;
        grid[tmpX][tmpY]->ChangeHeight((radius*radius - (j*j + k*k))/10 + rand()%6);
      }
    }
  }
  for (int j = 0; j < (width + height)/32; j++){
    Stream(random()%width, random()%height, random()%width, random()%height);
  }
}
//----------------------------------------------------------------------SetBiome
void World::SetBiome()
{
  for (int j = 0; j < height; j++){
    for (int i = 0; i < width; i++){
      grid[i][j]->SetBiome();
    }
  }
}
//----------------------------------------------------------------------Populate
void World::Populate()
{
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      if (rand()%100 < 2){
        grid[i][j]->AddArea(new Area(8));//'S', "\033[1;31m"));
      }
    }
  }
}
//--------------------------------------------------------------------CreateItem
Item *World::CreateItem(string str)
{
  if (str == ""){
    t_ItemBP::iterator it = itemBlueprints.begin();
    advance(it, rand()%itemBlueprints.size());
    return (*it).second->New();
  }else{
    t_ItemBP::iterator it = itemBlueprints.find(str);
    if (it == itemBlueprints.end()){
      return new Item(str);
    }else{
      return itemBlueprints[str]->New();
    }
  }
}
//---------------------------------------------------------------------CreateMob
Creature *World::CreateMob(int X, int Y, int L)
{
  return creatureBlueprints[rand()%creatureBlueprints.size()]->New(X, Y, L);
}
//-----------------------------------------------------------------------KillMob
vector <Item*> World::KillMob(Creature *mob)
{
  string name;
  int x, y, l;
  mob->GetInfo(name, x, y, l);
  return grid[x][y]->KillMob(mob, l);
}
//-----------------------------------------------------------------------AddMobs
void World::AddMobs()
{
  vector <Creature*> allCreatures;
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      for (std::vector <Area*>::iterator it  = grid[i][j]->m_Area.begin(),
                                         end = grid[i][j]->m_Area.end();
           it != end; ++it){
        if ((rand()%100 < 10) && creatureBlueprints.size()){
          Creature *crea = CreateMob(i, j, it-grid[i][j]->m_Area.begin());
          set<string>::iterator ii = m_Materials.begin();
          advance(ii, rand()%m_Materials.size());
          crea->GiveItem(CreateItem(*ii));
          crea->GiveItem(CreateItem());
          (*it)->AddCreature(crea);
          allCreatures.push_back(crea);
        }
      }
    }
  }
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      if (allCreatures.size() > 0){
        for (std::vector <Area*>::iterator it  = grid[i][j]->m_Area.begin(),
                                           end = grid[i][j]->m_Area.end();
             it != end; ++it){
          if ((rand()%100 < 6) && creatureBlueprints.size()){
            Creature * goal = allCreatures[rand()%allCreatures.size()];
            int x, y, l;
            goal->GetInfo(x, y, l);
            Ally *ally = new Ally("Friend", i, j,
                                  it-grid[i][j]->m_Area.begin(),
                                  !bool(rand()%3));
            for (int i = rand()%3+1; i >= 0; i--)
              ally->GiveItem(CreateItem());
            set<string>::iterator ii;
            for (int i = rand()%9+3; i >= 0; i--){
              ii = m_Materials.begin();
              advance(ii, rand()%m_Materials.size());
              ally->GiveItem(CreateItem(*ii));
            }
            (*it)->AddAlly(ally);
          }
        }
      }
    }
  }
  allCreatures.clear();
}
//------------------------------------------------------------------------Stream
void World::Stream(int begX, int begY, int endX, int endY){
  int chaosLimit = 90;
  int midx = random()%width;
  int midy = random()%height;
  int x = begX;
  int y = begY;
  int chaos;
  int heightChange = -rand()%5-4;
  while (x != midx || y != midy){
    if (x >= 0 && x < width &&
        y >= 0 && y < height)
    chaos = random()%100;
    if (chaos <= chaosLimit){
      if (chaos <= chaosLimit/2)
        x += random()%3-1;
      else
        y += random()%3-1;
    }else{
      if (midx > x)x+=1;
      else if (midx < x) x-=1;
      if (midy > y)y+=1;
      else if (midy < y) y-=1;
    }
  }
  while (x != endX || y != endY){
    if (x >= 0 && x < width &&
        y >= 0 && y < height)
      grid[x][y]->ChangeHeight(heightChange);
    chaos = random()%100;
    if (chaos <= chaosLimit){
      if (chaos <= chaosLimit/2)
        x += random()%3-1;
      else
        y += random()%3-1;
    }else{
      if (endX > x)x+=1;
      else if (endX < x) x-=1;
      if (endY > y)y+=1;
      else if (endY < y) y-=1;
    }
  }
  if (x >= 0 && x < width &&
      y >= 0 && y < height)
  grid[x][y]->ChangeHeight(heightChange);
}
//----------------------------------------------------------------------Discover
void World::Discover(bool state)
{
  for (int j = 0; j < height; j++){
    for (int i = 0; i < width; i++){
      grid[i][j]->Discover(state);
    }
  }
}
//----------------------------------------------------------------------Discover
void World::Discover(int x, int y, int radius)
{
  int tmpX, tmpY;
  for (int j = y-radius; j <= y+radius; j++){
    tmpY = (j + height) % height;
    for (int i = x-radius; i <= x+radius; i++){
      tmpX = (i + width) % width;
      if ((j-y)*(j-y) + (i-x)*(i-x) < radius*radius)
        grid[tmpX][tmpY]->Discover(true);
    }
  }
}
//-------------------------------------------------------------------------Paint
void World::Paint(int X, int Y, bool color,
                  map <int, map<int, char> > &changes) const
{
  for (int j = 0; j < height; j++){
    for (int i = 0; i < width; i++){
      if (X != i || Y != j){
        char res = changes[i][j];
        if (res == 0){
          int ret = GetCode(i, j);
          switch (ret){
          case -2:
            cout << (color?"\033[0;31m":"") << '!';
            break;
          case -1:
            cout << (color?"\033[0;31m":"") << 'x';
            break;
          case 0:
            cout << (color?"\033[0;30m":"") << '#';
            break;
          case 1:
            cout << (color?"\033[1;36m":"") << 'X';
            break;
          case 2:
            cout << (color?"\033[1;37m":"") << '^';
            break;
          case 3:
            cout << (color?"\033[1;33m":"") << 'A';
            break;
          case 4:
            cout << (color?"\033[0;32m":"") << 'Z';
            break;
          case 5:
            cout << (color?"\033[1;32m":"") << 'z';
            break;
          case 6:
            cout << (color?"\033[0;36m":"") << '~';
            break;
          case 7:
            cout << (color?"\033[0;34m":"") << '-';
            break;
          case 8:
            cout << (color?"\033[0;35m":"") << 'S';
            break;
          }
        }else{
          cout << (color?"\033[0;31m":"") << res;
        }
      }else{
        cout << (color?"\033[1;31m":"") << "&";
      }
    }
    cout << endl;
  }
  cout << (color?"\033[0;39m":"") << endl;
  /*
  for (int j = posY-range; j <= posY+range; j++){
    tmpY = (j + height) % height;
    for (int i = posX-range; i <= posX+range; i++){
      tmpX = (i + width) % width;
      grid[tmpX][tmpY]->Paint(cout, false);
    }
    cout << endl;
  }*/
}
//-----------------------------------------------------------------------GetCode
int World::GetCode(int X, int Y) const
{
  return grid[X][Y]->GetCode();
}
//------------------------------------------------------------------GetCreatures
vector <Creature*> World::GetCreatures(int X, int Y)
{
  return grid[X][Y]->GetCreatures();
}
//---------------------------------------------------------------------GetAllies
vector <Ally*> World::GetAllies(int X, int Y)
{
  return grid[X][Y]->GetAllies();
}
//--------------------------------------------------------------------------Save
void World::Save(ofstream &output) const
{
  output << width << " " << height << endl;
  for (int j = 0; j < height; j++){
    for (int i = 0; i < width; i++){
      grid[i][j]->Save(output);
    }
  }
}
//--------------------------------------------------------------------------Load
void World::Load(std::ifstream &input)
{
  for (int j = 0; j < height; j++){
    for (int i = 0; i < width; i++){
      grid[i][j]->Load(input);
    }
  }
}
