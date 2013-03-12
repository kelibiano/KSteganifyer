/*
 * IItem.h
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 */

#ifndef IITEM_H_
#define IITEM_H_

#include <string>

namespace Core
{

class IItem
{
public:
	inline virtual ~IItem(){}
	virtual std::string GetName() const = 0;
};

} /* namespace Core */
#endif /* IITEM_H_ */
