#pragma once
#include "EdgeWeightedDigraph.h"
#include "EdgeWeightedGraph.h"
#include <iostream>

namespace Graphsearch {

	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen G,
		* ab dem Knoten v aus und markiert alle besuchten
		* Knoten in marked.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]	 G			Graph
		* \param[in]	 v			Startknoten
		* \param[in/out] marked		Bereits besuchte Knoten
		* \param[in/out] edgeTo		Vektor mit dem Nachfolgeknoten zu jedem Knoten
		*/

	void DFS_recursive(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo)
	{
		marked[v] = true;
		std::cout << v;

		for (const Edge& vw : G.getAdj(v))
		{
			int w = vw.other(v);
			
			if (!marked[w])
			{
				edgeTo[w] = v;
				std::cout << " -> ";
				DFS_recursive(G, w, marked, edgeTo);
			}
		}
		
	}

	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		* Starterfunktion zu DFS_recursive(EdgeWeigtedGraph, int, std::vector<bool>, std::vector<int>)
		*
		* \param[in]  G			Graph
		* \param[out] marked	Bereits besuchte Knoten
		* \param[out] edgeTo	Vektor mit dem Nachfolgeknoten zu jedem Knoten
		* \param[in]  v			Startknoten
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/

	bool DFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo)
	{
		marked.resize(G.getV());
		edgeTo.resize(G.getV());

		for (size_t i = 0; i < G.getV(); i++)
		{
			marked[i] = false;
			edgeTo[i] = -1;
		}
		
		DFS_recursive(G, v, marked, edgeTo);

		for (const bool& isMarked : marked)
		{
			if (!isMarked)
			{
				return false;
			}
		}
		
		std::cout << std::endl;
		return true;
	}

	/**
		* Fuehrt eine iterative Breitensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]  G			Graph
		* \param[in]  v			Startknoten
		* \param[out] marked	Gibt an welche Knoten besucht wurden bei der Suche
		* \param[out] edgeTo	Gibt den Nachfolgerknoten eines Knoten an
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/

	bool BFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo)
	{
		marked.resize(G.getV());
		edgeTo.resize(G.getV());

		for (size_t i = 0; i < G.getV(); i++)
		{
			marked[i] = false;
			edgeTo[i] = -1;
		}

		std::queue<int> q;
		q.push(v);

		while (!q.empty())
		{
			int curr_v = q.front();
			q.pop();

			if (marked[curr_v])
			{
				continue;
			}

			marked[curr_v] = true;
			std::cout << (curr_v != v ? " -> " : "") << curr_v;

			//for (size_t i = 0; i < G.getAdj(curr_v).size(); i++)
			for (const Edge& e : G[curr_v])
			{
				//int w = G.getAdj(curr_v)[i].other(curr_v);
				int w = e.other(curr_v);

				if (!marked[w] && edgeTo[w] == -1)
				{
					// TODO: auf richtigkeit pruefen!!!
					edgeTo[w] = curr_v;
					q.push(w);
				}
			}
		}

		std::cout << std::endl;

		for (bool isMarked : marked)
		{
			if (!isMarked)
			{
				return false;
			}
		}

		return true;
	}
}
