#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<string.h>
#include<string>
#include<ctime>
#include<windows.h>
#include<fstream>
using namespace std;
fstream myFile;
char name[30];
int life = 3;
int score = 0;
int  j=15, k=15, num;
int n = 1, m = 1; //packman pos
int o = 10, p = 10;//ghost1 pos
int q = 5, r = 5;//ghost2 pos
int s = 9, t = 2,a=2;//ghost3 pos
string arr[50][50];
enum eDirection {STOP=0,LEFT,RIGHT,UP,DOWN };
eDirection dira;
int frameColor = 12;
int dotColor = 14;
int whiteColor = 15;
HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
void setConsoleTextColor(int colorCode)
{
	SetConsoleTextAttribute(consoleHandle, colorCode);
}
struct scoring
{
	string Name[20];
	int Score;
}sco;
void leaderboard()
{
	cout << "\n\n";
	cout << "\t\t\t _______________________________________________________________________\n";
	cout << "\t\t\t|                                                                       |\n";
	cout << "\t\t\t|                              LEADERBOARD                              |\n";
	cout << "\t\t\t|                                                                       |\n";
	cout << "\t\t\t|_______________________________________________________________________|\n";
	cout << "\t\t\t|                                                                       |\n";
	cout << "\t\t\t|          NAME                                  SCORE                  |\n";
	cout << "\t\t\t|_______________________________________________________________________|\n";
}
void out()
{
	cout << "\n\n\n				 |||||||||||||   |||||||||||||   |||||||||||||   |||||||||||||\n";
	cout << "				 |||             |||       |||   |||  |||  |||   |||		  \n";
	cout << "				 |||             |||       |||   |||  |||  |||   |||		  \n";
	cout << "				 |||             |||       |||   |||  |||  |||   |||		  \n";
	cout << "				 |||             |||||||||||||   |||  |||  |||   |||||||||||||\n";
	cout << "				 |||     |||||   |||       |||   |||  |||  |||   |||		  \n";
	cout << "				 |||       |||   |||       |||   |||  |||  |||   |||		  \n";
	cout << "				 |||||||||||||   |||       |||   |||  |||  |||   |||||||||||||\n\n";

	cout << "				 |||||||||||||   |||       |||   |||||||||||||   |||||||||||||\n";
	cout << "				 |||       |||   |||       |||   |||             |||       |||\n";
	cout << "				 |||       |||   |||       |||   |||             |||	   |||\n";
	cout << "				 |||       |||   |||       |||   |||             |||       |||\n";
	cout << "				 |||       |||   |||       |||   |||||||||||||   |||||||||||||\n";
	cout << "				 |||       |||   |||       |||   |||             |||         |||\n";
	cout << "				 |||       |||   |||       |||   |||             |||           |||\n";
	cout << "				 |||||||||||||   |||||||||||||   |||||||||||||   |||             |||\n";
}
void ghost()
{
	arr[50][50];
	srand(time(NULL));
	random:
	num = rand() % 4;
	if (num == 0)//left
	{
		if (arr[o][p - 1] == "#")
		{
			goto random;
		}
		p--;
		if (arr[o][p] == " ")
		{
			arr[o][p + 1] = " ";
		}
		if (arr[o][p] == ".")
		{
			arr[o][p + 1] = ".";
		}
		if (arr[o][p] == "0")
		{
			arr[o][p + 1] = "0";
		}
		if (arr[o][p] == "*")
		{
			arr[o][p + 1] = "*";
		}
	}
	if (num == 1)//right
	{
		if (arr[o][p + 1] == "#")
		{
			goto random;
		}
		p++;
		if (arr[o][p] == "0")
		{
			arr[o][p - 1] = "0";
		}
		if (arr[o][p] == " ")
		{
			arr[o][p - 1] = " ";
		}
		if (arr[o][p] == ".")
		{
			arr[o][p - 1] = ".";
		}
		if (arr[o][p] == "*")
		{
			arr[o][p - 1] = "*";
		}
	}
	if (num == 2)//up
	{
		if (arr[o - 1][p] == "#")
		{
			goto random;
		}
		o--;
		if (arr[o][p] == "0")
		{
			arr[o + 1][p] = "0";
		}
		if (arr[o][p] == " ")
		{
			arr[o + 1][p] = " ";
		}
		if (arr[o][p] == ".")
		{
			arr[o + 1][p] = ".";
		}
		if (arr[o][p] == "*")
		{
			arr[o + 1][p] = "*";
		}
	}
	if (num == 3)//down
	{

		if (arr[o + 1][p] == "#")
		{
			goto random;
		}
		o++;
		if (arr[o][p] == "0")
		{
			arr[o - 1][p] = "0";
		}
		if (arr[o][p] == " ")
		{
			arr[o - 1][p] = " ";
		}
		if (arr[o][p] == ".")
		{
			arr[o - 1][p] = ".";
		}
		if (arr[o][p] == "*")
		{
			arr[o - 1][p] = "*";
		}
	}
}
void ghost2()
{
	arr[50][50];
	srand(time(NULL));
random:
	num = rand() % 4;
	if (num == 0)//left
	{
		if (arr[q][r - 1] == "#")
		{
			goto random;
		}
		r--;
		if (arr[q][r] == " ")
		{
			arr[q][r + 1] = " ";
		}
		if (arr[q][r] == ".")
		{
			arr[q][r + 1] = ".";
		}
		if (arr[q][r] == "0")
		{
			arr[q][r + 1] = "0";
		}
		if (arr[q][r] == "*")
		{
			arr[q][r + 1] = "*";
		}
	}
	if (num == 1)//right
	{
		if (arr[q][r + 1] == "#")
		{
			goto random;
		}
		r++;
		if (arr[q][r] == "0")
		{
			arr[q][r - 1] = "0";
		}
		if (arr[q][r] == " ")
		{
			arr[q][r - 1] = " ";
		}
		if (arr[q][r] == ".")
		{
			arr[q][r - 1] = ".";
		}
		if (arr[q][r] == "*")
		{
			arr[q][r - 1] = "*";
		}
	}
	if (num == 2)//up
	{
		if (arr[q - 1][r] == "#")
		{
			goto random;
		}
		q--;
		if (arr[q][r] == "0")
		{
			arr[q + 1][r] = "0";
		}
		if (arr[q][r] == " ")
		{
			arr[q + 1][r] = " ";
		}
		if (arr[q][r] == ".")
		{
			arr[q + 1][r] = ".";
		}
		if (arr[q][r] == "*")
		{
			arr[q + 1][r] = "*";
		}
	}
	if (num == 3)//down
	{

		if (arr[q + 1][r] == "#")
		{
			goto random;
		}
		q++;
		if (arr[q][r] == "0")
		{
			arr[q - 1][r] = "0";
		}
		if (arr[q][r] == " ")
		{
			arr[q - 1][r] = " ";
		}
		if (arr[q][r] == ".")
		{
			arr[q - 1][r] = ".";
		}
		if (arr[q][r] == "*")
		{
			arr[q - 1][r] = "*";
		}
	}
}
void mghost()
{
	arr[50][50];
	srand(time(NULL));
random:
	num = rand() % 4;
	if (num == 0)//left
	{
		if (arr[o][p - 1] == "#")
		{
			goto random;
		}
		if (arr[o][p - 2] == "#")
		{
			goto random;
		}
		if (arr[o][p - 1] == "E")
		{
			goto random;
		}
		if (arr[o][p - 2] == "E")
		{
			goto random;
		}
		p--;
		p--;
		if (arr[o][p] == " ")
		{
			arr[o][p + 2] = " ";
		}
		if (arr[o][p] == ".")
		{
			arr[o][p + 2] = ".";
		}
		if (arr[o][p] == "0")
		{
			arr[o][p + 2] = "0";
		}

	}
	if (num == 1)//right
	{
		if (arr[o][p + 2] == "#")
		{
			goto random;
		}
		if (arr[o][p + 1] == "#")
		{
			goto random;
		}if (arr[o][p + 2] == "E")
		{
			goto random;
		}
		if (arr[o][p + 1] == "E")
		{
			goto random;
		}
		p++;
		p++;
		if (arr[o][p] == "0")
		{
			arr[o][p - 2] = "0";
		}
		if (arr[o][p] == " ")
		{
			arr[o][p - 2] = " ";
		}
		if (arr[o][p] == ".")
		{
			arr[o][p - 2] = ".";
		}
	}
	if (num == 2)//up
	{
		if (arr[o - 1][p] == "#")
		{
			goto random;
		}if (arr[o - 2][p] == "#")
		{
			goto random;
		}

		if (arr[o - 1][p] == "E")
		{
			goto random;
		}if (arr[o - 2][p] == "E")
		{
			goto random;
		}
		o--;
		o--;
		if (arr[o][p] == "0")
		{
			arr[o + 2][p] = "0";
		}
		if (arr[o][p] == " ")
		{
			arr[o + 2][p] = " ";
		}
		if (arr[o][p] == ".")
		{
			arr[o + 2][p] = ".";
		}
	}
	if (num == 3)//down
	{

		if (arr[o + 1][p] == "#")
		{
			goto random;
		}
		if (arr[o + 2][p] == "#")
		{
			goto random;
		}
		if (arr[o + 1][p] == "E")
		{
			goto random;
		}
		if (arr[o + 2][p] == "E")
		{
			goto random;
		}
		o++;
		o++;
		if (arr[o][p] == "0")
		{
			arr[o - 2][p] = "0";
		}
		if (arr[o][p] == " ")
		{
			arr[o - 2][p] = " ";
		}
		if (arr[o][p] == ".")
		{
			arr[o - 2][p] = ".";
		}
	}
}
void mghost2()
{
	arr[50][50];
	srand(time(NULL));
random:
	num = rand() % 4;
	if (num == 0)//left
	{
		if (arr[q][r - 1] == "#")
		{
			goto random;
		}
		if (arr[q][r - 2] == "#")
		{
			goto random;
		}
		if (arr[q][r - 1] == "E")
		{
			goto random;
		}
		if (arr[q][r - 2] == "E")
		{
			goto random;
		}
		r--;
		r--;
		if (arr[q][r] == " ")
		{
			arr[q][r + 2] = " ";
		}
		if (arr[q][r] == ".")
		{
			arr[q][r + 2] = ".";
		}
		if (arr[q][r] == "0")
		{
			arr[q][r + 2] = "0";
		}
		if (arr[q][r] == "*")
		{
			arr[q][r + 2] = "*";
		}
	}
	if (num == 1)//right
	{
		if (arr[q][r + 1] == "#")
		{
			goto random;
		}
		if (arr[q][r + 2] == "#")
		{
			goto random;
		}
		if (arr[q][r + 1] == "E")
		{
			goto random;
		}
		if (arr[q][r + 2] == "E")
		{
			goto random;
		}
		r++;
		r++;
		if (arr[q][r] == "0")
		{
			arr[q][r - 2] = "0";
		}
		if (arr[q][r] == " ")
		{
			arr[q][r - 2] = " ";
		}
		if (arr[q][r] == ".")
		{
			arr[q][r - 2] = ".";
		}
		if (arr[q][r] == "*")
		{
			arr[q][r - 2] = "*";
		}
	}
	if (num == 2)//up
	{
		if (arr[q- 1][r] == "#")
		{
			goto random;
		}
		if (arr[q - 2][r] == "#")
		{
			goto random;
		}
		if (arr[q - 1][r] == "E")
		{
			goto random;
		}
		if (arr[q - 2][r] == "E")
		{
			goto random;
		}
		q--;
		q--;
		if (arr[q][r] == "0")
		{
			arr[q + 2][r] = "0";
		}
		if (arr[q][r] == " ")
		{
			arr[q + 2][r] = " ";
		}
		if (arr[q][r] == ".")
		{
			arr[q + 2][r] = ".";
		}
		if (arr[q][r] == "*")
		{
			arr[q + 2][r] = "*";
		}
	}
	if (num == 3)//down
	{

		if (arr[q + 1][r] == "#")
		{
			goto random;
		}
		if (arr[q + 2][r] == "#")
		{
			goto random;
		}
		if (arr[q + 1][r] == "E")
		{
			goto random;
		}
		if (arr[q + 2][r] == "E")
		{
			goto random;
		}
		q++;
		q++;
		if (arr[q][r] == "0")
		{
			arr[q - 2][r] = "0";
		}
		if (arr[q][r] == " ")
		{
			arr[q - 2][r] = " ";
		}
		if (arr[q][p] == ".")
		{
			arr[q - 2][r] = ".";
		}
		if (arr[q][p] == "*")
		{
			arr[q - 2][r] = "*";
		}
	}
}
void hghost()
{
	arr[50][50];
	srand(time(NULL));
random:
	num = rand() % 4;
	if (num == 0)//left
	{
		if (arr[o][p - 1] == "#")
		{
			goto random;
		}
		if (arr[o][p - 2] == "#")
		{
			goto random;
		}
		if (arr[o][p - 3] == "#")
		{
			goto random;
		}
		if (arr[o][p - 1] == "E")
		{
			goto random;
		}
		if (arr[o][p - 2] == "E")
		{
			goto random;
		}
		if (arr[o][p - 3] == "E")
		{
			goto random;
		}
		p--;
		p--;
		p--;
		if (arr[o][p] == " ")
		{
			arr[o][p + 3] = " ";
		}
		if (arr[o][p] == ".")
		{
			arr[o][p + 3] = ".";
		}
		if (arr[o][p] == "0")
		{
			arr[o][p + 3] = "0";
		}
		if (arr[o][p] == "*")
		{
			arr[o][p + 3] = "*";
		}
	}
	if (num == 1)//right
	{
		if (arr[o][p + 1] == "#")
		{
			goto random;
		}
		if (arr[o][p + 2] == "#")
		{
			goto random;
		}
		if (arr[o][p + 3] == "#")
		{
			goto random;
		}
		if (arr[o][p + 1] == "E")
		{
			goto random;
		}
		if (arr[o][p + 2] == "E")
		{
			goto random;
		}
		if (arr[o][p + 3] == "E")
		{
			goto random;
		}
		p++;
		p++;
		p++;
		if (arr[o][p] == "0")
		{
			arr[o][p - 3] = "0";
		}
		if (arr[o][p] == " ")
		{
			arr[o][p - 3] = " ";
		}
		if (arr[o][p] == ".")
		{
			arr[o][p - 3] = ".";
		}
		if (arr[o][p] == "*")
		{
			arr[o][p - 3] = "*";
		}
	}
	if (num == 2)//up
	{
		if (arr[o - 1][p] == "#")
		{
			goto random;
		}
		if (arr[o - 2][p] == "#")
		{
			goto random;
		}
		if (arr[o - 3][p] == "#")
		{
			goto random;
		}
		if (arr[o - 1][p] == "E")
		{
			goto random;
		}
		if (arr[o - 2][p] == "E")
		{
			goto random;
		}
		if (arr[o - 3][p] == "E")
		{
			goto random;
		}
		o--;
		o--;
		o--;
		if (arr[o][p] == "0")
		{
			arr[o + 3][p] = "0";
		}
		if (arr[o][p] == " ")
		{
			arr[o + 3][p] = " ";
		}
		if (arr[o][p] == ".")
		{
			arr[o + 3][p] = ".";
		}
		if (arr[o][p] == "*")
		{
			arr[o + 3][p] = "*";
		}
	}
	if (num == 3)//down
	{
		if (arr[o + 1][p] == "#")
		{
			goto random;
		}
		if (arr[o + 2][p] == "#")
		{
			goto random;
		}
		if (arr[o + 3][p] == "#")
		{
			goto random;
		}

		if (arr[o + 1][p] == "E")
		{
			goto random;
		}
		if (arr[o + 2][p] == "E")
		{
			goto random;
		}
		if (arr[o + 3][p] == "E")
		{
			goto random;
		}
		o++;
		o++;
		o++;
		if (arr[o][p] == "0")
		{
			arr[o - 3][p] = "0";
		}
		if (arr[o][p] == " ")
		{
			arr[o - 3][p] = " ";
		}
		if (arr[o][p] == ".")
		{
			arr[o - 3][p] = ".";
		}
		if (arr[o][p] == "*")
		{
			arr[o - 3][p] = "*";
		}
	}
}
void hghost2()
{
	arr[50][50];
	srand(time(NULL));
random:
	num = rand() % 4;
	if (num == 0)//left
	{
		if (arr[q][r - 1] == "#")
		{
			goto random;
		}
		if (arr[q][r - 2] == "#")
		{
			goto random;
		}
		if (arr[q][r - 3] == "#")
		{
			goto random;
		}
		if (arr[q][r - 1] == "E")
		{
			goto random;
		}
		if (arr[q][r - 2] == "E")
		{
			goto random;
		}
		if (arr[q][r - 3] == "E")
		{
			goto random;
		}
		r--;
		r--;
		r--;
		if (arr[q][r] == " ")
		{
			arr[q][r + 3] = " ";
		}
		if (arr[q][r] == ".")
		{
			arr[q][r + 3] = ".";
		}
		if (arr[q][r] == "0")
		{
			arr[q][r + 3] = "0";
		}
		if (arr[q][r] == "*")
		{
			arr[q][r + 3] = "*";
		}
	}
	if (num == 1)//right
	{
		if (arr[q][r + 1] == "#")
		{
			goto random;
		}
		if (arr[q][r + 2] == "#")
		{
			goto random;
		}
		if (arr[q][r + 3] == "#")
		{
			goto random;
		}
		if (arr[q][r + 1] == "E")
		{
			goto random;
		}
		if (arr[q][r + 2] == "E")
		{
			goto random;
		}
		if (arr[q][r + 3] == "E")
		{
			goto random;
		}
		r++;
		r++;
		r++;
		if (arr[q][r] == "0")
		{
			arr[q][r - 3] = "0";
		}
		if (arr[q][r] == " ")
		{
			arr[q][r - 3] = " ";
		}
		if (arr[q][r] == ".")
		{
			arr[q][r - 3] = ".";
		}
		if (arr[q][r] == "*")
		{
			arr[q][r - 3] = "*";
		}
	}
	if (num == 2)//up
	{
		if (arr[q - 1][r] == "#")
		{
			goto random;
		}
		if (arr[q - 2][r] == "#")
		{
			goto random;
		}
		if (arr[q - 3][r] == "#")
		{
			goto random;
		}
		if (arr[q - 1][r] == "E")
		{
			goto random;
		}
		if (arr[q - 2][r] == "E")
		{
			goto random;
		}
		if (arr[q - 3][r] == "E")
		{
			goto random;
		}
		r--;
		r--;
		r--;
		if (arr[q][r] == "0")
		{
			arr[q + 3][r] = "0";
		}
		if (arr[q][r] == " ")
		{
			arr[q + 3][r] = " ";
		}
		if (arr[q][r] == ".")
		{
			arr[q + 3][r] = ".";
		}
		if (arr[q][r] == "*")
		{
			arr[q + 3][r] = "*";
		}
	}
	if (num == 3)//down
	{
		if (arr[q + 1][r] == "#")
		{
			goto random;
		}if (arr[q + 2][r] == "#")
		{
			goto random;
		}
		if (arr[q + 3][r] == "#")
		{
			goto random;
		}
		if (arr[q + 1][r] == "E")
		{
			goto random;
		}if (arr[q + 2][r] == "E")
		{
			goto random;
		}
		if (arr[q + 3][r] == "E")
		{
			goto random;
		}
		q++;
		q++;
		q++;
		if (arr[q][r] == "0")
		{
			arr[q - 3][r] = "0";
		}
		if (arr[q][r] == " ")
		{
			arr[q - 3][r] = " ";
		}
		if (arr[q][r] == ".")
		{
			arr[q - 3][r] = ".";
		}
		if (arr[q][r] == "*")
		{
			arr[q - 3][r] = "*";
		}
	}
}
void input()
{
	
	if (_kbhit)
	{
		switch (_getch())
		{
		case 'a':
			dira = LEFT;
			break;
		case 'd':
			dira = RIGHT;
			break;
		case 'w':
			dira = UP;
			break;
		case 's':
			dira = DOWN;
			break;
		}
	}

}
void level1()
{
	j = 15, k = 15;
	int a = 15, b = 15;
	arr[j][k];
	arr[a][b];
	int x, y;
	// designing the map
	for (x = 0; x < 15; x++)
	{
		for (y = 0; y < 15; y++)
		{
			if (x == 0 || x == 14)
			{
				arr[x][y] = "#";
			}
			else if (y == 0 || y == 14)
			{
				arr[x][y] = "#";
			}
			else if (x == 5 && y > 2 && y < 10)
			{
				arr[x][y] = "#";
			}
			else if (x == 9 && y > 2 && y < 10)
			{
				arr[x][y] = "#";
			}
			else if (y == 9 && x > 2 && x < 10)
			{
				arr[x][y] = "#";
			}
			else if (y == 12 && x > 2 && x < 10)
			{
				arr[x][y] = "#";
			}
			else if (y == 1 && x > 6 && x < 10)
			{
				arr[x][y] = "#";
			}
			else {
				arr[12][12] = "0";
				arr[5][3] = "*";
				arr[x][y] = ".";
			}
		}

	}
	// pritnting the map
	arr[n][m] = "@";
	arr[o][p] = "E";
	arr[q][r] = "E";
	cout << "Life:" << life << "\t\t\tScore: " << score << endl;
	{
		for (x = 0; x < 15; x++)
		{
			for (y = 0; y < 15; y++)
			{
				if (arr[x][y] == "#") {
					setConsoleTextColor(frameColor);
				}
				else {
					setConsoleTextColor(whiteColor);
				}

				string value = arr[x][y];
				if (value == ".") {
					setConsoleTextColor(dotColor);
				}

				cout << arr[x][y] << " ";
			}
			cout << endl;
		}
		while (true)
		{
			input:
			input();
			switch (dira)
			{
			case LEFT:
					if (arr[n][m - 1] == "#")
					{
						goto input;
					}
					m--;
					arr[n][m + 1] = " ";
					ghost();
					ghost2();
					break;
			case RIGHT:
				if (arr[n][m + 1] == "#")
				{
					goto input;
				}
				m++;
				arr[n][m - 1] = " ";
				ghost();
				ghost2();
				
				break;

			case UP:
				if (arr[n-1][m] == "#")
				{
					goto input;
				}
				n--;
				arr[n + 1][m] = " ";
				ghost();
				ghost2();
			
				break;

			case DOWN:
				if (arr[n+1][m] == "#")
				{
					goto input;
				}
				n++;
				arr[n - 1][m] = " ";
				ghost();
				ghost2();
			
				break;
			}
			{
				if (arr[n][m] == ".")
				{
					score = score + 1;
				}
				if (arr[n][m] == "0")
				{
					score = score + 10;
				}
				if (arr[n][m] == "*")
				{
					score = score + 5;
				}
				if (arr[n][m] == "0")
				{
					system("CLS");
					break;

				}
				
				system("CLS");
				arr[n][m] = "@";
				arr[o][p] = "E";
				arr[q][r] = "E";
				cout << "Life:" << life << "\t\t\tScore:" << score << endl;
				{
					for (x = 0; x < 15; x++)
					{
						for (y = 0; y < 15; y++)
						{
							if (arr[x][y] == "#") {
								setConsoleTextColor(frameColor);
							}
							else {
								setConsoleTextColor(whiteColor);
							}

							string value = arr[x][y];
							if (value == ".") {
								setConsoleTextColor(dotColor);
							}
							cout << arr[x][y] << " ";
						}
						cout << endl;
					}
				}
				if (arr[n][m] == arr[o][p]|| arr[n][m] == arr[q][r])
				{
					life = life - 1;
					arr[n + 1||-1][m+1||-1];
					if (life == 0)
					{
						system("CLS");
						cout << "\n\n\t\t\t\t\t\t\tYour Score is: " << score;
						out();
						system("CLS");
						out();
						system("CLS");
						out();
						system("CLS");
						score = score;
						cout << "\n\t\t\t\t\t\tEnter Your Name:";
						cin >> name;
						system("CLS");
						myFile.open("score.txt",std::ios::in | std::ios::out | std::ios::ate);
							if (myFile.is_open())
							{
								ios::ate;
								myFile << "\n"<<  sco.Name << "\t\t\t" << sco.Score<<"\n";
							}
						system("CLS");
						cout <<"\n\n\n\t\t\t\tYour Score\n\t\t\t"<< name << "\t\t\t" << "Score:" << score<<"\n";
						
						break;
					}
				}
			}
		}
	}
}
void level2()
{
	j = 25, k = 25;
	arr[j][k];
	arr[j][k];
	int x, y;
	// designing the map
	for (y = 0; y < 25; y++)
	{
		for (x = 0; x < 25; x++)
		{
			if (y == 0 || y == 24)
			{
				arr[y][x] = "#";

			}
			else if (x == 0 || x == 24)
			{
				arr[y][x] = "#";
			}
			else if (y == 5 && x > 2 && x < 10)
			{
				arr[y][x] = "#";
			}
			else if (y == 14 && x > 7 && x < 16)
			{
				arr[y][x] = "#";
			}
			else if (y == 8 && x > 7 && x < 14)
			{
				arr[y][x] = "#";
			}
			else if (y == 20 && x > 4 && x < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 8 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 20 && y > 9 && y < 21)
			{
				arr[y][x] = "#";
			}
			else if (y == 17 && x > 14 && x < 17)
			{
				arr[y][x] = "#";
			}
			else if (x == 23 && y > 22 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 15 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 9 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (y == 9 && x > 2 && x < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 9 && y > 2 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 12 && y > 2 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 1 && y > 6 && y < 10)
			{
				arr[y][x] = "#";
			}
			else {
				arr[19][3] = "0";
				arr[5][3] = "*";
				arr[y][x] = ".";
			}
		}
	}

	// pritnting the map
	arr[n][m] = "@";
	arr[o][p] = "E";
	arr[q][r] = "E";

	cout << "Life:" << life << "\t\t\tScore: " << score << endl;
	{
		for (x = 0; x < 25; x++)
		{
			for (y = 0; y < 25; y++)
			{
				if (arr[x][y] == "#") {
					setConsoleTextColor(frameColor);
				}
				else {
					setConsoleTextColor(whiteColor);
				}

				string value = arr[x][y];
				if (value == ".") {
					setConsoleTextColor(dotColor);
				}

				cout << arr[x][y] << " ";
			}
			cout << endl;
		}
		while (true)
		{
		input:
			input();
			switch (dira)
			{
			case LEFT:
				if (arr[n][m - 1] == "#")
				{
					goto input;
				}
				m--;
				arr[n][m + 1] = " ";
				ghost();
				ghost2();
				
				break;

			case RIGHT:
				if (arr[n][m + 1] == "#")
				{
					goto input;
				}
				m++;
				arr[n][m - 1] = " ";
				ghost();
				ghost2();
		
				break;

			case UP:
				if (arr[n - 1][m] == "#")
				{
					goto input;
				}
				n--;
				arr[n + 1][m] = " ";
				ghost();
				ghost2();
		
				break;

			case DOWN:
				if (arr[n + 1][m] == "#")
				{
					goto input;
				}
				n++;
				arr[n - 1][m] = " ";
				ghost();
				ghost2();
		
				break;
			}
			{
				if (arr[n][m] == ".")
				{
					score = score + 1;
				}
				if (arr[n][m] == "0")
				{
					score = score + 10;
				}
				if (arr[n][m] == "*")
				{
					score = score + 5;
				}
				if (arr[n][m] == "0")
				{
					
					system("CLS");
					break;
					
				}
				system("CLS");
				arr[n][m] = "@";
				arr[o][p] = "E";
				arr[q][r] = "E";

				cout << "Life:" << life << "\t\t\tScore:" << score << endl;
				{
					for (x = 0; x < 25; x++)
					{
						for (y = 0; y < 25; y++)
						{
							if (arr[x][y] == "#") {
								setConsoleTextColor(frameColor);
							}
							else {
								setConsoleTextColor(whiteColor);
							}

							string value = arr[x][y];
							if (value == ".") {
								setConsoleTextColor(dotColor);
							}
							cout << arr[x][y] << " ";
						}
						cout << endl;
					}
				}
				if (arr[n][m] == arr[o][p] || arr[n][m] == arr[q][r])
				{
					life = life - 1;
					arr[n + 1 || -1][m + 1 || -1];
					if (life == 0)
					{
						system("CLS");
						cout << "\n\n\t\t\t\t\t\t\tYour Score is: " << score;
						out();
						system("CLS");
						out();
						system("CLS");
						out();
						system("CLS");
						score = score;
						cout << "\n\t\t\t\t\t\tEnter Your Name:";
						cin >> name;
						system("CLS");
						myFile.open("score.txt", std::ios::in | std::ios::out | std::ios::ate);
						if (myFile.is_open())
						{
							ios::ate;
							myFile << "\n"<<name << "\t\t\t" << score << "\n";
						}
						system("CLS");
						cout << "\n\n\n\t\t\t\tYour Score\n\t\t\t" << name << "\t\t\t" << "Score:" << score << "\n";
						break;
					}
				}
			}
		}
	}
}
void level3()
{
	j = 25, k = 25;
	arr[j][k];
	arr[j][k];
	int x, y;
	// designing the map
	for (y = 0; y < 25; y++)
	{
		for (x = 0; x < 25; x++)
		{
			if (y == 0 || y == 24)
			{
				arr[y][x] = "#";

			}
			else if (x == 0 || x == 24)
			{
				arr[y][x] = "#";
			}
			else if (y == 5 && x > 2 && x < 10)
			{

				arr[y][x] = "#";
			}
			else if (x == 5 && y > 2 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (y == 14 && x > 7 && x < 16)
			{
				arr[y][x] = "#";
			}
			else if (y == 8 && x > 7 && x < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 8 && y > 7 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (y == 20 && x > 4 && x < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 8 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 20 && y > 9 && y < 21)
			{
				arr[y][x] = "#";
			}
			else if (y == 17 && x > 14 && x < 17)
			{
				arr[y][x] = "#";
			}
			else if (x == 23 && y > 22 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (y == 23 && x > 22 && x < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 15 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 9 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (y == 9 && x > 2 && x < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 9 && y > 2 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (y == 9 && x > 2 && x < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 12 && y > 2 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 1 && y > 6 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (y ==7  && x > 6 && x < 15)
			{
				arr[y][x] = "#";
			}
			else {
				arr[19][8] = "0";
				arr[5][3] = "*";
				arr[y][x] = ".";
			}
		}
	}

	// pritnting the map
	arr[n][m] = "@";
	arr[o][p] = "E";
	arr[q][r] = "E";

	cout << "Life:" << life << "\t\t\tScore: " << score << endl;
	{
		for (x = 0; x < 25; x++)
		{
			for (y = 0; y < 25; y++)
			{
				if (arr[x][y] == "#") {
					setConsoleTextColor(frameColor);
				}
				else {
					setConsoleTextColor(whiteColor);
				}

				string value = arr[x][y];
				if (value == ".") {
					setConsoleTextColor(dotColor);
				}

				cout << arr[x][y] << " ";
			}
			cout << endl;
		}
		while (true)
		{
		input:
			input();
			switch (dira)
			{
			case LEFT:
				if (arr[n][m - 1] == "#")
				{
					goto input;
				}
				m--;
				arr[n][m + 1] = " ";
				ghost();
				ghost2();

				break;

			case RIGHT:
				if (arr[n][m + 1] == "#")
				{
					goto input;
				}
				m++;
				arr[n][m - 1] = " ";
				ghost();
				ghost2();

				break;

			case UP:
				if (arr[n - 1][m] == "#")
				{
					goto input;
				}
				n--;
				arr[n + 1][m] = " ";
				ghost();
				ghost2();

				break;

			case DOWN:
				if (arr[n + 1][m] == "#")
				{
					goto input;
				}
				n++;
				arr[n - 1][m] = " ";
				ghost();
				ghost2();

				break;
			}
			{
				if (arr[n][m] == ".")
				{
					score = score + 1;
				}
				if (arr[n][m] == "0")
				{
					score = score + 10;
				}
				if (arr[n][m] == "*")
				{
					score = score + 5;
				}
				if (arr[n][m] == "0")
				{
					system("CLS");
					break;

				}
				system("CLS");
				arr[n][m] = "@";
				arr[o][p] = "E";
				arr[q][r] = "E";

				cout << "Life:" << life << "\t\t\tScore:" << score << endl;
				{
					for (x = 0; x < 25; x++)
					{
						for (y = 0; y < 25; y++)
						{
							if (arr[x][y] == "#") {
								setConsoleTextColor(frameColor);
							}
							else {
								setConsoleTextColor(whiteColor);
							}

							string value = arr[x][y];
							if (value == ".") {
								setConsoleTextColor(dotColor);
							}
							cout << arr[x][y] << " ";
						}
						cout << endl;
					}
				}
				if (arr[n][m] == arr[o][p] || arr[n][m] == arr[q][r])
				{
					life = life - 1;
					arr[n + 1 || -1][m + 1 || -1];
					if (life == 0)
					{
						system("CLS");
						cout << "\n\n\t\t\t\t\t\t\tYour Score is: " << score;
						out();
						system("CLS");
						out();
						system("CLS");
						out();
						system("CLS");
						score = score;
						cout << "\n\t\t\t\t\t\tEnter Your Name:";
						cin >> name;
						system("CLS");
						myFile.open("score.txt", std::ios::in | std::ios::out | std::ios::ate);
						if (myFile.is_open())
						{
							ios::ate;
							myFile << "\n"<<  name << "\t\t\t"  << score<<"\n";
						}
						system("CLS");
						cout << "\n\n\n\t\t\t\tYour Score\n\t\t\t" << name << "\t\t\t" << "Score:" << score << "\n";
						break;
					}
					
				}
			}
		}
	}
}
void mlevel1()
{
	j = 15, k = 15;
	int a = 15, b = 15;
	arr[j][k];
	arr[a][b];
	int x, y;
	// designing the map
	for (x = 0; x < 15; x++)
	{
		for (y = 0; y < 15; y++)
		{
			if (x == 0 || x == 14)
			{
				arr[x][y] = "#";
			}
			else if (y == 0 || y == 14)
			{
				arr[x][y] = "#";
			}
			else if (x == 5 && y > 2 && y < 10)
			{
				arr[x][y] = "#";
			}
			else if (x == 9 && y > 2 && y < 10)
			{
				arr[x][y] = "#";
			}
			else if (y == 9 && x > 2 && x < 10)
			{
				arr[x][y] = "#";
			}
			else if (y == 12 && x > 2 && x < 10)
			{
				arr[x][y] = "#";
			}
			else if (y == 1 && x > 6 && x < 10)
			{
				arr[x][y] = "#";
			}
			else {
				arr[12][12] = "0";
				arr[5][3] = "*";
				arr[x][y] = ".";
			}
		}

	}
	// pritnting the map
	arr[n][m] = "@";
	arr[o][p] = "E";
	arr[q][r] = "E";
	cout << "Life:" << life << "\t\t\tScore: " << score << endl;
	{
		for (x = 0; x < 15; x++)
		{
			for (y = 0; y < 15; y++)
			{
				if (arr[x][y] == "#") {
					setConsoleTextColor(frameColor);
				}
				else {
					setConsoleTextColor(whiteColor);
				}

				string value = arr[x][y];
				if (value == ".") {
					setConsoleTextColor(dotColor);
				}

				cout << arr[x][y] << " ";
			}
			cout << endl;
		}
		while (true)
		{
		input:
			input();
			switch (dira)
			{
			case LEFT:
				if (arr[n][m - 1] == "#")
				{
					goto input;
				}
				m--;
				arr[n][m + 1] = " ";
				mghost();
				mghost2();

				break;
			case RIGHT:
				if (arr[n][m + 1] == "#")
				{
					goto input;
				}
				m++;
				arr[n][m - 1] = " ";
				mghost();
				mghost2();

				break;

			case UP:
				if (arr[n - 1][m] == "#")
				{
					goto input;
				}
				n--;
				arr[n + 1][m] = " ";
				mghost();
				mghost2();

				break;

			case DOWN:
				if (arr[n + 1][m] == "#")
				{
					goto input;
				}
				n++;
				arr[n - 1][m] = " ";
				mghost();
				mghost2();

				break;
			}
			{
				if (arr[n][m] == ".")
				{
					score = score + 1;
				}
				if (arr[n][m] == "0")
				{
					score = score + 10;
				}
				if (arr[n][m] == "*")
				{
					score = score + 5;
				}
				if (arr[n][m] == "0")
				{
					system("CLS");
					break;

				}

				system("CLS");
				arr[n][m] = "@";
				arr[o][p] = "E";
				arr[q][r] = "E";
				cout << "Life:" << life << "\t\t\tScore:" << score << endl;
				{
					for (x = 0; x < 15; x++)
					{
						for (y = 0; y < 15; y++)
						{
							if (arr[x][y] == "#") {
								setConsoleTextColor(frameColor);
							}
							else {
								setConsoleTextColor(whiteColor);
							}

							string value = arr[x][y];
							if (value == ".") {
								setConsoleTextColor(dotColor);
							}
							cout << arr[x][y] << " ";
						}
						cout << endl;
					}
				}
				if (arr[n][m] == arr[o][p] || arr[n][m] == arr[q][r])
				{
					life = life - 1;
					arr[n + 1 || -1][m + 1 || -1];
					if (life <= 0)
					{
						system("CLS");
						cout << "\n\n\t\t\t\t\t\t\tYour Score is: " << score;
						out();
						system("CLS");
						out();
						system("CLS");
						out();
						system("CLS");
						score = score;
						cout << "\n\t\t\t\t\t\tEnter Your Name:";
						cin >> name;
						system("CLS");
						myFile.open("mediumscore.txt", std::ios::in | std::ios::out | std::ios::ate);
						if (myFile.is_open())
						{
							ios::ate;
							myFile << "\nName:" << name << "\t\t\t" << "Score:" << score;
						}
						system("CLS");
						cout << "\n\n\n\t\t\t\tYour Score\n\t\t\t" << name << "\t\t\t" << "Score:" << score << "\n";
						break;
					}
				}
			}
		}
	}
}
void mlevel2()
{
	j = 25, k = 25;
	arr[j][k];
	arr[j][k];
	int x, y;
	// designing the map
	for (y = 0; y < 25; y++)
	{
		for (x = 0; x < 25; x++)
		{
			if (y == 0 || y == 24)
			{
				arr[y][x] = "#";

			}
			else if (x == 0 || x == 24)
			{
				arr[y][x] = "#";
			}
			else if (y == 5 && x > 2 && x < 10)
			{
				arr[y][x] = "#";
			}
			else if (y == 14 && x > 7 && x < 16)
			{
				arr[y][x] = "#";
			}
			else if (y == 8 && x > 7 && x < 14)
			{
				arr[y][x] = "#";
			}
			else if (y == 20 && x > 4 && x < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 8 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 20 && y > 9 && y < 21)
			{
				arr[y][x] = "#";
			}
			else if (y == 17 && x > 14 && x < 17)
			{
				arr[y][x] = "#";
			}
			else if (x == 23 && y > 22 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 15 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 9 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (y == 9 && x > 2 && x < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 9 && y > 2 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 12 && y > 2 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 1 && y > 6 && y < 10)
			{
				arr[y][x] = "#";
			}
			else {
				arr[19][3] = "0";
				arr[5][3] = "*";
				arr[y][x] = ".";
			}
		}
	}

	// pritnting the map
	arr[n][m] = "@";
	arr[o][p] = "E";
	arr[q][r] = "E";

	cout << "Life:" << life << "\t\t\tScore: " << score << endl;
	{
		for (x = 0; x < 25; x++)
		{
			for (y = 0; y < 25; y++)
			{
				if (arr[x][y] == "#") {
					setConsoleTextColor(frameColor);
				}
				else {
					setConsoleTextColor(whiteColor);
				}

				string value = arr[x][y];
				if (value == ".") {
					setConsoleTextColor(dotColor);
				}

				cout << arr[x][y] << " ";
			}
			cout << endl;
		}
		while (true)
		{
		input:
			input();
			switch (dira)
			{
			case LEFT:
				if (arr[n][m - 1] == "#")
				{
					goto input;
				}
				m--;
				arr[n][m + 1] = " ";
				mghost();
				mghost2();

				break;

			case RIGHT:
				if (arr[n][m + 1] == "#")
				{
					goto input;
				}
				m++;
				arr[n][m - 1] = " ";
				mghost();
				mghost2();

				break;

			case UP:
				if (arr[n - 1][m] == "#")
				{
					goto input;
				}
				n--;
				arr[n + 1][m] = " ";
				mghost();
				mghost2();

				break;

			case DOWN:
				if (arr[n + 1][m] == "#")
				{
					goto input;
				}
				n++;
				arr[n - 1][m] = " ";
				mghost();
				mghost2();

				break;
			}
			{
				if (arr[n][m] == ".")
				{
					score = score + 1;
				}
				if (arr[n][m] == "0")
				{
					score = score + 10;
				}
				if (arr[n][m] == "*")
				{
					score = score + 5;
				}
				if (arr[n][m] == "0")
				{
					system("CLS");
					break;

				}
				system("CLS");
				arr[n][m] = "@";
				arr[o][p] = "E";
				arr[q][r] = "E";

				cout << "Life:" << life << "\t\t\tScore:" << score << endl;
				{
					for (x = 0; x < 25; x++)
					{
						for (y = 0; y < 25; y++)
						{
							if (arr[x][y] == "#") {
								setConsoleTextColor(frameColor);
							}
							else {
								setConsoleTextColor(whiteColor);
							}

							string value = arr[x][y];
							if (value == ".") {
								setConsoleTextColor(dotColor);
							}
							cout << arr[x][y] << " ";
						}
						cout << endl;
					}
				}
				if (arr[n][m] == arr[o][p] || arr[n][m] == arr[q][r])
				{
					life = life - 1;
					arr[n + 1 || -1][m + 1 || -1];
					if (life <= 0)
					{
						system("CLS");
						cout << "\n\n\t\t\t\t\t\t\tYour Score is: " << score;
						out();
						system("CLS");
						out();
						system("CLS");
						out();
						system("CLS");
						score = score;
						cout << "\n\t\t\t\t\t\tEnter Your Name:";
						cin >> name;
						system("CLS");
						myFile.open("mediumscore.txt", std::ios::in | std::ios::out | std::ios::ate);
						if (myFile.is_open())
						{
							ios::ate;
							myFile << "\nName:" << name << "\t\t\t" << "Score:" << score;
						}
						system("CLS");
						cout << "\n\n\n\t\t\t\tYour Score\n\t\t\t" << name << "\t\t\t" << "Score:" << score << "\n";
						break;
					}
				}
			}
		}
	}
}
void hlevel1()
{
	j = 15, k = 15;
	int a = 15, b = 15;
	arr[j][k];
	arr[a][b];
	int x, y;
	// designing the map
	for (x = 0; x < 15; x++)
	{
		for (y = 0; y < 15; y++)
		{
			if (x == 0 || x == 14)
			{
				arr[x][y] = "#";
			}
			else if (y == 0 || y == 14)
			{
				arr[x][y] = "#";
			}
			else if (x == 5 && y > 2 && y < 10)
			{
				arr[x][y] = "#";
			}
			else if (x == 9 && y > 2 && y < 10)
			{
				arr[x][y] = "#";
			}
			else if (y == 9 && x > 2 && x < 10)
			{
				arr[x][y] = "#";
			}
			else if (y == 12 && x > 2 && x < 10)
			{
				arr[x][y] = "#";
			}
			else if (y == 1 && x > 6 && x < 10)
			{
				arr[x][y] = "#";
			}
			else {
				arr[12][12] = "0";
				arr[5][3] = "*";
				arr[x][y] = ".";
			}
		}

	}
	// pritnting the map
	arr[n][m] = "@";
	arr[o][p] = "E";
	arr[q][r] = "E";
	cout << "Life:" << life << "\t\t\tScore: " << score << endl;
	{
		for (x = 0; x < 15; x++)
		{
			for (y = 0; y < 15; y++)
			{
				if (arr[x][y] == "#") {
					setConsoleTextColor(frameColor);
				}
				else {
					setConsoleTextColor(whiteColor);
				}

				string value = arr[x][y];
				if (value == ".") {
					setConsoleTextColor(dotColor);
				}

				cout << arr[x][y] << " ";
			}
			cout << endl;
		}
		while (true)
		{
		input:
			input();
			switch (dira)
			{
			case LEFT:
				if (arr[n][m - 1] == "#")
				{
					goto input;
				}
				m--;
				arr[n][m + 1] = " ";
				hghost();
				hghost2();

				break;
			case RIGHT:
				if (arr[n][m + 1] == "#")
				{
					goto input;
				}
				m++;
				arr[n][m - 1] = " ";
				hghost();
				hghost2();

				break;

			case UP:
				if (arr[n - 1][m] == "#")
				{
					goto input;
				}
				n--;
				arr[n + 1][m] = " ";
				hghost();
				hghost2();

				break;

			case DOWN:
				if (arr[n + 1][m] == "#")
				{
					goto input;
				}
				n++;
				arr[n - 1][m] = " ";
				hghost();
				hghost2();

				break;
			}
			{
				if (arr[n][m] == ".")
				{
					score = score + 1;
				}
				if (arr[n][m] == "0")
				{
					score = score + 10;
				}
				if (arr[n][m] == "*")
				{
					score = score + 5;
				}
				if (arr[n][m] == "0")
				{
					system("CLS");
					break;

				}

				system("CLS");
				arr[n][m] = "@";
				arr[o][p] = "E";
				arr[q][r] = "E";
				cout << "Life:" << life << "\t\t\tScore:" << score << endl;
				{
					for (x = 0; x < 15; x++)
					{
						for (y = 0; y < 15; y++)
						{
							if (arr[x][y] == "#") {
								setConsoleTextColor(frameColor);
							}
							else {
								setConsoleTextColor(whiteColor);
							}

							string value = arr[x][y];
							if (value == ".") {
								setConsoleTextColor(dotColor);
							}
							cout << arr[x][y] << " ";
						}
						cout << endl;
					}
				}
				if (arr[n][m] == arr[o][p] || arr[n][m] == arr[q][r])
				{
					life = life - 1;
					arr[n + 1 || -1][m + 1 || -1];
					if (life <= 0)
					{
						system("CLS");
						cout << "\n\n\t\t\t\t\t\t\tYour Score is: " << score;
						out();
						system("CLS");
						out();
						system("CLS");
						out();
						system("CLS");
						score = score;
						cout << "\n\t\t\t\t\t\tEnter Your Name:";
						cin >> name;
						system("CLS");
						myFile.open("hardscore.txt", std::ios::in | std::ios::out | std::ios::ate);
						if (myFile.is_open())
						{
							ios::ate;
							myFile << "\nName:" << name << "\t\t\t" << "Score:" << score;
						}
						system("CLS");
						cout << "\n\n\n\t\t\t\tYour Score\n\t\t\t" << name << "\t\t\t" << "Score:" << score << "\n";
						break;
					}
				}
			}
		}
	}
}
void hlevel2()
{
	j = 25, k = 25;
	arr[j][k];
	arr[j][k];
	int x, y;
	// designing the map
	for (y = 0; y < 25; y++)
	{
		for (x = 0; x < 25; x++)
		{
			if (y == 0 || y == 24)
			{
				arr[y][x] = "#";

			}
			else if (x == 0 || x == 24)
			{
				arr[y][x] = "#";
			}
			else if (y == 5 && x > 2 && x < 10)
			{
				arr[y][x] = "#";
			}
			else if (y == 14 && x > 7 && x < 16)
			{
				arr[y][x] = "#";
			}
			else if (y == 8 && x > 7 && x < 14)
			{
				arr[y][x] = "#";
			}
			else if (y == 20 && x > 4 && x < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 8 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 20 && y > 9 && y < 21)
			{
				arr[y][x] = "#";
			}
			else if (y == 17 && x > 14 && x < 17)
			{
				arr[y][x] = "#";
			}
			else if (x == 23 && y > 22 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 15 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 9 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (y == 9 && x > 2 && x < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 9 && y > 2 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 12 && y > 2 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 1 && y > 6 && y < 10)
			{
				arr[y][x] = "#";
			}
			else {
				arr[19][3] = "0";
				arr[5][3] = "*";
				arr[y][x] = ".";
			}
		}
	}

	// pritnting the map
	arr[n][m] = "@";
	arr[o][p] = "E";
	arr[q][r] = "E";

	cout << "Life:" << life << "\t\t\tScore: " << score << endl;
	{
		for (x = 0; x < 25; x++)
		{
			for (y = 0; y < 25; y++)
			{
				if (arr[x][y] == "#") {
					setConsoleTextColor(frameColor);
				}
				else {
					setConsoleTextColor(whiteColor);
				}

				string value = arr[x][y];
				if (value == ".") {
					setConsoleTextColor(dotColor);
				}

				cout << arr[x][y] << " ";
			}
			cout << endl;
		}
		while (true)
		{
		input:
			input();
			switch (dira)
			{
			case LEFT:
				if (arr[n][m - 1] == "#")
				{
					goto input;
				}
				m--;
				arr[n][m + 1] = " ";
				hghost();
				hghost2();

				break;

			case RIGHT:
				if (arr[n][m + 1] == "#")
				{
					goto input;
				}
				m++;
				arr[n][m - 1] = " ";
				hghost();
				hghost2();

				break;

			case UP:
				if (arr[n - 1][m] == "#")
				{
					goto input;
				}
				n--;
				arr[n + 1][m] = " ";
				hghost();
				hghost2();

				break;

			case DOWN:
				if (arr[n + 1][m] == "#")
				{
					goto input;
				}
				n++;
				arr[n - 1][m] = " ";
				hghost();
				hghost2();

				break;
			}
			{
				if (arr[n][m] == ".")
				{
					score = score + 1;
				}
				if (arr[n][m] == "0")
				{
					score = score + 10;
				}
				if (arr[n][m] == "*")
				{
					score = score + 5;
				}
				if (arr[n][m] == "0")
				{
					system("CLS");
					break;

				}
				system("CLS");
				arr[n][m] = "@";
				arr[o][p] = "E";
				arr[q][r] = "E";

				cout << "Life:" << life << "\t\t\tScore:" << score << endl;
				{
					for (x = 0; x < 25; x++)
					{
						for (y = 0; y < 25; y++)
						{
							if (arr[x][y] == "#") {
								setConsoleTextColor(frameColor);
							}
							else {
								setConsoleTextColor(whiteColor);
							}

							string value = arr[x][y];
							if (value == ".") {
								setConsoleTextColor(dotColor);
							}
							cout << arr[x][y] << " ";
						}
						cout << endl;
					}
				}
				if (arr[n][m] == arr[o][p] || arr[n][m] == arr[q][r])
				{
					life = life - 1;
					arr[n + 1 || -1][m + 1 || -1];
					if (life <= 0)
					{
						system("CLS");
						cout << "\n\n\t\t\t\t\t\t\tYour Score is: " << score;
						out();
						system("CLS");
						out();
						system("CLS");
						out();
						system("CLS");
						score = score;
						cout << "\n\t\t\t\t\t\tEnter Your Name:";
						cin >> name;
						system("CLS");
						myFile.open("hardscore.txt", std::ios::in | std::ios::out | std::ios::ate);
						if (myFile.is_open())
						{
							ios::ate;
							myFile << "\nName:" << name << "\t\t\t" << "Score:" << score;
						}
						system("CLS");
						cout << "\n\n\n\t\t\t\tYour Score\n\t\t\t" << name << "\t\t\t" << "Score:" << score << "\n";
						break;
					}
				}
			}
		}
	}
}
void map1()
{
	int x, y;
	j = 15, k = 15;
	arr[j][k];
	//storage of the map
	// designing the map

	for (x = 0; x < 15; x++)
	{
		for (y = 0; y < 15; y++)
		{

			if (x == 0 || x == 14)
			{
				arr[x][y] = "#";
			}
			else if (y == 0 || y == 14)
			{
				arr[x][y] = "#";
			}
			else if (x == 5 && y > 2 && y < 10)
			{
				arr[x][y] = "#";
			}
			else if (x == 9 && y > 2 && y < 10)
			{
				arr[x][y] = "#";
			}
			else if (y == 9 && x > 2 && x < 10)
			{
				arr[x][y] = "#";
			}
			else if (y == 12 && x > 2 && x < 10)
			{
				arr[x][y] = "#";
			}
			else if (y == 1 && x > 6 && x < 10)
			{
				arr[x][y] = "#";
			}
			else {
				arr[12][12] = "0";
				arr[5][3] = "*";
				arr[x][y] = ".";
			}

		}

	}
	for (x = 0; x < 15; x++)
	{
		for (y = 0; y < 15; y++)
		{
			cout << arr[x][y] << " ";
		}
		cout << endl;
	}
}
void map2()
{
	string arr[25][25];
	int x, y;
	// designing the map
	for (y = 0; y < 25; y++)
	{
		for (x = 0; x < 25; x++)
		{
			if (y == 0 || y == 24)
			{
				arr[y][x] = "#";

			}
			else if (x == 0 || x == 24)
			{
				arr[y][x] = "#";
			}
			else if (y == 5 && x > 2 && x < 10)
			{
				arr[y][x] = "#";
			}
			else if (y == 14 && x > 7 && x < 16)
			{
				arr[y][x] = "#";
			}
			else if (y == 8 && x > 7 && x < 14)
			{
				arr[y][x] = "#";
			}
			else if (y == 20 && x > 4 && x < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 8 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 20 && y > 9 && y < 21)
			{
				arr[y][x] = "#";
			}
			else if (y == 17 && x > 14 && x < 17)
			{
				arr[y][x] = "#";
			}
			else if (x == 23 && y > 22 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 15 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 9 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (y == 9 && x > 2 && x < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 9 && y > 2 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 12 && y > 2 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 1 && y > 6 && y < 10)
			{
				arr[y][x] = "#";
			}
			else {
				arr[19][3] = "0";
				arr[5][3] = "*";
				arr[y][x] = ".";
			}
		}
	}
	for (x = 0; x < 25; x++)
	{
		for (y = 0; y < 25; y++)
		{
			cout << arr[x][y] << " ";
		}
		cout << endl;
	}
}
void map3()
{
	string arr[25][25];
	int x, y;
	for (y = 0; y < 25; y++)
	{
		for (x = 0; x < 25; x++)
		{
			if (y == 0 || y == 24)
			{
				arr[y][x] = "#";

			}
			else if (x == 0 || x == 24)
			{
				arr[y][x] = "#";
			}
			else if (y == 5 && x > 2 && x < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 5 && y > 2 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (y == 14 && x > 7 && x < 16)
			{
				arr[y][x] = "#";
			}
			else if (y == 8 && x > 7 && x < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 8 && y > 7 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (y == 20 && x > 4 && x < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 8 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 20 && y > 9 && y < 21)
			{
				arr[y][x] = "#";
			}
			else if (y == 17 && x > 14 && x < 17)
			{
				arr[y][x] = "#";
			}
			else if (x == 23 && y > 22 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (y == 23 && x > 22 && x < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 15 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (x == 9 && y > 9 && y < 14)
			{
				arr[y][x] = "#";
			}
			else if (y == 9 && x > 2 && x < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 9 && y > 2 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (y == 9 && x > 2 && x < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 12 && y > 2 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (x == 1 && y > 6 && y < 10)
			{
				arr[y][x] = "#";
			}
			else if (y == 7 && x > 6 && x < 15)
			{
				arr[y][x] = "#";
			}
			else {
				arr[19][3] = "0";
				arr[5][3] = "*";
				arr[y][x] = ".";
			}
		}
	}
}
void character()
{

	cout << "\t\t\t\t          ...........\n";
	cout << "\t\t\t\t       ..................\n";
	cout << "\t\t\t\t     .............@@@.......\n";
	cout << "\t\t\t\t    ...............@......\n";
	cout << "\t\t\t\t    ..................\n";
	cout << "\t\t\t\t    .................       @    @   @\n";
	cout << "\t\t\t\t    ..................\n";
	cout << "\t\t\t\t     ......................\n";
	cout << "\t\t\t\t      .......................\n";
	cout << "\t\t\t\t       ..................\n";
	cout << "\t\t\t\t          ...........\n       ";
}
void pacman()
{
	cout << "       |||||||||||||   |||||||||||||   |||||||||||||          |||||||||||||   |||||||||||||   ||||||||  |||\n";
	cout << "       |||       |||   |||       |||   |||                    |||  |||  |||   |||       |||   |||  |||  |||\n";
	cout << "       |||       |||   |||       |||   |||                    |||  |||  |||   |||       |||   |||  |||  |||\n";
	cout << "       |||       |||   |||       |||   |||                    |||  |||  |||   |||       |||   |||  |||  |||\n";
	cout << "       |||||||||||||   |||||||||||||   |||            ||||||  |||  |||  |||   |||||||||||||   |||  |||  |||\n";
	cout << "       |||             |||       |||   |||                    |||  |||  |||   |||       |||   |||  |||  |||\n";
	cout << "       |||             |||       |||   |||                    |||  |||  |||   |||       |||   |||  |||  |||\n";
	cout << "       |||             |||       |||   |||||||||||||          |||  |||  |||   |||       |||   |||  ||||||||\n";
}
void menu()
{
	system("Color 03");
	cout << "\n\n";
	cout << "\t\t\t _______________________________________________________________________\n";
	cout << "\t\t\t|                                                                       |\n";
	cout << "\t\t\t|                              MAIN  MENU                               |\n";
	cout << "\t\t\t|                                                                       |\n";
	cout << "\t\t\t|_______________________________________________________________________|\n";
	cout << "\t\t\t|                                                                       |\n";
	cout << "\t\t\t|   Press 1:   Carrer Mode                                              |\n";
	cout << "\t\t\t|   Press 2:   Difficulty Mode                                          |\n";
	cout << "\t\t\t|   Press 3:   Map Mode                                                 |\n";
	cout << "\t\t\t|   Press 4:   Controlles                                               |\n";
	cout << "\t\t\t|   Press 5:   Games Rules                                              |\n";
	cout << "\t\t\t|   Press 6:   Leader Board                                             |\n";
	cout << "\t\t\t|_______________________________________________________________________|\n";
}
void difficulty()
{
	cout << "\n\n";
	cout << "\t\t\t _______________________________________________________________________\n";
	cout << "\t\t\t|                                                                       |\n";
	cout << "\t\t\t|                            Difficulty Mode                            |\n";
	cout << "\t\t\t|                                                                       |\n";
	cout << "\t\t\t|_______________________________________________________________________|\n";
	cout << "\t\t\t|                                                                       |\n";
	cout << "\t\t\t|   Press E:   Easy                                                     |\n";
	cout << "\t\t\t|   Press M:   Medium                                                   |\n";
	cout << "\t\t\t|   Press H:   Hard                                                     |\n";
	cout << "\t\t\t|   Press Y:   Back to menu                                             |\n";
	cout << "\t\t\t|_______________________________________________________________________|\n";
}
void controlles()
{
	cout << "Key Controls:\n";
	cout << "\t\tLeft=A\n\t\tRight=D\n\t\tUp=W\n\t\tDown=S\n";

}
void rules()
{
	cout << "Rules:\n";
	cout << "\t1. If you collide with the ghost, you will lose a live.\n\n";
	cout << "\t2. You have 3 lives, if you lose all 3 lives the game will be over.\n\n";
	cout << "Scoring:\n";
	cout << "\tSmall grains are worth 1-point.\n\tBigger grains are worth 5-points.\n\tNext-level grain worth 10-points and you move to next level.\n\n";
}
int main()
{
	
	int choice;
	char opp;
	dira = STOP;
	{
		cout << "\n\n";
		system("Color 06");
		character();
		cout << "\n\n";
		system("Color 04");
		pacman();
		system("CLS");
		cout << "\n\n";
		system("Color 06");
		character();
		cout << "\n\n";
		system("Color 04");
		pacman();
		system("CLS");
		cout << "\n\n";
		system("Color 06");
		character();
		cout << "\n\n";
		system("Color 04");
		pacman();
		system("CLS");
		cout << "\n\n";
		system("Color 06");
		character();
		cout << "\n\n";
		system("Color 04");
		pacman();
		system("CLS");
		cout << "\n\n";
		system("Color 06");
		character();
		cout << "\n\n";
		system("Color 04");
		pacman();
		system("CLS");
		cout << "\n\n";
		system("Color 06");
		character();
		cout << "\n\n";
		system("Color 04");
		pacman();
		system("Color 06");
	}
	cout << "\n\t\t\t\t\tPRESS ANY KEY TO CONTINUE";
	_getch();
	system("Color 07");
	system("CLS");
menu:
	menu();
	cin >> choice;
	system("CLS");
	switch (choice)
	{
	case 1://level mode
		level1();
		if (life > 0)
		{
			level2();
		}
		if (life > 0)
		{
			level3();
		}
		system("CLS");
		myFile.open("score.txt", std::ios::in | std::ios::out | std::ios::ate);
		if (myFile.is_open())
		{
			ios::ate;
			myFile << "\n"<<name << "\t\t\t" << score << "\n";
		}
		system("CLS");
		cout << "\n\n\n\t\t\t\tYour Score\n\t\t\t" << name << "\t\t\t" << "Score:" << score << "\n";
		break;
	case 2://difficulty
		difficulty();
		cin >> opp;
		system("CLS");
		if (opp == 'Y')
		{
			goto menu;
		}
		else
			switch (opp)
			{
			case 'E'://easy
				level1();
				if (life > 0)
				{
					level2();
				}
				break;
			case 'M'://medium
				mlevel1();
				if (life > 0)
				{
					mlevel2();
				}
				break;
			case 'H'://hard
				hlevel1();
				if (life > 0)
				{
					hlevel2();
				}
				break;
			}
		break;
	case 3://map mode
		map1();
		cout << "\nPress 1";
		cout << endl;
		map2();
		cout << "\nPress 2";
		cout<<endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("CLS");
			level1();
			break;
		case 2:
			system("CLS");
			level2();
			break;
		case 3:
			system("CLS");
			level3();
			break;
		}
		cout << "\n\nPress Y to go back to menu\n\n";
		cin >> opp;
		system("CLS");
		if (opp == 'Y')
		{
			goto menu;
		}
		break;
	case 4://controlles
		controlles();
		cout << "\n\nPress Y to go back to menu\n\n";
		cin >> opp;
		system("CLS");
		if (opp == 'Y')
		{
			goto menu;
		}
		break;
	case 5://rules
		rules();
		cout << "\n\nPress Y to go back to menu\n\n";
		cin >> opp;
		system("CLS");
		if (opp == 'Y')
		{
			goto menu;
		}
		break;
	case 6:
		leaderboard();
		ifstream fin("score.txt");
		string name, score;
		while (fin >> name >> score)
		{
			cout <<"\t\t\t\t   "<< name << "\t\t\t\t\t" << score << "\n";
		}
		cout << "\n\nPress Y to go back to menu\n\n";
		cin >> opp;
		system("CLS");
		if (opp == 'Y')
		{
			goto menu;
		}
	}
	_getch();
	return 0;
}