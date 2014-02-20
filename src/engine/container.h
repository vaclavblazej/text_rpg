/*! \file
 */

/*! \class Container
 * \brief Informace o úkolech.
 * 
 * Uchoávvá informace a spravuje všechny otevřené úkoly.
 */
 
/*! \fn Container::Print()
 * \brief Vytiskne cíle.
 *
 * Vypíše na výstup seznam všech cílů
 * \return Počet cílů.
 */
 
/*! \fn Container::Check()
 * \brief Kontrola splnění úkolů.
 *
 * Zkontroluje jestli byl nějaký úkol splněn.
 * \return Kolik bylo splněno úkolů.
 */
 
/*! \fn Container::AddQuest(Quest *)
 * \brief Přidá úkol.
 *
 * Přidá úkol mezi ostatní.
 * \param quest Přidávaný úkol.
 */
 
/*! \fn Container::RemQuest(Quest *)
 * \brief Odebere úkol.
 *
 * Najde úkol odpovídající parametru a odebere ho.
 * \param quest Odebíraný úkol.
 */
 
/*! \fn Container::Save(std::ofstream &) const
 * \brief Uloží úkoly.
 *
 * Uloží úkoly do souboru.
 * \param output Výstupní soubur
 */
 
/*! \fn Container::Load(std::ifstream &)
 * \brief Načte úkoly.
 *
 * Načte informace o úkolech ze souboru a načte podle toho odkazy objekty z objektu světa.
 * \param input Vstupní soubur
 */
 
#ifndef CONTAINER
#define CONTAINER
typedef std::map <int, std::map<int, char> > t_ChangeArr;
class Quest;
class World;
class Container : public QuestAbs {
public:
               Container(World *world, Creature *player);
  virtual      ~Container();
  virtual int  Check();
  virtual void Print(std::ostream &os) const;
  virtual void Save(ofstream &output) const;
  virtual void Load(ifstream &input);
  void         AddQuest(Quest *quest);
  void         RemQuest(Quest *quest);
  t_ChangeArr &GetChanges();
private:
  std::vector <Quest*> m_Quests;
  t_ChangeArr          m_Changes;
  bool                 m_Active;
};

#endif /*CONTAINER*/
