#pragma once
#include "CInFrameAccess.h"
#include "CInRegAccess.h"
#include "IFrame.h"

class CX86MiniJavaFrame : public IFrame {
  public:
    ~CX86MiniJavaFrame() {}

    std::map<std::string, int> vars;
    virtual IAccess* Formal(int index) const override;


  private:
    int FramePointer;
    int StackPointer;

};