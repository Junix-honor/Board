#pragma once
#include "graph.h"
class Line :
	public graph
{
public:
	Line();
	~Line();
	Line(const Line& L);
	void DrawGraph();
	Line* renew();
	bool IsInGraph(screenPt TP, double error);
	bool IsEnd();
	const char* getType();
};

