/*! \file
 */

/*! \class Expression
 * \brief Hodnota pro skriptování.
 * 
 * Polymorfní hodnoty u skriptování. Může zastupovat proměnnou, textový řetězec, matematickou funkci nebo metodu rozhraní. Všechny obsahují počítené reference.
 */

/*! \fn Expression::getValue() const = 0
 * \brief Vrátí hodnotu.
 *
 * Vyhodnotí a vrátí uloženou hodnotu.
 * \return Uložená hodnota.
 */

/*! \fn Expression::Create()
 * \brief Přidá referenci
 */

/*! \fn Expression::Destroy()
 * \brief Odebere referenci / ničí
 */


#ifndef EXPRESSION
#define EXPRESSION
class ReturnVal;
class Expression{
public:
  Expression();
  virtual ~Expression();
  virtual ReturnVal *getValue() const = 0;
  void Create ();
  void Destroy();
protected:
  int refCount;  //!< Počítané reference.
};

#endif /*EXPRESSION*/
