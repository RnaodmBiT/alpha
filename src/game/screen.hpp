#pragma once
#include <string>
#include <vector>
#include <maths.hpp>
#include "rendering/renderer.hpp"

class IScreenElement {
public:
    virtual ~IScreenElement() { }

    virtual void Draw(Renderer*) = 0;

    virtual bool HandleKeyboardEvent(KeyboardEvent* event) { return false; }
    virtual bool HandleMouseEvent(MouseEvent* event) { return false; }
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
        int Padding;
    };

    ButtonElement(const vec2& position, const std::string& text, const Theme& theme, int size, std::function<void()> callback) :
        position(position), text(text), size(size), theme(theme), callback(callback), state(Up) { }

    void Draw(Renderer* r) {
        vec4 color = theme.Up;
        color = state == Over ? theme.Over : color;
        color = state == Down ? theme.Down : color;

        r->DrawText(position, text, color, size);

        // Calculate the size of the button if we haven't already done so.
        if (bounds.x == 0 && bounds.y == 0) {
            bounds = r->MeasureText(text, size);
        }
    }

    bool HandleMouseEvent(MouseEvent* event) {
        vec2 mouse = { (float)event->X, (float)event->Y };

        if (event->Type == MouseEvent::Moved) {
            if (state == Up && IsInside(mouse)) {
                state = Over;
            } else if (state == Over && !IsInside(mouse)) {
                state = Up;
            }

            if (state == DownButOut && IsInside(mouse)) {
                state = Down;
            } else if (state == Down && !IsInside(mouse)) {
                state = DownButOut;
            }
        }

        if (event->Type == MouseEvent::Pressed && state == Over && event->Button == SDL_BUTTON_LEFT) {
            state = Down;
        }

        if (event->Type == MouseEvent::Released && event->Button == SDL_BUTTON_LEFT) {
            if (state == Down) {
                callback();
                state = Over;
                return true;
            }

            if (state != Over) {
                state = Up;
            }
        }

        return false;
    }

private:

    bool IsInside(vec2 p) {
        float top = position.y - (float)theme.Padding;
        float left = position.x - (float)theme.Padding;
        float right = position.x + bounds.x + (float)theme.Padding;
        float bottom = position.y + bounds.y + (float)theme.Padding;
        return p.x >= left && p.x <= right && p.y >= top && p.y <= bottom;
    }

    enum { Up, Over, Down, DownButOut } state;
    std::string text;
    vec2 position, bounds;
    Theme theme;
    int size;
    std::function<void()> callback;
};

