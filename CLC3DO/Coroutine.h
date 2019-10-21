//////////////////////////////////////////////////////////////////////////////
// File: Coroutine.h
// Date: 15.10.2019
// Revision: 1
// Author: Christian Steinbrecher
// Descritpion: General purpose coroutine functions
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Generator.h"

template<typename T>
Generator<T> take(Generator<T>& src, size_t count)
{
	for (auto const val : src)
	{
		if (count-- == 0)
		{
			break;
		}

		co_yield val;
	}
}

template<typename T>
void print(Generator<T>& src)
{
	for (auto const val : src)
	{
		std::cout << val << ", ";
	}
}