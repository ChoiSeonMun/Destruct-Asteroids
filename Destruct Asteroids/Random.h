// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma  once
#include <random>
#include "Math.h"

class Random
{
public:
	static void Init();

	// Seed the generator with the specified int
	// NOTE: You should generally not need to manually use this
	static void Seed(unsigned int seed);

	// Get a float between 0.0f and 1.0f
	static float GetFloat();
	
	// Get a float from the specified range
	static float GetFloatRange(float min, float max);

	// Get an int from the specified range
	static int GetIntRange(int min, int max);

	// Get a random vector given the min/max bounds
	static Vector2D GetVector(const Vector2D& min, const Vector2D& max);
	static Vector3D GetVector(const Vector3D& min, const Vector3D& max);
private:
	static std::mt19937 sGenerator;
};
