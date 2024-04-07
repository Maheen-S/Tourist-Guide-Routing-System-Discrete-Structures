#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

void Display(int** matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << setw(4) << matrix[i][j] << setw(4);
		}
		cout << endl;
	}
}
int** create_matrix(string file_name)
{
	int cities = 0, roads = 0, x = 0, y = 0, passengers = 0;
	ifstream my_file(file_name);
	my_file >> cities;
	int** matrix = new int* [cities];
	for (int i = 0; i < cities; i++)
	{
		matrix[i] = new int[cities];
	}
	for (int i = 0; i < cities; i++)
	{
		for (int j = 0; j < cities; j++)
		{
			matrix[i][j] = 0;
		}
	}
	my_file >> roads;
	cout << "Cities = " << cities << endl;
	cout << "Roads = " << roads << endl;
	for (int i = 0; i < roads; i++)
	{
		my_file >> x;
		my_file >> y;
		my_file >> passengers;
		matrix[x - 1][y - 1] = passengers;
		matrix[y - 1][x - 1] = passengers;

	}
	my_file.close();
	Display(matrix, cities);

	return matrix;
}

int main()
{
	create_matrix("discrete.txt");
	return 0;
}
