#include "PrimMST.h"

/**
 * Erstellt einen MST zum Graph G mit dem Prim Algorithmus
 *
 * \param[in]  G		Kantengewichteter-Graph
 * \param[in]  s		Startknoten
 */
PrimMST::PrimMST(EdgeWeightedGraph G, int s)
{
	marked = std::vector<bool>(G.getV(), false);

	visit(G, s);

	while (!pq.empty())
	{
		Edge min_e = pq.top();
		pq.pop();
		int v = min_e.either();
		int w = min_e.other(v);
		
		if (marked[v] && marked[w]) { continue; }
	
		mst.push_back(min_e);
		
		if (!marked[v]) { visit(G, v); }
		if (!marked[w]) { visit(G, w); }

	}
}

/**
 * Markiert Knoten v im Graph G als markiert und fuegt alle Nachbarn zur pq hinzu
 *
 * \param[in]  G		Kantengewichteter-Graph
 * \param[in]  v		Knoten im Graph G
 */
void PrimMST::visit(EdgeWeightedGraph G, int v)
{
	marked[v] = true;

	for (const Edge& edge : G.getAdj(v))
	{
		if (!marked[edge.other(v)]) { pq.push(edge); }
	}
}

/**
 * Gibt alle Kanten vom MST zurueck
 *
 * \return Vektor mit Kanten des MST
 */
std::vector<Edge> PrimMST::edges() const
{
	return mst;
}

/**
 * Gibt die Summe aller Gewichte im MST zurueck
 *
 * \return Summe der Gewichte im MST
 */
double PrimMST::weight() const
{
	double sum_MST_weights = 0.0;

	for (const Edge& edge : mst)
	{
		sum_MST_weights += edge.weight();
	}

	return sum_MST_weights;
}
