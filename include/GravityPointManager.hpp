
#pragma once

#include "GravityPoint.hpp"

class GravityPointManager
{
public:
	GravityPointManager(unsigned gpCount);

	GravityPoint *		getFreeGP();
	bool				isGPFree(const GravityPoint & gp) const;
	void				freeGP(GravityPoint & gp);
	void				freeAllGPs();

	unsigned					gpCount;
	std::vector<GravityPoint>	gravityPoints;
};

