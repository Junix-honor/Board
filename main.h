#pragma once
#include"hender.h"
#include"screenPt.h"
#include"graph.h"
#include"Line.h"
#include"Rectangle.h"
#include"Cricle.h"
#include"Polygon.h"
#include"Move.h"
#include"RightTriangle.h"
GLint winWidth = 800, winHeight = 600;

//�������⹦�ܵı��
bool Bmove = false;//�ƶ�����
bool Berase = false;//ɾ������
bool InGraph = false;//�ж��ƶ�ͼԪ�Ƿ�ȷ�����ƶ�ͼԪ���ܣ�

//����ͼԪʵ��
Line* liner = new Line;
MyRectangle* MyRectangler = new MyRectangle;
Cricle* Cricler = new Cricle;
MyPolygon* MyPolygoner = new MyPolygon;
Move* MyMover = new Move;
RightTriangle* RightTriangler = new RightTriangle;

graph* CG;//��ǰͼԪ
list<graph*>CGlist;//ͼԪ����

//key��ͼԪʵ���Ĺ�ϣ��
unordered_map<char,graph*> creat_new
({
	{'e', MyMover},{'E',MyMover},
	{'m', MyMover},{'M',MyMover},
	{'l', liner},{'L', liner},
	{'c', Cricler},{'C', Cricler},
	{'r', MyRectangler},{'R', MyRectangler},
	{'p', MyPolygoner},{'P', MyPolygoner},
	{'t', RightTriangler},{'T', RightTriangler}
	});

unordered_map<string, graph*>typeMap({{"Line",liner},{"Circle",Cricler},{"Rectangle",MyRectangler},{"Polygon",MyPolygoner},{"RightTriangle",RightTriangler} });