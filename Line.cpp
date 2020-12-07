#include "Line.h"
Line::Line() :graph() {}
Line::~Line() {}
Line::Line(const Line& L) : graph(L) {};
void Line::DrawGraph()
{
	if (GraphPt.size() == 2)//点的数目需要两个
	{
		glColor3f(0.0, 0.0, 0.0);//设置颜色
		glLineWidth(2.0);//设置线宽

		//绘制直线，每一对顶点被解释为一条直线
		glBegin(GL_LINES);
		for (auto it = GraphPt.begin(); it != GraphPt.end(); ++it)
			glVertex2i((*it).getx(), (*it).gety());
		glEnd();
	}

}
bool Line::IsInGraph(screenPt TP, double error)//error为误差值
{
	GLdouble EP1x = GraphPt[0].getx(), EP1y = GraphPt[0].gety(),
		EP2x = GraphPt[1].getx(), EP2y = GraphPt[1].gety(),
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
	if (abs(k1 - k2) <= error
		&& ((TPx <= EP1x && TPx >= EP2x) || (TPx <= EP2x && TPx >= EP1x))
		&& ((TPy <= EP1y && TPy >= EP2y) || (TPy <= EP2y && TPy >= EP1y)))
		return true;
	return false;
}
bool Line::IsEnd()
{
	if (GraphPt.size() == 2)
		return true;
	else
		return false;
}
Line* Line::renew()
{
	return new Line;//新建Line的实例并返回
}
const char* Line::getType()
{
	return "Line";
}