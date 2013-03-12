/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                   *
 *******************************************************************************
 * IIterator.h
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 ******************************************************************************/

#ifndef IITERATOR_H_
#define IITERATOR_H_

namespace Core {

template <class T>
class IIterator {
public:
	inline virtual ~IIterator(){};
	virtual T Current() const = 0;
	virtual T First() const = 0;
	virtual T Next() = 0;
	virtual bool End() const = 0;
	virtual int GetLevel() = 0;
};

} /* namespace Core */
#endif /* IITERATOR_H_ */
