#pragma once
#include "SymbolTable/Symbol.h"
#include "IAccess.h"
#include <string>
#include <map>


class IFrame{
  public:
    ~IFrame() {}
    virtual void AddFormal(const Symbol* name) = 0;
    void AddLocal(const Symbol* name);
    int FormalsCount() const;
    const IAccess* Formal(int index) const;
    const IAccess* FindLocalOrFormal(const Symbol* name) const;

};