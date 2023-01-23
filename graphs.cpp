#include <iostream>
#include <vector>
#include <string>

using namespace std;

// wyswietla sasiadujace wierzcholki dla kazdego wierzcholka
void findNeighboursOfEachVertex(std::vector<std::vector<int>> graph, int numVertex)
{
	for (int i = 0; i < numVertex; i++)
	{
		string neighbours = "";
		for (int j = 0; j < numVertex; j++)
		{
			if (i != j && graph[i][j] == 1)
				neighbours += to_string(j) + " ";
		}
		if (neighbours.empty())
			cout << "Wierzcholek " << i << " nie ma sasiadujacych wierzcholkow" << endl;
		else
			cout << "Wierzcholek " << i << " ma sasiadujace wierzcholki: " << neighbours << endl;
	}
}

// wyswietla wierzcholki, ktorych sasiadami sa wszystkie inne wierzcholki
void findVervicesHavingAllOtherVerticesNeighbours(std::vector<std::vector<int>> graph, int numVertex)
{
	std::vector<int> edges;
	edges.resize(numVertex);

	for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			if (i != j && graph[i][j] == 1)
				edges[i]++;
		}
	}

	bool found = false;
	for (int i = 0; i < numVertex; i++)
	{
		if (edges[i] == numVertex - 1)
		{
			cout << "Sasiadami wierzcholka " << i << " sa wszystkie pozostale wierzcholki" << endl;
			found = true;
		}
	}
	if (found == false)
	{
		cout << "Nie ma wierzcholkow, ktorych sasiadami sa wszystkie pozostale wierzcholki" << endl;
	}
}

// wyswietla stopnie wychodzace wszystkich wierzcholkow
void findOutDegreeOfEachVertex(std::vector<std::vector<int>> graph, int numVertex)
{
	for (int i = 0; i < numVertex; i++)
	{
		int outDegree = 0;
		for (int j = 0; j < numVertex; j++)
		{
			if (i != j && graph[i][j] == 1)
				outDegree++;
		}
		cout << "Stopien wychodzacy wierzcholka " << i << ": " << outDegree << endl;
	}
}

// wyswietla stopnie wchodzace wszystkich wierzcholkow
void findInDegreeOfEachVertex(std::vector<std::vector<int>> graph, int numVertex)
{
	for (int j = 0; j < numVertex; j++)
	{
		int inDegree = 0;
		for (int i = 0; i < numVertex; i++)
		{
			if (i != j && graph[i][j] == 1)
				inDegree++;
		}
		cout << "Stopien wchodzacy wierzcholka " << j << ": " << inDegree << endl;
	}
}

// wyswietla izolowane wierzcholki
void findIsolatedVertices(std::vector<std::vector<int>> graph, int numVertex)
{
	bool foundIsolated = false;
	for (int v = 0; v < numVertex; v++)
	{
		bool isolated = true;
		for (int x = 0; x < numVertex; x++)
		{
			if (graph[x][v] != 0)
			{
				isolated = false;
				break;
			}
		}
		if (isolated)
		{
			for (int y = 0; y < numVertex; y++)
			{
				if (graph[v][y] != 0)
				{
					isolated = false;
					break;
				}
			}
		}

		if (isolated)
		{
			cout << "Wierzcholek izolowany: " << v << endl;
			foundIsolated = true;
		}
	}
	if (foundIsolated == false)
		cout << "Brak izolowanych wierzcholkow" << endl;
}

// znajduje i wyswietla wierzcholki, ktore posiadaja petle
void findLoopsOfEachVertex(std::vector<std::vector<int>> graph, int numVertex)
{
	for (int i = 0; i < numVertex; i++)
	{
		bool loop = false;
		for (int j = 0; j < numVertex; j++)
		{
			if (i == j && graph[i][j] == 1)
			{
				loop = true;
				break;
			}
		}
		cout << "Wierzcholek " << i;
		if (loop)
			cout << " posiada petle" << endl;
		else
			cout << " nie posiada petli" << endl;
	}
}

