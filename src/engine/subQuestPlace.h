/*! \file
 */

/*! \class SubquestPlace
 * \brief Definuje úkol dojití na místo.
 * 
 * Ukládá kam hráč musí dojít ke splnění úkolu.
 */
 
/*! \fn SubquestPlace::SubquestPlace(World *, Creature *, int , int )
 * \brief Zkontroluje splnění.
 *
 * Zkontroluje jeslti hráč dočel na místo určení.
 * \param world Odkaz na svět.
 * \param player Odkaz na hráče.
 * \param x Pozice, na kterou se má hráč dostat pro splnění úkolu.
 * \param y Pozice, na kterou se má hráč dostat pro splnění úkolu.
 * \return Splnění úkolu.
 */
 
/*! \fn SubquestPlace::Check()
 * \brief Zkontroluje splnění.
 *
 * Zkontroluje jeslti hráč dočel na místo určení.
 * \return Splnení úkolu.
 */
 
/*! \fn SubquestPlace::Print(std::ostream &os);
 * \brief Vypíše cíl úkolu.
 *
 * Vypíše zadání cíl úkolu na výstup.
 * \param os Výstupní stream.
 */
 
/*! \fn SubquestPlace::Save(std::ofstream &) const
 * \brief Uloží úkol.
 *
 * Uloží cíl úkolu do souboru.
 * \param output Výstupní soubur
 */
 
/*! \fn SubquestPlace::Load(std::ifstream &)
 * \brief Načte úkol.
 *
 * Načte cíl úkolu ze souboru.
 * \param input Vstupní soubur
 */

#ifndef SUBQUESTPLACE
#define SUBQUESTPLACE
class SubquestPlace : public Subquest {
public:
  SubquestPlace(World *world, Creature *player, int x = 0, int y = 0);
  virtual ~SubquestPlace();
  virtual int  Check();
  virtual void Print(std::ostream &os) const;
  virtual void Save(std::ofstream &output) const;
  virtual void Load(std::ifstream &input);
  virtual void GetMark(int &x, int &y) const;
private:
  int m_X, m_Y;
};

#endif /*SUBQUESTPLACE*/
