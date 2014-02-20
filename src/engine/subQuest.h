/*! \file
 */

/*! \class Subquest
 * \brief Definuje úkol.
 * 
 * Ukládá co musí hráč provést ke splnění úkolu.
 */
 
/* \fn Subquest::Subquest()
 * \brief Vytvoří cíl úkolu.
 *
 * Vytvoří cíl úkolu a uloží si co je potřeba k jeho splnění
 */
 
/* \fn Subquest::Check()
 * \brief Zkontroluje splnění.
 *
 * Zkontroluje jeslti byl cíl úkolu splněn.
 * \return Splnení úkolu.
 */
 
/* \fn Subquest::Print(std::ostream &os);
 * \brief Vypíše cíl úkolu.
 *
 * Vypíše zadání cíl úkolu na výstup.
 * \param os Výstupní stream.
 */
 
/* \fn Subquest::Save(std::ofstream &) const
 * \brief Uloží úkol.
 *
 * Uloží cíl úkolu do souboru.
 * \param output Výstupní soubur
 */
 
/* \fn Subquest::Load(std::ifstream &)
 * \brief Načte úkol.
 *
 * Načte cíl úkolu ze souboru.
 * \param input Vstupní soubur
 */

#ifndef SUBQUEST
#define SUBQUEST
#include "questAbs.h"
class World;
class Creature;
class Subquest : public QuestAbs{
public:
  Subquest(World* world, Creature *player):QuestAbs(world, player){}
  virtual ~Subquest(){}
  virtual void GetMark(int &x, int &y) const = 0;
protected:
};

#endif /*SUBQUEST*/
