/*
 * IWIIterator.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 */

#include "../headers/IWIIterator.h"
#include "../headers/IWorkItem.h"
#include "../headers/Config.h"
using namespace Core;

IWIIterator::IWIIterator(IWorkItem* ipFirst):
		mpFirst(ipFirst)
{
}

Core::IWIIterator::~IWIIterator()
{

}

IWorkItem * Core::IWIIterator::Current() const
{
	if(mStack.empty())
		return NULL;
	return mStack.top().first;
}

IWorkItem* Core::IWIIterator::First() const
{
	return mpFirst;
}

IWorkItem * IWIIterator::Next()
{
	return Current();
}

