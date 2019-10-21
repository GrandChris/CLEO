//////////////////////////////////////////////////////////////////////////////
// File: Promise.h
// Date: 12.10.2019
// Revision: 1
// Author: Christian Steinbrecher
// Descritpion: A promise for a coroutine
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <experimental/coroutine>

#include <utility>

template<typename TBase>
class Promise
{
public:
	using TVal = typename TBase::TVal;

	TBase get_return_object();
	auto initial_suspend() const;
	auto final_suspend() const;
	auto yield_value(TVal const & val);
	//void retunr
	//void return_value(TVal const& val);
	

	TVal mVal = TVal();
};


// #######+++++++ Implementation +++++++#######

template<typename TBase>
inline TBase Promise<TBase>::get_return_object()
{
	return TBase(std::experimental::coroutine_handle<Promise<TBase>>::from_promise(*this));
}

template<typename TBase>
inline auto Promise<TBase>::initial_suspend() const
{
	return std::experimental::suspend_never();
}

template<typename TBase>
inline auto Promise<TBase>::final_suspend() const
{
	return std::experimental::suspend_always();
}

template<typename TBase>
inline auto Promise<TBase>::yield_value(TVal const& val)
{
	mVal = val;
	return std::experimental::suspend_always();
}

//template<typename TBase>
//inline void Promise<TBase>::return_void()
//{
//}
//
//template<typename TBase>
//inline void Promise<TBase>::return_value(TVal const & val)
//{
//	mVal = val;
//}
