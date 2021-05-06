#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

void play_with_computer();
void play_with_friend();

int main()
{ 
  char vidp; //User's answer
  do {
  cout << "*** Choose mode to play ***\n"
		   <<"Mode 0 : With computer\n"
		   <<"Mode 1 : With another player\n";

	int mode; // Mode of playing
  
  cout << "Select mode: " <<"\n";
  while (!(cin >> mode)){        //пока не будет введено нормальное число, выполняем цикл
        cout << "Wrong input \n"; //сообщаем об ошибке ввода
        cout << "Choose between 0 and 1 mode: " <<"\n";         
        cin.clear();                //сбрасываем коматозное состояние cin
        fflush(stdin);              //очищаем поток ввода
    }

	if (mode) {
		play_with_friend();
	}
	else {
		play_with_computer();
	}
    cout << "\nContinue (Y - yes)? "; // Запит на продовження роботи
    while ((vidp = getchar()) == ' ' || vidp == '\n' || vidp == '\t');
  } while (vidp == 'Y' || vidp == 'y'); // умова повтору програми
  cout << "Have a nice day! :)";
  return 0;
}
/* Player vs Computer.
*  Computer fill a number with random value,
*  then player just try to guess it.*/
void play_with_computer(){
  
  srand(time(NULL));
  time_t start, end;

    int num, guess, tries = 0;
    srand(time(0)); //seed random number generator
    num = rand() % 100 + 1; // random number between 1 and 100
    cout <<setw(70)<< "Guess a number!\n\n" << num << endl;

    do
    {
      cout << "Enter number between 1 and 100 : ";
      cin >> guess; //користувач намагається вгадати число
      start = clock();
      if (guess < 1 || guess > 100) cout << "range from 1 to 100, but you have entered " << guess << endl << endl;
      else if (guess < num) {
        if (num - guess < 5) cout << "so close, but ";
        cout << "too low, let`s try one more time\n\n";
        tries++;
      }
      else if (guess > num) {
        if (guess - num < 5) cout << "so close, but ";
        cout << "too much, let`s try one more time\n\n";
        tries++;
      }
      else
        cout << "\nRighhttt! You guess with " << tries << " tries!\n";
    } while (guess != num);

  end = clock();
  cout << "You played " << double(end - start) / CLOCKS_PER_SEC << " seconds";
}

/*We have two players (player vs player). 
 *First one should enter a number,
 *than second one would try to guess it.
 *First player could also set the amount of tries that second player could do*/
void play_with_friend(){
  char vidp;
  srand(time(NULL));
  time_t start, end;
    
    int num, guess, tries = 0,amount_of_tries;
    cout << "First player enter a number: \n";
    cin >> num;
    cout << "And amount of tries, that second player could do: \n";
    cin >> amount_of_tries;

    for (int prop = 0; prop < 100; prop++) cout << endl;
    cout <<setw(70)<< "Second player,try to guess a number in " << amount_of_tries<< " tries!"<< endl;

    do
    {
      cout << "Enter number between 1 and 100 : ";
      cin >> guess;
      start = clock();
      if (guess < 1 || guess > 100) cout << "range from 1 to 100, but you have entered " << guess << endl << endl;
      else if (guess < num) {
        if (num - guess < 5) cout << "so close, but ";
        cout << "too low, let`s try one more time\n\n";
        tries++;
      }
      else if (guess > num) {
        if (guess - num < 5) cout << "so close, but ";
        cout << "too much, let`s try one more time\n\n";
        tries++;
      }
      else{
        cout << "\nRighhttt! You guess with " << tries << " tries!\n";
        if(tries > amount_of_tries) // check who won
          cout << "First player win! \n";
        else
          cout << "Second player win! \n";
      }
    } while (guess != num);

  end = clock();
  cout << "You played " << double(end - start) / CLOCKS_PER_SEC << " seconds";
}
