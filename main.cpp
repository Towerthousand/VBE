#include "Game.hpp"
#include "SceneMain/SceneMain.hpp"
int main() {
	if(Game::init()) {
		Game::setRoot(new SceneMain());
		Game::run();
		Game::close();
	}
	return 42;
}
