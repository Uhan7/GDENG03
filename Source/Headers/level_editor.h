#pragma once

#include <array>
#include <string>

#include "level_data.h"

struct LevelEditorState{
    int selectedObjectIndex = -1;
    std::array<char, 256> filePath = {"sample.level"};
};

void CreateDefaultLevel(LevelData& level);
bool LoadLevelOrCreateDefault(LevelData& level, const std::string& filePath);
void DrawLevelEditor(LevelData& level, LevelEditorState& editorState);
