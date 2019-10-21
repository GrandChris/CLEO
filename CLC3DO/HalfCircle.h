//////////////////////////////////////////////////////////////////////////////
// File: HalfCircle.h
// Date: 18.10.2019
// Revision: 1
// Author: Christian Steinbrecher
// Descritpion: A mathematical cirlce cut in half
///////////////////////////////////////////////////////////////////////////////

#pragma once


#pragma once

#include "Object.h"

class HalfCircle : public Object {
public:
	// C-Tor
	HalfCircle(float const r);

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


inline HalfCircle::HalfCircle(float const r)
	: mR(r)
{
}

inline bool HalfCircle::isInside(glm::vec2 const& pos) const
{
	auto const p = pos - mPos;

	return p.x > 0 && (p.x * p.x) + (p.y * p.y) <= (mR * mR);
}

inline float HalfCircle::maxX() const
{
	return mPos.x + mR;
}

inline float HalfCircle::maxY() const
{
	return mPos.y + mR;
}

inline float HalfCircle::minX() const
{
	return mPos.x + 0;
}

inline float HalfCircle::minY() const
{
	return mPos.y + -mR;
}



