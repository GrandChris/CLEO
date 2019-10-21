//////////////////////////////////////////////////////////////////////////////
// File: Objects.h
// Date: 18.10.2019
// Revision: 1
// Author: Christian Steinbrecher
// Descritpion: A base class for an object
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <glm/glm.hpp>

#include <memory>


class Object {
public:
	using uPtr = std::unique_ptr<Object>;

	// D-Tor
	virtual ~Object() = default;

	virtual bool isInside(glm::vec2 const & pos) const = 0;

	virtual float maxX() const = 0;
	virtual float maxY() const = 0;

	virtual float minX() const = 0;
	virtual float minY() const = 0;

	void setPos(glm::vec2 const& pos);
	glm::vec2 getPos() const;

protected:
	glm::vec2 mPos;
};



// #######+++++++ Implementation +++++++#######


inline void Object::setPos(glm::vec2 const& pos)
{
	mPos = pos;
}

inline glm::vec2 Object::getPos() const
{
	return mPos;
}
