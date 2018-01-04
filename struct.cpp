#include "struct.h"
#include "iterator.h"

Iterator<Term*> * Struct::createIterator()
{
  return new StructIterator<Term*>(this);
}

Iterator<Term*> * Struct::createBFSIterator()
{
  return new createStructBFSIterator<Term*>(this);
}

Iterator<Term*> * Struct::createDFSIterator()
{
  return new createStructDFSIterator<Term*>(this);
}