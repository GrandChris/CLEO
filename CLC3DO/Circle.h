//////////////////////////////////////////////////////////////////////////////
// File: Circle.h
// Date: 13.10.2019
// Revision: 1
// Author: Christian Steinbrecher
// Descritpion: A mathematical cirlce
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Object.h"

class Circle : public Object {
public:
	// C-Tor
	Circle(float const r);

	// Geerbt über Object
	virtual bool isInside(glm::vec2 const& pos) const override;

	virtual float maxX() const override;
	virtual float maxY() const override;

	virtual float minX() const override;
	virtual float minY() const override;

private:
	float mR = 0;
};



// #######+++++++ Implementation +++++++#######


inline Circle::Circle(float const r)
	: mR(r)
{
}

inline bool Circle::isInside(glm::vec2 const& pos) const
{
	auto const p = pos - mPos;

	return (p.x * p.x) + (p.y * p.y) <= (mR * mR);
}

inline float Circle::maxX() const
{
	return mPos.x + mR;
}

inline float Circle::maxY() const
{
	return mPos.y + mR;
}

inline float Circle::minX() const
{
	return mPos.x + -mR;
}

inline float Circle::minY() const
{
	return mPos.y + -mR;
}


