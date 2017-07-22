#include <application.hpp>
#include "rendering/renderer.hpp"
#include "screen.hpp"
#include "main_menu.hpp"

class HumanView : public IGameView {
public:
    void OnAttach(Application* app) {
        renderer.Initialize(app);

        PushElement(new MainMenuElement);
    }

    void Update(float dt) {
    }

    void Draw() {
        renderer.DrawScene();

        for (auto& element : screenElements) {
            element->Draw(&renderer);
        }
    }

    void PushElement(IScreenElement* element) {
        screenElements.emplace_back(element);
    }

    void RemoveElement(IScreenElement* element) {
        auto it = std::remove_if(screenElements.begin(), screenElements.end(), [element] (const std::unique_ptr<IScreenElement>& ptr) {
            return ptr.get() == element;
        });
        screenElements.erase(it, screenElements.end());
    }

private:
    std::vector<std::unique_ptr<IScreenElement>> screenElements;
    Renderer renderer;
};

