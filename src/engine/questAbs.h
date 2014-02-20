/*! \file
 */

/*! \class QuestAbs
 * \brief Rozhraní práce s úkoly.
 * 
 * Ukládá základní informace a definuje rozhraní které musí mít každý objekt, který ukládá a pracuje s úkoly.
 */
 
/*! \fn QuestAbs::QuestAbs()
 * \brief Vytvoří cíl úkolu.
 *
 * Vytvoří cíl úkolu a uloží si co je potřeba k jeho splnění
 */
 
/*! \fn QuestAbs::Check()
 * \brief Zkontroluje splnění.
 *
 * Zkontroluje jeslti byl cíl úkolu splněn.
 * \return Splnení úkolu.
 */
 
/*! \fn QuestAbs::Print(std::ostream &os);
 * \brief Vypíše cíl úkolu.
 *
 * Vypíše zadání cíl úkolu na výstup.
 * \param os Výstupní stream.
 */
 
/*! \fn QuestAbs::Save(std::ofstream &) const
 * \brief Uloží úkol.
 *
 * Uloží cíl úkolu do souboru.
 * \param output Výstupní soubur
 */
 
/*! \fn QuestAbs::Load(std::ifstream &)
 * \brief Načte úkol.
 *
 * Načte cíl úkolu ze souboru.
 * \param input Vstupní soubur
 */

#ifndef QUESTABS
#define QUESTABS
class World;
class Creature;
class QuestAbs {
public:
  QuestAbs(World* world, Creature *player):m_World(world), m_Player(player){}
  virtual ~QuestAbs(){}
  virtual int  Check() = 0;
  virtual void Print(std::ostream &os) const = 0;
  virtual void Save(std::ofstream &output) const = 0;
  virtual void Load(std::ifstream &input) = 0;
protected:
  World *m_World;     //!< Odkaz na strukturu světa.
  Creature *m_Player; //!< Odkaz na strukturu hráče.
};

#endif /*QUESTABS*/
