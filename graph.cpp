#include "graph.h"
graph::graph(vector<screenPt> G, GLint P) :GraphPt(G), PtCtr(P) {}
graph::graph() : GraphPt(), PtCtr(0) {}
graph::~graph() {}
graph::graph(const graph& G)
{
	GraphPt = G.GraphPt;
	PtCtr = G.PtCtr;
}
vector<screenPt> graph::getPt()const//���ص������ĸ���
{
	return GraphPt;
}
void graph::push_back(screenPt Pt)
{
	if (GraphPt.size() == PtCtr)
		GraphPt.push_back(Pt);//����һ���㣬���������µ���һ�����������Ϣ

	GraphPt[PtCtr] = Pt;//�޸��������һ���㣬Ҳ���Ǹ�����һ�����������Ϣ
}
void graph::clear()//��յ�����
{
	GraphPt.clear();
	PtCtr = 0;
}
GLint graph::size()//���ص������Ĵ�С
{
	return GraphPt.size();
}
void graph::Pt_increase() { PtCtr++; }//����ȷ�����������Ŀ
GLint graph::Pt_num() { return PtCtr; }//�������������Ŀ
void graph::DrawGraph() {}
bool graph::IsInGraph(screenPt TP, double error) { return 0; }
bool graph::IsEnd() { return 0; }
graph* graph::renew()
{
	return new graph;
}
void graph::move(GLint dx, GLint dy)//dx��dyΪ�ƶ���
{
	//����ÿһ��������
	for (auto it = GraphPt.begin(); it != GraphPt.end(); ++it)
	{
		//�޸�ÿһ��������ĺ�������
		(*it).x += dx;
		(*it).y += dy;
	}
}
const char* graph::getType()
{
	return "Graph";
}