
#include "GravityPointManager.hpp"
#include <iostream>

GravityPointManager::GravityPointManager(unsigned gpCount) :
	gpCount(gpCount)
{
	gravityPoints.resize(gpCount);
	memset(gravityPoints.data(), 0, sizeof(GravityPoint) * gpCount);
}

GravityPoint *	GravityPointManager::getFreeGP()
{
	for (GravityPoint & gp : gravityPoints)
	{
		if (!isGPFree(gp))
			return &gp;
	}

	return nullptr;
}

bool			GravityPointManager::isGPFree(const GravityPoint & gp) const
{
	return (gp.s[3] != 0);
}

void			GravityPointManager::freeGP(GravityPoint & gp)
{
	gp.s[3] = 0; // We use the "w" component to determine if the gravity point is available
}

void			GravityPointManager::freeAllGPs()
{
	for (GravityPoint & gp : gravityPoints)
		freeGP(gp);
}
