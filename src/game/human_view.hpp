#include <application.hpp>
#include <cache.hpp>
#include "rendering/renderer.hpp"
#include "screen.hpp"
#include "main_menu.hpp"
#include <components/common.hpp>


class HumanView : public IGameView {
public:
    void OnAttach(Application* app) {
        time = 0;

        LoadResources();


        camera = new SceneCamera;


        auto& scripting = app->GetScripting();
        LoadScripting(scripting);

        scripting.use("test.chai");
        auto main = scripting.eval<std::function<ScriptObject(HumanView*)>>("main");

        state = main(this);
        stateUpdate = scripting.eval<std::function<ScriptObject(ScriptObject, float)>>("Update");


        camera->SetSkybox("cube", "skybox", "skyboxShader");
        camera->SetProjection(app->GetAspectRatio(), 3.1415f / 4.0f, 0.1f, 100.0f);
        camera->SetUp({ 0.0f, 1.0f, 0.0f });


        renderer.Initialize(app, camera, "fontShader");

        Events.Register<MouseEvent>(this, &HumanView::HandleMouseEvent);
        Events.Register<KeyboardEvent>(this, &HumanView::HandleKeyboardEvent);
        Events.Register<ActorCreatedEvent>(this, &HumanView::HandleActorCreatedEvent);

        Events.QueueEvent(new RequestCreateActorEvent("test"));

        PushElement(new MainMenuElement);
    }

    void OnDetach(Application* app) {
        Events.Unregister<MouseEvent>(this);
        Events.Unregister<KeyboardEvent>(this);
        Events.Unregister<ActorCreatedEvent>(this);
    }

    void Update(float dt) {
        time += dt;
        state = stateUpdate(state, dt);
    }

    void Draw() {
        renderer.DrawScene();

        for (auto& element : screenElements) {
            element->Draw(&renderer);
        }
    }


    // Screen Element management
    void PushElement(IScreenElement* element) {
        screenElements.emplace_back(element);
    }

    void RemoveElement(IScreenElement* element) {
        auto it = std::remove_if(screenElements.begin(), screenElements.end(), [element] (const std::unique_ptr<IScreenElement>& ptr) {
            return ptr.get() == element;
        });
        screenElements.erase(it, screenElements.end());
    }

    // Event Management
    void HandleMouseEvent(MouseEvent* event) {
        for (auto it = screenElements.rbegin(); it != screenElements.rend(); ++it) {
            if ((*it)->HandleMouseEvent(event)) {
                return;
            }
        }
    }

    void HandleKeyboardEvent(KeyboardEvent* event) {
        for (auto it = screenElements.rbegin(); it != screenElements.rend(); ++it) {
            if ((*it)->HandleKeyboardEvent(event)) {
                return;
            }
        }
    }

    void HandleActorCreatedEvent(ActorCreatedEvent* event) {
        SceneObjectComponent* component = event->Object->GetComponent<SceneObjectComponent>();
        if (component) {
            SceneObject* obj = new SceneObject(Cache.Get<Mesh>(component->Mesh), Cache.Get<Shader>(component->Shader));
            camera->PushNode(obj);
            sceneElements[event->Object->GetID()] = std::make_pair(event->Object, obj);
        }
    }

    SceneCamera* GetCamera() {
        return camera;
    }

private:

    void LoadResources() {
        Cache.AddLoader("shader", &Shader::LoadResource);
        Cache.AddLoader("dae", &Mesh::LoadResource);
        Cache.AddLoader("png", &Texture::LoadResource);
        Cache.AddLoader("cubemap", &CubeMap::LoadResource);

        Cache.Load("fontShader", "shaders/font.shader");
        Cache.Load("objectShader", "shaders/object.shader");
        Cache.Load("skyboxShader", "shaders/skybox.shader");

        Cache.Load("cube", "models/cube.dae");
        Cache.Load("p90", "models/P90.dae");

        Cache.Load("skybox", "textures/skybox.cubemap");
    }

    void LoadScripting(Scripting& scripting) {
        // register the useful classes
        scripting.add(chaiscript::user_type<vec3>(), "vec3");
        scripting.add(chaiscript::constructor<vec3()>(), "vec3");
        scripting.add(chaiscript::fun([] (float x, float y, float z) { return vec3 { x, y, z }; }), "vec3");
        scripting.add(chaiscript::fun((float(vec3::*))&vec3::x), "x");
        scripting.add(chaiscript::fun((float(vec3::*))&vec3::y), "y");
        scripting.add(chaiscript::fun((float(vec3::*))&vec3::z), "z");
        scripting.add(chaiscript::fun((vec3 (*)(vec3, const vec3&))&operator-), "-");

        scripting.add(chaiscript::fun((float(*)(float))&std::sin), "sin");
        scripting.add(chaiscript::fun((float(*)(float))&std::cos), "cos");

        scripting.add(chaiscript::user_type<HumanView>(), "HumanView");
        scripting.add(chaiscript::fun(&HumanView::GetCamera), "GetCamera");


        Renderer::RegisterScripting(scripting);
    }

    ScriptObject state;
    std::function<ScriptObject(ScriptObject, float)> stateUpdate;

    std::vector<std::unique_ptr<IScreenElement>> screenElements;
    Renderer renderer;

    SceneCamera* camera;
    std::map<ActorID, std::pair<Actor*, ISceneNode*>> sceneElements;

    float time;
};

