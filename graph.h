#pragma once
#include"hender.h"
#include"screenPt.h"
class graph
{
public:
	graph();
	graph(vector<screenPt> G, GLint P);
	virtual~graph();
	graph(const graph& G);
	vector<screenPt> getPt()const;
	void push_back(screenPt Pt);
	void clear();
	void move(GLint dx,GLint dy);
	GLint size();
	void Pt_increase();
	GLint Pt_num();
	virtual graph* renew();
	virtual void DrawGraph();
	virtual bool IsInGraph(screenPt TP,double error=0.3);
	virtual bool IsEnd();
	virtual const char* getType();
protected:
	vector<screenPt> GraphPt;
	GLint PtCtr;
};

