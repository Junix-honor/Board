#pragma once
#include "graph.h"
class RightTriangle :
	public graph
{
public:
	RightTriangle();
	~RightTriangle();
	RightTriangle(const RightTriangle& R);
	void DrawGraph();
	RightTriangle* renew();
	bool IsInGraph(screenPt TP, double error);
	bool IsEnd();
	const char* getType();
};