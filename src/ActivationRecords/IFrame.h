#pragma once
#include "SymbolTable/Symbol.h"
#include "IFrame.h"
#include "IAccess.h"
#include <string>
#include <map>
#include <memory>
#include <unordered_map>
#include "IRTree/IIRExp.h"


class IFrame{
  public:
    ~IFrame() = default;
    virtual void AddAddr(const std::string& name, IAccess* addr) = 0;
    virtual void AddFormal(const std::string& name) = 0;
    virtual void AddLocal(const std::string& name) = 0;
    virtual IAccess* GetAccess(const std::string& name) = 0;

    virtual const std::string& Name() const = 0;
    virtual IIRExp* CallFunction(const std::string& func_name, IIRExp* arg) const = 0;
    virtual int WordSize() const = 0;
};


class MiniJavaFrame : public IFrame {
  public:
    MiniJavaFrame(const Symbol* class_symb, const Symbol* method_symb) {
      _name = class_symb->String() + "::" + method_symb->String();
      _size = 0;
      Temp frame_pointer("FRAME_POINTER");
      Temp ths("THIS");
      Temp ret_val("RETURN_VALUE");
      AddAddr("FRAME_POINTER", new CInRegAccess(frame_pointer));
      AddAddr("THIS", new CInRegAccess(ths));
      AddAddr("RETURN_VALUE", new CInRegAccess(ret_val));
    }

    void AddAddr(const std::string& name, IAccess* addr) override {
      _addresses[name] = std::unique_ptr<IAccess>(addr);
    }

    void AddFormal(const std::string& name) override {
      AddAddr(name, new CInFrameAccess(GetAccess("THIS"), _size));
      _size += _word_size;
    }

    void AddLocal(const std::string& name) override {
      AddAddr(name, new CInFrameAccess(GetAccess("FRAME_POINTER"), _size));
      _size += _word_size;
    }

    const std::string& Name() const override {
      return _name;
    }

    IIRExp* CallFunction(const std::string& func_name, IIRExp* args) const override {
      return new CallExp(new NameExp(Label(func_name)), new IRExpList(args));
    }

    IAccess* GetAccess(const std::string& name) override {
      auto element = _addresses.find(name);
      if (element != _addresses.end()) {
        return element->second.get();
      }
      return nullptr;
    }
    int WordSize() const override {
        return _word_size;
    }

  private:
    std::string _name;
    int _size;
    std::unordered_map<std::string, std::unique_ptr<IAccess> > _addresses;
    int _word_size = 4;
};