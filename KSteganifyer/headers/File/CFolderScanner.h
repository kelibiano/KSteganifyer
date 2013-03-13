/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                   *
********************************************************************************
** CFolderScanner.h
**
**  Created on: 13.03.2013
**      Author: yacine.haoues
*******************************************************************************/

#ifndef CFOLDERSCANNER_H_
#define CFOLDERSCANNER_H_

#include "Core/IItem.h"
#include <string>

namespace NFile
{

class CFolder;
enum EScanDepth
{
	Recursive = 0,
	FirstLevel
};
class CFolderScanner : public NCore::IItem
{
public:
	CFolderScanner();
	CFolderScanner(const std::string & iPath);
	virtual ~CFolderScanner();
	CFolder * Scan(EScanDepth iDepth = Recursive) const;
	CFolder * Scan(const std::string & iPath, EScanDepth iDepth = Recursive) const;
	CFolder * Update(CFolder * iOldFolder);
	void SetScanPath(std::string & iPath);
protected:
private :
	std::string mPath;
};

} /* namespace NFile */
#endif /* CFOLDERSCANNER_H_ */
