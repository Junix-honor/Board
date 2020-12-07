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

//画板特殊功能的标记
bool Bmove = false;//移动功能
bool Berase = false;//删除功能
bool InGraph = false;//判断移动图元是否确定（移动图元功能）

//各种图元实例
Line* liner = new Line;
MyRectangle* MyRectangler = new MyRectangle;
Cricle* Cricler = new Cricle;
MyPolygon* MyPolygoner = new MyPolygon;
Move* MyMover = new Move;
RightTriangle* RightTriangler = new RightTriangle;

graph* CG;//当前图元
list<graph*>CGlist;//图元链表

//key和图元实例的哈希表
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