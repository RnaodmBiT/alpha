#include "screen.hpp"

class MainMenuElement : public IScreenElement {
public:
    MainMenuElement() {


        ButtonElement::Theme buttonTheme;
        buttonTheme.Up = { 0.7f, 0.7f, 0.7f, 1.0f };
        buttonTheme.Over = { 1.0f, 1.0f, 1.0f, 1.0f };
        buttonTheme.Down = { 0.3f, 0.3f, 0.3f, 1.0f };
        buttonTheme.Padding = 3;

        PushElement(new TextElement({ 50, 50 }, "- ALPHA -", { 1, 1, 1, 1 }, 5));
        PushElement(new ButtonElement({ 50, 200 }, "Button", buttonTheme, 2, [] () { }));
        PushElement(new ButtonElement({ 50, 230 }, "Quit", buttonTheme, 2, [] () { Events.QueueEvent(new QuitEvent); }));
    }

    void Draw(Renderer* r) {
        for (auto& element : elements) {
            element->Draw(r);
        }
    }


    // Event management
    bool HandleKeybaordEvent(KeyboardEvent* event) {
        for (auto it = elements.rbegin(); it != elements.rend(); it++) {
            if ((*it)->HandleKeyboardEvent(event)) {
                return true;
            }
        }

        return false;
    }

    bool HandleMouseEvent(MouseEvent* event) {
        for (auto it = elements.rbegin(); it != elements.rend(); it++) {
            if ((*it)->HandleMouseEvent(event)) {
                return true;
            }
        }
        return false;
    }

private:

    void PushElement(IScreenElement* element) {
        elements.emplace_back(element);
    }

    std::vector<std::unique_ptr<IScreenElement>> elements;

};

