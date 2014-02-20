/*! \file
 */

/*! \class Method
 * \brief Šablona metody pro scriptování.
 * 
 * Přes tento objekt může jiný poskytnout své rozhraní pro scriptování. Stačí nastavit jednu funkci, která bude na požadavek jména scriptu vracet tento objekt s příslušnou metodou rozhraní.
 */
 
/*! \fn Method<A>::Method(A *, methodPtr , vector<Expression*> )
 * \brief Uloží metodu.
 *
 * Uloží metodu objektu a je připraven ji zavolat.
 * \param obj Objekt od metody rozhraní.
 * \param func Metoda rozhraní.
 * \param params Parametry metody rozhraní.
 */
 
/*! \fn Method<A>::getValue() const
 * \brief Zavolá metodu.
 *
 * Zavolá metodu s danými parametry a výslednou hodnotu vrátí.
 * \return Výsledek zavolání metody rozhraní.
 */
 
#ifndef METHOD
#define METHOD
class ReturnVal;
#include "expression.h"
template <class A>
class Method : public Expression{
public:
  typedef ReturnVal *(A::*methodPtr)(vector<Expression*> atr);
  Method(A *obj, methodPtr func, vector<Expression*> params = vector<Expression*>());
  virtual ~Method();
  virtual ReturnVal *getValue() const;
private:
  ReturnVal *(A::*m_Func)(vector<Expression*> atr);
  A  *m_Obj;
  vector<Expression*> m_Param;
};

//------------------------------------------------------------------------Method
template <class A>
Method<A>::Method(A *obj, methodPtr func, vector<Expression*> params)
{
  m_Obj = obj;
  m_Func = func;
  m_Param = params;
}
//-----------------------------------------------------------------------~Method
template <class A>
Method<A>::~Method(){
  for (vector<Expression*>::iterator it = m_Param.begin();
       it != m_Param.end(); ++it){
    (*it)->Destroy();
  }
}
//----------------------------------------------------------------------getValue
template <class A>
ReturnVal *Method<A>::getValue() const
{
  return (m_Obj ->* m_Func)(m_Param);
}

#endif /*METHOD*/
