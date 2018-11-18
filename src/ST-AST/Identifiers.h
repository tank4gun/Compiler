#include <utility>

#pragma once
#include "IVisitor.h"
#include <string>

class IVisitor;

class IIdentifier {
  public:
    virtual void Accept( IVisitor* v ) const = 0;
    virtual char* Name() const = 0;
};

class Identifier : public IIdentifier {
  public:
    explicit Identifier(std::string str);
    void Accept(IVisitor* v) const override;
    char* Name() const override;
    std::string id;
};