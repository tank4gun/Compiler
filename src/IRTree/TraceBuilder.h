#pragma once
#include "IIRStm.h"

class TraceBuilder {
  public:
    explicit TraceBuilder(std::unique_ptr<std::vector<std::unique_ptr<const IRStmList>>> blocks_);
    std::unique_ptr<std::vector<std::unique_ptr<const IRStmList>>> BuildTraces();

  private:
    // Заполняет словари парами (метка блока, jump метка блока)
    void buildMaps();
    bool hasJumpLabel(int id) const;
    bool formingTrace(int id) const;
    void addTrace(int id);

    std::unique_ptr<std::vector<std::unique_ptr<const IRStmList>>> blocks;
    std::vector<bool> visited;
    std::unique_ptr<std::vector<std::unique_ptr<const IRStmList>>> traces;
    std::map<std::string, int> LabelToId;
    std::map<int, std::string> IdToLabel;
    std::map<int, std::shared_ptr<std::string>> IdToJump;
};