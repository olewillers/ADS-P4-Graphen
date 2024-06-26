#include <assert.h>
#include <limits>
#include "DijkstraSP.h"

const int infinite_int = std::numeric_limits<int>::max();

/**
 * Füge eine Kante mit minimalen Kosten hinzu, die von einem
 * Baumknoten zu einem Nicht-Baumknoten verläuft und deren
 * Ziel w dem Startknoten s am nächsten ist.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  v		Zielknoten
 */
void DijkstraSP::relax(EdgeWeightedDigraph G, int v)
{
	for (DirectedEdge edge : G.getAdj(v))
	{
		int w = edge.to();
		if (v != edge.from())
		{
			continue;
		}

		if (distToVect[w] > distToVect[v] + edge.weight())
		{
			distToVect[w] = distToVect[v] + edge.weight();
			edgeTo[w] = edge;

			if (pq.contains(w))
			{
				pq.change(w, distToVect[w]);
			}
			else
			{
				pq.push(w, distToVect[w]);
			}
		}
	}
}

/**
 * Fuert den Dijkstra Algorithmus von s, im Graph G aus.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  s		Startknoten
 */
DijkstraSP::DijkstraSP(EdgeWeightedDigraph G, int s)
{
	DirectedEdge empty(-1, -1, -1);
	distToVect.resize(G.getV(), infinite_int);
	
	for (size_t i = 0; i < G.getV(); i++)
	{
		edgeTo[i] = empty;
	}

	distToVect[s] = 0;
	pq.push(s, 0.0);

	while (!pq.empty())
	{
		int v = pq.pop_top();

		relax(G, v);
	}
}

/**
 * Gibt die Distanz von s zum Knoten v zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Summe der Gewichte auf dem Pfad zu v
 */
double DijkstraSP::distTo(int v) const
{
	return distToVect[v];
}

/**
 * Gibt zurueck ob es einen Pfad zu v von s aus gibt
 *
 * \param[in]  v		Zielknoten
 * \return true, wenn es einen Pfad von s nach v gibt, sonst false
 */
bool DijkstraSP::hasPathTo(int v) const
{
	DirectedEdge edge = edgeTo.at(v);
	int curr_v = edge.from();
	double summed_weights = distToVect[v];

	while (true)
	{
		summed_weights -= edge.weight();

		if (distToVect[curr_v] == 0.0 || summed_weights <= 0.0)
		{
			break;
		}

		edge = edgeTo.at(curr_v);
		curr_v = edge.from();
	}

	if (distToVect[curr_v] == 0 && summed_weights == 0.0)
	{
		return true;
	}

	return false;
}

/**
 * Gibt den Pfad von s nach v als Vektor zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Vektor mit allen Kanten des Pfades von s nach v
 */
std::vector<DirectedEdge> DijkstraSP::pathTo(int v)
{
	std::vector<DirectedEdge> path_backwards;

	DirectedEdge edge = edgeTo[v];
	int curr_v = edge.from();
	double summed_weights = distToVect[v];

	//while (distToVect[curr_v] != 0 || summed_weights >= 0.0)
	while (true)
	{
		path_backwards.push_back(edge);

		summed_weights -= edge.weight();

		if (distToVect[curr_v] == 0.0 || summed_weights <= 0.0)
		{
			break;
		}

		edge = edgeTo[curr_v];
		curr_v = edge.from();
	}

	if (distToVect[curr_v] == 0.0 && summed_weights == 0.0)
	{
		int path_length = path_backwards.size();
		
		std::vector<DirectedEdge> path(path_length);

		for (DirectedEdge edge : path_backwards)
		{
			path_length--;
			path[path_length] = edge;
		}

		return path;
	}

	return std::vector<DirectedEdge>();
}
