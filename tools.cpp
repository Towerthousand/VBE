#include "tools.hpp"

//extern'd in tools.hpp
std::string WINDOW_TITLE = "Engine";
sf::ContextSettings CONTEXT_SETTINGS_OPENGL(32, 32, 0, 4, 2);
const float DEG_TO_RAD =  ((2.0*M_PI)/360.0);
float FOV =  60.0f;
float ZNEAR = 0.01f;
float ZFAR = 100.0f;
int SCRWIDTH = sf::VideoMode::getFullscreenModes()[0].width;
int SCRHEIGHT = sf::VideoMode::getFullscreenModes()[0].height;
bool WINDOWFOCUS = false;
const sf::Clock GLOBALCLOCK;
