#include "TraceBuilder.h"
#include "BasicBlockBuilder.h"
#include "BasicBlockMarker.h"

TraceBuilder::TraceBuilder(std::unique_ptr<std::vector<std::unique_ptr<IRStmList>>> blocks_) :
    blocks(std::move(blocks_)),
    visited(blocks->size(), false),
    traces(new std::vector<std::unique_ptr<IRStmList>>()) {
    traces->reserve(blocks->size());
}

void TraceBuilder::buildMaps() {
    for (int id = 0; id < blocks->size(); ++id) {
        BasicBlockMarker blockMarker;

        blocks->at(id)->Accept(&blockMarker);
        std::string blockName = blockMarker.BlockLabel();
        LabelToId.emplace(blockName, id);
        IdToLabel.emplace(id, blockName);
        IdToJump.emplace(id, blockMarker.BlockJumpLabel());
    }
}

bool TraceBuilder::hasJumpLabel(int id) const {
    Label epilogueLabel(BasicBlockBuilder::EndName());

    return IdToJump.find(id) != IdToJump.end()
        && *IdToJump.at(id) != epilogueLabel.label;
}

bool TraceBuilder::formingTrace(int id) const {
    return id >= 0 && !visited[id];
}

void TraceBuilder::addTrace(int id) {
    auto stmPtr = blocks->at(id)->Copy();
    std::unique_ptr<IRStmList> blockPtr(reinterpret_cast<IRStmList *>( stmPtr.release()));
    traces->push_back(std::move(blockPtr));
}

std::unique_ptr<std::vector<std::unique_ptr<IRStmList>>> TraceBuilder::BuildTraces() {
    buildMaps();
    for (int start = 0; start < blocks->size(); start++) {
        int id = start;
        while (formingTrace(id)) {
            visited[id] = true;
            addTrace(id);
            if (hasJumpLabel(id)) {
                auto x = *IdToJump[id];
                id = LabelToId.at(x);
            } else {
                id = -1;
            }
        }
    }
    return std::move(traces);
}