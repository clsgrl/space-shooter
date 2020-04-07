#include "Game.h"
#include <stdlib.h>

// 2020-03-22: SFML / C++ Game Development 10 / 11 | 2D Space shooter

int main(int argc, char* argv[])
{
    short w = sf::VideoMode::getDesktopMode().width / 1.5;
    short h = sf::VideoMode::getDesktopMode().height / 1.5;
    if(argc > 2) {
      w = strtod( argv[1], 0 );
      h = strtod( argv[2], 0 );
    }
    else
    {
        w = 800;
        h = 600;
    }

    // Create the main window

    RenderWindow window(VideoMode(w, h), "Space", Style::Default);

    Game game(&window);

	// Start the game loop
    while (window.isOpen())
    {
        // Process events
        Event event;
        while (window.pollEvent(event))
        {
            switch(event.type) {
            // Close window : exit
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Escape){
                    window.close();
                }
                break;
            }
        }

        game.Update();
        game.Draw();
        // Clear screen
        //window.clear();

        // Draw the sprite
        //window.draw(sprite);

        // Update the window
        //window.display();
    }

    return EXIT_SUCCESS;
}
