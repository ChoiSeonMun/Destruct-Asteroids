#pragma once

#include <vector>
#include <functional>
#include "Actor.h"

namespace vec_util
{
	template <typename T>
	inline void Remove(std::vector<T>& vec, const T& value)
	{
		auto iter = std::find(vec.begin(), vec.end(), value);
		if (iter != vec.end())
		{
			std::iter_swap(iter, vec.end() - 1);
			vec.pop_back();
		}
	}

	template <typename T>
	inline void RemoveStable(std::vector<T>& vec, const T& value)
	{
		auto iter = std::find(vec.begin(), vec.end(), value);
		if (iter != vec.end())
		{
			vec.erase(iter);
		}
	}
}