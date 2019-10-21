//////////////////////////////////////////////////////////////////////////////
// File: Generator.h
// Date: 12.10.2019
// Revision: 1
// Author: Christian Steinbrecher
// Descritpion: Generates stuff through a coroutine
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Promise.h"
#include "CoIterator.h"

template<typename T>
class Generator
{
public: 
	using TVal = T;
	
	// using "promis_type" is mandatory
	using promise_type = Promise<Generator<T>>;

	using TIter = CoIterator<std::experimental::coroutine_handle<promise_type>>;

	// C-Tor
	explicit Generator(std::experimental::coroutine_handle<promise_type> coroutine);

	// D-Tor
	~Generator();

	void resume() const;

	T const & get() const;

	TIter begin();
	TIter end();

private:
	std::experimental::coroutine_handle<promise_type> mCoroutine = nullptr;
};




// #######+++++++ Implementation +++++++#######

template<typename T>
inline Generator<T>::Generator(std::experimental::coroutine_handle<promise_type> coroutine)
	: mCoroutine(coroutine)
{
}

template<typename T>
inline Generator<T>::~Generator()
{

	// if (!mCoroutine) // does not work as expected
	{
		mCoroutine.destroy();
	}
}

template<typename T>
inline void Generator<T>::resume() const
{
	mCoroutine.resume();
}

template<typename T>
inline T const & Generator<T>::get() const
{
	return mCoroutine.promise().mVal;
}

template<typename T>
inline typename Generator<T>::TIter Generator<T>::begin()
{
	if (mCoroutine.done())
	{
		return TIter();
	}
	else
	{
		return TIter(mCoroutine);
	}
}

template<typename T>
inline typename Generator<T>::TIter Generator<T>::end()
{
	return TIter();
}

