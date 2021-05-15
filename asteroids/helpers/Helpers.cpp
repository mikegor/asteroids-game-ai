#include "Helpers.h"

/*x^2 + y^2 = speed^2
	x = tan(degree) * y
	speed = 1*/

float Helpers::getDirX(float deg)
{
	float sq = pow(tan(deg * (3.14 / 180)), 2);
	float dirY = sqrt(1 / (1 + sq));
	float dirX = tan(deg * (3.14 / 180)) * dirY;
	if (deg <= 90.f || (deg > 270.f && deg <= 360.f))
		return -dirX;
	else
		return dirX;
}

float Helpers::getDirY(float deg)
{
	float sq = pow(tan(deg * (3.14 / 180)), 2);
	float dirY = sqrt(1 / (1 + sq));
	if (deg <= 270.f && deg > 90.f)
		return -dirY;
	return dirY;
}
