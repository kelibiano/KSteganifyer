/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                   *
 *******************************************************************************
 * IWIComposite.h
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 ******************************************************************************/

#ifndef IWICOMPOSITE_H_
#define IWICOMPOSITE_H_

#include "IWorkItem.h"

namespace NCore {

class IWIComposite: public NCore::IWorkItem {
public:
	inline virtual ~IWIComposite(){}
	virtual bool IsRoot() const = 0;
	virtual bool HasChildren() const = 0;
	virtual void AddChild(IWorkItem * iChild) = 0;
	virtual IWorkItem * DeleteChild(const int iIndex) = 0;
	virtual IWorkItem * GetChild(const int iIndex) const = 0;
};

} /* namespace Core */
#endif /* IWICOMPOSITE_H_ */