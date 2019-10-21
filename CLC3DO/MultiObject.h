//////////////////////////////////////////////////////////////////////////////
// File: MultiObject.h
// Date: 18.10.2019
// Revision: 1
// Author: Christian Steinbrecher
// Descritpion: Some objects combined into one
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Object.h"

#include <vector>

class MultiObject : public Object {
public:
	// Geerbt über Object
	virtual bool isInside(glm::vec2 const& pos) const override;

	virtual float maxX() const override;
	virtual float maxY() const override;

	virtual float minX() const override;
	virtual float minY() const override;

	void add(Object::uPtr obj);

private:
	std::vector<Object::uPtr> mVec;
};




// #######+++++++ Implementation +++++++#######

#include <algorithm>

inline bool MultiObject::isInside(glm::vec2 const& pos) const
{
	for (auto const& elem : mVec)
	{
		if (elem->isInside(pos))
		{
			return true;
		}
	}

	return false;
}

inline float MultiObject::maxX() const
{
	if (mVec.empty())
	{
		return 0;
	}

	float max = mVec.front()->maxX();

	for (auto const& elem : mVec)
	{
		max = std::max(max, elem->maxX());
	}

	return max;
}

inline float MultiObject::maxY() const
{
	if (mVec.empty())
	{
		return 0;
	}

	float max = mVec.front()->maxY();

	for (auto const& elem : mVec)
	{
		max = std::max(max, elem->maxY());
	}

	return max;
}

inline float MultiObject::minX() const
{
	if (mVec.empty())
	{
		return 0;
	}

	float max = mVec.front()->minX();

	for (auto const& elem : mVec)
	{
		max = std::min(max, elem->minX());
	}

	return max;
}

inline float MultiObject::minY() const
{
	if (mVec.empty())
	{
		return 0;
	}

	float max = mVec.front()->minY();

	for (auto const& elem : mVec)
	{
		max = std::min(max, elem->minY());
	}

	return max;
}

inline void MultiObject::add(Object::uPtr obj)
{
	mVec.push_back(std::move(obj));
}
