#include "Move.h"
Move::Move() :graph() {}
Move::~Move() {}
Move::Move(Move& M) : graph(M) {}
Move* Move::renew()
{
	PtCtr = 0;
	GraphPt.clear();
	return this;
}
bool Move::IsEnd()
{
	if (GraphPt.size() == 2)
		return true;
	else
		return false;
}