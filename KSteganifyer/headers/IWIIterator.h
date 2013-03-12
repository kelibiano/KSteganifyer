/*
 * IWIIterator.h
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 */

#ifndef IWIITERATOR_H_
#define IWIITERATOR_H_

#include "IIterator.h"
#include <stack>
namespace Core
{

class IWorkItem;

class IWIIterator: public Core::IIterator<IWorkItem*>
{
public:
	IWIIterator(IWorkItem * ipFirst);
	virtual ~IWIIterator();
	virtual IWorkItem * Current() const;
	virtual IWorkItem * First() const;
	virtual IWorkItem * Next();
	virtual bool End() const = 0;
private:
	typedef std::pair<IWorkItem*, int> StackItem;
	typedef std::stack<StackItem> StackType;
	IWorkItem * mpFirst;
	StackType mStack;
};

} /* namespace Core */
#endif /* IWIITERATOR_H_ */
