#include "Header.h"

void Game::set_console_output() {
	SetConsoleOutputCP(1251);														// добавляем возможность выводить українські літери в консоль
}

void Game::get_game_time(time_t start, time_t end) {
	cout << "Ви грали " << double(end - start) / CLOCKS_PER_SEC << " секунд" << endl;
	cout << "Гарного дня! :)" << endl;
}

void Menu::choose_mode(int& mode) {
	cout << "*** Оберіть режим гри! ***\n"
		<< "Режим 0 : Гра проти комп'ютера\n"
		<< "Режим 1 : Гра проти іншого гравця\n";

	cout << "Введіть номер режиму: " << "\n";
	cin >> mode;

	while (cin.fail() || mode < 0 || mode > 1) {									// пока не будет введено целочисельное число, выполняем цикл
		cin.clear();																// сбрасываем коматозное состояние cin
		cin.ignore(LONG__MAX, '\n');
		//SETCOLOR(RED);
		cout << "Помилка вводу. Введіть 0 або 1: ";									// сообщаем об ошибке ввода
		//SETCOLOR(WHITE);
		cin >> mode;																// просим ещё раз ввести число
	}

	play_intro();				// проигрываем звук go.wav
}

/* Player vs Computer.
*  Computer fill a number with random value,
*  then player just try to guess it.*/
void GameMode::play_with_computer() {
	srand(time(NULL));																// ф-ция для генерации рандомных чисел

	int num, guess, tries = 1;														// вводим переменные num(загаданое число), guess(предположение пользователя) и tries(кол-во попыток)
	srand(time(0));																	// генератор случайных чисел начального числа
	num = rand() % 100 + 1;															// присваиваем переменной num рандомное число между 1 и 100
	cout << setw(70) << "Вгадай число!\n\n" << num << endl;							// задаём пропуск на 70 пропусков и выводим название игры

	do
	{
		cout << "Введіть число від 1 до 100: ";										// выводим диапазон загаданого числа
		cin >> guess;																// считывем предположение пользователя

		while (cin.fail() || guess < MIN_NUMBER || guess > MAX_NUMBER) {																	// пока не будет введено целочисельное число, выполняем цикл
			cin.clear();															// сбрасываем коматозное состояние cin
			cin.ignore(LONG__MAX, '\n');
			cout << "Помилка вводу. Введіть ЧИСЛО від 1 до 100: ";					// сообщаем об ошибке ввода
			cin >> guess;															// просим ещё раз ввести число
		}

		if (guess < MIN_NUMBER || guess > MAX_NUMBER)								// если предположение пользователя выходит за заданые границы выводим предупреждение
			cout << "Діапазон від 1 до 100, а було введено число " << guess << endl << endl;
		else if (guess < num) {														// если предположение пользователя меньше за истинное
			if (num - guess < 5) cout << "дууже близько, але й досі менше ніж потрібно " << endl;			// если предположение пользователя меньше за истинное и оч близко к нему выводим 2ю подсказку
			else
				cout << "занадто мало, спробуй ще раз\n\n";							// выводим подсказку
			play_no();			// проигрываем звук no-6.wav
			tries++;																// добавляем +одну попытку
		}
		else if (guess > num) {														// если предположение пользователя больше за истинное
			if (guess - num < 5) cout << "дуже близько, але досі більше ніж потрібно " << endl;	// если предположение пользователя больше за истинное и очень близко к нему выводим 2ю подсказку
			else
				cout << "забагато, спробуй ще раз\n\n";								// выводим подсказку
			play_no();		// проигрываем звук no-4.wav
			tries++;																// добавляем +одну попытку
		}
		else {
			cout << "\nВііітаємо, це правильна відповідь! Ви використали " << tries << " спроб!\n";			// выводим информацию о том, что пользователь угадал(его предположение == истинному числу)
			play_congatulation();		// проигрываем звук woohoo.wav
		}
	} while (guess != num);
}

/*We have two players (player vs player).
 *First one should enter a number,
 *than second one would try to guess it.
 *First player could also set the amount of tries that second player could do*/
