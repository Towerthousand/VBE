#include "tools.hpp"

//extern'd in tools.hpp
sf::ContextSettings CONTEXT_SETTINGS_OPENGL(32, 32, 0, 4, 2);
const float DEG_TO_RAD = float(M_PI)/180.0f;
int SCRWIDTH = sf::VideoMode::getFullscreenModes()[0].width;
int SCRHEIGHT = sf::VideoMode::getFullscreenModes()[0].height;
const sf::Clock GLOBALCLOCK;
