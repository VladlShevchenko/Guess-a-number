#include "Header.h"																	// підключаємо хедерний файл

void Game::set_console_output() {
	SetConsoleOutputCP(1251);														// додаємо можливість виводити українські літери в консоль
}
void Game::get_game_time(time_t start, time_t end) {
	cout << "Ви грали " << int(end - start) / CLOCKS_PER_SEC << " секунд" << endl;
	cout << "Гарного дня! :)" << endl;
}

void Menu::choose_mode(int& mode) {
	cout << "*** Оберіть режим гри! ***\n"
		<< "Режим 0 : Гра проти комп'ютера\n"
		<< "Режим 1 : Гра проти іншого гравця\n";

	cout << "Введіть номер режиму: " << "\n";
	cin >> mode;

	while (cin.fail() || mode < 0 || mode > 1) {									// поки не буде введено ціле число, виконуємо цикл
		cin.clear();																// скидаємо коматозний стан cin
		cin.ignore(LONG__MAX, '\n');
		int color = system("color 4");
		play_error();
		cout << "Помилка вводу. Введіть 0 або 1: ";									// повідомляємо про помилку введення
		cin >> mode;																// просимо ще раз ввести число
		color = system("color 7");
	}
	play_intro();																	// програємо звук go.wav
}

/* Player vs Computer.
*  Computer fill a number with random value,
*  then player just try to guess it.*/
void GameMode::play_with_computer() {
	srand(time(NULL));																// ф-ція для генерації рандомних чисел

	int num, guess, tries = 1;														// вводимо змінні num (задумане число), guess (припущення користувача) і tries (к-ть спроб)
	srand(time(0));																	// генератор випадкових чисел для генерації початкового числа
	num = rand() % 100 + 1;															// присвоюємо змінній num рандомноє число між 1 і 100
	cout << setw(70) << "Вгадай число!\n\n" << num << endl;							// задаємо пропуск на 70 пробілів і виводимо назву гри

	do
	{
		cout << "Введіть число від 1 до 100: ";										// виводимо діапазон загаданого числа
		cin >> guess;																// зчитуючи припущення користувача в змінну guess

		while (cin.fail() || guess < MIN_NUMBER || guess > MAX_NUMBER) {			// поки не буде введено ціле число, виконуємо цикл
			cin.clear();															// скидаємо коматозний стан cin
			cin.ignore(LONG__MAX, '\n');
			int color = system("color 4");
			cout << "Помилка вводу. Введіть ЧИСЛО від 1 до 100: ";					// повідомляємо про помилку введення
			play_error();
			cin >> guess;															// просимо ще раз ввести число
			color = system("color 7");
		}

		if (guess < MIN_NUMBER || guess > MAX_NUMBER)								// якщо припущення користувача виходить за задані межі виводимо попередження
			cout << "Діапазон від 1 до 100, а було введено число " << guess << endl << endl;
		else if (guess < num) {														// якщо припущення користувача менше за дійсне
			if (num - guess < 5) cout << "дууже близько, але й досі менше ніж потрібно " << endl;			// якщо припущення користувача менше за дійсне і дуже близьке до нього виводимо 2гу підказку
			else
				cout << "занадто мало, спробуй ще раз\n\n";							// виводимо підказку
			play_no();			// проигрываем звук no-6.wav
			tries++;																// додаємо ще одну спробу
		}
		else if (guess > num) {														// якщо припущення користувача більше за дійсне
			if (guess - num < 5) cout << "дуже близько, але досі більше ніж потрібно " << endl;	// якщо припущення користувача більше за справжнє і дуже близьке до нього виводимо 2гу підказку
			else
				cout << "забагато, спробуй ще раз\n\n";								// виводимо підказку
			play_no();		// проигрываем звук no-4.wav
			tries++;																// додаємо ще одну спробу
		}
		else {
			cout << "\nВііітаємо, це правильна відповідь! Ви використали " << tries << " спроб!\n";			// виводимо інформацію про те, що користувач вгадав (його припущення == загадоне число)
			play_congatulation();													// програємо звук woohoo.wav
		}
	} while (guess != num);
}

/*We have two players (player vs player).
 *First one should enter a number,
 *than second one would try to guess it.
 *First player could also set the amount of tries that second player could do*/
