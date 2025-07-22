#include "events.hpp"

void ProcessEvents(sf::Window& window)
{
    while (const std::optional event = window.pollEvent())
        {
            // closes window if close button is clicked
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            // closes window if escape key is pressed
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
            }
        }
}