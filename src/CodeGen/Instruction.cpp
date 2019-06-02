#include <memory>
#include "Instruction.h"

std::string Instruction::Format(const std::map<std::string, std::string> &varsMapping) const {
    std::shared_ptr<const TempList> src = UsedVars();
    std::shared_ptr<const TempList> dst = DefinedVars();
    std::shared_ptr<const LabelList> jumps = JumpTargets();

    std::string instr;
    for (int i = 0; i < instruction.length(); ++i) {
        if (instruction[i] == '\'') {
            bool breakFlag = false;
            switch (instruction[++i]) {
                case 's': {
                    int n = instruction[++i] - '0';
                    instr += varsMapping.at(getTemp(src, n)->label);
                    break;
                }
                case 'd': {
                    int n = instruction[++i] - '0';
                    instr += varsMapping.at(getTemp(dst, n)->label);
                    break;
                }
                case 'j': {
                    int n = instruction[++i] - '0';
                    std::string name = getLabel(jumps, n)->label;
                    instr += varsMapping.find(name) != varsMapping.end() ?
                             varsMapping.at(name) : name;
                    break;
                }
                case 'l': {
                    instr += jumps->Head()->label + '\n';
                    breakFlag = true;
                    break;
                }
            }
            if (breakFlag) {
                break;
            }
        } else {
            instr += instruction[i];
        }
    }

    return instr;
}

std::string Instruction::Format() const {
    std::shared_ptr<const TempList> src = UsedVars();
    std::shared_ptr<const TempList> dst = DefinedVars();
    std::shared_ptr<const LabelList> jumps = JumpTargets();

    std::string instr;
    for (int i = 0; i < instruction.length(); ++i) {
        if (instruction[i] == '\'') {
            bool breakFlag = false;
            switch (instruction[++i]) {
                case 's': {
                    int n = instruction[++i] - '0';
                    instr += getTemp(src, n)->label;
                    break;
                }
                case 'd': {
                    int n = instruction[++i] - '0';
                    instr += getTemp(dst, n)->label;
                    break;
                }
                case 'j': {
                    int n = instruction[++i] - '0';
                    instr += getLabel(jumps, n)->label;
                    break;
                }
                case 'l': {
                    instr += jumps->Head()->label + '\n';
                    breakFlag = true;
                    break;
                }
            }
            if (breakFlag) {
                break;
            }
        } else {
            instr += instruction[i];
        }
    }

    return instr;
}

std::shared_ptr<const Temp> Instruction::getTemp(std::shared_ptr<const TempList> list, int tempNumber) const {
    if (tempNumber == 0) {
        return list->Head();
    }
    return getTemp(list->Tail(), tempNumber - 1);
}

std::shared_ptr<const Label> Instruction::getLabel(std::shared_ptr<const LabelList> list, int labelNumber) const {
    if (labelNumber == 0) {
        return list->Head();
    }
    return getLabel(list->Tail(), labelNumber - 1);
}