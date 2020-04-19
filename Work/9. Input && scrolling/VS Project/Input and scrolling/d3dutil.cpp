#include "d3dutil.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

static float gTime = 0;

float GetClock()
{
	return gTime;
}

void AddSecToClock(float sec)
{
	gTime += sec;
}


