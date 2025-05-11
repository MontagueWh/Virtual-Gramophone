#pragma once

#include <JuceHeader.h>
#include <../Source/assimp/include/assimp/Importer.hpp>
#include <../Source/assimp/include/assimp/scene.h>
#include <../Source/assimp/include/assimp/postprocess.h>
#include <../Source/assimp/include/assimp/mesh.h>

class GramoModelLoader : public juce::Component, public juce::OpenGLRenderer
{
public:
    GramoModelLoader();
    ~GramoModelLoader() override;

    void resized() override;

    // Imports a model from the given file path. Returns true on success, false on failure.
    bool importModel(const std::string& pFile);

    // Checks if a model is currently loaded.
    bool isModelLoaded() const;

    // Renders the loaded model using JUCE's Graphics.
    void renderModel(juce::Graphics& g, const juce::Rectangle<float>& bounds);

private:
    struct MeshData
    {
        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<float> texCoords;
        std::vector<unsigned int> indices;
        unsigned int materialIndex; // Index to the material used by this mesh
    };

    // Processes a mesh and returns its data.
    MeshData processMesh(aiMesh* mesh);

    // Processes a node in the scene graph.
    void processNode(aiNode* node, const aiScene* scene);

    // Processes a material (currently unused).
    void processMaterial(aiMaterial* material);

    // Flag to indicate if a model is loaded.
    bool modelLoaded = false;

    // Stores the processed mesh data.
    std::vector<MeshData> meshes;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GramoModelLoader)
};