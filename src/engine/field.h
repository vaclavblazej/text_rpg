/*! \file
 */

/*! \class Field
 * \brief Lokace na mapě.
 * 
 * Uchovává informace a poskytuje rozhraní práce s lokací. 
 */
 
/*! \fn Field::AddArea(Area * )
 * \brief Přidá oblast.
 *
 * Přidá oblast do lokace.
 * \param area Přidávaná oblast.
 */
 
/*! \fn Field::ChangeHeight(int )
 * \brief Změní výšku pole.
 *
 * Změní nadmořskou výšku pole. Využívá se u generování biomu.
 * \param newHeight Změna výšky.
 */
 
/*! \fn Field::GetCode() const
 * \return Kód lokace.
 */
 
/*! \fn Field::SetBiome()
 * \brief Přidá oblast.
 *
 * Přidá oblast podle nadmořské výšky.
 */
 
/*! \fn Field::Discover(bool )
 * \brief Objeví nebo zahalí lokaci.
 *
 * Objeví nebo zahalí lokaci, takže se bude vykreslovat na mapě.
 * \param state True odhalí. False zahalí.
 */
 
/*! \fn Field::Save(std::ofstream &) const
 * \brief Uloží předmět.
 *
 * Uloží předmět do souboru.
 * \param output Výstupní soubur
 */
 
/*! \fn Field::Load(std::ifstream &)
 * \brief Načte předmět.
 *
 * Načte předmět ze souboru.
 * \param input Vstupní soubur
 */
 
/*! \fn Field::KillMob(Creature *, const int &);
 * \brief Odebere jednotku.
 *
 * Odebere jednotku danou parametrem z oblasti dané parametrem. Vrací předměty, které měla jednotka.
 * \param mob Odebíraná jednotka.
 * \param l Oblast, ze které je odebírána.
 * \return Předměty, které měla jednotka.
 */
  
/*! \fn Field::GetCreatures()
 * \brief Vrátí všechny jednotky.
 *
 * Vrátí všechny přítomné jednotky v lokaci.
 * \return Všechny přítomné jednotky v lokaci.
 */
 
/*! \fn Field::GetAllies()
 * \brief Vrátí všechny spřátelené jednotky.
 *
 * Vrátí všechny přítomné spřátelené jednotky v lokaci.
 * \return Všechny přítomné spřátelené jednotky v lokaci.
 */
 
#ifndef FIELD
#define FIELD
class Creature;
class Area;
class Field{
public:
  Field();
  ~Field();
  void AddArea(Area * area);
  void ChangeHeight(int newHeight);
  int  GetCode() const;
  void SetBiome();
  void Discover(bool state){m_Discovered = state;}
  void Save(std::ofstream &output) const;
  void Load(std::ifstream &input);
  std::vector <Item*>     KillMob(Creature *mob, const int &l);
  std::vector <Creature*> GetCreatures();
  std::vector <Ally*>     GetAllies();
  std::vector <Area*>     m_Area; //<!
  //+++because of AddMobs in World
private:
  int  m_Height;
  bool m_Discovered;
};

#endif /*FIELD*/
