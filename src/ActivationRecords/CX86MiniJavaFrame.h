#pragma once
#include "IFrame.h"

class CX86MiniJavaFrame : public IFrame {
  public:
    ~CX86MiniJavaFrame() {}

    std::map<std::string, int> local_vars;
    std::map<std::string, int> formal_vars;
    virtual IAccess* Formal(int index) const override;
    virtual IAccess* FindLocalOrFormal(const Symbol* name) const;

    IAccess* CreateFormal(RecordTypes type, int size);

  private:
    int FramePointer;
    int StackPointer;

};