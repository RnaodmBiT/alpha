#include <application.hpp>


class AlphaApplication : public Application {
public:
    void Update(float dt) {
    }

    void Draw() {
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};


int main(int argc, char** argv) {

    AlphaApplication app;

    Application::options opts;
    opts.title = "ALPHA";
    opts.width = 1280;
    opts.height = 720;

    if (app.Initialize(opts)) {
        app.Run();
    }

    app.Shutdown();

    return 0;
}

