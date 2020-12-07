#include "Polygon.h"
MyPolygon::MyPolygon() :graph() {}
MyPolygon::~MyPolygon() {}
MyPolygon::MyPolygon(const MyPolygon& P) : graph(P) {}
void MyPolygon::DrawGraph()
{
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	//GL_LINE_STRIP: 一系列的连续直线,绘制多边形
	glBegin(GL_LINE_STRIP);
	for (auto it = GraphPt.begin(); it != GraphPt.end(); ++it)
		glVertex2i((*it).getx(), (*it).gety());
	glEnd();
}
bool IsInLine(screenPt EP1, screenPt EP2, screenPt TP, double error)
{
	GLdouble EP1x = EP1.getx(), EP1y = EP1.gety(),
		EP2x = EP2.getx(), EP2y = EP2.gety(),
		TPx = TP.getx(), TPy = TP.gety();
	//斜率不存在
	if (abs((TPx - EP1x) / (TPy - EP1y)) <= error && abs((EP2x - TPx) / (EP2y - TPy)) <= error
		&& ((TPx <= EP1x && TPx >= EP2x) || (TPx <= EP2x && TPx >= EP1x))
		&& ((TPy <= EP1y && TPy >= EP2y) || (TPy <= EP2y && TPy >= EP1y)))
		return true;

	//斜率存在
	GLdouble k1, k2;
	k1 = (TPy - EP1y) / (TPx - EP1x);
	k2 = (EP2y - TPy) / (EP2x - TPx);
	if (abs(k1 - k2) <= error && ((TPx <= EP1x && TPx >= EP2x) || (TPx <= EP2x && TPx >= EP1x)))
		return true;
	return false;
}
bool MyPolygon::IsInGraph(screenPt TP, double error)
{
	for (auto i = GraphPt.begin(); i != GraphPt.end() - 1; ++i)
		//点TP是否在多边形任一线段上
		if (IsInLine(*i, *(i + 1), TP, error))
			return true;
	return false;
}
bool MyPolygon::IsEnd()
{
	screenPt SPt, EPt;
	if (!GraphPt.empty())
	{
		SPt = GraphPt.front();//第一个点
		EPt = GraphPt.back();//最后一个点

		//当多边形首尾相接的时候，即在误差运行范围内，第一个点的坐标和最后一个点的坐标基本一致
		if (abs(SPt.getx() * 0.1 - EPt.getx() * 0.1) < 0.5 && abs(SPt.gety() * 0.1 - EPt.gety() * 0.1) < 0.5)
		{
			GraphPt.back() = SPt;
			return true;
		}
	}
	return false;
}
MyPolygon* MyPolygon::renew()
{
	return new MyPolygon;
}
const char* MyPolygon::getType()
{
	return "Polygon";
}