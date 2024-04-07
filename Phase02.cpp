#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <list>
#include <cmath>
using namespace std;
class Node
{
private:
	int data;
	Node* next;
public:
	Node()
	{
		this->data = 0;
		this->next = NULL;
	}
	Node(int v)
	{
		this->data = v;
		this->next = NULL;
	}
	int get_data()
	{
		return this->data;
	}
	Node* get_next()
	{
		return this->next;
	}
	void set_data(int value)
	{
		this->data = value;
	}
	void set_next(Node* n)
	{
		this->next = n;
	}
};

class SinglyLinkedList
{
private:
	Node* head;
public:
	SinglyLinkedList()
	{
		this->head = NULL;
	}
	Node* get_head()
	{
		return this->head;
	}
	void set_head(Node* h)
	{
		this->head = h;
	}
	bool isEmpty()
	{
		if (head == NULL)
			return true;
		else
			return false;
	}
	void insertAtTail(Node* t)
	{
		if (isEmpty())
		{
			set_head(t);
		}
		else
		{
			Node* temp = head;
			while (temp->get_next() != NULL)
			{
				temp = temp->get_next();
			}
			temp->set_next(t);
		}
	}
	void insertAtTail(int v)
	{
		Node* t = new Node(v);
		if (isEmpty())
		{
			set_head(t);
		}
		else
		{
			Node* temp = head;
			while (temp->get_next() != NULL)
			{
				temp = temp->get_next();
			}
			temp->set_next(t);
		}
	}
	void display()
	{
		Node* temp = get_head();
		while (temp != NULL)
		{
			cout << temp->get_data() << "  ";
			temp = temp->get_next();
		}
	}
};

SinglyLinkedList global;

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
	//cout << "Cities = " << cities << endl;
	//cout << "Roads = " << roads << endl;
	for (int i = 0; i < roads; i++)
	{
		my_file >> x;
		my_file >> y;
		my_file >> passengers;
		matrix[x - 1][y - 1] = passengers;
		matrix[y - 1][x - 1] = passengers;	
	}
	my_file.close();
	//Display(matrix, cities);

	return matrix;
}
void display_adjacency_list(Node* m, int size)
{
	for (int i = 0; i < size; i++)
	{
		SinglyLinkedList si;
		si.set_head(m[i].get_next());
		si.display();
		cout << endl;
	}
}

class Graph
{
private:
	int vertices;
	list<int>* adj;

	void print_all_paths_helper(int, int, bool[], int[], int&);

public:
	Graph() {};
	Graph(int V)
	{
		this->vertices = V;
		adj = new list<int>[V];
	}
	void add_edge(int ver1, int ver2)
	{
		adj[ver1].push_back(ver2);
	}
	void print_all_paths(int start, int destination)
	{
		// vertices as not visited
		bool* visited = new bool[vertices];

		// array to store paths
		int* path = new int[vertices];
		int path_index = 0;

		// Initialize vertices
		for (int i = 0; i < vertices; i++)
		{
			visited[i] = false;
		}
		print_all_paths_helper(start, destination, visited, path, path_index);
	}
};

void Graph::print_all_paths_helper(int start, int destination, bool visited[], int path[], int& path_index)
{
	// store current node in path
	visited[start] = true;
	path[path_index] = start;
	path_index++;

	if (start == destination) {
		for (int i = 0; i < path_index; i++)
		{
			//cout << path[i] << " ";
			global.insertAtTail(path[i]);
		}
		//cout << endl;
	}
	else
	{
		// vertices adjacent to current vertex
		list<int>::iterator i;
		for (i = adj[start].begin(); i != adj[start].end(); ++i)
		{
			if (!visited[*i])
			{
				print_all_paths_helper(*i, destination, visited, path, path_index);
			}
		}
	}
	path_index--;
	visited[start] = false;
}

