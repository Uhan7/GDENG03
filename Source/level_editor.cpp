#include "level_editor.h"

#include <iostream>
#include <string>

#include <imgui/imgui.h>

#include "level_bios.h"

LevelObject MakeDefaultLevelObject(PrimitiveType type){
    LevelObject object;
    object.type = type;

    if (type == PrimitiveType::Plane){
        object.position = glm::vec3(0.0f, 0.0f, 0.0f);
        object.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        object.scale = glm::vec3(8.0f, 1.0f, 8.0f);
    }
    else if (type == PrimitiveType::Cube){
        object.position = glm::vec3(0.0f, 0.0f, 0.0f);
        object.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        object.scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }
    else if (type == PrimitiveType::Sphere){
        object.position = glm::vec3(0.0f, 0.0f, 0.0f);
        object.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        object.scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }
    else if (type == PrimitiveType::Capsule){
        object.position = glm::vec3(0.0f, 0.0f, 0.0f);
        object.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        object.scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    return object;
}

// Clamp as safety check
void ClampSelectedObjectIndex(const LevelData& level, LevelEditorState& editorState){
    if (level.objects.empty()) editorState.selectedObjectIndex = -1;
    else if (editorState.selectedObjectIndex >= static_cast<int>(level.objects.size())) editorState.selectedObjectIndex = static_cast<int>(level.objects.size()) - 1;
}

void AddLevelObject(LevelData& level, PrimitiveType type, LevelEditorState& editorState){
    level.objects.push_back(MakeDefaultLevelObject(type));
    editorState.selectedObjectIndex = static_cast<int>(level.objects.size()) - 1;
}

void DrawLevelObjectList(LevelData& level, LevelEditorState& editorState){
    ImGui::Text("Objects: %d", static_cast<int>(level.objects.size()));

    for (int i = 0; i < static_cast<int>(level.objects.size()); i++){
        std::string label = std::to_string(i) + " - " + PrimitiveTypeToString(level.objects[i].type);
        if (ImGui::Selectable(label.c_str(), editorState.selectedObjectIndex == i)) editorState.selectedObjectIndex = i;
    }
}

void DrawSelectedLevelObjectEditor(LevelData& level, LevelEditorState& editorState){
    ClampSelectedObjectIndex(level, editorState);
    if (editorState.selectedObjectIndex < 0 || editorState.selectedObjectIndex >= static_cast<int>(level.objects.size())) return;

    const char* primitiveOptions[] = {"Plane", "Cube", "Sphere", "Capsule"};

    LevelObject& selectedObject = level.objects[editorState.selectedObjectIndex];
    int primitiveIndex = static_cast<int>(selectedObject.type);

    ImGui::Separator();
    ImGui::Text("Selected Object");

    if (ImGui::Combo("Type", &primitiveIndex, primitiveOptions, IM_ARRAYSIZE(primitiveOptions))) selectedObject.type = static_cast<PrimitiveType>(primitiveIndex);

    ImGui::DragFloat3("Position", &selectedObject.position.x, 0.1f);
    ImGui::DragFloat3("Rotation", &selectedObject.rotation.x, 1.0f);
    ImGui::DragFloat3("Scale", &selectedObject.scale.x, 0.1f);
    ImGui::Checkbox("Has Rigid Body", &selectedObject.hasRigidBody);

    if (ImGui::Button("Delete Selected")){
        level.objects.erase(level.objects.begin() + editorState.selectedObjectIndex);
        ClampSelectedObjectIndex(level, editorState);
    }
}

void CreateDefaultLevel(LevelData& level){
    level.objects.clear();
    level.objects.push_back(MakeDefaultLevelObject(PrimitiveType::Plane));
    level.objects.push_back(MakeDefaultLevelObject(PrimitiveType::Capsule));
}

bool LoadLevelOrCreateDefault(LevelData& level, const std::string& filePath){
    if (LoadLevelFromFile(level, filePath)){
        std::cout << "Loaded " << level.objects.size() << " object(s)\n";
        return true;
    }

    std::cout << filePath << " not found, creating default level\n";
    CreateDefaultLevel(level);

    if (SaveLevelToFile(level, filePath)) std::cout << "Created " << filePath << " successfully\n";
    else std::cout << "Failed to create " << filePath << "\n";

    return false;
}

void DrawLevelEditor(LevelData& level, LevelEditorState& editorState){
    ImGui::Begin("Level Editor");

    ImGui::InputText("Level File", editorState.filePath.data(), editorState.filePath.size());

    if (ImGui::Button("New Level")){
        CreateDefaultLevel(level);
        editorState.selectedObjectIndex = -1;
    }

    ImGui::SameLine();

    if (ImGui::Button("Load Level")){
        if (LoadLevelFromFile(level, editorState.filePath.data())){
            std::cout << "Loaded " << level.objects.size() << " object(s)\n";
            editorState.selectedObjectIndex = -1;
        }
        else std::cout << "Failed to load " << editorState.filePath.data() << "\n";
    }

    ImGui::SameLine();

    if (ImGui::Button("Save Level")){
        if (SaveLevelToFile(level, editorState.filePath.data())) std::cout << "Saved " << editorState.filePath.data() << "\n";
        else std::cout << "Failed to save " << editorState.filePath.data() << "\n";
    }

    ImGui::Separator();

    if (ImGui::Button("Add Plane")) AddLevelObject(level, PrimitiveType::Plane, editorState);
    ImGui::SameLine();
    if (ImGui::Button("Add Cube")) AddLevelObject(level, PrimitiveType::Cube, editorState);
    ImGui::SameLine();
    if (ImGui::Button("Add Sphere")) AddLevelObject(level, PrimitiveType::Sphere, editorState);
    ImGui::SameLine();
    if (ImGui::Button("Add Capsule")) AddLevelObject(level, PrimitiveType::Capsule, editorState);

    ImGui::Separator();

    DrawLevelObjectList(level, editorState);
    DrawSelectedLevelObjectEditor(level, editorState);

    ImGui::End();
}
