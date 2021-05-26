#include "Header.h" //добавляем хедерный файл

int main()
{
	Game game;
	Menu menu;
	GameMode gamemode;

	char vidp;																		// переменная для проверки на продолжения работы программы
														
	game.set_console_output();
	time_t start, end;																// вводим локальные переменные типа time_t для опредиления начального и конечного времени игры
	do {
		int mode;
		menu.choose_mode(mode);

		start = clock();															// присваиваем переменной start время начала игры
		if (mode) {																	// если mode истина(mode==1)
			gamemode.play_with_friend();											// вызываем ф-цию play_with_friend()
		}
		else {																		// если mode ложь(mode==0)
			gamemode.play_with_computer();											// вызываем ф-цию play_with_computer()
		}

		cout << "\nПродовжуємо (Y - yes)? ";										// предложение продолжить работу
		while ((vidp = getchar()) == ' ' || vidp == '\n' || vidp == '\t');			// игнорирование пропусков
	} while (vidp == 'Y' || vidp == 'y');											// условие повторной работы программы
	
	end = clock();																	// присваиваем переменной start время начала игры
	game.get_game_time(start, end);
	return 0;
}
