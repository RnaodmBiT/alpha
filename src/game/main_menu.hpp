#include "screen.hpp"

class MainMenuElement : public IScreenElement {
public:
    MainMenuElement() {
        PushElement(new TextElement({ 50, 50 }, "- ALPHA -", { 1, 1, 1, 1 }, 5));
    }

    void Draw(Renderer* r) {
        for (auto& element : elements) {
            element->Draw(r);
        }
    }

private:

    void PushElement(IScreenElement* element) {
        elements.emplace_back(element);
    }

    std::vector<std::unique_ptr<IScreenElement>> elements;

};

