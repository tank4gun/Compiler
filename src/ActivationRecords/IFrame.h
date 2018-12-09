#pragma once
#include "SymbolTable/Symbol.h"
#include "IAccess.h"
#include <string>
#include <map>
#include <memory>
#include <unordered_map>


class IFrame{
  public:
    ~IFrame() = default;
    virtual void AddAddr(const std::string& name, const IAccess* addr) = 0;
    virtual void AddFormal(const std::string& name) = 0;
    virtual void AddLocal(const std::string& name) = 0;
    virtual const IAccess* GetAccess(const std::string& name) = 0;

    virtual const std::string& Name() const = 0;
    virtual const IIRExp* CallFunction(const std::string& func_name, const IIRExp* arg) const = 0;
};


class MiniJavaFrame : public IFrame {
  public:
    MiniJavaFrame(const Symbol* class_symb, const Symbol* method_symb) {
      _name = class_symb->String() + "::" + method_symb->String();
      _size = 0;
      AddAddress(FP, new CInRegAddress(Temp(FP)));
      AddAddress(THIS, new CInRegAddress(Temp(THIS)));
      AddAddress(RET, new CInRegAddress(Temp(RET)));
    }

    void AddAddr(const std::string& name, IAccess* addr) {
      _addresses[name] = std::unique_ptr<IAccess>(addr);
    }

    void AddFormal(const std::string& name) override {
      AddAddr(name, new CInFrameAccess(GetAccess(THIS), _size));
      _size += _word_size;
    }

    void AddLocal(const std::string& name) override {
      AddAddr(name, new CInFrameAccess(GetAccess(FRAME_POINTER), _size));
      _size += _word_size;
    }

    const std::string& Name() const override {
      return _name;
    }

    const IIRExp* CallFunction(const std::string& func_name, const IIRExp* args) const override {
      return new IRCallExp(new IRNameExp(Label(func_name)), new IRExpList(args));
    }

  private:
    const static std::string FRAME_POINTER = "FRAME_POINTER";
    const static std::string THIS = "THIS";
    const static std::string RETURN_VALUE = "RETURN_VALUE";

    std::string _name;
    int _size;
    std::unordered_map<std::string, std::unique_ptr<IAccess> > _addresses;
    const int _word_size = 4;
};