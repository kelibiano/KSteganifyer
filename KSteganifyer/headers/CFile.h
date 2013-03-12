/*
 * CFile.h
 *
 *  Created on: 12.03.2013
 *      Author: yacine.haoues
 */

#ifndef CFILE_H_
#define CFILE_H_

#include "CWorkItemImpl.h"
#include <string>


namespace Core
{
	class IWIComposite;
}


namespace Utils {

class CFile: public Core::CWorkItemImpl {
public:
	CFile();
	CFile(Core::IWIComposite * iParent);
	virtual ~CFile();
	std::string GetName() const;

};

} /* namespace Utils */
#endif /* CFILE_H_ */
