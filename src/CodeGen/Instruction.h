#pragma once
#include <string>
#include <IRTree/Label.h>
#include <map>

class Instruction {
  public:
    explicit Instruction(const std::string &instruction_) :
        instruction(instruction_) {
    }

    virtual ~Instruction() {
    }

    virtual std::shared_ptr<const TempList> UsedVars() const = 0;
    virtual std::shared_ptr<const TempList> DefinedVars() const = 0;
    virtual std::shared_ptr<const LabelList> JumpTargets() const = 0;

    std::string Format(const std::map<std::string, std::string> &varsMapping) const;
    std::string Format() const;

    std::string GetInstr() const {
        return instruction;
    }

    void SetInstr(const std::string &instruction_) {
        instruction = instruction_;
    }

    std::string instruction;

  private:
    std::shared_ptr<const Temp> getTemp(std::shared_ptr<const TempList> list, int tempNumber) const;
    std::shared_ptr<const Label> getLabel(std::shared_ptr<const LabelList> list, int labelNumber) const;
};

class InstructionList {
  public:
    InstructionList(Instruction *_head, InstructionList *_tail) :
        head(_head), tail(_tail) {
    }

    std::shared_ptr<Instruction> head;
    std::shared_ptr<InstructionList> tail;
};

class InstrLabel : public Instruction {
  public:
    InstrLabel(const std::string &instructLine, std::shared_ptr<const Label> _label) :
        Instruction(instructLine), label(_label) {
    }

    std::shared_ptr<const TempList> UsedVars() const override {
        return nullptr;
    }

    std::shared_ptr<const TempList> DefinedVars() const override {
        return nullptr;
    }

    std::shared_ptr<const LabelList> JumpTargets() const override {
        return std::make_shared<LabelList>(label, nullptr);
    }

  private:
    std::shared_ptr<const Label> label;
};

class Move : public Instruction {
  public:
    Move(const std::string &assemblerLine, std::shared_ptr<const Temp> dest,
         std::shared_ptr<const Temp> src) :
        Instruction(assemblerLine), dest(dest), src(src) {
    }

    std::shared_ptr<const TempList> UsedVars() const override {
        return std::make_shared<TempList>(src, nullptr);
    }

    std::shared_ptr<const TempList> DefinedVars() const override {
        return std::make_shared<TempList>(dest, nullptr);
    }

    std::shared_ptr<const LabelList> JumpTargets() const override {
        return nullptr;
    }

  private:
    std::shared_ptr<const Temp> dest;
    std::shared_ptr<const Temp> src;
};

class Oper : public Instruction {
  public:
    Oper(const std::string &assemblerLine,
         std::shared_ptr<const TempList> dest,
         std::shared_ptr<const TempList> src,
         std::shared_ptr<const LabelList> jump) :
        Instruction(assemblerLine), jumpTargets(jump), dest(dest), src(src) {
    }

    Oper(const std::string &assemblerLine, std::shared_ptr<const TempList> dest, std::shared_ptr<const TempList> src) :
        Instruction(assemblerLine), dest(dest), src(src) {
    }

    std::shared_ptr<const TempList> UsedVars() const override {
        return src;
    }

    std::shared_ptr<const TempList> DefinedVars() const override {
        return dest;
    }

    std::shared_ptr<const LabelList> JumpTargets() const override {
        return jumpTargets;
    }

    std::string GetOperator() const {
        return instruction.substr(0, instruction.find(' '));
    }

  private:
    std::shared_ptr<const LabelList> jumpTargets;
    std::shared_ptr<const TempList> dest;
    std::shared_ptr<const TempList> src;
};