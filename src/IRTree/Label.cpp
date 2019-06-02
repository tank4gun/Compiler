#include "Label.h"
#include <map>

//template<>
//std::map<std::string, int> Label::counter = {};
//
//template<>
//std::map<std::string, int> Temp::counter = {};

std::shared_ptr<const Temp> TempList::Head() const
{
    return head;
}

std::shared_ptr<const TempList> TempList::Tail() const
{
    return tail;
}

std::shared_ptr<const Label> LabelList::Head() const
{
    return head;
}

std::shared_ptr<const LabelList> LabelList::Tail() const
{
    return tail;
}