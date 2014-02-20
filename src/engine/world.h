/*! \file
 */

/*! \class World
 * \brief Mapa světa.
 * 
 * Ukládá veškeré lokace a sublokace mapy světa. Obsluhuje její vykreslení, ukládání, načítání, atd.
 */
 
/*! \fn World::World(int , int , std::string , std::string )
 * \brief Vytvoří svět.
 *
 * Vytvoří svět s danou výškou a šířkou, načte jednotky a předměty a přidá je do světa.
 * \param width Šířka mapy v počtu lokací.
 * \param height Výška mapy v počtu lokací.
 * \param creaDir Složka s jednotkami.
 * \param itemDir Složka s předměty.
 */
 
/*! \fn World::Paint(int , int , bool ) const
 * \brief Vykreslí svět.
 *
 * Vykreslí svět na výstup.
 * \param X Souřadnice vykreslení hráče.
 * \param Y Souřadnice vykreslení hráče.
 * \param color True vykreslí mapu barevně. False vykreslí mapu černobíle.
 * \return 
 */
 
/*! \fn World::Discover(bool )
 * \brief Odhalí nebo zahalí mapu.
 *
 * Odhalí nebo zahalí hráči celou mapu.
 * \param state True odhalí. False zahalí.
 */
 
/*! \fn World::Discover(int , int , int )
 * \brief Odhalí oblast.
 *
 * Odhalí hráči oblast danou parametry.
 * \param X Souřadnice oblasti.
 * \param Y Souřadnice oblasti.
 * \param radius Poloměr odhalované oblasti.
 */
 
/*! \fn World::GetCreatures(int , int )
 * \brief Vrátí jednotky na pozici.
 *
 * Vrátí všechny jednotky stojící na dané pozici na mapě.
 * \param X Souřasnice pozice hledání jednotek.
 * \param Y Souřasnice pozice hledání jednotek.
 * \return Nalezené jednotky.
 */
 
/*! \fn World::GetAllies(int , int );
 * \brief Vrátí spřátelené jednotky na pozici.
 *
 * Vrátí všechny spřátelené jednotky stojící na dané pozici na mapě.
 * \param X Souřasnice pozice hledání jednotek.
 * \param Y Souřasnice pozice hledání jednotek.
 * \return Nalezené spřátelené jednotky.
 */
 
/*! \fn World::KillMob(Creature *)
 * \brief Zničí jednotku.
 *
 * Zničí jednotku denou parametrem. Vrátí předměty, které jednotka měla.
 * \param mob Jednotka ke zničení.
 * \return Předměty, které jednotka měla.
 */
 
/*! \fn World::CreateItem();
 * \brief Vytvoří předmět.
 *
 * Vytvoří a vrátí náhodný předmět.
 * \return Vyrvořený předmět.
 */
 
/*! \fn World::Save(std::ofstream &) const
 * \brief Uloží svět.
 *
 * Uloží svět do souboru.
 * \param output Výstupní soubur
 */
 
/*! \fn World::Load(std::ifstream &)
 * \brief Načte svět.
 *
 * Načte svět ze souboru.
 * \param input Vstupní soubur
 */

#ifndef WORLD
#define WORLD
#include <map>
#include <set>
class CreaBP;
class Creature;
class ItemBP;
class Item;
class Ally;
class Field;
typedef std::map <string, ItemBP*> t_ItemBP;
class World{
public:
  World(int width, int height, std::string creaDir, std::string itemDir);
 ~World();
  void                Paint(int X, int Y, bool color,
                        std::map <int, std::map<int, char> > &changes) const;
  int                 GetCode(int X, int Y) const;
  void                Discover(bool state = true);
  void                Discover(int X, int Y, int radius);
  vector <Creature*>  GetCreatures(int X, int Y);
  vector <Ally*>      GetAllies(int X, int Y);
  std::vector <Item*> KillMob(Creature *mob);
  Item *              CreateItem(std::string str = "");
  void                Save(std::ofstream &output) const;
  void                Load(std::ifstream &input);
private:
  void Mountanize();
  void SetBiome();
  void Populate();
  Creature *CreateMob(int X, int Y, int L);
  void AddMobs();
  void Point();
  void Stream(int begX, int begY, int endX, int endY);
  
  int width;
  int height;
  std::vector <CreaBP*> creatureBlueprints;
  t_ItemBP              itemBlueprints;
  std::set<string>      m_Materials;
  Field ***grid;
};

#endif /*WORLD*/
