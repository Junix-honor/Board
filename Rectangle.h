#pragma once
#include "graph.h"
class MyRectangle :
	public graph
{
public:
	MyRectangle();
	~MyRectangle();
	MyRectangle(const MyRectangle& R);
	void DrawGraph();
	MyRectangle* renew();
	bool IsInGraph(screenPt TP, double error);
	bool IsEnd();
	const char* getType();
};

