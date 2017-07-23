#include "scene.hpp"
#include "renderer.hpp"



// SceneCamera

void SceneCamera::Draw(Renderer* r) {
    r->SetProjection(GetProjection());
    r->SetView(GetView());

    DrawChildren(r);
}


// SceneObject

void SceneObject::Draw(Renderer* r) {
    r->PushTransform(transform);

    r->DrawMesh(mesh, shader);
    DrawChildren(r);

    r->PopTransform();
}


// Scene

void Scene::Initialize(SceneCamera* camera) {
    root.reset(camera);
}


void Scene::Shutdown() {
    root.reset(nullptr);
}


void Scene::Draw(Renderer* r) {
    root->Draw(r);
}


SceneCamera* Scene::GetCamera() {
    return root.get();
}

