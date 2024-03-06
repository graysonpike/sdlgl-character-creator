#include <sdlgl/game/clock.h>
#include <sdlgl/game/context.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/graphics/graphics.h>
#include <sdlgl/input/inputs.h>
#include <sdlgl/ui/entity_count.h>
#include <sdlgl/ui/fps_display.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "tilemap.h"

#define BACKGROUND_COLOR (SDL_Color){222, 222, 222, 255}

int main() {
    srand(time(NULL));

    // Load a window
    Graphics::initialize(1020, 768);
    Context context(std::make_shared<Clock>());
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    Resources::get_instance().load_resources("resources.json");

    Resources& resources = Resources::get_instance();

    while (*context.loop) {
        Graphics &graphics = Graphics::get_instance();
        Inputs &inputs = Inputs::get_instance();
        inputs.update();
        context.clock->tick();
        graphics.clear_screen(BACKGROUND_COLOR);

        room_tilemap.draw();

        scene->update(context.clock->get_delta());
        scene->render();

        if (inputs.get_quit()) {
            *context.loop = false;
        }

        graphics.present_renderer(context.clock->get_delta());
    }

    return 0;
}
