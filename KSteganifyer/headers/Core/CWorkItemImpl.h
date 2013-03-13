/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                   *
 *******************************************************************************
 * CWorkItemImpl.h
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 ******************************************************************************/

#ifndef CWORKITEMIMPL_H_
#define CWORKITEMIMPL_H_

#include "Core/IWorkItem.h"

namespace NCore
{
class IWIComposite;

/**
 * Implementation class for the abstract interface IWorkItem. This class deliver
 * an implementation for the common methods defined in the interface.
 */
class CWorkItemImpl: public IWorkItem
{
public:

	/** Class's constructor */
	CWorkItemImpl();
	CWorkItemImpl(IWIComposite * iParent);

	/** Class's destructor */
	virtual ~CWorkItemImpl();

	virtual IWorkItem * GetParent() const;

private:
	virtual bool IsCompound() const;

private:
	IWIComposite * mpParent;
};

} /* namespace Core */
#endif /* CWORKITEMIMPL_H_ */