// znajduje i wyswietla krawedzie dwukierunkowe grafu
void findTwoWayEdges(std::vector<std::vector<int>> graph, int numVertex)
{
	bool found = false;
	for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			if (i != j && graph[i][j] == 1 && graph[j][i] == 1)
			{
				cout << "Krawedz dwukierunkowa pomiedzy wierzcholkami " << i << " a " << j << endl;
				found = true;
				i++; // zapobiega ponownemu wypisywaniu tej samej krawedzi z odwroconymi wierzcholkami
			}
		}
	}
	if (found == false)
	{
		cout << "Nie ma krawedzi dwukierunkowych w grafie" << endl;
	}
}

// generuje tablice sasiedztwa grafu
std::vector<std::vector<int>> generateAdjacencyMatrix(int numVertex, std::vector<int> P, std::vector<int> K)
{
	std::vector<std::vector<int>> matrix;
	matrix.resize(numVertex);
	for (int i = 0; i < numVertex; i++)
	{
		matrix[i].resize(numVertex);
	}

	for (int i = 0; i < P.size(); i++)
	{
		int p = P[i];     // wierzcholek startowy
		int k = K[i];     // wierzcholek koncowy
		matrix[p][k] = 1; // Krawedz P->K obecna
	}

	for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	return matrix;
}

// pobieranie danych grafu od uzytkownika
bool readGraphData(int& numVertex, std::vector<int>& P, std::vector<int>& K)
{
	int numEdges, p, k;
	cout << "Podaj liczbe wierzcholkow grafu: ";
	cin >> numVertex;
	cout << "Podaj liczbe krawedzi grafu: ";
	cin >> numEdges;

	if (numVertex > 0)
	{
		P.clear();
		K.clear();
		for (int i = 0; i < numEdges; i++)
		{
			cout << "Podaj krawedz " << i << " [P K]: ";
			cin >> p >> k;
			if (p >= 0 && k >= 0 && p < numVertex && k < numVertex)
			{
				P.push_back(p);
				K.push_back(k);
			}
			else
			{
				cout << "Podana krawedz zawiera nieprawidlowe wierzcholki." << endl;
				i--;
			}
		}

		return true;
	}

	return false;
}

// funkcja main
int main()
{
	// ilosc wierzcholkow
	int numVertex;
	// tablice krawedzi grafu (poczatki, konce)
	std::vector<int> P, K;
	// pobieranie danych grafu od uzytkownika
	if (readGraphData(numVertex, P, K) == false)
		return 1; // brak wierzcholkow

	// definicja krawedzi grafu (P, K)
//	std::vector<int> P = { 0, 1, 1, 3, 2 }; // wierzcholki poczatkowe
//	std::vector<int> K = { 1, 0, 2, 3, 0 }; // wierzcholki koncowe

	// generowanie macierzy sasiedztwa
	cout << "Macierz sasiedztwa" << endl;
	std::vector<std::vector<int>> graph = generateAdjacencyMatrix(numVertex, P, K);

	// sasiadujace wierzcholki dla kazdego wierzcholka
	cout << endl << "Zadanie 1" << endl;
	findNeighboursOfEachVertex(graph, numVertex);

	cout << endl << "Zadanie 2" << endl;
	// wierzcholki, ktorych sasiadami sa wszystkie pozostale wierzcholki
	findVervicesHavingAllOtherVerticesNeighbours(graph, numVertex);

	// stopnie wychodzace wszystkich wierzcholkow
	cout << endl << "Zadanie 3" << endl;
	findOutDegreeOfEachVertex(graph, numVertex);

	// stopnie wchodzace wszystkich wierzcholkow
	cout << endl << "Zadanie 4" << endl;
	findInDegreeOfEachVertex(graph, numVertex);

	// izolowane wierzcholki
	cout << endl << "Zadanie 5" << endl;
	findIsolatedVertices(graph, numVertex);

	// wierzcholki, ktore posiadaja petle
	cout << endl << "Zadanie 6" << endl;
	findLoopsOfEachVertex(graph, numVertex);

	// krawedzie dwukierunkowe grafu
	cout << endl << "Zadanie 7" << endl;
	findTwoWayEdges(graph, numVertex);

	return 0;
}
