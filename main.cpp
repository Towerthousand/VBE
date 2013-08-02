#include "Game.hpp"
int main() {
	Game myGame;
	//mkdir(std::string("data").c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if(myGame.init()) {
		myGame.setScene(new SceneMain(myGame));
		myGame.run();
	}
	return 42;
}
