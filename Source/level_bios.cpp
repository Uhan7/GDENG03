#include "level_bios.h"

#include <algorithm>
#include <fstream>
#include <sstream>

// PARSING BULLSHI BC NO LIBRARIES !!! CURSES !!! ---------------------------------------------

static std::string Trim(const std::string& text){
    size_t start = text.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";

    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

static bool ParseJsonStringValue(const std::string& line, std::string& outValue){
    size_t colon = line.find(':');
    if (colon == std::string::npos) return false;

    size_t firstQuote = line.find('"', colon);
    if (firstQuote == std::string::npos) return false;

    size_t secondQuote = line.find('"', firstQuote + 1);
    if (secondQuote == std::string::npos) return false;

    outValue = line.substr(firstQuote + 1, secondQuote - firstQuote - 1);
    return true;
}

static bool ParseJsonVec3Value(const std::string& line, glm::vec3& outValue){
    size_t leftBracket = line.find('[');
    size_t rightBracket = line.find(']');
    if (leftBracket == std::string::npos || rightBracket == std::string::npos) return false;

    std::string values = line.substr(leftBracket + 1, rightBracket - leftBracket - 1);
    std::replace(values.begin(), values.end(), ',', ' ');

    std::istringstream iss(values);
    return static_cast<bool>(iss >> outValue.x >> outValue.y >> outValue.z);
}

static bool ParseJsonBoolValue(const std::string& line, bool& outValue){
    size_t colon = line.find(':');
    if (colon == std::string::npos) return false;

    std::string valueText = Trim(line.substr(colon + 1));

    if (!valueText.empty() && valueText.back() == ','){
        valueText.pop_back();
    }
    if (valueText == "true"){
        outValue = true;
        return true;
    }
    if (valueText == "false"){
        outValue = false;
        return true;
    }

    return false;
}

// Actual saving stuff go here ----------------------------------
bool SaveLevelToFile(const LevelData& level, const std::string& filePath){
    std::ofstream file(filePath);
    if (!file.is_open()) return false;

    // Then JSON format
    file << "{\n";
    file << "  \"objects\": [\n";

    for (size_t i = 0; i < level.objects.size(); i++){
        const LevelObject& object = level.objects[i];

        file << "    {\n";
        file << "      \"type\": \"" << PrimitiveTypeToString(object.type) << "\",\n";
        file << "      \"position\": [" << object.position.x << ", " << object.position.y << ", " << object.position.z << "],\n";
        file << "      \"rotation\": [" << object.rotation.x << ", " << object.rotation.y << ", " << object.rotation.z << "],\n";
        file << "      \"scale\": [" << object.scale.x << ", " << object.scale.y << ", " << object.scale.z << "],\n";
        file << "      \"hasRigidBody\": " << (object.hasRigidBody ? "true" : "false") << "\n";
        file << "    }";

        if (i < level.objects.size() - 1) file << ",";

        file << "\n";
    }

    file << "  ]\n";
    file << "}\n";

    return true;
}

bool LoadLevelFromFile(LevelData& level, const std::string& filePath){
    std::ifstream file(filePath);
    if (!file.is_open()) return false;

    LevelData loadedLevel;

    std::string line;
    bool insideObjectsArray = false;
    bool isBuildingObject = false;

    LevelObject currentObject;
    bool foundType = false;
    bool foundPosition = false;
    bool foundRotation = false;
    bool foundScale = false;
    bool foundRigidBodyField = false;

    while (std::getline(file, line)){
        std::string trimmed = Trim(line);

        if (trimmed.find("\"objects\"") != std::string::npos){
            insideObjectsArray = true;
            continue;
        }

        if (!insideObjectsArray) continue;

        if (trimmed == "]" || trimmed == "],"){
            insideObjectsArray = false;
            continue;
        }

        if (trimmed == "{"){
            currentObject = LevelObject{};
            foundType = false;
            foundPosition = false;
            foundRotation = false;
            foundScale = false;
            foundRigidBodyField = false;
            isBuildingObject = true;
            continue;
        }

        if (trimmed == "}" || trimmed == "},"){
            if (isBuildingObject && foundType && foundPosition && foundRotation && foundScale && foundRigidBodyField) loadedLevel.objects.push_back(currentObject);

            isBuildingObject = false;
            continue;
        }

        if (!isBuildingObject) continue;

        if (trimmed.find("\"type\"") != std::string::npos){
            std::string typeText;
            if (ParseJsonStringValue(trimmed, typeText)) foundType = StringToPrimitiveType(typeText, currentObject.type);
        }
        else if (trimmed.find("\"position\"") != std::string::npos) foundPosition = ParseJsonVec3Value(trimmed, currentObject.position);
        else if (trimmed.find("\"rotation\"") != std::string::npos) foundRotation = ParseJsonVec3Value(trimmed, currentObject.rotation);
        else if (trimmed.find("\"scale\"") != std::string::npos) foundScale = ParseJsonVec3Value(trimmed, currentObject.scale);
        else if (trimmed.find("\"hasRigidBody\"") != std::string::npos) foundRigidBodyField = ParseJsonBoolValue(trimmed, currentObject.hasRigidBody);
    }

    level = loadedLevel;
    return true;
}
