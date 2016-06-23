
#include "GravityPointManager.hpp"

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
	return (gp.w != 0);
}

void			GravityPointManager::freeGP(GravityPoint & gp)
{
	gp.w = 0;
}

void			GravityPointManager::freeAllGPs()
{
	for (GravityPoint & gp : gravityPoints)
		freeGP(gp);
}
