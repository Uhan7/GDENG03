#include "level_bios.h"

#include <fstream>

bool SaveLevelToFile(const LevelData& level, const std::string& filePath){
    std::ofstream file(filePath);
    if (!file.is_open()) return false;

    file << "{\n";
    file << "  \"objects\": [\n";

    for (size_t i = 0; i < level.objects.size(); i++){
        const LevelObject& object = level.objects[i];

        // JSON gaming typeshi below
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
    // We'll do this in the next step.
    return false;
}