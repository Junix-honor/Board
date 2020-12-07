#pragma once
#include "graph.h"
class Cricle :
	public graph
{
public:
	Cricle();
	~Cricle();
	Cricle(const Cricle& C);
	void DrawGraph();
	Cricle* renew();
	bool IsInGraph(screenPt TP, double error);
	bool IsEnd();
	const char* getType();
private:
	GLint radius, Cx, Cy;
};

