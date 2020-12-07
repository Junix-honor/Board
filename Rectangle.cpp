#include "Rectangle.h"
MyRectangle::MyRectangle() :graph() {}
MyRectangle::~MyRectangle() {}
MyRectangle::MyRectangle(const MyRectangle& R) : graph(R) {}
void MyRectangle::DrawGraph()
{
	if (GraphPt.size() == 2)
	{
		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(2.0);

		//GL_LINE_LOOP连续点生成封闭曲线，绘制矩形
		glBegin(GL_LINE_LOOP);
		glVertex2i(GraphPt[0].getx(), GraphPt[0].gety());
		glVertex2i(GraphPt[0].getx(), GraphPt[1].gety());
		glVertex2i(GraphPt[1].getx(), GraphPt[1].gety());
		glVertex2i(GraphPt[1].getx(), GraphPt[0].gety());
		glEnd();
	}
}
bool MyRectangle::IsInGraph(screenPt TP, double error)
{
	error += 1.2;//误差值
	GLdouble EP1x = GraphPt[0].getx(), EP1y = GraphPt[0].gety(),
		EP2x = GraphPt[1].getx(), EP2y = GraphPt[1].gety(),
		TPx = TP.getx(), TPy = TP.gety();

	//在误差运行范围内，在矩形的一段线段上即可
	if (((abs(TPx - EP1x) <= error || abs(TPx - EP2x) <= error)
		&& ((TPy<EP1y && TPy > EP2y) || (TPy > EP1y&& TPy < EP2y)))
		|| ((abs(TPy - EP1y) <= error || abs(TPy - EP2y) <= error)
			&& ((TPx<EP1x && TPx > EP2x) || (TPx > EP1x&& TPx < EP2x))))
		return true;

	return false;
}
bool MyRectangle::IsEnd()
{
	if (GraphPt.size() == 2)
		return true;
	else
		return false;
}
MyRectangle* MyRectangle::renew()
{
	return new MyRectangle;
}
const char* MyRectangle::getType()
{
	return "Rectangle";
}