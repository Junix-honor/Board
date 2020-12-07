#include "RightTriangle.h"
RightTriangle::RightTriangle() :graph() {}
RightTriangle::~RightTriangle() {}
RightTriangle::RightTriangle(const RightTriangle& R) : graph(R) {}
void RightTriangle::DrawGraph()
{
	if (GraphPt.size() == 2)
	{
		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(GraphPt[0].getx(), GraphPt[0].gety());
		glVertex2i(GraphPt[0].getx(), GraphPt[1].gety());
		glVertex2i(GraphPt[1].getx(), GraphPt[1].gety());
		glEnd();
	}
}
bool RightTriangle::IsInGraph(screenPt TP, double error)
{
	GLdouble EP1x = GraphPt[0].getx(), EP1y = GraphPt[0].gety(),
		EP2x = GraphPt[1].getx(), EP2y = GraphPt[1].gety(),
		TPx = TP.getx(), TPy = TP.gety();

	//斜边

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

	error += 1.2;
	//两直角边
	if (((abs(TPx - EP1x) <= error) && ((TPy < EP1y && TPy > EP2y) || (TPy > EP1y&& TPy < EP2y)))
		|| ((abs(TPy - EP2y) <= error) && ((TPx < EP1x && TPx > EP2x) || (TPx > EP1x&& TPx < EP2x))))
		return true;

	return false;
}
bool RightTriangle::IsEnd()
{
	if (GraphPt.size() == 2)
		return true;
	else
		return false;
}
RightTriangle* RightTriangle::renew()
{
	return new RightTriangle;
}
const char* RightTriangle::getType()
{
	return "RightTriangle";
}