#pragma once

#include <string>
#include <memory>

class Label {
  public:
    Label() = default;
    explicit Label(std::string label): label(std::move(label)) {}

    std::string label;
};

class Temp {
  public:
    Temp(): label("T" + std::to_string(counter++)) {}
    explicit Temp(std::string label): label(std::move(label)) {}

    const std::string label;
    static int counter;
};

class LabelList {
  public:
    LabelList(std::shared_ptr<const Label> _head, std::shared_ptr<const LabelList> _tail) :
        head(_head), tail(_tail) {
    }

    std::shared_ptr<const Label> Head() const;
    std::shared_ptr<const LabelList> Tail() const;
  private:
    std::shared_ptr<const Label> head;
    std::shared_ptr<const LabelList> tail;
};

class TempList {
  public:
    TempList(std::shared_ptr<const Temp> _head, std::shared_ptr<const TempList> _tail) :
        head(_head), tail(_tail) {
    }

    std::shared_ptr<const Temp> Head() const;
    std::shared_ptr<const TempList> Tail() const;

  private:
    std::shared_ptr<const Temp> head;
    std::shared_ptr<const TempList> tail;
};