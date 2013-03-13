/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                   *
 *******************************************************************************
 * IWIIterator.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 ******************************************************************************/

#include "Core/IWIIterator.h"
#include "Core/IWorkItem.h"
#include "Core/IWIComposite.h"
#include "Config.h"
using namespace NCore;

/******************************************************************************/
/* IWIIterator::IWIIterator(IWorkItem* ipFirst)                               */
/******************************************************************************/
IWIIterator::IWIIterator(IWorkItem* ipFirst):
		mpFirst(ipFirst), mIsDone(false)
{
	mStack.push(std::make_pair(ipFirst,-1));
}

/******************************************************************************/
/* IWIIterator::~IWIIterator()                                                */
/******************************************************************************/
IWIIterator::~IWIIterator()
{
}

/******************************************************************************/
/* IWorkItem * IWIIterator::Current() const                                   */
/******************************************************************************/
IWorkItem * IWIIterator::Current() const
{
	if(mStack.empty())
		return NULL;
	return mStack.top().first;
}

/******************************************************************************/
/* IWorkItem* IWIIterator::First() const                                      */
/******************************************************************************/
IWorkItem* IWIIterator::First() const
{
	return mpFirst;
}

/******************************************************************************/
/* IWorkItem * IWIIterator::Next()                                            */
/******************************************************************************/
IWorkItem * IWIIterator::Next()
{
	if(mStack.empty())
	{
		mIsDone = true;
		return  Current();
	}

	mStack.top().second++;
	IWorkItem* pCurrent = mStack.top().first;
	if(pCurrent->IsCompound())
	{
		IWIComposite* pCurrComp = static_cast<IWIComposite*>(pCurrent);
		if (pCurrComp->HasChildren())
		{
			int idx = mStack.top().second;
			IWorkItem* child = pCurrComp->GetChild(idx);
			if (child)
			{
				mStack.push(std::make_pair(child, -1));
				return Current();
			}
		}
	}
	mStack.pop();
	Next();
	return Current();
}

/******************************************************************************/
/* bool IWIIterator::End() const                                              */
/******************************************************************************/
bool IWIIterator::End() const
{
	return mIsDone;
}

/******************************************************************************/
/* int IWIIterator::GetLevel()                                                */
/******************************************************************************/
int IWIIterator::GetLevel()
{
	return mStack.size() -1;
}
