#ifndef POSITION_H
#define POSITION_H

struct Position {
	double x;
	double y;
	bool operator == (const Position& p) {
		return x == p.x && y == p.y;
	}
};

#endif