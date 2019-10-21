//////////////////////////////////////////////////////////////////////////////
// File: CoIterator.h
// Date: 12.10.2019
// Revision: 1
// Author: Christian Steinbrecher
// Descritpion: Iterator for a coroutine
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <iterator>

template<typename TCoroutine>
class CoIterator
{
public:
	using iterator_category = std::forward_iterator_tag;
	//using value_type = T;
	//using difference_type = T;
	//using pointer = T*;
	//using reference = T&;

	// C-Tor
	CoIterator() = default;

	CoIterator(TCoroutine & coroutine);

	CoIterator& operator++();

	bool operator==(CoIterator<TCoroutine> const& right) const;

	auto const & operator*() const;


private:
	TCoroutine mCoroutine;
};



// #######+++++++ Implementation +++++++#######

//template<typename TCoroutine>
//inline CoIterator<TCoroutine>::CoIterator()
//	: mCoroutine(nullptr)
//{
//}

template<typename TCoroutine>
inline CoIterator<TCoroutine>::CoIterator(TCoroutine & coroutine)
	: mCoroutine(coroutine)
{
}

template<typename TCoroutine>
inline CoIterator<TCoroutine> & CoIterator<TCoroutine>::operator++()
{
	mCoroutine.resume();
	return *this;
}

template<typename TCoroutine>
inline bool CoIterator<TCoroutine>::operator==(CoIterator<TCoroutine> const & right) const
{
	return mCoroutine.done();
}

template<typename TCoroutine>
inline auto const & CoIterator<TCoroutine>::operator*() const
{
	return mCoroutine.promise().mVal;
}
