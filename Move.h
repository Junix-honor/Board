#pragma once
#include "graph.h"
class Move :
	public graph
{
public:
	Move();
	~Move();
	Move(Move& M);
	Move* renew();
	bool IsEnd();
};

