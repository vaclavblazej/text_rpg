#include "returnVal.h"
#include "word.h"
using namespace std;
//--------------------------------------------------------------------------Word
Word::Word(string word):m_Word(word){}
//-------------------------------------------------------------------------~Word
Word::~Word(){}
//----------------------------------------------------------------------getValue
ReturnVal *Word::getValue() const
{
  return new ReturnVal(m_Word);
}
