/*
 * CFolder.h
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 */

#ifndef CWICOMPOSITEIMPL_H_
#define CWICOMPOSITEIMPL_H_

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
	virtual bool IsRoot() const;
	virtual bool IsCompound() const;
	virtual bool HasChildren() const;
	virtual void AddChild(IWorkItem * iChild);
	virtual IWorkItem * GetParent() const;
	virtual IWorkItem * DeleteChild(const int iIndex);
	virtual IWorkItem * GetChild(const int iIndex) const;
private:
	std::vector<IWorkItem*> mItems;
	IWIComposite * mpParent;
};

} /* namespace Core */

#endif /* CWICOMPOSITEIMPL_H_ */
