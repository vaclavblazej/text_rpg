/*! \file
 */

/*! \class Quest
 * \brief Definuje úkol.
 * 
 * Ukládá co musí hráč provést ke splnění úkolu.
 */
 
/*! \fn Quest::Quest(int , int , int , int )
 * \brief Vytvoří úkol.
 *
 * Vytvoří úkol a uloží si co je potřeba k jeho splnění. Hlavní částí úkolu jsou podúkoly. Pokud jsou všechny splněny, je splněn úkol jako celek. Podúkoly mohou být plněny pouze postupně.
 */
 
/*! \fn Quest::Check( )
 * \brief Zkontroluje splnění.
 *
 * Zkontroluje jeslti byl cíl prvního podúkolu splněn. Pokud ano, tak pokročí k dalšímu podúkolu a jeslti i ten je splněn, tak pokračuje dál. Pokud jsou splněny všechny, tak je úkol jako celek splněn.
 * \return Počet zbývajících podúkolů.
 */
 
/*! \fn Quest::Print(std::ostream &os);
 * \brief Vypíše první podúkol.
 *
 * Vypíše popis pro splnění prvního podúkolu na výstup
 * \param os Výstupní stream.
 */
 
/*! \fn Quest::Save(std::ofstream &) const
 * \brief Uloží úkol.
 *
 * Uloží metadata úkolu a všechny podúkoly do souboru.
 * \param output Výstupní soubur
 */
 
/*! \fn Quest::Load(std::ifstream &)
 * \brief Načte úkol.
 *
 * Načte metadata a všechny podúkoly ze souboru.
 * \param input Vstupní soubur
 */

#ifndef QUEST
#define QUEST
#include "questAbs.h"
class Expression;
class Subquest;
class World;
class Creature;
class Quest : public QuestAbs{
public:
               Quest(World *world, Creature *player, vector <Subquest*> quests = vector <Subquest*>());
  virtual      ~Quest();
  virtual int  Check();
  virtual void Print(std::ostream &os) const;
  virtual void Save(std::ofstream &output) const;
  virtual void Load(std::ifstream &input);
  void         GetMark(int &x, int &y);
private:
  vector <Subquest *> m_Goals;
};

#endif /*QUEST*/
