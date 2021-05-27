#pragma once
#include <iostream> // заголовочний файл з класами, функціями і змінними для організації введення-виведення в мові програмування C++
#include <cstdlib> // заголовочний файл стандартної бібліотеки мови С++, який містить в собі функції, які займаються виділенням пам'яті, контролем процесу виконання програми, перетворенням типів і тд
#include <ctime> // Цей заголовочний файл містить функції для роботи з часом і датою в С++
#include <iomanip> // заголовочний файл, який містить модифікатор setw. З його допомогою можна, як наприклад на 60 і 101 сходинці, встановити ширину зсуву виведення поля
#include <windows.h> // windows.h є Windows-конкретним файлом заголовків для мови C++, який містить заголовки для всіх функцій в Windows API, всі загальні макроси, які використовуються програмістами Windows, і всі типи даних, що використовуються різними функціями і підсистем
#include <mmsystem.h> // Windows Multimedia (файл-дитина windows.h)
#pragma comment(lib, "winmm") // це директива компілятора, яка вказує Visual C++ залишити коментар в створеному об'єктному файлі

using namespace std;

//#define SETCOLOR(COLOR) SetConsoleTextAttribute(hConsole, (WORD)((WHITE << 4) | COLOR));

#define RED 4
#define WHITE 15
static const streamsize  LONG__MAX = 9223372036854775807;
static const int  MAX_NUMBER = 100;							//  максимальне загадане число
static const int  MIN_NUMBER = 1;							//  мінімальне загадане число

// 
class Game {												// клас з ф-ціями інтерфейсу гри
protected:
	void play_intro();										// ф-ція програвання звуку початку гри
	void play_no();											// ф-ція програвання звуку невдачної спроби вгадати число
	void play_congatulation();								// ф-ція програвання звуку перемоги
	void play_error();										// ф-ція програвання звуку помилки

public:
	void set_console_output();								// ф-ція української локалізації
	void get_game_time(time_t start, time_t end);			// ф-ція для отримання часу проведеного в грі

};

// 
class Menu : public Game {									// клас-нащадок класу Game для вибору режиму гри
public:
	void choose_mode(int& mode);							// ф-ція для вибору режиму гри
};

//
class GameMode : public Game {								// клас-нащадок класу Game для режиму гри
public:
	void play_with_computer();								// ція для режиму гри з комп'ютером
	void play_with_friend();								// ція для режиму гри з іншим користувачем
};
