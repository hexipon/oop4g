#include"Game.h"
int main()
{
	Player player;
	Game twoDiceGame(&player);
	std::cout << "\n________________________";
	std::cout << "\nGame starting...";
	twoDiceGame.displayData();
	std::cout << "\n________________________";
	twoDiceGame.run();
	std::cout << "\n________________________";
	std::cout << "\nGame ended...";
	twoDiceGame.displayData();
	std::cout << "\n________________________\n";

	system("pause");
	return 0;
}
