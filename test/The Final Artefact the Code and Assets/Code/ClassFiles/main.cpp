//Using SDL and standard IO
#include "Game.h"
enum Screensize : bool { DISABLE_FULLSCREEN = false, ENABLE_FULLSCREEN = true };

int main(int argc, char* args[])
{
	/*
	std::vector<int*> zahlen;
	printf("SIZE: %d\n", zahlen.size());
	zahlen.push_back(new int(12));
	int* a = new int(13);
	zahlen.push_back(a);
	zahlen.push_back(new int(14));

	printf("SIZE: %d\n", zahlen.size());
	zahlen.erase(zahlen.begin() + 1);
	printf("ERASE ONE ELEMENT\nSIZE: %d\n", zahlen.size());
	//zahlen.emplace(zahlen.begin() + 1, new int(3));

	for (int i = 0; i < zahlen.size(); i++) {
		printf("PLACE: %d, VALUE: %d\n",i,*zahlen.at(i));
	}
	zahlen.clear();

	printf("VALUE: %d\n", *a);

	system("pause");
	*/
	Game* game = new Game(ENABLE_FULLSCREEN);
	game->start();
	delete game;
	
	return 0;
};