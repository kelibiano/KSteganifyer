/*
 * CFolder.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 */

#include "CWICompositeImpl.h"

using namespace Core;

CWICompositeImpl::CWICompositeImpl() :
		CWorkItemImpl(NULL), mpParent(NULL)
{
}

CWICompositeImpl::CWICompositeImpl(IWIComposite* iParent) :
		CWorkItemImpl(iParent), mpParent(NULL)
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
	if (iIndex >= (int)mItems.size())
		return NULL;
	IWorkItem * tmp = mItems[iIndex];
	mItems.erase(mItems.begin() + iIndex);
	return tmp;
}

bool CWICompositeImpl::HasChildren() const
{
	return !mItems.empty();
}

bool CWICompositeImpl::IsRoot() const
{
	return mpParent == NULL;
}

IWorkItem* Core::CWICompositeImpl::GetParent() const
{
	return CWorkItemImpl::GetParent();
}

IWorkItem* CWICompositeImpl::GetChild(const int iIndex) const
{
	if (iIndex >= (int)mItems.size())
		return NULL;
	return mItems[iIndex];
}
