#include <JuceHeader.h>
#include "GramoModelLoader.h"

GramoModelLoader::GramoModelLoader() {}

GramoModelLoader::~GramoModelLoader() {}

void GramoModelLoader::resized() {}

bool GramoModelLoader::importModel(const std::string& pFile)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(pFile,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    if (!scene || !scene->mRootNode)
    {
        juce::Logger::writeToLog("Failed to load model: " + juce::String(pFile));
        modelLoaded = false;
        return false;
    }

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

    // Scale and center the model within the given bounds
    float scale = std::min(bounds.getWidth(), bounds.getHeight()) / 2.0f;
	juce::Point<float> center = bounds.getCentre();

    for (const auto& mesh : meshes)
    {
        for (size_t i = 0; i < mesh.indices.size(); i += 3)
        {
            auto v1 = juce::Point<float>(
                mesh.vertices[mesh.indices[i] * 3] * scale + center.x,
                mesh.vertices[mesh.indices[i] * 3 + 1] * scale + center.y
            );

            auto v2 = juce::Point<float>(
                mesh.vertices[mesh.indices[i + 1] * 3] * scale + center.x,
                mesh.vertices[mesh.indices[i + 1] * 3 + 1] * scale + center.y
            );

            auto v3 = juce::Point<float>(
                mesh.vertices[mesh.indices[i + 2] * 3] * scale + center.x,
                mesh.vertices[mesh.indices[i + 2] * 3 + 1] * scale + center.y
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

void GramoModelLoader::processNode(aiNode* node, const aiScene* scene)
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
}

void GramoModelLoader::processMaterial(aiMaterial* material)
{
    // Skipping material processing for now
}