
#include "Core/instance.h"
#include "Window/window.h"
#include "Time/clock.h"
#include "Time/scoped_timer.h"

void run();
void init();
void mainLoop();
void cleanup();

    void run() {
        init();
        mainLoop();
        cleanup();
    }

    Gem::Window::Window* window = nullptr;

    void init() {
        
        Gem::Core::GemInstance::getInstance().initialize();
        Gem::Core::ScopedTimer ott("Window init");
        
        window = new Gem::Window::Window(1000, 800, "Gem Engine");

    }

    void mainLoop() {
        Gem::Core::Clock clock = Gem::Core::Clock();
        clock.set_debugFps(1, 10);

        while (!window->should_close()) {
            
            window->get_inputs()->update(); // @todo: Add this somewhere else ( input or window else )
            window->handle_events();

            if (window->get_inputs()->is_key_pressed(SDL_SCANCODE_W))
                std::cout << "Moving Forward \n";
            
            // Rendering code will go here

            clock.update(10);
        }
    }

    void cleanup() {
        delete window;
    }

int main(int argc, char* argv[]) {
    
    try {
        run();
    } catch (const std::exception& e) {
        std::cerr << "Application Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
