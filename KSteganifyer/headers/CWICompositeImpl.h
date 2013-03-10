/*
 * CFolder.h
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 */

#ifndef CFOLDER_H_
#define CFOLDER_H_

#include "IWIComposite.h"
#include "CWorkItemImpl.h"
#include <vector>

namespace Core
{
class IWorkItem;

class CWICompositeImpl: public CWorkItemImpl,
						public IWIComposite
{
public:
	CWICompositeImpl();
	CWICompositeImpl(IWIComposite * iParent);
	virtual ~CWICompositeImpl();
	virtual bool IsCompound() const;
	virtual bool HasChildren() const;
	virtual void AddChild(IWorkItem * iChild);
	virtual IWorkItem * DeleteChild(const int iIndex);
	virtual IWorkItem * GetChild(const int iIndex) const;
private:
	std::vector<IWorkItem*> mItems;
};

} /* namespace Core */

#endif /* CFOLDER_H_ */
