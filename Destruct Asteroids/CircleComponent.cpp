#include "CircleComponent.h"
#include "Math.h"

CircleComponent::CircleComponent(Actor * owner)
	: Component{ owner }
{
}

/*
 * Check collision between two circles 
 * @Return : if two circles intersect each other, true
 * @Param
 * lhs : one CircleComponent
 * rhs : the other CircleComponent
 */
bool IsCollided(const CircleComponent & lhs, const CircleComponent & rhs)
{
	Vector2D dis = lhs.GetCenter() - rhs.GetCenter();
	float radii = lhs.GetRadius() - rhs.GetRadius();
	return dis.LengthSq() <= radii * radii;
}
