#include "GameOfLife.h"
#include <windows.h>
#include <map>
#include <vector>
#include <iostream>
#include <string>
using namespace std;
const int n = 25;
int grid[n][n];
int gridcopy[n][n];

 std::map<string, std::vector<int>> Shapes = {
   {"Blinker",{0,0,0,1,0,2}},
   {"Glider",{1,0,2,1,0,2,1,2,2,2} },
   {"Block",{0,0,1,0,0,1,1,1}},
   {"Beacon", {0,0,1,0,0,1,2,3,3,3,3,2}},
   {"Pentadecathlon",{0,1,1,1,2,0,2,2,3,1,4,1,5,1,6,1,7,2,7,0,8,1,9,1 }},
	{"Boat",{0,0,1,0,0,1,2,1,1,2}},
	{"Pulsar",{2,0, 3,0, 4,0, 0,2,    0,3,   0,4, 2,5, 3,5 ,  4,5,  5,4, 5,3, 5,2,
8,0, 9,0, 10,0 ,7,2 ,7,3 ,7,4, 8,5, 9,5, 10,5, 12,4 ,12,3, 12,2,
2,7, 3,7, 4,7, 0,8,    0,9,   0,10, 2,12, 3,12 ,  4,12,  5,10, 5,9, 5,8,
8,7, 9,7 ,10,7, 7,8 ,  7,9  ,7,10, 8,12, 9,12, 10,12 ,12,10 ,12,9 ,12,8
}}

};
int main()
{
	int y, x, n, i = 0;
	string shape;
	std::map<string, std::vector<int>>::iterator ShapesIt = Shapes.begin();
		while (ShapesIt != Shapes.end()) {
			std::cout << " " << i << ":" << ShapesIt->first << std::endl;
			i++;
			ShapesIt++;

		}
	std::cout << "Pattern name: ";
	std::getline(cin, shape);
	cout << "x :";
	cin >> x;
	cout << "y :";
	cin >> y;
	cout << "Number of ticks :";
	cin >> n;	
	system("cls");	
	DrawShape(shape, x, y);	
	

	system("cls");
	while (n) {
		system("cls");
		DrawGrid();

		Sleep(500);
		TestGeneration();
		n--;
	}

	return 0;
}

int DrawShape( string shape, int x, int y)
{
	
	vector<int> Positions= Shapes.at(shape);
	for (int i = 0; i < Positions.size(); i++) grid[x + Positions[i]][y + Positions[i++]] = 1;
	return 0;
}

void DrawGrid() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			if (grid[i][j] == 0)
				std::cout << ' ';
			else std::cout << 'O';
		}
		std::cout << '\n';
	}
}
void TestGeneration()
{
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			gridcopy[i][j] = grid[i][j];
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			int Alive = GetNeighbours(i, j);
			if (grid[i][j] == 1) {
				if (Alive<2 || Alive>3) grid[i][j] = 0;
			}
			else  {
				if (Alive == 3) grid[i][j] = 1;
			}
			
		}
	}
}
int GetNeighbours(int xc, int yc)
{
	
	int count = 0;
	for (int i = xc - 1; i <= xc + 1; i++) {
		for (int j = yc - 1; j <= yc + 1; j++) {
		if (!(i < 0 || i >= n || j < 0 || j >= n) && gridcopy[i][j]==1) count++;
		}
	}
	if (gridcopy[xc][yc] == 1) count--;
	return count;
}
