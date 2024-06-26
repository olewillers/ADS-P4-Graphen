#include "KruskalMST.h"
#include <queue>

/**
 * Erstellt einen MST zum Graph G mit dem Kruskal Algorithmus
 *
 * \param[in]  G		Kantengewichteter-Graph
 */
KruskalMST::KruskalMST(EdgeWeightedGraph G)
{
	int anz_V = G.getV();
	treeID = std::vector<int>(anz_V);
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

	for (size_t ID = 0; ID < anz_V; ID++)
	{
		treeID[ID] = ID;
	}

	for (const Edge& e : G.edges())
	{
		pq.push(e);
	}

	while (!pq.empty() && mst.size() < anz_V)
	{
		Edge e = pq.top();
		pq.pop();
		int u = e.either();
		int v = e.other(u);

		if (treeID[u] != treeID[v])
		{
			mst.push_back(e);
			treeID_union(u, v);
		}
	}
}

void KruskalMST::treeID_union(int u, int v)
{
	int u_ID = treeID[u];
	int v_ID = treeID[v];
	
	for (int& ID : treeID)
	{
		if (ID == v_ID) { ID = u_ID; }
	}
}

/**
 * Gibt alle Kanten vom MST zurueck
 *
 * \return Vektor mit Kanten des MST
 */
std::vector<Edge> KruskalMST::edges() const
{
	return mst;
}

/**
 * Gibt die Summe aller Gewichte im MST zurueck
 *
 * \return Summe der Gewichte im MST
 */
double KruskalMST::weight() const
{
	double sum_MST_weights = 0.0;

	for (const Edge& edge : mst)
	{
		sum_MST_weights += edge.weight();
	}

	return sum_MST_weights;
}
