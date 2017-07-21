#include <application.hpp>
#include <logic.hpp>

#include "human_view.hpp"


int main(int argc, char** argv) {

    Application app;

    Application::Options opts;
    opts.title = "ALPHA";
    opts.width = 1280;
    opts.height = 720;
    opts.updateRate = 60;

    if (app.Initialize(opts)) {

        app.AttachView(new HumanView);

        app.Run();
    }

    app.Shutdown();

    return 0;
}

