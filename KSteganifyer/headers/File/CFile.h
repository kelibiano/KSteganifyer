/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                   *
 *******************************************************************************
 * CFile.h
 *
 *  Created on: 12.03.2013
 *      Author: yacine.haoues
 ******************************************************************************/

#ifndef CFILE_H_
#define CFILE_H_

#include "Core/CWorkItemImpl.h"
#include <string>


namespace NCore
{
	class IWIComposite;
}


namespace NFile {

/**
 * Class to represent a generic file in the file system.
 */
class CFile: public NCore::CWorkItemImpl {
public:
	/** Classe's constructor */
	CFile();

	/**
	 * Classe's constructor with parent as parameter
	 * @param[in] iParent Parent Composite
	 */
	CFile(NCore::IWIComposite * iParent);

	/** Destructor */
	virtual ~CFile();

	/**
	 * Returns the name of the current item
	 * @return copy of the name (std::string)
	 */
	std::string GetName() const;

};

} /* namespace Utils */
#endif /* CFILE_H_ */
