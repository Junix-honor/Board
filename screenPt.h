#pragma once
#include"hender.h"
class screenPt
{
public:
	friend class graph;
	screenPt();
	screenPt(GLint nx, GLint ny);
	~screenPt();
	screenPt(const screenPt& S);
	void setCoords(GLint xCoordValue, GLint yCoordValue);
	GLint getx() const;
	GLint gety() const;
	void incrementx();
	void decrementy();
private:
	GLint x, y;
};