int main()
{
	//reading file
	string file_name = "discrete.txt";
	int start = 0, destination = 0;
	float total_passengers = 0;
	int cities = 0, roads = 0, x = 0, y = 0, passengers = 0;
	ifstream my_file(file_name);
	my_file >> cities;
	if (cities <= 0)
	{
		cout << "No cities." << endl;
		return 0;
	}
	if (cities == 1)
	{
		cout << "Error. Only one city." << endl;
		return 0;
	}
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
	if (roads <= 0)
	{
		cout << "No roads." << endl;
		return 0;
	}

	Graph g(cities + 1);
	for (int i = 0; i < roads; i++)
	{
		//checking for errors in file
		if (my_file.eof())
		{
			cout << "Error in file." << endl;
			return 0;
		}
		my_file >> x;
		if (x > cities)
		{
			cout << "Error in file." << endl;
			return 0;
		}
		my_file >> y;
		if (y > cities)
		{
			cout << "Error in file." << endl;
			return 0;
		}
		g.add_edge(x, y);
		g.add_edge(y, x);
		my_file >> passengers;
		if (passengers < 0)
		{
			cout << "Error in file." << endl;
			return 0;
		}
	}
	if (my_file.eof())
	{
		cout << "Error in file." << endl;
		return 0;
	}
	my_file >> start;
	my_file >> destination;
	if (start == destination)
	{
		cout << "0 trips required because starting position and ending position is the same." << endl;
		return 0;
	}
	my_file >> total_passengers;
	if (total_passengers < 0)
	{
		cout << "Error in file." << endl;
		return 0;
	}
	my_file.close();

	//simple paths
	g.print_all_paths(start, destination);

	//counting number of paths
	int number_of_paths = 0;
	Node* temp = global.get_head();
	while (temp != NULL)
	{
		if (temp->get_data() == start)
		{
			number_of_paths++;
		}
		temp = temp->get_next();
	}

	// array of node pointers to make adjacency list
	Node* arr_ptrz = new Node[number_of_paths];
	temp = global.get_head();
	for (int i = 0; i < number_of_paths; i++)
	{
		if (temp->get_data() == start)
		{
			SinglyLinkedList adjacency_list;
			Node* n = new Node(temp->get_data());
			adjacency_list.insertAtTail(n);
			temp = temp->get_next();
			while (temp->get_data() != start && temp->get_next()!=NULL)
			{
				Node* n = new Node(temp->get_data());
				adjacency_list.insertAtTail(n);
				temp = temp->get_next();
			}
			if (temp->get_next() == NULL)
			{
				Node* n = new Node(temp->get_data());
				adjacency_list.insertAtTail(n);
			}
			arr_ptrz[i].set_next(adjacency_list.get_head());
		}
		
	}

	int**matrix_2=create_matrix(file_name);

	// finding minimum passengers in each path
	temp = global.get_head();
	int* minimum_pass = new int[number_of_paths];
	for (int i = 0; i < number_of_paths; i++)
	{
		int min = 1000;
		Node* temp = arr_ptrz[i].get_next();
		Node* temp2 = arr_ptrz[i].get_next()->get_next();
		while (temp2->get_next() != NULL)
		{
			if (min>matrix_2[temp->get_data()-1][temp2->get_data()-1])
			{
				min = matrix_2[temp->get_data()-1][temp2->get_data()-1];
			}
			temp = temp->get_next();
			temp2 = temp2->get_next();
		}
		if (temp2->get_next() == NULL)
		{
			if (min > matrix_2[temp->get_data() - 1][temp2->get_data() - 1])
			{
				min = matrix_2[temp->get_data() - 1][temp2->get_data() - 1];
			}
		}
		minimum_pass[i] = min;
	}
	// finding max in minimum array
	int max = 0;
	for (int i = 0; i < number_of_paths; i++)
	{	
		if (max < minimum_pass[i])
		{
			max = minimum_pass[i];
		}
	}
	if (max <= 0)
	{
		cout << "No path exists between these points." << endl;
		return 0;
	}

	// total number of trips
	float trips = total_passengers / max;
	cout << round(trips) << endl;
	return 0;
}