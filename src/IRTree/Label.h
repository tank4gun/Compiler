#pragma once

#include <string>


class Label;

class Temp {
  public:
    std::string String() const
    {
        return label;
    }

  private:
    std::string label;
};