void GameMode::play_with_friend() {

	srand(time(NULL));															// ф-ція для генерації рандомних чисел

	int num, guess, tries = 1, amount_of_tries;									// вводимо змінні num (задумане число), guess (припущення користувача), tries (к-ть спроб) і amount_of_tries (максимальна к-ть спроб)
	cout << "First player загадує число: \n";									// зчитуємо введену змінну num
	cin >> num;

	while (cin.fail() || num < 1 || num > 100)									// поки не буде введено ціле число, виконуємо цикл
	{
		cin.clear();															// скидаємо коматозний стан cin
		cin.ignore(LONG__MAX, '\n');
		int color = system("color 4");
		play_error();
		cout << "Помилка вводу. Введіть ЧИСЛО від 1 до 100  : ";				// повідомляємо про помилку введення
		cin >> num;																// просимо ще раз ввести число
		color = system("color 7");
	}

	cout << "Кількість спроб, яка надається для Second player: \n";
	cin >> amount_of_tries;														// зчитуємо введену змінну amount_of_tries 

	while (cin.fail()) {														// поки не буде введено целочісельное число, виконуємо цикл
		cin.clear();															// скидаємо коматозний стан cin
		cin.ignore(LONG__MAX, '\n');
		int color = system("color 4");
		play_error();
		cout << "Помилка вводу. Введіть ЧИСЛО: ";								// сообщаем об ошибке вводаскидаємо коматозний стан cin
		cin >> amount_of_tries;													// просимо ще раз ввести число
		color = system("color 7");
	}

	for (int prop = 0; prop < 100; prop++)
		cout << endl;
	cout << setw(70) << "Second player, спробуй вгадати це число за " << amount_of_tries << " спроб!" << endl; // задаємо пропуск на 70 пробілів і виводимо к-сть спроб

	do
	{
		cout << "Введіть число від 1 до 100: ";									// виводимо діапазон задуманого числа
		cin >> guess;															// зчитуючи припущення користувача

		while (cin.fail() || guess < MIN_NUMBER || guess > MAX_NUMBER) {		// поки не буде введено ціле число, виконуємо цикл
			cin.clear();														// скидаємо коматозний стан cin
			cin.ignore(LONG__MAX, '\n');
			int color = system("color 4");
			play_error();
			cout << "Помилка вводу. Введіть ЧИСЛО від 1 до 100: ";				// повідомляємо про помилку введення
			cin >> guess;														// просимо ще раз ввести число
			color = system("color 7");
		}

		if (guess < MIN_NUMBER || guess > MAX_NUMBER)							// якщо припущення користувача виходить за задані межі виводимо попередження
			cout << "Діапазон від 1 до 100, а було введено число " << guess << endl << endl;
		else if (guess < num) {													// якщо припущення користувача менше за дійсне
			if (num - guess < 5) cout << "дуже близько, але й досі менше ніж потрібно" << endl;		// якщо припущення користувача менше за дійсне і дуже близьке до нього виводимо 2гу підказку
			else
				cout << "занадто мало, спробуй ще раз\n\n";						// виводимо підказку
			play_no();															// програємо звук no-4.wav
			tries++;															// додаємо ще одну спробу
		}
		else if (guess > num) {													// якщо припущення користувача більше за дійсне
			if (guess - num < 5) cout << "дууже близько, але досі більше ніж потрібно" << endl;		// якщо припущення користувача менше за дійсне і дуже близьке до нього виводимо 2гу підказку
			else
				cout << "забагато, спробуй ще раз\n\n";							// виводимо підказку
			play_no();															// програємо звук no-6.wav
			tries++;															// додаємо ще одну спробу
		}
		else {
			cout << "\nВііітаємо, це правильна відповідь! Ви використали " << tries << " спроб!\n";			// виводимо інформацію про те, що користувач вгадав (його припущення == істинне число) і про к-сть спроб
			if (tries > amount_of_tries) {										// якщо к-сть спроб більша за максимальну задану 1-им користувачем
				cout << "First player переміг! \n";								// виводимо інформацію про те, що переміг перший гравець
				play_congatulation();
			}
			else {
				cout << "Second player переміг! \n";							// виводимо інформацію про те, що переміг другий гравець
				play_congatulation();
			}

		}
	} while (guess != num);
}

void Game::play_intro() {
	PlaySoundA((LPCSTR)"go.wav", NULL, SND_FILENAME | SND_ASYNC);				// програємо звук go.wav
}

void Game::play_no() {															// додаємо Випадкове вибір звуку, аби смороду Постійно НЕ повторювалісь, та не надокучалі гравця
	int num = rand() % 2;
	cout << num;
	if (num)
		PlaySoundA((LPCSTR)"no-4.wav", NULL, SND_FILENAME | SND_ASYNC);			// програємо звук no-4.wav
	else
		PlaySoundA((LPCSTR)"no-6.wav", NULL, SND_FILENAME | SND_ASYNC);			// програємо звук no-6.wav
}
void Game::play_congatulation() {
	PlaySoundA((LPCSTR)"woohoo.wav", NULL, SND_FILENAME | SND_ASYNC);			// програємо звук woohoo.wav
}

void Game::play_error()
{
	PlaySoundA((LPCSTR)"error0606.wav", NULL, SND_FILENAME | SND_ASYNC);			// програємо звук error0606.wav
}
