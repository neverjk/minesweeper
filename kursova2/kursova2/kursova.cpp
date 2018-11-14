#include "headers.h"
#include <iostream>
using namespace std;
HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
char mines[SIZE][SIZE]; // масив генерується на початку гри
char mns[SIZE][SIZE]; // масив, що виводиться на екран (в ньому ми граємо)
char flags[SIZE][SIZE]; //  масив, що відповідає за флажки
int flags_num = (MINES_NUM);
int pos_i = (SIZE / 2); // змінні, що відповідають за позицію в грі (управління клавішами)
int pos_j = (SIZE / 2);
bool first_game = true;
bool saved_game = false;


void setcur(int x, int y) //  функція для очищення консолі без миготіння
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Game();
void Menu() {
	mciSendString("open \"use\\VECTOR_GRAPHICS_DESTINE.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	mciSendString("play mp3 from 0", NULL, 0, NULL);
	Sleep(1);
	system("cls");
	SetConsoleTextAttribute(hConsoleHandle, 15);
	int menu = 1;
	cout << endl;
	cout << setw(40) << "MINESWEEPER" << endl;
	cout << setw(40) << "> start new game\n";
	cout << setw(30) << "exit\n";
	cout << setw(38) << "how to play?\n";

	while (1)
	{

		char push1;
		int push_int1;
		push1 = _getch();

		push_int1 = static_cast<int>(push1);
		switch (push_int1) {
		case 72: {if (menu == 3)
				menu = 2;
			else if (menu == 2)
				menu = 1;
			break;
		}
		case 80: {if (menu == 2)
				menu = 3;
			else if (menu == 1)
				menu = 2;
			break;
		}
		case 13: {
			if (menu == 2) {
				exit(0);
			}
			else if (menu == 1) {
				mciSendString("close mp3", NULL, 0, NULL);
				PlaySound(".\\use\\FGBS(8).wav", NULL, SND_ASYNC);
				cout << setw(42) << "starting new game";
				Sleep(1000);
				cout << ".";
				Sleep(1000);
				cout << ".";
				Sleep(1000);
				cout << ".";
				Sleep(1000);
				system("cls");
				Game();
			}
			else if (menu == 3) {
				system("cls");
				cout << "\n\t use UP DOWN RIGHT LEFT keys to move in field" << endl;
				cout << "\t use X key to mark mine" << endl;
				cout << "\t use ESC key to return to the menu" << endl;
				cout << "\t use SPACE or ENTER keys to open cell" << endl;
				cout << "< back";
				_getch();
				PlaySound(".\\use\\FGBS(5).wav", NULL, SND_ASYNC);

			}
			break;
		}
		}
		system("cls");
		cout << endl;
		switch (menu) {
		case 1: {
			Sleep(10);
			PlaySound(".\\use\\FGBS(5).wav", NULL, SND_ASYNC);
			cout << setw(40) << "MINESWEEPER" << endl;
			cout << setw(40) << "> start new game\n";
			cout << setw(30) << "exit\n";
			cout << setw(38) << "how to play?\n";
			break;
		}
		case 2: {
			Sleep(10);
			PlaySound(".\\use\\FGBS(5).wav", NULL, SND_ASYNC);
			cout << setw(40) << "MINESWEEPER" << endl;
			cout << setw(40) << "start new game\n";
			cout << setw(30) << "> exit\n";
			cout << setw(38) << "how to play?\n";
			break;
		}
		case 3: {
			Sleep(10);
			PlaySound(".\\use\\FGBS(5).wav", NULL, SND_ASYNC);
			cout << setw(40) << "MINESWEEPER" << endl;
			cout << setw(40) << "start new game\n";
			cout << setw(30) << "exit\n";
			cout << setw(38) << "> how to play?\n";
			break;
		}
		}


	}



}
void fullInStart() {

	// початкове заповнення mns (x - невідкриті клітинки) і mines (. - пусті клітинки)
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < 9; j++) {
			mns[i][j] = 'x';
			mines[i][j] = '.';
		}
	}
	// початкове заповнення масиву флажків
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < 9; j++) {
			flags[i][j] = ' ';
		}
	}
}
void fullIn() {

	// генерування mines:
	// 1. міни
	for (int i = 0; i < MINES_NUM; i++) {
		for (;;) {
			// * - міни
			int index_i = rand() % 9;
			int index_j = rand() % 9;
			if (mines[index_i][index_j] != '*' && pos_i != index_i && pos_j != index_j && pos_i + 1 != index_i && pos_i - 1 != index_i && pos_j + 1 != index_j && pos_j - 1 != index_j) {
				mines[index_i][index_j] = '*';
				break;
			}
			else {
				continue;
			}
		}
	}
	// 2. клітинки біля мін
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			int mines_num = 0; // к-сть мін навколо клітинки
							   // перевірка не супер гарна, but
			if (mines[i][j] != '*') {
				if (i != (SIZE - 1) && mines[i + 1][j] == '*') { // справа
					mines_num++;
				}
				if (i != 0 && mines[i - 1][j] == '*') { // зліва
					mines_num++;
				}
				if (j != (SIZE - 1) && mines[i][j + 1] == '*') { // і т. д
					mines_num++;
				}
				if (j != 0 && mines[i][j - 1] == '*') {
					mines_num++;
				}
				if (i != (SIZE - 1) && j != (SIZE - 1) && mines[i + 1][j + 1] == '*') {
					mines_num++;
				}
				if (i != 0 && j != 0 && mines[i - 1][j - 1] == '*') {
					mines_num++;
				}
				if (i != (SIZE - 1) && j != 0 && mines[i + 1][j - 1] == '*') {
					mines_num++;
				}
				if (i != 0 && j != (SIZE - 1) && mines[i - 1][j + 1] == '*') {
					mines_num++;
				}
			}
			switch (mines_num)
			{
			case 1: {
				mines[i][j] = '1';
				break;
			}
			case 2: {
				mines[i][j] = '2';
				break;
			}
			case 3: {
				mines[i][j] = '3';
				break;
			}
			case 4: {
				mines[i][j] = '4';
				break;
			}
			case 5: {
				mines[i][j] = '5';
				break;
			}
			case 6: {
				mines[i][j] = '6';
				break;
			}
			case 7: {
				mines[i][j] = '7';
				break;
			}
			case 8: {
				mines[i][j] = '8';
				break;
			}
			default: {
				break;
			}

			}
		}
	}



}
void SetColor(int a, int b) { // функція для встановлення кольору при виводі на екран
	switch (mns[a][b]) {
	case '1': {
		SetConsoleTextAttribute(hConsoleHandle, 9);
		break;
	}
	case '2': {
		SetConsoleTextAttribute(hConsoleHandle, 2);
		break;
	}
	case '3': {
		SetConsoleTextAttribute(hConsoleHandle, 3);
		break;
	}
	case '4': {
		SetConsoleTextAttribute(hConsoleHandle, 5);
		break;
	}
	case '5': {
		SetConsoleTextAttribute(hConsoleHandle, 6);
		break;
	}
	case '6': {
		SetConsoleTextAttribute(hConsoleHandle, 10);
		break;
	}
	case '7': {
		SetConsoleTextAttribute(hConsoleHandle, 11);
		break;
	}
	case '8': {
		SetConsoleTextAttribute(hConsoleHandle, 13);
		break;
	}
	case '*': {
		SetConsoleTextAttribute(hConsoleHandle, 4);
		break;
	}
	case '.': {
		SetConsoleTextAttribute(hConsoleHandle, 8);
		break;
	}
	}
	if (a == pos_i && b == pos_j) {
		SetConsoleTextAttribute(hConsoleHandle, 2);
	}
}
void CoutField() {
	SetConsoleTextAttribute(hConsoleHandle, 8);
	cout << "\n\n\n";
	for (int i = 0; i < SIZE; i++) {
		SetConsoleTextAttribute(hConsoleHandle, 8);
		cout << "\t\t\t";
		for (int j = 0; j < SIZE; j++) {
			SetConsoleTextAttribute(hConsoleHandle, 8);
			SetColor(i, j);
			if (i == pos_i && j == pos_j) {
				SetConsoleTextAttribute(hConsoleHandle, 15);
			}
			if (flags[i][j] == '!') {
				SetConsoleTextAttribute(hConsoleHandle, 4);
				if (i == pos_i && j == pos_j) {
					SetConsoleTextAttribute(hConsoleHandle, 15);
				}
				cout << " " << '!';
			}
			else {
				cout << " " << mns[i][j];
			}
		}
		SetConsoleTextAttribute(hConsoleHandle, 8);
		cout << endl;
	}
	SetConsoleTextAttribute(hConsoleHandle, 4);
	if (flags_num < 10 && flags_num >= 0)
		cout << "\n\n   ! 0" << flags_num;
	else
		cout << "\n\n   ! " << flags_num;
	SetConsoleTextAttribute(hConsoleHandle, 15);
}
void CoutFieldX() { // справа від ігрового поля поле з усіма відкритими клітинками
	SetConsoleTextAttribute(hConsoleHandle, 8);
	cout << "   0 1 2 3 4 5 6 7 8 9" << endl;
	for (int i = 0; i < SIZE; i++) {
		SetConsoleTextAttribute(hConsoleHandle, 8);
		cout << endl << i << " ";
		for (int j = 0; j < SIZE; j++) {
			SetConsoleTextAttribute(hConsoleHandle, 8);
			SetColor(i, j);
			if (i == pos_i && j == pos_j) {
				SetConsoleTextAttribute(hConsoleHandle, 15);
			}
			if (flags[i][j] == '!') {
				SetConsoleTextAttribute(hConsoleHandle, 4);
				if (i == pos_i && j == pos_j) {
					SetConsoleTextAttribute(hConsoleHandle, 15);
				}
				cout << " " << '!';
			}
			else {
				cout << " " << mns[i][j];
			}
		}
		SetConsoleTextAttribute(hConsoleHandle, 8);
		cout << "\t";
		for (int j = 0; j < SIZE; j++) {
			SetConsoleTextAttribute(hConsoleHandle, 8);
			SetColor(i, j);
			if (i == pos_i && j == pos_j) {
				SetConsoleTextAttribute(hConsoleHandle, 2);
			}
			cout << " " << mines[i][j];
			SetConsoleTextAttribute(hConsoleHandle, 8);
		}

	}
	SetConsoleTextAttribute(hConsoleHandle, 4);
	if (flags_num < 10 && flags_num >= 0)
		cout << "\n\n   ! 0" << flags_num;
	else
		cout << "\n\n   ! " << flags_num;
	SetConsoleTextAttribute(hConsoleHandle, 15);
}
void CoutAll() {
	system("cls");
	SetConsoleTextAttribute(hConsoleHandle, 8);
	cout << "\n\n\n";
	for (int i = 0; i < SIZE; i++) {
		SetConsoleTextAttribute(hConsoleHandle, 8);
		cout << "\t\t\t";
		for (int j = 0; j < SIZE; j++) {
			SetConsoleTextAttribute(hConsoleHandle, 8);
			SetColor(i, j);
			cout << " " << mines[i][j];
		}
		SetConsoleTextAttribute(hConsoleHandle, 8);
		cout << endl;
	}
	SetConsoleTextAttribute(hConsoleHandle, 4);
	if (flags_num < 10 && flags_num >= 0)
		cout << "\n\n   ! 0" << flags_num;
	else
		cout << "\n\n   ! " << flags_num;
	SetConsoleTextAttribute(hConsoleHandle, 15);
}
void YouLose() {
	mciSendString("close mp3", NULL, 0, NULL);
	PlaySound(".\\use\\FGBS(40).wav", NULL, SND_ASYNC);
	CoutAll();
	cout << "\tYOU LOSE" << endl;
	Sleep(3000);
	cout << "\n\n> go to menu" << endl;
	while (1) {
		char push = _getch();
		int push_int = static_cast<int>(push);
		if (push == 13) {
			PlaySound(".\\use\\FGBS(9).wav", NULL, SND_ASYNC);
			Menu();
		}
	}
}
void YouWin() {
	mciSendString("close mp3", NULL, 0, NULL);
	PlaySound(".\\use\\FGBS(40).wav", NULL, SND_ASYNC);
	CoutAll();
	cout << "\tYOU WIN" << endl;
	Sleep(3000);
	cout << "\n\n> go to menu" << endl;
	while (1) {
		char push = _getch();
		int push_int = static_cast<int>(push);
		if (push == 13) {
			PlaySound(".\\use\\FGBS(9).wav", NULL, SND_ASYNC);
			Menu();
		}
	}
}
void Empty(int a, int b) { // функція, яка відкриває 8 клітинок навколо пустих клітинок
	mns[a][b] = mines[a][b];
	if (a > 0 && mns[a - 1][b] == 'x') { // якщо клітинка зліва закрита
		mns[a - 1][b] = mines[a - 1][b];
		if (mines[a - 1][b] == '.') { // якщо клітинка зліва пуста
			Empty(a - 1, b); // потрібно відкрити 8 клітинок навколо неї
		}
	}
	// і так далі
	if (b > 0 && mns[a][b - 1] == 'x') {
		mns[a][b - 1] = mines[a][b - 1];
		if (mines[a][b - 1] == '.') {
			Empty(a, b - 1);
		}
	}
	if (a > 0 && b > 0 && mns[a - 1][b - 1] == 'x') {
		mns[a - 1][b - 1] = mines[a - 1][b - 1];
		if (mines[a - 1][b - 1] == '.') {
			Empty(a - 1, b - 1);
		}
	}
	if (a < (SIZE - 1) && b < (SIZE - 1) && mns[a + 1][b + 1] == 'x') {
		mns[a + 1][b + 1] = mines[a + 1][b + 1];
		if (mines[a + 1][b + 1] == '.') {
			Empty(a + 1, b + 1);
		}
	}
	if (a < (SIZE - 1) && mns[a + 1][b] == 'x') {
		mns[a + 1][b] = mines[a + 1][b];
		if (mines[a + 1][b] == '.') {
			Empty(a + 1, b);
		}
	}
	if (b < (SIZE - 1) && mns[a][b + 1] == 'x') {
		mns[a][b + 1] = mines[a][b + 1];
		if (mines[a][b + 1] == '.') {
			Empty(a, b + 1);
		}
	}
	if (a < (SIZE - 1) && b > 0 && mns[a + 1][b - 1] == 'x') {
		mns[a + 1][b - 1] = mines[a + 1][b - 1];
		if (mines[a + 1][b - 1] == '.') {
			Empty(a + 1, b - 1);
		}
	}
	if (a > 0 && b < (SIZE - 1) && mns[a - 1][b + 1] == 'x') {
		mns[a - 1][b + 1] = mines[a - 1][b + 1];
		if (mines[a - 1][b + 1] == '.') {
			Empty(a - 1, b + 1);
		}
	}


}
void OpenField(int aa, int bb) { // відкриває клітинки


	if (mines[aa][bb] == '*') {
		YouLose();
	}
	else if (isdigit(mines[aa][bb]) == 4) {
		mns[aa][bb] = mines[aa][bb];
	}
	else if (mines[aa][bb] == '.') {
		Empty(aa, bb);
	}

}
void Flags() { // функція для виставлення флажків
	if (mns[pos_i][pos_j] == 'x') { // якщо клітинка закрита
		if (flags[pos_i][pos_j] == '!') { // якщо флажок вже є, забираємо його
			flags[pos_i][pos_j] = ' ';
			flags_num++;
		}
		else {
			flags[pos_i][pos_j] = '!'; // якщо немає, ставимо
			flags_num--;
		}
	}
}
bool CheckWin() { // перевірка, чи ми виграли
	int unopened = ((SIZE)*(SIZE));
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (mns[i][j] != 'x') {
				unopened--;
			}

		}
	}

	if (unopened == (MINES_NUM)) // якщо к-сть відкритих клітинок співпадає з к-стю мін
		return true;
	else
		return false;
}

