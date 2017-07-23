#include "mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void Mesh::LoadFromFile(const std::string& filename) {
    object.Initialize();
    vertexBuffer.Initialize();
    object.BindBuffer(vertexBuffer, 3, GL_FLOAT, false);

    std::vector<vec3> vertices;

    // TODO: Load the mesh using Assimp
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_ConvertToLeftHanded | aiProcess_ImproveCacheLocality);
    assert(scene && "Error loading mesh from file");

    for (int m = 0; m < scene->mNumMeshes; ++m) {
        const aiMesh* obj = scene->mMeshes[m];

        for (int i = 0; i < obj->mNumFaces; ++i) {
            for (int j = 0; j < 3; ++j) {
                int v = obj->mFaces[i].mIndices[j];
                aiVector3D p = obj->mVertices[v];
                aiVector3D n = obj->mNormals[v];
                vertices.push_back(vec3{ p.x, p.y, p.z });
                // normals.push_back(vec3{ n.x, n.y, n.z });
            }
        }
    }

    vertexBuffer.SetData(vertices);
    vertexCount = (int)vertices.size();
}


void Mesh::Draw() const {
    object.Draw(vertexCount);
}

