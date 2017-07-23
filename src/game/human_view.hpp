#include <application.hpp>
#include "rendering/renderer.hpp"
#include "screen.hpp"
#include "main_menu.hpp"

class HumanView : public IGameView {
public:
    void OnAttach(Application* app) {
        time = 0;

        camera = new SceneCamera;
        camera->SetProjection(1.0f, 3.1415f / 4.0f, 0.1f, 100.0f);
        camera->SetPosition({ -3.0f, -2.0f, -4.0f });
        camera->SetDirection({ 3.0f, 2.0f, 4.0f });
        camera->SetUp({ 0.0f, 1.0f, 0.0f });

        shader.LoadFromFiles("shaders/object.vert", "shaders/object.frag");

        mesh.LoadFromFile("models/P90.dae");
        mesh.SetShader(&shader);

        SceneObject* object = new SceneObject(&mesh);
        camera->PushNode(object);

        renderer.Initialize(app, camera);

        Events.Register<MouseEvent>(this, &HumanView::HandleMouseEvent);
        Events.Register<KeyboardEvent>(this, &HumanView::HandleKeyboardEvent);

        PushElement(new MainMenuElement);
    }

    void OnDetach(Application* app) {
        Events.Unregister<MouseEvent>(this);
        Events.Unregister<KeyboardEvent>(this);
    }

    void Update(float dt) {
        time += dt;

        vec3 pos = { 5 * sin(time), 2, 5 * cos(time) };
        camera->SetPosition(pos);
        camera->SetDirection(-pos);

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

private:
    std::vector<std::unique_ptr<IScreenElement>> screenElements;
    Renderer renderer;

    Mesh mesh;
    Shader shader;

    SceneCamera* camera;

    float time;
};

