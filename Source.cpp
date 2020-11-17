#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define N_MAX 50
#define N_CITIES 6
#define INFINITY 1000000
using namespace std;

/*Issue: skips because 3rd smallest is 4, skips over 3 and never returns to 3 in a set*/
struct Vertex {

	int name;
	int weight;
	Vertex *prev = NULL;
	bool visited = false;
	
}; typedef struct Vertex Vertex;

struct Edge
{
	Vertex node1;
	Vertex node2;
	int weight;
}; typedef struct Edge Edge;

struct  Graph
{
	Edge *path[N_MAX];
	
}; typedef struct Graph Graph;

struct Stack_Node
{
	int city;
	Stack_Node *next = NULL;

}; typedef struct Stack_Node Stack_Node;

void printTable(Vertex *cities[], int n);
void push_Node(int data_in);
void pop_Node();
void printStack(Stack_Node *Top);
void Find_Shortest_Path(Vertex *cities[], int start_city);
void print_Diagram(Graph diagram, int count_pth);
void set_Cities(int user_input, Vertex *cities[], bool Visited[]);
void DijktraAlgrthm(Vertex *cities[], bool Visited[], Graph diagram, int count_pth);

Stack_Node *Top;

int main()
{
	int count = 0;
	string lines[N_MAX];
	
	Graph diagram;
	Vertex *cities[N_CITIES];
	bool Visited[N_CITIES];
	
	int user_input;
	char YorN;

	int start_city;

	string filename = "a5.txt";
	ifstream myfile(filename.c_str());

	int i = 0;
	int count_pth = 0;
	string temp;

	int keep_going = 1;

	if (myfile.is_open() == true)
	{
		while (getline(myfile, lines[count]))
		{
			count++;
		}

		myfile.close();
	}
	cout << endl;

	while (lines[i][0] != 'Q')
	{
		diagram.path[i] = new Edge();

		temp = lines[i][0];
		diagram.path[count_pth]->node1.name = atoi(temp.c_str());

		temp = lines[i][2];
		diagram.path[count_pth]->node2.name = atoi(temp.c_str());

		temp = lines[i].substr(4, lines[i].length() - 1);
		diagram.path[count_pth]->weight = atoi(temp.c_str());

		count_pth++;
		i++;
	}
	
	print_Diagram(diagram, count_pth);

	cout << "This program will ask you what city you want to start at. " << endl;

	while (keep_going == 1)
	{
		do
		{
			cout << "Enter City: ";
			for (int i = 0; i < N_CITIES; i++)
			{
				cout << i + 1 << " ";
			}
			cout << endl; 

			cin >> user_input;
		} while (user_input ==0 || user_input >5);

		cin.ignore(1000, '\n');

		set_Cities(user_input, cities, Visited);
		DijktraAlgrthm(cities, Visited, diagram, count_pth);
		printTable(cities, N_CITIES);

		start_city = user_input;

		Find_Shortest_Path(cities, start_city);

		do {
			cout << "Do you want to continue ? y or n " << endl;
			cin >> YorN;
			if (YorN == 'n')
			{
				keep_going = 0;
			}
		} while ( YorN !='y' && YorN !='n');

	}

	system("PAUSE");
	return 0;
}

void DijktraAlgrthm(Vertex *cities[], bool Visited[], Graph diagram, int count_pth)
{

	int find = 0;
	int temp1 = 0;
	bool flag = true;
	int ctr = 0;

	int min_wght;

	min_wght = cities[N_CITIES - 1]->weight;;

	while (Visited[N_CITIES - 1] == false)
	{

		for (int i = 0; i < N_CITIES; i++)   //finds which city is the smallest 
		{
			if (min_wght >= cities[i]->weight && cities[i]->visited == false)
			{
				min_wght = cities[i]->weight;
				find = cities[i]->name;

			}
		}

		for (int i = 0; i < count_pth; i++)
		{
			if (find == diagram.path[i]->node1.name)
			{
				for (int updte = 0; updte < N_CITIES; updte++)
				{
					if (cities[updte]->name == diagram.path[i]->node2.name)
					{
						temp1 = cities[find - 1]->weight + diagram.path[i]->weight;

						if (temp1 <= cities[updte]->weight)
						{
							cities[updte]->weight = temp1;
							cities[updte]->prev = cities[find - 1];
						}
					}

				}
			}
		}
		cities[find - 1]->visited = true;
		Visited[ctr] = true;
		/*refreshes the min weight, but also excluding the visited paths*/
		for (int i = 0; i < N_CITIES; i++)
		{
			if (cities[i]->visited == false)
			{
				min_wght = cities[i]->weight;
			}
		}
		ctr++;
	}
}
void set_Cities(int user_input, Vertex *cities[], bool Visited[])
{
	Vertex *tmp_city = NULL;

	for (int i = 0; i < N_CITIES; i++)
	{
		cities[i] = new Vertex();
		Visited[i] = false;
		cities[i]->visited = false;
		cities[i]->name = i + 1;

		if (cities[i]->name == user_input)
		{
			cities[i]->weight = 0;
			tmp_city = cities[i];
		}
		else
		{
			cities[i]->weight = INFINITY;
		}

		cities[i]->prev = tmp_city;

	}
}

void print_Diagram(Graph diagram, int count_pth)
{
	cout << "Diagram Chart" << endl;
	for (int i = 0; i < count_pth; i++)
	{
		cout << diagram.path[i]->node1.name << " " << diagram.path[i]->node2.name << " " << diagram.path[i]->weight << endl;
	}
	cout << endl;
}
void Find_Shortest_Path(Vertex *cities[], int start_city )
{
	Vertex *temp3;
	temp3 = new Vertex();

	int shrtest_pth = 0;
	int temp_pth = 0;

	for (int i = 0; i < N_CITIES; i++)
	{
		temp3 = cities[i];
		cout << "Shortest Path: " << start_city << "-->" << i + 1 << ": ";

		while (temp3->name != start_city)
		{
			push_Node(temp3->name);

			shrtest_pth += temp3->weight;
			temp3 = temp3->prev;
		}
		// pushes the last node 
		push_Node(temp3->name);
		/*empties the stack */
		while (Top != NULL)
		{
			temp_pth = Top->city;
			cout << temp_pth << " ";
			pop_Node();
		}
		cout << endl;
		//cout << "Total Weight: " << shrtest_pth << endl << endl;;
		shrtest_pth = 0;
	}

}

void printTable(Vertex *cities[], int n)
{
	cout << endl;
	cout << "_____________________________" << endl;
	cout << "NODE      WEIGHT    PREV NODE" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << cities[i]->name << "           " << cities[i]->weight << "            " << cities[i]->prev->name << endl;
	}
	cout << endl;
}

void push_Node(int data_in)
{
	Stack_Node *new_add = new Stack_Node;
	
	new_add->city = data_in;
	new_add->next = Top;
	Top = new_add;
}

void pop_Node()
{
	Stack_Node *temp;

	if (Top == NULL)
	{
		cout << "\nThe stack is empty" << endl << endl;

	}
	temp = Top;
	Top = Top->next;

	delete(temp);
}

void printStack(Stack_Node *Top)
{
	Stack_Node *temp;
	temp = new Stack_Node;

	cout << endl;
	cout << "Top of the Stack: " << endl;
	for (temp = Top; temp != NULL; temp = temp->next)
	{
		cout << temp->city << endl;
	}
}