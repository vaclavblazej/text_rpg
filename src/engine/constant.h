/*! \file
 */

/*! \class Constant
 * \brief Proměnná pro scriptování.
 * 
 * Přes tento objekt je poskytnuta možnost využívat proměnné ve scriptování.
 */
 
/*! \fn Constant::Constant(int )
 * \brief Uloží proměnnou.
 *
 * Uloží proměnnou, které se dále využívá, při scriptovacím procesu.
 * \param var Uložená proměnná.
 */
 
/*! \fn Constant::getValue() const
 * \return Uložená proměnná.
 */

#ifndef CONSTANT
#define CONSTANT
#include <vector>
#include "expression.h"
class Constant : public Expression{
public:
  Constant(int var);
  virtual ~Constant();
  virtual ReturnVal *getValue() const;
private:
  int var;
};

#endif /*CONSTANT*/
