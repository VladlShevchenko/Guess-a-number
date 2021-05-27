#include "Header.h"																	// підключаємо хедерний файл

int main()
{
	Game game;
	Menu menu;
	GameMode gamemode;

	char vidp;																		// змінна для перевірки на продовження роботи програми

	game.set_console_output();
	time_t start, end;																// вводимо локальні змінні типу time_t для визначення початкового і кінцевого часу гри
	do {
		int mode;
		menu.choose_mode(mode);

		start = clock();															// присвоюємо змінній start час початку гри
		if (mode) {																	// якщо mode істина (mode == 1)
			gamemode.play_with_friend();											// викликаємо ф-цію play_with_friend ()
		}
		else {																		// якщо mode брехня (mode == 0)
			gamemode.play_with_computer();											// викликаємо ф-цію play_with_computer ()
		}
		int NotUsed = system("color 2");
		cout << "\nПродовжуємо (Y - yes)? ";										// пропозиція продовжити роботу
		while ((vidp = getchar()) == ' ' || vidp == '\n' || vidp == '\t');			// ігнорування пропусків
		NotUsed = system("color 7");
	} while (vidp == 'Y' || vidp == 'y');											// умова повторної роботи програми

	end = clock();																	// присвоюємо змінної end час початку гри
	game.get_game_time(start, end);
	system("pause");
	return 0;
}
