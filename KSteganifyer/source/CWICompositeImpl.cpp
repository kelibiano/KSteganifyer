/*
 * CFolder.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 */

#include "../headers/CWICompositeImpl.h"
#include <algorithm>

using namespace Core;

CWICompositeImpl::CWICompositeImpl()
{
}

Core::CWICompositeImpl::CWICompositeImpl(IWIComposite* iParent)
{
}

CWICompositeImpl::~CWICompositeImpl()
{
}

bool CWICompositeImpl::IsCompound() const
{
	return true;
}

void CWICompositeImpl::AddChild(IWorkItem* iChild)
{
	if (iChild != NULL)
		mItems.push_back(iChild);
}

IWorkItem* CWICompositeImpl::DeleteChild(const int iIndex)
{
	if (iIndex >= mItems.size())
		return NULL;
	IWorkItem * tmp = mItems[iIndex];
	mItems.erase(mItems.begin() + iIndex);
	return tmp;
}

bool CWICompositeImpl::HasChildren() const
{
	return !mItems.empty();
}

IWorkItem* CWICompositeImpl::GetChild(const int iIndex) const
{
	if (iIndex >= mItems.size())
		return NULL;
	return mItems[iIndex];
}
