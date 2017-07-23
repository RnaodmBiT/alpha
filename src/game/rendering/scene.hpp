#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <maths.hpp>
#include "mesh.hpp"

class Renderer;
class ISceneNode;

typedef std::unique_ptr<ISceneNode> NodePtr;
typedef std::vector<NodePtr> NodeList;

class ISceneNode {
public:
    virtual ~ISceneNode() { }

    virtual void Draw(Renderer* r) = 0;

    void PushNode(ISceneNode* node) {
        nodes.emplace_back(node);
    }

    void RemoveNode(ISceneNode* node) {
        auto it = std::remove_if(nodes.begin(), nodes.end(), [node] (const NodePtr& ptr) { return ptr.get() == node; });
        nodes.erase(it, nodes.end());
    }

protected:
    void DrawChildren(Renderer* r) {
        for (NodePtr& child : nodes) {
            child->Draw(r);
        }
    }

private:

    NodeList nodes;
};



// A SceneCamera is used to say how/where to render the scene from.
class SceneCamera : public ISceneNode {
public:

    void SetPosition(const vec3& p) { position = p; }
    void SetDirection(const vec3& d) { direction = d; }
    void SetUp(const vec3& u) { up = u; }

    const vec3& GetPosition() const { return position; }
    const vec3& GetDirection() const { return direction; }
    const vec3& GetUp() const { return up; }

    void SetProjection(float aspectRatio, float fieldOfView, float nearClipPlane, float farClipPlane) {
        aspect = aspectRatio;
        fov = fieldOfView;
        nearClip = nearClipPlane;
        farClip = farClipPlane;
    }

    void SetAspectRatio(float ar) {
        aspect = ar;
    }

    mat4 GetProjection() const {
        return perspective(fov, aspect, nearClip, farClip);
    }

    mat4 GetView() const {
        return look_at(position, position + direction, up);
    }

    void Draw(Renderer* r);

private:
    vec3 position, direction, up;
    float aspect, fov, nearClip, farClip;
};


// A SceneObject is a 3D mesh with a transform that can be drawn to the screen
class SceneObject : public ISceneNode {
public:

    SceneObject(const Mesh* mesh, mat4 transform = mat4()) : transform(transform), mesh(mesh) { }

    const mat4& GetTransform() const { return transform; }
    void SetTransform(mat4 t) { transform = t; }

    void Draw(Renderer* r);

private:
    mat4 transform;
    const Mesh* mesh;
};


// A Scene is a tree of nodes that describe how to render a 3D scene.
class Scene {
public:

    void Initialize(SceneCamera* camera);
    void Shutdown();

    void Draw(Renderer* r);

    SceneCamera* GetCamera();

private:
    std::unique_ptr<SceneCamera> root;
};



