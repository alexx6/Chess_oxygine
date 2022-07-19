#include "ox/oxygine.hpp"
#include "ox/Stage.hpp"
#include "ox/DebugActor.hpp"
#include "game.h"


using namespace oxygine;

int mainloop()
{
    bool done = core::update();

    getStage()->update();

    if (core::beginRendering())
    {
        Color clearColor(32, 32, 32, 255);
        Rect viewport(Point(0, 0), core::getDisplaySize());
        getStage()->render(clearColor, viewport);

        core::swapDisplayBuffers();
    }

    return done ? 1 : 0;
}

void run()
{
    ObjectBase::__startTracingLeaks();

    core::init_desc desc;
    desc.title = "Chess";

    desc.w = 1500;
    desc.h = 1000;


    core::init(&desc);

    Stage::instance = new Stage();
    Point size = core::getDisplaySize();
    getStage()->setSize(size);

    init();

    while (1)
    {
        int done = mainloop();
        if (done)
            break;
    }

    ObjectBase::dumpCreatedObjects();

    destroy();

    core::release();
    ObjectBase::dumpCreatedObjects();
    ObjectBase::__stopTracingLeaks();
}

#ifdef OXYGINE_SDL

#include "SDL_main.h"
#include "SDL.h"

extern "C"
{
    int main(int argc, char* argv[])
    {

        run();
        return 0;
    }
};
#endif