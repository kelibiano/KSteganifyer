/*
 * CWorkItemImpl.h
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 */

#ifndef CWORKITEMIMPL_H_
#define CWORKITEMIMPL_H_

#include "IWorkItem.h"

namespace Core
{
class IWIComposite;
class CWorkItemImpl: public IWorkItem
{
public:
	CWorkItemImpl();
	CWorkItemImpl(IWIComposite * iParent);
	virtual ~CWorkItemImpl();
	virtual IWorkItem * GetParent() const;
	virtual bool IsCompound() const;
private:
	IWIComposite * mpParent;
};

} /* namespace Core */
#endif /* CWORKITEMIMPL_H_ */
