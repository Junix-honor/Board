#include "Line.h"
Line::Line() :graph() {}
Line::~Line() {}
Line::Line(const Line& L) : graph(L) {};
void Line::DrawGraph()
{
	if (GraphPt.size() == 2)//�����Ŀ��Ҫ����
	{
		glColor3f(0.0, 0.0, 0.0);//������ɫ
		glLineWidth(2.0);//�����߿�

		//����ֱ�ߣ�ÿһ�Զ��㱻����Ϊһ��ֱ��
		glBegin(GL_LINES);
		for (auto it = GraphPt.begin(); it != GraphPt.end(); ++it)
			glVertex2i((*it).getx(), (*it).gety());
		glEnd();
	}

}
bool Line::IsInGraph(screenPt TP, double error)//errorΪ���ֵ
{
	GLdouble EP1x = GraphPt[0].getx(), EP1y = GraphPt[0].gety(),
		EP2x = GraphPt[1].getx(), EP2y = GraphPt[1].gety(),
		TPx = TP.getx(), TPy = TP.gety();
	//б�ʲ�����
	if (abs((TPx - EP1x) / (TPy - EP1y)) <= error && abs((EP2x - TPx) / (EP2y - TPy)) <= error
		&& ((TPx <= EP1x && TPx >= EP2x) || (TPx <= EP2x && TPx >= EP1x))
		&& ((TPy <= EP1y && TPy >= EP2y) || (TPy <= EP2y && TPy >= EP1y)))
		return true;

	//б�ʴ���
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
	return new Line;//�½�Line��ʵ��������
}
const char* Line::getType()
{
	return "Line";
}