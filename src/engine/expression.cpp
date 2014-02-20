#include "returnVal.h"
#include "expression.h"

Expression::Expression()
{
  refCount = 0;
}
Expression::~Expression(){}
void Expression::Create ()
{
  refCount++;
}
void Expression::Destroy()
{
  if(--refCount <= 0) delete this;
}
