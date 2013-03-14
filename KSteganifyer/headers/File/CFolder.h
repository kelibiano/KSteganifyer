/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                   *
 *******************************************************************************
 * CFolder.h
 *
 *  Created on: 12.03.2013
 *      Author: yacine.haoues
 ******************************************************************************/

#ifndef CFOLDER_H_
#define CFOLDER_H_

#include "Core/CWICompositeImpl.h"
#include "CFile.h"

namespace NFile {

/**
 * Class to represent a generic folder in file system
 */
class CFolder : public NCore::CWICompositeImpl,
				public CFile
{
public:

	/** class's constructor */
	CFolder();

	/**
	 * Classe's constructor with parent as parameter
	 * @param[in] iParent Parent Composite
	 */
	CFolder(IWIComposite * iParent);

	/** Class's destructor */
	virtual ~CFolder();

	/**
	 * Returns the name of the current item
	 * @return copy of the name (std::string)
	 */
	std::string GetName() const;
	virtual std::string ToString();

};

} /* namespace Utils */
#endif /* CFOLDER_H_ */
