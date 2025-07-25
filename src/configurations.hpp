#pragma once
#include <SFML/Window.hpp>

namespace conf
{
// Window Configuration
sf::Vector2u const window_size = {1420, 1420};
sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size);
const uint32_t max_framerate = 60;
float const dt = 1.0f/static_cast<float>(max_framerate);

}