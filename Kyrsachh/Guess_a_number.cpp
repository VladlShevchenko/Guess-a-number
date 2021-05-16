#include <iostream> // заголовочный файл с классами, функциями и переменными для организации ввода-вывода в языке программирования C++
#include <cstdlib> // заголовочный файл стандартной библиотеки языка С++, который содержит в себе функции, занимающиеся выделением памяти, контролем процесса выполнения программы, преобразованием типов и тд
#include <ctime> // Этот заголовочный файл содержит функции для работы со временем и датой в С++
#include <iomanip> // заголовочный файл, который содержит модификатор setw. С его помощью можно, как например на 60 и 101 строчке, установить ширину сдвига вывода поля.
#include <windows.h> // windows.h является Windows-конкретный файл заголовков для языка C++, который содержит заявления для всех функций в Windows API, все общие макросы, которые используются программистами окон, и все типы данных, используемых различными функциями и подсистем.
#include <mmsystem.h> // Windows Multimedia (файл ребёнок windows.h)
#pragma comment(lib, "winmm") // это директива компилятора, которая указывает Visual C++ оставить комментарий в сгенерированном объектном файле.

using namespace std;

void play_with_computer(); // ф-ция для игры с прораммой
void play_with_friend(); // ф-ция для игры с 2им человеком

int main()
{
	char vidp;																	// User's answer
	srand(time(NULL));															// ф-ция для генерации рандомных чисел
	time_t start, end;															// вводим локальные переменные типа time_t для опредиления начального и конечного времени игры
	do {
		cout << "*** Choose mode to play ***\n"
			<< "Mode 0 : With computer\n"
			<< "Mode 1 : With another player\n";

		int mode;																// Mode of playing

		cout << "Select mode: " << "\n";
		while (!(cin >> mode)) {												// пока не будет введено целочисельное число, выполняем цикл
			cout << "Wrong input \n";											// сообщаем об ошибке ввода
			cout << "Choose between 0 and 1 mode: " << "\n";					// просим ввести числа 1 или 0
			cin.clear();														// сбрасываем коматозное состояние cin
			fflush(stdin);														// очищаем поток ввода
		}
		start = clock();														// присваиваем переменной start время начала игры
		if (mode) {																// если mode истина(mode==1)
			PlaySoundA((LPCSTR)"go.wav", NULL, SND_FILENAME | SND_ASYNC);		// проигрываем звук go.wav
			play_with_friend();													// вызываем ф-цию play_with_friend()
		}
		else {																	// если mode ложь(mode==0)
			PlaySoundA((LPCSTR)"go.wav", NULL, SND_FILENAME | SND_ASYNC);		// проигрываем звук go.wav
			play_with_computer();												// вызываем ф-цию play_with_computer()
		}
		cout << "\nContinue (Y - yes)? ";									    // предложение продолжить работу
		while ((vidp = getchar()) == ' ' || vidp == '\n' || vidp == '\t');	    // игнорирование пропусков
	} while (vidp == 'Y' || vidp == 'y');										// условие повторной работы программы
	end = clock();																// присваиваем переменной start время начала игры
	cout << "You played " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Have a nice day! :)" << endl;
	return 0;
}
/* Player vs Computer.
*  Computer fill a number with random value,
*  then player just try to guess it.*/
void play_with_computer() {

	srand(time(NULL));															// ф-ция для генерации рандомных чисел

	int num, guess, tries = 0;													// вводим переменные num(загаданое число), guess(предположение пользователя) и tries(кол-во попыток)
	srand(time(0));																// генератор случайных чисел начального числа
	num = rand() % 100 + 1;														// присваиваем переменной num рандомное число между 1 и 100
	cout << setw(70) << "Guess a number!\n\n" << num << endl;					// задаём пропуск на 70 пропусков и выводим название игры

	do
	{
		cout << "Enter number between 1 and 100 : ";							// выводим диапазон загаданого числа
		cin >> guess;															// считывем предположение пользователя
		if (guess < 1 || guess > 100)											// если предположение пользователя выходит за заданые границы выводим предупреждение
			cout << "range from 1 to 100, but you have entered " << guess << endl << endl;	
		else if (guess < num) {													// если предположение пользователя меньше за истинное
			if (num - guess < 5) cout << "so close, but ";						// если предположение пользователя меньше за истинное и оч близко к нему выводим 2ю подсказку
			cout << "too low, let`s try one more time\n\n";						// выводим подсказку
			PlaySoundA((LPCSTR)"no-6.wav", NULL, SND_FILENAME | SND_ASYNC);		// проигрываем звук no-6.wav
			tries++;															// добавляем +одну попытку
		}
		else if (guess > num) {													// если предположение пользователя больше за истинное
			if (guess - num < 5) cout << "so close, but ";						// если предположение пользователя больше за истинное и очень близко к нему выводим 2ю подсказку
			cout << "too much, let`s try one more time\n\n";					// выводим подсказку
			PlaySoundA((LPCSTR)"no-4.wav", NULL, SND_FILENAME | SND_ASYNC);		// проигрываем звук no-4.wav
			tries++;															// добавляем +одну попытку
		}
		else {
			cout << "\nRighhttt! You guess with " << tries << " tries!\n";		// выводим информацию о том, что пользователь угадал(его предположение == истинному числу)
			PlaySoundA((LPCSTR)"woohoo.wav", NULL, SND_FILENAME | SND_ASYNC);	// проигрываем звук woohoo.wav
		}
	} while (guess != num);														// повторяем цыкл, пока пользователь не угадает число
}

/*We have two players (player vs player).
 *First one should enter a number,
 *than second one would try to guess it.
 *First player could also set the amount of tries that second player could do*/
void play_with_friend() {
	char vidp;
	srand(time(NULL));															// ф-ция для генерации рандомных чисел

	int num, guess, tries = 0, amount_of_tries;									// вводим переменные num(загаданое число), guess(предположение пользователя), tries(кол-во попыток) и amount_of_tries(максимальное кол-во попыток)
	cout << "First player enter a number: \n";
	cin >> num;
	cout << "And amount of tries, that second player could do: \n";
	cin >> amount_of_tries;

	for (int prop = 0; prop < 100; prop++) cout << endl;
	cout << setw(70) << "Second player,try to guess a number in " << amount_of_tries << " tries!" << endl;

	do
	{
		cout << "Enter number between 1 and 100 : ";
		cin >> guess;
		if (guess < 1 || guess > 100) cout << "range from 1 to 100, but you have entered " << guess << endl << endl;
		else if (guess < num) {
			if (num - guess < 5) {
				cout << "so close, but ";
			}
			cout << "too low, let`s try one more time\n\n";
			PlaySoundA((LPCSTR)"no-4.wav", NULL, SND_FILENAME | SND_ASYNC);
			tries++;
		}
		else if (guess > num) {
			if (guess - num < 5) {
				cout << "so close, but ";
			}
			cout << "too much, let`s try one more time\n\n";
			PlaySoundA((LPCSTR)"no-6.wav", NULL, SND_FILENAME | SND_ASYNC);
			tries++;
		}
		else {
			cout << "\nRighhttt! You guess with " << tries << " tries!\n";
			if (tries > amount_of_tries) {// check who won
				cout << "First player win! \n";
				PlaySoundA((LPCSTR)"woohoo.wav", NULL, SND_FILENAME | SND_ASYNC); //
			}


			else {
				cout << "Second player win! \n";
				PlaySoundA((LPCSTR)"woohoo.wav", NULL, SND_FILENAME | SND_ASYNC);
			}

		}
	} while (guess != num);
}
