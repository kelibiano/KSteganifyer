/*
 * CFolder.h
 *
 *  Created on: 12.03.2013
 *      Author: yacine.haoues
 */

#ifndef CFOLDER_H_
#define CFOLDER_H_

#include "CWICompositeImpl.h"

namespace Utils {

class CFolder : public Core::CWICompositeImpl {
public:
	CFolder();
	virtual ~CFolder();
	std::string GetName() const;
};

} /* namespace Utils */
#endif /* CFOLDER_H_ */
