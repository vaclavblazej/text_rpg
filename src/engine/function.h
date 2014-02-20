/*! \file
 */

/*! \class Function
 * \brief Funkce pro scriptování.
 * 
 * Přes tento objekt může být poskytnuto rozhraní pro scriptování. Toto rozhraní se nehodí do žádného objektu, je tedy definováno stranou. Stačí nastavit jednu funkci, která bude na požadavek jména scriptu vracet tento objekt s příslušnou funkcí rozhraní.
 */
 
/*! \fn Function::Function(funcPtr , std::vector<Expression*> &);
 * \brief Uloží funkci.
 *
 * Uloží funkci a je připraven ji zavolat.
 * \param func Funkce rozhraní.
 * \param params Parametry funkce rozhraní.
 */
 
/*! \fn Function::getValue() const
 * \brief Zavolá metodu.
 *
 * Zavolá metodu s danými parametry a výslednou hodnotu vrátí.
 * \return Výsledek zavolání metody rozhraní.
 */
 
#ifndef FUNCTION
#define FUNCTION
typedef ReturnVal *(*funcPtr)(std::vector<Expression*> atr);
class Function : public Expression{
public:
  Function(funcPtr func, std::vector<Expression*> &params);
  virtual ~Function();
  virtual ReturnVal *getValue() const;
private:
  std::vector <Expression*> atributes;
  ReturnVal *(*func)(std::vector<Expression*>);
  int val;
};

#endif /*FUNCTION*/
