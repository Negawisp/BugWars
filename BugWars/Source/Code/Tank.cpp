#include "pch.h"
#include "Tank.h"
#include "Globals.h"
#include "Game.h"
#include "Bullet.h"
#include "Bug.h"
#include "GameBase/Log.h"

IMPLEMENT_RTTI(Tank);

void Tank::OnUpdate(float dt)
{
}

BugBase* Tank::GetBugToShoot() const
{
	Bug* bug = nullptr;
	Bug* tmpBug = nullptr;
	float closest = INFINITY;
	for (auto obj : g_Game->objects)
	{
		if (obj->GetRTTI() == Bug::s_RTTI)
		{
			auto tmpBug = static_cast<Bug*>(obj);
			if (!tmpBug->disabled)
			{
				float dist2 = position.Distance2(tmpBug->position);
				if (dist2 < closest) {
					closest = dist2;
					bug = tmpBug;
				}
			}
		}
	} 

	return bug;
}

Point Tank::CalcShootDirection(Point target_pos, Point target_dir, float target_vel, float bullet_vel) const
{
  // Intersection between circle of variable radius and line

	Point tankToTarget = target_pos - position;
	float a = bullet_vel * bullet_vel - target_vel * target_vel;
	float b = tankToTarget.Dot(target_dir) * target_vel;
	float c = -tankToTarget.Dot(tankToTarget);

	float D = b * b - a * c;
	float t1 = (b + sqrtf(D)) / a;
	float t2 = (b - sqrtf(D)) / a;
	if (t2 > t1 && t1 <= 0) {
			t1 = t2;
	}
	return (tankToTarget + target_dir * target_vel * t1) / (bullet_vel * t1);
}
