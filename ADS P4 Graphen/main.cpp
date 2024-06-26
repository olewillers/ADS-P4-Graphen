#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include <iostream>
#include "EdgeWeightedGraph.h"
#include "PrimMST.h"
#include "Graphsearch.h"
#include "KruskalMST.h"
#include "DijkstraSP.h"

using namespace std;

void print_adj_list(EdgeWeightedGraph G)
{
	cout << endl;
	int i = 0;

	for (vector<Edge> adjList : G.getAdj())
	{
		int curr_V = i;
		cout << curr_V;
		i++;

		for (Edge adj : adjList)
		{
			cout << "  -> " << adj.other(curr_V) << " [" << adj.weight() << "]";
		}

		cout << endl;
	}
}

bool menu(EdgeWeightedGraph*& Graph)
{
    // Print Menu:
    cout << "=============================================" << endl
        << "       - Menu Graphen (by Ole Willers) -" << endl
        << "=============================================" << endl
        << "1) Graph einlesen" << endl
        << "2) Tiefensuche" << endl
        << "3) Breitensuche" << endl
        << "4) MST nach Prim (Eingabe: Startknoten)" << endl
        << "5) MST nach Kruskal" << endl
        << "6) Kuerzeste Wege nach Dijkstra (Eingabe: Startknoten)" << endl
        << "7) Ausgabe der Adjazenzliste" << endl
        << "8) Kante loeschen" << endl
        << "9) Kante hinzufuegen" << endl
        << "0) Programm beenden" << endl
        << "?> ";

    int eingabe = 0;
	string filename = "";
    cin >> eingabe;
    cin.ignore();

    switch (eingabe)
    {
	case 0:

		return false;
		break;

    case 1:

		cout << "+Welcher Graph soll aus den Testdateien eingelesen werden (1 / 2 / 3) ?> ";
		cin >> eingabe;
		cin.ignore();

		while (eingabe < 1 || eingabe > 3)
		{
			cout << endl << "+Ungueltige Eingabe!" << endl << endl
				 << "+Welcher Graph soll aus den Testdateien eingelesen werden (1 / 2 / 3) ?> ";
			cin >> eingabe;
			cin.ignore();
		}

		filename = "graph" + to_string(eingabe) + ".txt";

		delete Graph;

		Graph = new EdgeWeightedGraph(filename);

        break;

    case 2:
	 cout << "\n+ Startknoten auswählen ?> ";
		cin >> eingabe;
		cin.ignore();

		DFS::tiefensuche(Graph, eingabe);

        break;

    case 3:
	 cout << "\n+ Startknoten auswählen ?> ";
		cin >> eingabe;
		cin.ignore();

		DFS::bteitensuche(Graph, eingabe);
        break;

    case 4:

        break;

    case 5:

        break;

    case 6:

        break;

	case 7:

		print_adj_list(*Graph);

		break;

	case 8:

		break;

	case 9:
		
		break;

    default:

        cout << "!Ungueltige Eingabe! Eingabe wiederholen!" << endl;

        break;
    }

    return true;
}

int main() {
	// Starte Unit-Tests
	Catch::Session().run();

	//------------------------------------------------------------------------
	// 1. Ausgabe eines Graphen als Adjazenzliste implementieren
	//------------------------------------------------------------------------
	EdgeWeightedGraph* Graph = new EdgeWeightedGraph(0);
	while (menu(Graph)) {}


	//------------------------------------------------------------------------
	// 2. Suche in Graphen
	//------------------------------------------------------------------------
	// Verwenden Sie hierfür die Vorlagen in Graphsearch.h
	//
	// Beispielaufruf der Tiefensuche: 
	// std::vector<bool> marked;
	// std::vector<int>  edgeTo;
	// bool connected = Graphsearch::DFS(G1, start, marked, edgeTo);



	//------------------------------------------------------------------------
	// 3. Minimaler Spannbaum mit Prim und Kruskal
	//------------------------------------------------------------------------
	// Vorlage für Prim ist die Klasse PrimMST (PrimMST.h + PrimMST.cpp)
	// Vorlage für Kruskal ist die Klasse KruskalMST (KruskalMST.h + KruskalMST.cpp)
	//
	// Beispielaufruf von Prim:
	// PrimMST prim(G, 0);



	//------------------------------------------------------------------------
	// 4. Kuerzeste Wege mit Dijkstra
	//------------------------------------------------------------------------
	// Beispielaufruf von Dijkstra
	//
	// EdgeWeightedDigraph G1_directed("graph1.txt");
	// Dijkstra dijkstra(G1_directed, start);
	// path = dijkstra.pathTo(target);



	//------------------------------------------------------------------------
	// 5. Menü für Benutzereingaben
	//------------------------------------------------------------------------
	// Alle Funktionalitäten aus der Aufgabenstellung muessen umgesetzt werden

	return 0;
}