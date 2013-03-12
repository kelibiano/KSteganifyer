/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                   *
 *******************************************************************************
 * IWorkItem.h
 *
 *  Created on: Mar 9, 2013
 *      Author: Kelibiano
 ******************************************************************************/

#ifndef IWORKITEM_H_
#define IWORKITEM_H_

#include "IItem.h"

namespace Core {

class IWorkItem : public IItem {
public:
	/**
	 * Class's destructor
	 */
	inline virtual ~IWorkItem(){}
	virtual IWorkItem * GetParent() const = 0;
	virtual bool IsCompound() const = 0;
};

} /* namespace Core */
#endif /* IWORKITEM_H_ */
