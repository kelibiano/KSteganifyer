/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                   *
 *******************************************************************************
 * IItem.h
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 ******************************************************************************/

#ifndef IITEM_H_
#define IITEM_H_

#include <string>

namespace NCore
{

class IItem
{
public:
	inline virtual ~IItem(){}
	virtual std::string ToString() = 0;
};

} /* namespace Core */
#endif /* IITEM_H_ */
