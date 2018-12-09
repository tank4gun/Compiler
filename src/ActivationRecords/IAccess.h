#pragma once
#include "IRTree/Label.h"
#include "IRTree/IIRExp.h"
#include "IRTree/IIRStm.h"

class IAccess {
  public:
    virtual ~IAccess() = default;
    virtual IIRExp* GetExp() const = 0;
};

class CInRegAccess : public IAccess {
  public:
    explicit CInRegAccess(Temp& temp) : _temp(temp) {}

    IIRExp* GetExp() const override {
      return new TempExp(_temp);
    }

  private:
    Temp _temp;
};

class CInFrameAccess : public IAccess {
  public:
    CInFrameAccess(IAccess* frame_addr, int offset) : _frame_addr(frame_addr), _offset(offset) {}

    IIRExp* GetExp() const override {
      if(_offset != 0) {
        return new MemoryExp(new BinaryExp(BinaryOps::PLUSOP, _frame_addr->GetExp(), new ConstExp(_offset)));
      }
      return new MemoryExp(_frame_addr->GetExp());
    }

  private:
    IAccess* _frame_addr;
    int _offset;
};