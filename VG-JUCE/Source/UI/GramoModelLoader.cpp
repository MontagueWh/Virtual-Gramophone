#include <JuceHeader.h>
#include "GramoModelLoader.h"

GramoModelLoader::GramoModelLoader() {}

GramoModelLoader::~GramoModelLoader() {}

void GramoModelLoader::resized() {}

void GramoModelLoader::newOpenGLContextCreated() // Initialise OpenGL resources here
{
    // Create shaders, VBOs, VAOs

    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 view;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = projection * view * vec4(aPos, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
        "}\n\0";
    // Create and compile shaders (not shown for brevity)

    for (auto& mesh : meshes)
    {
        // *** Create and configure VBOs, VAOs, EBOs ***
        glGenVertexArrays(1, &mesh.vao);
        glBindVertexArray(mesh.vao);

        glGenBuffers(1, &mesh.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
        glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(float), mesh.vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &mesh.ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);
    }
}

void GramoModelLoader::renderOpenGL()
{
    // Perform OpenGL rendering here

    // Clear buffer
    // Set projection and view matrices (from camera)
    // Bind VAO
    // Draw elements

     // *** OpenGL Rendering ***
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    // Set projection and view matrices
    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    for (const auto& mesh : meshes)
    {
        glBindVertexArray(mesh.vao);
        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
    }
}

void GramoModelLoader::openGLContextClosing()
{
    // Clean up OpenGL resources here
 
    // Delete VBOs, VAOs, shaders
}


bool GramoModelLoader::importModel(const std::string& pFile)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(pFile,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    const aiCamera* sceneCamera = scene->mNumCameras > 0 ? scene->mCameras[0] : nullptr; // Get first camera (or none)

    processNode(scene->mRootNode, scene, sceneCamera); // Pass camera to processNode

    // Clear previous data
    meshes.clear();

    // Process the root node
    processNode(scene->mRootNode, scene);

    modelLoaded = true;
    return true;
}

bool GramoModelLoader::isModelLoaded() const
{
    return modelLoaded;
}

void GramoModelLoader::renderModel(juce::Graphics& g, const juce::Rectangle<float>& bounds)
{
    if (!modelLoaded)
        return;

    // Scale and center the scene from the FBX
    float scaleX = bounds.getWidth() / 5.0f;
    float scaleY = bounds.getHeight() / 5.0f;
	juce::Point<float> center = bounds.getCentre();

    for (const auto& mesh : meshes)
    {
        for (size_t i = 0; i < mesh.indices.size(); i += 3)
        {
            auto v1 = juce::Point<float>(
                mesh.vertices[mesh.indices[i] * 3] * scaleX + center.x,
                mesh.vertices[mesh.indices[i] * 3 + 1] * scaleY + center.y
            );

            auto v2 = juce::Point<float>(
                mesh.vertices[mesh.indices[i + 1] * 3] * scaleX + center.x,
                mesh.vertices[mesh.indices[i + 1] * 3 + 1] * scaleY + center.y
            );

            auto v3 = juce::Point<float>(
                mesh.vertices[mesh.indices[i + 2] * 3] * scaleX + center.x,
                mesh.vertices[mesh.indices[i + 2] * 3 + 1] * scaleY + center.y
            );

            g.drawLine(juce::Line<float>(v1, v2), 1.0f);
            g.drawLine(juce::Line<float>(v2, v3), 1.0f);
            g.drawLine(juce::Line<float>(v3, v1), 1.0f);
        }
    }
}

GramoModelLoader::MeshData GramoModelLoader::processMesh(aiMesh* mesh)
{
    MeshData meshData;

    std::vector<MeshData> meshes;
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        // Positions
        meshData.vertices.push_back(mesh->mVertices[i].x);
        meshData.vertices.push_back(mesh->mVertices[i].y);
        meshData.vertices.push_back(mesh->mVertices[i].z);

        // Normals
        if (mesh->HasNormals())
        {
            meshData.normals.push_back(mesh->mNormals[i].x);
            meshData.normals.push_back(mesh->mNormals[i].y);
            meshData.normals.push_back(mesh->mNormals[i].z);
        }

        // Texture Coordinates
        if (mesh->HasTextureCoords(0))
        {
            meshData.texCoords.push_back(mesh->mTextureCoords[0][i].x);
            meshData.texCoords.push_back(mesh->mTextureCoords[0][i].y);
        }
    }

    // Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            meshData.indices.push_back(face.mIndices[j]);
    }

    return meshData;
}

void GramoModelLoader::processNode(aiNode* node, const aiScene* scene, const aiCamera* camera)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

    if (camera)  // Process camera if available
        processCamera(camera);
}

void GramoModelLoader::processMaterial(aiMaterial* material)
{
    // Skipping material processing for now
}

void GramoModelLoader::processCamera(const aiCamera* camera)
{
	// Extract camera data if needed

        // *** Extract camera parameters and calculate view/projection matrices ***
    // Use glm functions like glm::lookAt, glm::perspective
    glm::vec3 position(camera->mPosition.x, camera->mPosition.y, camera->mPosition.z);
    glm::vec3 lookAt(camera->mLookAt.x, camera->mLookAt.y, camera->mLookAt.z);
    glm::vec3 up(camera->mUp.x, camera->mUp.y, camera->mUp.z);

    viewMatrix = glm::lookAt(position, lookAt, up);
    projectionMatrix = glm::perspective(glm::radians(camera->mFoV), camera->mAspect, 0.1f, 100.0f); // Adjust near/far
}