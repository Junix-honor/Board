#include "graph.h"
graph::graph(vector<screenPt> G, GLint P) :GraphPt(G), PtCtr(P) {}
graph::graph() : GraphPt(), PtCtr(0) {}
graph::~graph() {}
graph::graph(const graph& G)
{
	GraphPt = G.GraphPt;
	PtCtr = G.PtCtr;
}
vector<screenPt> graph::getPt()const//返回点容器的副本
{
	return GraphPt;
}
void graph::push_back(screenPt Pt)
{
	if (GraphPt.size() == PtCtr)
		GraphPt.push_back(Pt);//新增一个点，这个点就是新的下一个特征点的信息

	GraphPt[PtCtr] = Pt;//修改容器最后一个点，也就是更新下一个特征点的信息
}
void graph::clear()//清空点容器
{
	GraphPt.clear();
	PtCtr = 0;
}
GLint graph::size()//返回点容器的大小
{
	return GraphPt.size();
}
void graph::Pt_increase() { PtCtr++; }//增加确定特征点的数目
GLint graph::Pt_num() { return PtCtr; }//返回特征点的数目
void graph::DrawGraph() {}
bool graph::IsInGraph(screenPt TP, double error) { return 0; }
bool graph::IsEnd() { return 0; }
graph* graph::renew()
{
	return new graph;
}
void graph::move(GLint dx, GLint dy)//dx、dy为移动量
{
	//遍历每一个特征点
	for (auto it = GraphPt.begin(); it != GraphPt.end(); ++it)
	{
		//修改每一个特征点的横纵坐标
		(*it).x += dx;
		(*it).y += dy;
	}
}
const char* graph::getType()
{
	return "Graph";
}