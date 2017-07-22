#pragma once
#include "rendering/renderer.hpp"

class IScreenElement {
public:
    virtual ~IScreenElement() { }

    virtual void Draw(Renderer*) = 0;
};


class TextElement : public IScreenElement {
public:
    TextElement(const vec2& position, const std::string& text, const vec4& color, int size) :
        position(position), text(text), color(color), size(size) { }

    void Draw(Renderer* r) {
        r->DrawText(position, text, color, size);
    }

private:
    std::string text;
    vec2 position;
    vec4 color;
    int size;
};


class ButtonElement : public IScreenElement {
public:
    struct Theme {
        vec4 Up, Down, Over;
    };

    ButtonElement(const vec2& position, const std::string& text, int size, const Theme& theme) :
        position(position), text(text), size(size), theme(theme) { }

    void Draw(Renderer* r) {
        r->DrawText(position, text, theme.Up, size);
    }

    // TODO: Some way of handling input and then triggering a callback.

private:
    std::string text;
    vec2 position;
    Theme theme;
    int size;
};

