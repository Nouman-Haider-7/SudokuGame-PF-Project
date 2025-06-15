#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<string>
using namespace std;
int score = 0;
string name;
void file_handeling();
void play_game();
void instructions();
void show_scores();
void print_board(int arr[9][9]);
void credits();
void initialization(int arr[9][9]);
void initialization(int arr[9][9])
{
	
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int x = rand() % 2;
			if (x == 0)
			{
				arr[i][j] = rand() % 9 + 1;
			}
			if (x == 1)
			{
				arr[i][j] = 0;

			}
		}
	}
}
void print_board(int arr[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		int l = i + 1;
		for (int j = 0; j < 9; j++)
		{

			if (arr[i][j] == 0)
			{
				cout << "\033[1;31m- \033[0m";
			}
			else
			{
				cout <<"\033[1;32m" <<arr[i][j] << "\033[0m ";
			}
			int k = j + 1;
			if (k % 3 == 0)
			{
				cout << "|";
			}

		}
		if (l % 3 == 0)
		{
			cout << endl << "\033[1;33m---------------------\033[0m" << endl;
		}
		else
		cout << endl;
	}
	cout << "\033[1;31mYour score is \033[0m" << score << endl;
}
void play_game()
{
	cout << "\033[1;36mEnter your name \033[0m" << endl;
	cin >> name;
	int arr[9][9];
	initialization(arr);
	print_board(arr);
	int x;
	int count = 0; 
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (arr[i][j] == 0)
			{
				cout << "\033[1;33mEnter value for\033[0m"<<" \033[1;31mrow\033[0m " << i + 1 <<" \033[1;33m and\033[0m" << "\033[1;31m column\033[0m " << j + 1 << endl;
				cin >> x;
				if (x == 0)
				{
					cout << "\033[1;31mExit game\033[0m" << endl;
					file_handeling();
					return;
				}
				bool valid = true;
				for (int k = 0; k < 9; k++)
				{
					if (arr[i][k] == x || arr[k][j] == x)
					{
						cout << "\033[1;32mInvalid input\033[0m" << endl;
						j--; 
						valid = false;
						count++;
						break;
					}
				}
				int subr = (i / 3) * 3;
				int subc = (j / 3) * 3;
				if (valid)
				{
					for (int row = 0; row < 3; row++)
					{
						for (int col = 0; col < 3; col++)
						{
							if (arr[subr + row][subc + col] == x)
							{
								cout << "\033[1;32mInvalid input\033[0m" << endl;
								j--; 
								valid = false;
								count++;
								break;
							}
						}
						if (!valid)
							break;
					}
				}

				if (valid)
				{
					score++;
					arr[i][j] = x;
					count = 0; 
					system("cls");
					print_board(arr); 
				}
				if (count == 3)
				{
					cout << "\033[1;31mThree consecutive invalid inputs Game over\033[0m" << endl;
					file_handeling();
					return;
				}
			}
		}
	}
}
void show_scores()
{
	ifstream read;
	read.open("score.txt");
	string s, n;
	int c=0;
	cout << "\033[1;31mTotal players played\033[0m " << endl;
	while (read >> s >> n)
	{
		cout << "\033[1;36mName is \033[0m" <<"\033[1;31m" << s <<"\033[0m" << " \033[1;36mscore is\033[0m " <<"\033[1;31m" << n <<"\033[0m"<< endl;
		c++;
	}
     read.clear(); 
    read.seekg(0); 
	int *ptr=new int [c];
	string *k=new string[c];
	int v;
	for (int i = 0; i < c; i++)
	{
		read >> s >> ptr[i];
		k[i] = s;
	}
	for (int i = 0; i < c - 1; i++)
	{
		int max = i;
		for (int j = i + 1; j < c; j++)
		{
			if (ptr[j] > ptr[max])
			{
				max= j;
			}
		}
		int temp = ptr[max];
		ptr[max] = ptr[i];
		ptr[i] = temp;
		string str = k[max];
		k[max] = k[i];
		k[i] = str;
	}
	cout << "\033[1;31mTop scorers are\033[0m" << endl;
	for (int i = 0; i < min(3,c); i++)
	{
		cout << "\033[1;36mName is \033[0m"<<"\033[1;31m" << k[i]<<"\033[0m" << " \033[1;36mscore is \033[0m" <<"\033[1;31m" << ptr[i] <<"\033[0m" << endl;
	}
	delete[]k;
	delete[]ptr;
}
void file_handeling()
{
	ofstream rite;
	rite.open("score.txt", ios::app);
	rite <<name <<" " << score << endl;
}
void credits() 
{
	cout << "\033[1;34mThis game is created by Students of FAST CFD"<<endl;
	cout << "Game created by Ahmad (23F-0763) and Noman (23F-0629)\033[0m"<<endl;
}
void instructions() 
{
	cout << "\033[1;35mInstructions"<<endl;
	cout << "1 Input numbers from 1 to 9 to fill in the Sudoku puzzle"<<endl;
	cout << "2 Numbers should not repeat in any 3x3 box"<<endl;
	cout << "3 Enter 0 at any time to exit game \033[0m"<<endl;
}
int main() 
{

	int option = 0;
	cout << "\033[1;31mHere is Menu\033[0m" << endl;
	cout << "\033[1;33m1 Play Game"<<endl;
	cout << "2 Credits"<<endl;
	cout << "3 Instructions"<<endl;
	cout << "4 Score"<<endl;
	cout << "5 Exit\033[0m"<<endl;
	cout << "\033[1;31mEnter option\033[0m "<<endl;
	cin >> option;
	switch (option) 
	{
	case 1:
	{
		srand(time(0));
		play_game();
		break;
	}
	case 2: 
	{
		credits();
		break;
	}
	case 3: 
	{
		instructions();
		break;
	}
	case 4: 
	{
		show_scores();
		break;
	}
	case 5: 
	{
		cout << "\033[1;32mYou successfully exited\033[0m " << endl;
		break;
	}
	default:
	{
		cout << "\033[1;32mInvalid input\033[0m" << endl;
		break;
	}
	}
	system("pause");
	return 0;
}