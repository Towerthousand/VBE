#include "Game.hpp"
#include "SceneMain/SceneMain.hpp"
int main() {
	if(Game::init()) {
		Game::setRoot(new SceneMain());
		Game::run();
	}
	return 42;
}
