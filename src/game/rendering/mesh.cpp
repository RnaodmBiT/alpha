#include "mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


Mesh* Mesh::LoadResource(const std::string& filename) {
    Mesh* mesh = new Mesh;
    mesh->LoadFromFile(filename);
    return mesh;
}


void Mesh::LoadFromFile(const std::string& filename) {

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_ConvertToLeftHanded | aiProcess_ImproveCacheLocality);
    assert(scene && "Error loading mesh from file");

    parts.resize(scene->mNumMeshes);

    for (int m = 0; m < scene->mNumMeshes; ++m) {
        std::vector<vec3> vertices, normals;

        Part& part = parts[m];

        part.object.Initialize();
        part.object.Bind();

        part.vertexBuffer.Initialize();
        part.normalBuffer.Initialize();
        part.object.BindBuffer(part.vertexBuffer, 3, GL_FLOAT, false);
        part.object.BindBuffer(part.normalBuffer, 3, GL_FLOAT, false);

        const aiMesh* obj = scene->mMeshes[m];

        for (int i = 0; i < obj->mNumFaces; ++i) {
            for (int j = 0; j < 3; ++j) {
                int v = obj->mFaces[i].mIndices[j];
                aiVector3D p = obj->mVertices[v];
                aiVector3D n = obj->mNormals[v];
                vertices.push_back(vec3{ p.x, p.y, p.z });
                normals.push_back(vec3{ n.x, n.y, n.z });
            }
        }


        part.vertexBuffer.SetData(vertices);
        part.normalBuffer.SetData(normals);
        part.vertexCount = (int)vertices.size();


        const aiMaterial* material = scene->mMaterials[obj->mMaterialIndex];

        if (material) {
            aiColor3D color;
            material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
            part.diffuse = { color.r, color.g, color.b, 1 };
        } else {
            part.diffuse = { 1, 1, 0, 1 };
        }
    }
}


void Mesh::Draw(const Shader* shader, const mat4& projection, const mat4& view, const mat4& world) const {
    shader->Apply();
    shader->Get("projection") = projection;
    shader->Get("view") = view;
    shader->Get("world") = world;

    for (const Part& part : parts) {
        shader->Get("diffuse") = part.diffuse;
        part.object.Draw(part.vertexCount);
    }
}

