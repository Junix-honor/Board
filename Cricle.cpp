#include "Cricle.h"
Cricle::Cricle():graph(),radius(0),Cx(0),Cy(0){}
Cricle::~Cricle(){}
Cricle::Cricle(const Cricle& C) : graph(C),radius(C.radius),Cx(C.Cx),Cy(C.Cy){}
void setPixel(GLint xCoord, GLint yCoord)
{
	glPointSize(2.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2i(xCoord, yCoord);
	glEnd();
}

void circleMidpoint(GLint xc, GLint yc, GLint radius)
{
	screenPt circPt;

	GLint p = 1 - radius;

	circPt.setCoords(0, radius);

	void circlePlotPoints(GLint, GLint, screenPt);
	circlePlotPoints(xc, yc, circPt);
	while (circPt.getx() < circPt.gety()) {
		circPt.incrementx();
		if (p < 0)
			p += 2 * circPt.getx() + 1;
		else {
			circPt.decrementy();
			p += 2 * (circPt.getx() - circPt.gety()) + 1;
		}
		circlePlotPoints(xc, yc, circPt);
	}
}

void circlePlotPoints(GLint xc, GLint yc, screenPt circPt)
{
	setPixel(xc + circPt.getx(), yc + circPt.gety());
	setPixel(xc - circPt.getx(), yc + circPt.gety());
	setPixel(xc + circPt.getx(), yc - circPt.gety());
	setPixel(xc - circPt.getx(), yc - circPt.gety());
	setPixel(xc + circPt.gety(), yc + circPt.getx());
	setPixel(xc - circPt.gety(), yc + circPt.getx());
	setPixel(xc + circPt.gety(), yc - circPt.getx());
	setPixel(xc - circPt.gety(), yc - circPt.getx());
}
GLint sgn(GLint x)
{
	if (x < 0)
		return -1;
	else if (x >= 0)
		return 1;
}
void Cricle::DrawGraph()
{
	if (GraphPt.size() == 2)
	{
		GLint x1, x2, y1, y2;
		x1 = GraphPt[0].getx();
		x2 = GraphPt[1].getx();
		y1 = GraphPt[0].gety();
		y2 = GraphPt[1].gety();
		GLint dx = x2 - x1;
		GLint dy = y2 - y1;
		//ȷ���뾶
		radius = min(abs(dx), abs(dy)) / 2.0;
		//ȷ��Բ��
			//GLint sgn(GLint x) �ж�ֵ�����������Ϊ������1�����򣬷���-1
		Cx = radius * sgn(dx) + x1;
		Cy =radius * sgn(dy)+ y1;
		//�е㻭Բ�㷨
		circleMidpoint(Cx, Cy, radius);
	}
}
bool Cricle::IsInGraph(screenPt TP, double error)
{
	error +=1.3;//���ֵ
	GLdouble k;
	GLdouble TPx = TP.getx(), TPy = TP.gety();
	//��TP��Բ�ĵľ���k
	k = sqrt((TPx - Cx) * (TPx - Cx) + (TPy - Cy) * (TPy - Cy));
	//�������kԼ���ڰ뾶
	if (abs(k - radius) <= error)
		return true;
	else
		return false;
}
bool Cricle::IsEnd()
{
	if (GraphPt.size() == 2)
		return true;
	else
		return false;
}
Cricle* Cricle::renew()
{
	return new Cricle;
}
const char* Cricle::getType()
{
	return "Circle";
}