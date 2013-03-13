/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                   *
 *******************************************************************************
 * CWorkItemImpl.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 ******************************************************************************/

#include "Core/CWorkItemImpl.h"
#include "Core/IWIComposite.h"

using namespace NCore;

/******************************************************************************/
/* CWorkItemImpl::CWorkItemImpl(IWIComposite * iParent)                       */
/******************************************************************************/
CWorkItemImpl::CWorkItemImpl(IWIComposite * iParent) :
		mpParent(iParent)
{
	if(mpParent != NULL)
	{
		mpParent->AddChild(this);
	}
}

/******************************************************************************/
/* CWorkItemImpl::CWorkItemImpl()                                             */
/******************************************************************************/
CWorkItemImpl::CWorkItemImpl() :
		mpParent(NULL)
{
}

/******************************************************************************/
/* CWorkItemImpl::~CWorkItemImpl()                                            */
/******************************************************************************/
CWorkItemImpl::~CWorkItemImpl()
{
}

/******************************************************************************/
/* IWorkItem* CWorkItemImpl::GetParent() const                                */
/******************************************************************************/
IWorkItem* CWorkItemImpl::GetParent() const
{
	return mpParent;
}

/******************************************************************************/
/* bool CWorkItemImpl::IsCompound() const                                     */
/******************************************************************************/
bool CWorkItemImpl::IsCompound() const
{
	return false;
}

