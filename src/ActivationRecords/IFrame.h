#pragma once
#include "SymbolTable/Symbol.h"
#include "IAccess.h"
#include <string>
#include <map>
#include <memory>
#include <unordered_map>
#include "IRTree/IIRExp.h"


class IFrame{
  public:
    ~IFrame() = default;
    virtual void AddAddr(const std::string& name, const IAccess* addr) = 0;
    virtual void AddFormal(const std::string& name) = 0;
    virtual void AddLocal(const std::string& name) = 0;
    virtual const IAccess* GetAccess(const std::string& name) = 0;

    virtual const std::string& Name() const = 0;
    virtual const IIRExp* CallFunction(const std::string& func_name, IIRExp* arg) const = 0;
};


class MiniJavaFrame : public IFrame {
  public:
    MiniJavaFrame(const Symbol* class_symb, const Symbol* method_symb) {
      _name = class_symb->String() + "::" + method_symb->String();
      _size = 0;
    }

    void AddAddr(const std::string& name, IAccess* addr) {
      _addresses[name] = std::unique_ptr<IAccess>(addr);
    }

    void AddFormal(const std::string& name) override {
      AddAddr(name, new CInFrameAccess(GetAccess("THIS"), _size));
      _size += _cell_size;
    }

    void AddLocal(const std::string& name) override {
      AddAddr(name, new CInFrameAccess(GetAccess("FRAME_POINTER"), _size));
      _size += _cell_size;
    }

    const std::string& Name() const override {
      return _name;
    }

    const IIRExp* CallFunction(const std::string& func_name, IIRExp* args) const override {
      return new CallExp(new NameExp(Label(func_name)), new IRExpList(args));
    }

  private:
    std::string _name;
    int _size;
    std::unordered_map<std::string, std::unique_ptr<IAccess> > _addresses;
    const int _cell_size = 4;
};