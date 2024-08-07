#pragma once
#include <vector>
#include <queue>
#include "EdgeWeightedGraph.h"

class KruskalMST
{
private:
	std::vector<Edge> mst;				// MST-Kanten
	std::vector<int> treeID;			// BaumId zu jedem Knoten
public:
	KruskalMST() {};
	KruskalMST(EdgeWeightedGraph G);
	void treeID_union(int u, int v);
	std::vector<Edge> edges() const;	// liefert MST
	double weight() const;     			// berechnet Gesamtkosten des MST
};

