#pragma once


class IAccess {
  public:
    virtual ~IAccess() = default;
};

class CInRegAccess : public IAccess {
  public:
    explicit CInRegAccess(const IRTemp& temp) : _temp(temp) {}

    IIRExp* GetExp() {
      return new IRTempExp(_temp);
    }

  private:
    IRTemp _temp;
};

class CInFrameAccess : public IAccess {
  public:
    CInFrameAccess(const IAccess* frame_addr, int offset) : _frame_addr(frame_addr), _offset(offset) {}

    IIRExp* GetExp() {
      if(_offset != 0) {
        return new IRMemoryExp(new IRBinaryExp(/*TYPE*/, _frame_addr->GetExp(), new IRConstExp(_offset)));
      }
      return new IRMemoryExp(_frame_addr->GetExp());
    }

  private:
    IAccess* _frame_addr;
    int _offset;
};