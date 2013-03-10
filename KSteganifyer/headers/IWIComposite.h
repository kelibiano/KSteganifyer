/*
 * IWIComposite.h
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 */

#ifndef IWICOMPOSITE_H_
#define IWICOMPOSITE_H_

#include "IWorkItem.h"

namespace Core {

class IWIComposite: public Core::IWorkItem {
public:
	virtual ~IWIComposite() = 0;
	virtual bool IsRoot() const = 0;
	virtual bool HasChildren() const = 0;
	virtual void AddChild(IWorkItem * iChild) = 0;
	virtual IWorkItem * DeleteChild(const int iIndex) = 0;
	virtual IWorkItem * GetChild(const int iIndex) const = 0;
};

} /* namespace Core */
#endif /* IWICOMPOSITE_H_ */
