/*
 * CWorkItemImpl.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 */

#include "CWorkItemImpl.h"
#include "IWIComposite.h"

using namespace Core;

CWorkItemImpl::CWorkItemImpl(IWIComposite * iParent) :
		mpParent(iParent)
{
	if(mpParent != NULL)
	{
		mpParent->AddChild(this);
	}
}

CWorkItemImpl::CWorkItemImpl() :
		mpParent(NULL)
{
}

CWorkItemImpl::~CWorkItemImpl()
{
}

IWorkItem* CWorkItemImpl::GetParent() const
{
	return mpParent;
}

bool CWorkItemImpl::IsCompound() const
{
	return false;
}