void GameMode::play_with_friend() {

	srand(time(NULL));															// ф-ция для генерации рандомных чисел

	int num, guess, tries = 1, amount_of_tries;									// вводим переменные num(загаданое число), guess(предположение пользователя), tries(кол-во попыток) и amount_of_tries(максимальное кол-во попыток)
	cout << "First player загадує число: \n";									// считываем введённую переменную num 
	cin >> num;

	while (cin.fail() || num < 1 || num > 100)									// пока не будет введено целочисельное число, выполняем цикл
	{
		cin.clear();															// сбрасываем коматозное состояние cin
		cin.ignore(LONG__MAX, '\n');
		cout << "Помилка вводу. Введіть ЧИСЛО від 1 до 100  : ";				// сообщаем об ошибке ввода
		cin >> num;																// просим ещё раз ввести число
	}

	cout << "Кількість спроб, яка надається для Second player: \n";
	cin >> amount_of_tries;														// считываем введённую переменную amount_of_tries 

	while (cin.fail()) {														// пока не будет введено целочисельное число, выполняем цикл
		cin.clear();															// сбрасываем коматозное состояние cin
		cin.ignore(LONG__MAX, '\n');
		cout << "Помилка вводу. Введіть ЧИСЛО: ";								// сообщаем об ошибке ввода
		cin >> amount_of_tries;													// просим ещё раз ввести число
	}

	for (int prop = 0; prop < 100; prop++)
		cout << endl;
	cout << setw(70) << "Second player, спробуй вгадати це число за " << amount_of_tries << " спроб!" << endl; // задаём пропуск на 70 пропусков и выводим кол попыток

	do
	{
		cout << "Введіть число від 1 до 100: ";									// выводим диапазон загаданого числа
		cin >> guess;															// считывем предположение пользователя

		while (cin.fail() || guess < MIN_NUMBER || guess > MAX_NUMBER) {																	// пока не будет введено целочисельное число, выполняем цикл
			cin.clear();														// сбрасываем коматозное состояние cin
			cin.ignore(LONG__MAX, '\n');
			cout << "Помилка вводу. Введіть ЧИСЛО від 1 до 100: ";				// сообщаем об ошибке ввода
			cin >> guess;														// просим ещё раз ввести число
		}

		if (guess < MIN_NUMBER || guess > MAX_NUMBER)							// если предположение пользователя выходит за заданые границы выводим предупреждение
			cout << "Діапазон від 1 до 100, а було введено число " << guess << endl << endl;
		else if (guess < num) {													// если предположение пользователя меньше за истинное
			if (num - guess < 5) cout << "дуже близько, але й досі менше ніж потрібно" << endl;							// если предположение пользователя меньше за истинное и оч близко к нему выводим 2ю подсказку
			else
				cout << "занадто мало, спробуй ще раз\n\n";						// выводим подсказку
			play_no();															// проигрываем звук no-4.wav
			tries++;															// добавляем +одну попытку
		}
		else if (guess > num) {													// если предположение пользователя больше за истинное
			if (guess - num < 5) cout << "дууже близько, але досі більше ніж потрібно" << endl;		// если предположение пользователя меньше за истинное и оч близко к нему выводим 2ю подсказку
			else
				cout << "забагато, спробуй ще раз\n\n";							// выводим подсказку
			play_no();															// проигрываем звук no-6.wav
			tries++;															// добавляем +одну попытку
		}
		else {
			cout << "\nВііітаємо, це правильна відповідь! Ви використали " << tries << " спроб!\n";			// выводим информацию о том, что пользователь угадал(его предположение == истинному числу) и о кол-ве попыток
			if (tries > amount_of_tries) {										// если кол попыток больше "максимального"
				cout << "First player переміг! \n";								// выводим информацию о том, что победил первый игрок
				play_congatulation();
			}
			else {
				cout << "Second player переміг! \n";								// выводим информацию о том, что победил второй игрок
				play_congatulation();
			}

		}
	} while (guess != num);
}

void Game::play_intro() {
	PlaySoundA((LPCSTR)"go.wav", NULL, SND_FILENAME | SND_ASYNC);						// проигрываем звук go.wav
}

void Game::play_no() {																	// додаємо випадковий вибір звуку, аби вони постійно не повторювались, та не надокучали гравцю
	int num = rand() % 2;
	cout << num;
	if(num)	
		PlaySoundA((LPCSTR)"no-4.wav", NULL, SND_FILENAME | SND_ASYNC);					// проигрываем звук no-4.wav
	else
		PlaySoundA((LPCSTR)"no-6.wav", NULL, SND_FILENAME | SND_ASYNC);					// проигрываем звук no-6.wav
}
void Game::play_congatulation() {
	PlaySoundA((LPCSTR)"woohoo.wav", NULL, SND_FILENAME | SND_ASYNC);					// проигрываем звук woohoo.wav
}
