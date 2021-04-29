#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <cstdlib>

constexpr auto N = 9;

using namespace std;

int matrica[N][N] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						  { 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

bool nema(int row, int col, int broj) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrica[row + i][col + j] == broj)
				return false;
		}
	}
	return true;
}

void fillBox(int row, int col) {
	int broj;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			do {
				broj = rand() % 9 + 1;
			} while (!nema(row, col, broj));
			matrica[row + i][col + j] = broj;
		}
	}
}

void fillDiagonalBoxes() {
	for (int i = 0; i < N; i += 3) {
		fillBox(i, i);
	}
}

bool provjeri(int row, int col, int broj) {
	for (int i = 0; i < N; i++) {
		if (matrica[i][col] == broj)
			return false;
	}
	for (int i = 0; i < N; i++) {
		if (matrica[row][i] == broj)
			return false;
	}
	if (nema(row - (row % 3), col - (col % 3), broj))
		return true;
	return false;
}

bool fillRemaining(int row, int col) {
	if (col >= N && row < N - 1) {
		row++;
		col = 0;
	}
	if (row >= N && col >= N)
		return true;
	if (row < 3) {
		if (col < 3)
			col = 3;
	}
	else if (row < 6) {
		if (col == (int)(row / 3) * 3)
			col += 3;
	}
	else {
		if (col == 6) {
			row++;
			col = 0;
			if (row >= N)
				return true;
		}
	}
	cout << row << col << endl;
	for (int num = 1; num <= N; num++) {
		if (provjeri(row, col, num)) {
			matrica[row][col] = num;
			if (fillRemaining(row, col + 1))
				return true;
			matrica[row][col] = 0;
		}
	}
	return false;
}

void removeDigits(int brojObrisanih) {
	int t = brojObrisanih;
	while (t--) {
		int celija = rand() % 81 + 1;
		int row = celija / N;
		int col = celija % N;
		if (col != 0)
			col--;
		if (matrica[row][col] != 0) {
			matrica[row][col] = 0;
			continue;
		}
	}
}

void ispis() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << matrica[i][j] << " ";
		}
		cout << endl;
	}
}

void nuliraj() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			matrica[i][j] = 0;
		}
	}
}

void generator(ofstream& testFile, int brojObrisanih) {
	fillDiagonalBoxes();
	//fillRemaining(matrica, 0, 3);
	removeDigits(brojObrisanih);
	ispis();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			testFile << matrica[i][j];
			testFile << " ";
		}
		testFile << endl;
	}
	nuliraj();
}

int main() {
	cout << "How many examples you want to create(txt files)" << endl;
	int t;
	cin >> t;
	int num = 1;
	while (t--) {
		int tezina = 0;
		cout << "Choose difficulty(1-5/super_easy - extreme):" << endl;
		cin >> tezina;
		int brojObrisanih = 0;
		switch (tezina)
		{
		case 5:
			brojObrisanih = rand() % 10 + 54;
			break;
		case 4:
			brojObrisanih = rand() % 10 + 44;
			break;
		case 3:
			brojObrisanih = rand() % 10 + 34;
			break;
		case 2:
			brojObrisanih = rand() % 10 + 24;
			break;
		case 1:
			brojObrisanih = rand() % 10 + 10;
			break;
		default:
			break;
		}
		string fileName = "test" + to_string(num) + ".txt";
		ofstream testFile;
		testFile.open(fileName);
		if (testFile.is_open()) {
			cout << "oppened file succesfully" << endl;
			generator(testFile, brojObrisanih);
			cout << "closing file" << endl;
			testFile.close();
			num++;
		}
		else {
			cout << "error opening file" << endl;
		}
	}
	system("PAUSE");
	return 0;
}