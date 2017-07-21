#include <application.hpp>
#include <logic.hpp>



class AlphaApplication : public Application {
public:
    bool Initialize(Application::Options opts) {
        if (!Application::Initialize(opts)) {
            return false;
        }

        if (!logic.Initialize()) {
            return false;
        }

        return true;
    }

    void Shutdown() {
        logic.Reset();
    }

    void Update(float dt) {
        Events.UpdateQueue();
        logic.Update(dt);
    }

    void Draw() {
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

private:

    GameLogic logic;
};


int main(int argc, char** argv) {

    AlphaApplication app;

    Application::Options opts;
    opts.title = "ALPHA";
    opts.width = 1280;
    opts.height = 720;
    opts.updateRate = 60;

    if (app.Initialize(opts)) {
        app.Run();
    }

    app.Shutdown();

    return 0;
}

