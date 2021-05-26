#pragma once
#include <iostream> // заголовочный файл с классами, функциями и переменными для организации ввода-вывода в языке программирования C++
#include <cstdlib> // заголовочный файл стандартной библиотеки языка С++, который содержит в себе функции, занимающиеся выделением памяти, контролем процесса выполнения программы, преобразованием типов и тд
#include <ctime> // Этот заголовочный файл содержит функции для работы со временем и датой в С++
#include <iomanip> // заголовочный файл, который содержит модификатор setw. С его помощью можно, как например на 60 и 101 строчке, установить ширину сдвига вывода поля.
#include <windows.h> // windows.h является Windows-конкретный файл заголовков для языка C++, который содержит заявления для всех функций в Windows API, все общие макросы, которые используются программистами окон, и все типы данных, используемых различными функциями и подсистем.
#include <mmsystem.h> // Windows Multimedia (файл ребёнок windows.h)
#pragma comment(lib, "winmm") // это директива компилятора, которая указывает Visual C++ оставить комментарий в сгенерированном объектном файле.

using namespace std;

//#define SETCOLOR(COLOR) SetConsoleTextAttribute(hConsole, (WORD)((WHITE << 4) | COLOR));

#define RED 4
#define WHITE 15
static const long LONG__MAX = 9223372036854775807;
static const int  MAX_NUMBER = 100;
static const int  MIN_NUMBER = 1;

// 
class Game {
protected:
	void play_intro();
	void play_no();
	void play_congatulation();
	
public:
	void set_console_output();
	void get_game_time(time_t start, time_t end);

};

// 
class Menu : public Game {
public:
	void choose_mode(int& mode);
};

//
class GameMode : public Game {
public:
	void play_with_computer();
	void play_with_friend();
};

