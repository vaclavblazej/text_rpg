/*! \file
 */

/*! \class Area
 * \brief Oblast.
 * 
 * Uchovává informace a poskytuje rozhraní pro oblast.
 */
 
/*! \fn Area::Area(char , std::string );
 * \brief Vytvoří oblast.
 *
 * Vytvoří oblast a definuje jak se oblast má vykreslovat.
 * \param fill Je znak pro vykreslení reprezentace oblasti.
 * \param color Je barva znaku reprezentace oblasti.
 */
 
/*! \fn Area::AddCreature(Creature *)
 * \brief Přidání jednotky
 *
 * Přidá do oblasti jednotku.
 * \param mob Přidávaná jednotka
 */
 
/*! \fn Area::AddAlly(Ally *)
 * \brief Přidání spřátelené jednotky
 *
 * Přidá do oblasti spřátelenou jednotku.
 * \param ally Přidávaná jednotka
 */
 
/*! \fn Area::KillMob(Creature *);
 * \brief Zničí jednotku
 *
 * Najde jednotku která odpovádí parametru a smaže ji. Vrací její předměty.
 * \param mob Zničená jednotka
 * \return Předměty jednotky.
 */
 
/*! \fn Area::GetCreatures();
 * \return Všechny nepřátelské jednotky v oblasti.
 */
 
/*! \fn Area::GetAllies();
 * \return Všechny přátelské jednotky v oblasti.
 */
 
/*! \fn Area::GetCode() const
 * \return Kód lokace.
 */
 
/*! \fn Area::Save(std::ofstream &) const
 * \brief Uloží podoblast.
 *
 * Uloží podoblast do souboru.
 * \param output Výstupní soubur
 */
 
/*! \fn Area::Load(std::ifstream &)
 * \brief Načte podoblast.
 *
 * Načte podoblast ze souboru.
 * \param input Vstupní soubur
 */
 
#ifndef AREA
#define AREA
class Creature;
class Ally;
class Area{
public:
  Area(int areaCode = 0);
  ~Area();
  int  GetCode() const;
  void AddCreature(Creature *mob);
  void AddAlly(Ally *ally);
  void Save(std::ofstream &output) const;
  void Load(std::ifstream &input);
  std::vector <Item*> KillMob(Creature *mob);
  std::vector <Creature*> GetCreatures();
  std::vector <Ally*> GetAllies();
private:
  int m_AreaCode;
  std::vector <Creature*> m_Creatures;
  std::vector <Ally*> m_Allies;
};

#endif /*AREA*/
