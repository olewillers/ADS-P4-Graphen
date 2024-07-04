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

	for (size_t i = 0; i < G.getV(); i++)
	{
		cout << i;

		for (Edge e : G[i])
		{
			cout << "  -> " << e.other(i) << " [" << e.weight() << "]";
		}

		cout << endl;
	}
}

bool menu(EdgeWeightedGraph*& Graph, EdgeWeightedDigraph*& dGraph)
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

	vector<bool> marked;
	vector<int> edgeTo;
	bool connected;
	
	PrimMST P_MST;
	vector<vector<Edge>> Prim_adj;

	KruskalMST K_MST;
	vector<vector<Edge>> kruskal_adj;

	DijkstraSP dijkstra;

	int v;
	int w;
	int weight;

    switch (eingabe)
    {
	case 0:

		return false;
		break;

    case 1:

		cout << "+ Welcher Graph soll aus den Testdateien eingelesen werden (1 / 2 / 3) ?> ";
		cin >> eingabe;
		cin.ignore();

		while (eingabe < 1 || eingabe > 3)
		{
			cout << endl << "+ Ungueltige Eingabe!" << endl << endl
				 << "+ Welcher Graph soll aus den Testdateien eingelesen werden (1 / 2 / 3) ?> ";
			cin >> eingabe;
			cin.ignore();
		}

		filename = "graph" + to_string(eingabe) + ".txt";

		delete Graph;
		delete dGraph;

		Graph = new EdgeWeightedGraph(filename);
		dGraph = new EdgeWeightedDigraph(filename);

        break;

    case 2:

		cout << "\n+ Startknoten auswaehlen ?> ";
		cin >> eingabe;
		cin.ignore();

		cout << "\nTiefensuche (Depth-First-Search (DFS)) - Startknoten: " << eingabe << endl;
		
		cout << "Besuchsreihenfolge:" << endl;
		connected = Graphsearch::DFS(*Graph, eingabe, marked, edgeTo);

		cout << endl << endl << "EdgeTo_Array:" << endl;
		for (size_t i = 0; i < Graph->getV(); i++)
		{
			cout << i << " -> " << edgeTo[i] << (i == eingabe ? " (StartKnoten)" : "") << endl;
		}

		cout << endl << "Marked-Array:" << endl;
		for (size_t i = 0; i < Graph->getV(); i++)
		{
			cout << i << " -> " << (marked[i] ? "true" : "false") << (i == eingabe ? " (StartKnoten)" : "") << endl;
		}

		cout << endl << "Graph ist " << (connected ? "zusammenhaengend" : "nicht zusammenhaengend") << endl << endl;

        break;

    case 3:

		cout << "\n+ Startknoten auswaehlen ?> ";
		cin >> eingabe;
		cin.ignore();

		cout << "\nBreitensuche (Breadth-First-Search (BFS)) - Startknoten: " << eingabe << endl;

		cout << "Besuchsreihenfolge:" << endl;
		connected = Graphsearch::BFS(*Graph, eingabe, marked, edgeTo);

		cout << endl << "EdgeTo_Array:" << endl;
		for (size_t i = 0; i < Graph->getV(); i++)
		{
			cout << i << " -> " << edgeTo[i] << (i == eingabe ? " (StartKnoten)" : "") << endl;
		}

		cout << endl << "Marked_Array:" << endl;
		for (size_t i = 0; i < Graph->getV(); i++)
		{
			cout << i << " -> " << (marked[i] ? "true" : "false") << (i == eingabe ? " (StartKnoten)" : "") << endl;
		}

		cout << endl << "Graph ist " << (connected ? "zusammenhaengend" : "nicht zusammenhaengend") << endl << endl;

        break;

    case 4:

		cout << endl << "+ Startknoten auswaehlen ?> ";
		cin >> eingabe;
		cin.ignore();

		P_MST = PrimMST(*Graph, eingabe);

		cout << "Minimaler Spannbaum (MST) nach Prim:" << endl
			 << "Gewicht: " << P_MST.weight() << endl
			 << "Adjazenzliste:" << endl;

		Prim_adj.resize(Graph->getV());

		for (Edge edge : P_MST.edges())
		{
			Prim_adj[edge.either()].push_back(edge);
		}
		for (size_t i = 0; i < Prim_adj.size(); i++)
		{
			if (Prim_adj[i].empty())
			{
				continue;
			}

			cout << i;
			for (Edge edge : Prim_adj[i])
			{
				cout << " -> " << edge.other(i) << " [" << edge.weight() << "]";
			}
			cout << endl;
		}
		cout << endl;

        break;

    case 5:

		// treeId zu Ausgabe hinzufuegen

		K_MST = KruskalMST(*Graph);

		cout << "Minimaler Spannbaum (MST) nach Kruskal:" << endl
			<< "Gewicht: " << K_MST.weight() << endl
			<< "Adjazenzliste:" << endl;

		kruskal_adj.resize(Graph->getV());

		for (Edge edge : K_MST.edges())
		{
			kruskal_adj[edge.either()].push_back(edge);
		}
		for (size_t i = 0; i < kruskal_adj.size(); i++)
		{
			if (kruskal_adj[i].empty())
			{
				continue;
			}

			cout << i;
			for (Edge edge : kruskal_adj[i])
			{
				cout << " -> " << edge.other(i) << " [" << edge.weight() << "]";
			}
			cout << endl;
		}
		cout << endl;

        break;

    case 6:

		int start;
		cout << "Startknoten: ?> ";
		cin >> start;

		int ziel;
		cout << "Zielknoten: ?> ";
		cin >> ziel;

		dijkstra = DijkstraSP(*dGraph, start);

		dijkstra.print_dijkstra(*dGraph);

		if (dijkstra.hasPathTo(ziel))
		{
			vector<DirectedEdge> path = dijkstra.pathTo(ziel);

			cout << endl;

			cout << endl
				<< "Kurzerster Weg (Djikstra):" << endl
				<< "Start:  " << start << endl
				<< "Ziel:   " << ziel << endl
				<< "Pfad:   " << start;

			for (DirectedEdge p : path)
			{
				cout << " [" << p.weight() << "] -> " << p.to();
			}

			cout << endl
				<< "Kosten: " << dijkstra.distTo(ziel) << endl
				<< endl;
			break;
		}
		else
		{
			cout << "Es gibt keinen Pfad vom Start zum Zielknoten" << endl;
			break;
		}

	case 7:

		print_adj_list(*Graph);

		break;

	case 8:

		cout << "Bitte ersten Knoten eingeben: " << endl;
		cout << "?> ";
		cin >> v;
		cout << "Bitte zweiten Knoten eingeben: " << endl;
		cout << "?> ";
		cin >> w;
		cout << "Bitte Kantengewicht eingeben: " << endl;
		cout << "?> ";
		cin >> weight;
		if (dGraph->del_Edge(DirectedEdge(v, w, weight)) && Graph->del_Edge(Edge(v, w, weight)))
		{
			cout << "Kante geloescht" << endl;
		}
		else
		{
			cout << "Kante nicht gefunden" << endl;
		}
		break;

	case 9:
		
		cout << "Bitte ersten Knoten eingeben: " << endl;
		cout << "?> ";
		cin >> v;
		cout << "Bitte zweiten Knoten eingeben: " << endl;
		cout << "?> ";
		cin >> w;
		cout << "Bitte Kantengewicht eingeben: " << endl;
		cout << "?> ";
		cin >> weight;
		dGraph->add(DirectedEdge(v, w, weight));
		Graph->add(Edge(v, w, weight));
		cout << "Kante hinzugefuegt" << endl;

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
	EdgeWeightedDigraph* dGraph = new EdgeWeightedDigraph(0);
	while (menu(Graph, dGraph)) {}


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