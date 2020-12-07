#pragma once
#include "graph.h"
class MyPolygon :
	public graph
{
public:
	MyPolygon();
	~MyPolygon();
	MyPolygon(const MyPolygon& P);
	void DrawGraph();
	MyPolygon* renew();
	bool IsInGraph(screenPt TP, double error);
	bool IsEnd();
	const char* getType();
};

