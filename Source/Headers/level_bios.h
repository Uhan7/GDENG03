#pragma once

#include <string>

#include "level_data.h"

bool SaveLevelToFile(const LevelData& level, const std::string& filePath);
bool LoadLevelFromFile(LevelData& level, const std::string& filePath);