void Game() { // функція, що відповідає за ігрове поле
	bool first_push = true;
	flags_num = (MINES_NUM);
	mciSendString("open \"use\\18_Carat_Affair_Modus_Operandi.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	mciSendString("play mp3 from 0", NULL, 0, NULL);
	char push; // змінні для зчитування клавіш
	int push_int;
	fullInStart();
	while (1)
	{
		setcur(0, 0);
		CoutField();
		push = _getch(); // зчитування клавіш
		PlaySound(".\\use\\ButtonMove1.wav", NULL, SND_ASYNC);
		push_int = static_cast<int>(push);

		switch (push_int) {
		case 13: {  // enter
			if (first_push == true) {
				fullIn();
				first_push = false;
			}
			if (flags[pos_i][pos_j] != '!') {
				OpenField(pos_i, pos_j);
			}
			break;
		}
		case 32: { // пробіл
			if (first_push == true) {
				fullIn();
				first_push = false;
			}
			if (flags[pos_i][pos_j] != '!') {
				OpenField(pos_i, pos_j);
			}
			break;
		}
		case 77: {
			if (pos_j != (SIZE - 1)) {
				pos_j++;
			}
			break;
		}
		case 75: {
			if (pos_j != 0) {
				pos_j--;
			}
			break;
		}
		case 72: {
			if (pos_i != 0) {
				pos_i--;
			}
			break;
		}
		case 80: {
			if (pos_i != (SIZE - 1)) {
				pos_i++;
			}
			break;
		}
		case 120: {
			Flags();
			break;
		}
		case 27: {
			cout << "\ncancel game? [y/n]";
			char exit;
			cin >> exit;
			if (exit == 'y') {
				system("cls");

				mciSendString("close mp3", NULL, 0, NULL);
				Menu();
			}
			else {
				Sleep(1);
				system("cls");
			}

			break;
		}
		}
		if (CheckWin() == true) { // перевірка на виграш
			YouWin();
		}
	}
}

void checkKey() { // перевірка кодів клавіш
	char push;
	int push_int;
	while (1)
	{
		push = _getch();
		push_int = static_cast<int>(push);
		cout << "you pressed key " << push_int << endl;


	}
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	srand(time(0));

	Menu();







	cout << endl;
	system("pause");
	return 0;
}