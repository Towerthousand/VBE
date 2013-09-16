#include "Game.hpp"
#include "SceneMain/SceneMain.hpp"
int main() {
	Game myGame;
	if(myGame.init()) {
		myGame.setRoot(new SceneMain(myGame));
		myGame.run();
	}
	return 42;
}
