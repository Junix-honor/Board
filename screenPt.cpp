#include "screenPt.h"
void screenPt::setCoords(GLint xCoordValue, GLint yCoordValue) {
	x = xCoordValue;
	y = yCoordValue;
}
screenPt::screenPt():x(0),y(0){}
screenPt::screenPt(GLint nx, GLint ny):x(nx), y(ny) {}
screenPt::~screenPt(){}
screenPt::screenPt(const screenPt& S):x(S.getx()),y(S.gety()){}
GLint screenPt::getx() const {
	return x;
}

GLint screenPt::gety() const {
	return y;
}
void screenPt::incrementx() {
	x++;
}
void screenPt::decrementy() {
	y--;
}