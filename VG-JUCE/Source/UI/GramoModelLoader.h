#pragma once

#include <JuceHeader.h>

#include <../Source/Libs/assimp/include/assimp/Importer.hpp>
#include <../Source/Libs/assimp/include/assimp/scene.h>
#include <../Source/Libs/assimp/include/assimp/postprocess.h>
#include <../Source/Libs/assimp/include/assimp/mesh.h>
#include <../Source/Libs/assimp/include/assimp/camera.h>

/*#include <../Source/glm/glm.hpp> //  For basic GLM types
#include <../Source/glm/glm/gtc/matrix_transform.hpp> //  For transformations (translate, rotate, scale)
#include <../Source/Libs/glm/glm/gtc/type_ptr.hpp>   //  For glm::value_ptr (to pass matrices to OpenGL)
#include <../Source/Libs/glm/glm/ext/matrix_clip_space.hpp> // For perspective projection*/


class GramoModelLoader : public juce::Component, public juce::OpenGLRenderer
{
public:
    GramoModelLoader();
    ~GramoModelLoader() override;

    void resized() override;
    void newOpenGLContextCreated() override;
	void renderOpenGL() override;
	void openGLContextClosing() override;

    // Imports a model from the given file path. Returns true on success, false on failure.
    bool importModel(const std::string& pFile);

    // Checks if a model is currently loaded.
    bool isModelLoaded() const;

    // Renders the loaded model using JUCE's Graphics.
    void renderModel(juce::Graphics& g, const juce::Rectangle<float>& bounds);

    // Processes a node in the scene graph.
    void processNode(aiNode* node, const aiScene* scene, const aiCamera* camera);

    // Processes a material (currently unused).
    void processMaterial(aiMaterial* material);

    void processCamera(const aiCamera* camera); // Extract camera data

private:
    struct MeshData
    {
        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<float> texCoords;
        std::vector<unsigned int> indices;
        unsigned int materialIndex; // Index to the material used by this mesh

        GLuint vao;
        GLuint vbo;
        GLuint ebo; // Index buffer
    };

    // Processes a mesh and returns its data.
    MeshData processMesh(aiMesh* mesh);

    // Flag to indicate if a model is loaded.
    bool modelLoaded = false;

    // Stores the processed mesh data.
    std::vector<MeshData> meshes;

    
    glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
    {
        glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
        glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
        View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
        View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
        return Projection * View * Model;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GramoModelLoader)
};