/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                  **
********************************************************************************
** CFolderScanner.cpp
**
**  Created on: 13.03.2013
**      Author: yacine.haoues
*******************************************************************************/

#include "File/CFolderScanner.h"
#include "File/CFolder.h"
#include <dirent.h>
#include <stack>
#include <iostream>
using namespace NFile;

CFolderScanner::CFolderScanner():
	mPath("")
{
}

CFolderScanner::CFolderScanner(const std::string& iPath):
		mPath(iPath)
{
}

CFolderScanner::~CFolderScanner()
{

}

CFolder* CFolderScanner::Scan(EScanDepth iDepth) const
{
	return Scan(mPath, iDepth);
}

CFolder* CFolderScanner::Scan(const std::string& iPath, EScanDepth iDepth) const
{
	DIR *pdir;
	struct dirent *pent;
	std::stack<std::string> stck;
	stck.push(iPath);

	while (!stck.empty()) {
		std::string tPath = stck.top();
		stck.pop();
		pdir = opendir(tPath.c_str()); //"." refers to the current dir
		if (!pdir) {
			std::cout << "opendir() failure; terminating" << std::endl;
			return NULL;
		}
		errno = 0;
		while ((pent = readdir(pdir))) {
			std::string file(pent->d_name);
			DIR * pcDir = opendir(file.c_str());
			if (file != "." && file != ".." && pcDir) {
				closedir(pcDir);
				stck.push(tPath + "/" + file);
				std::cout << " [D] ";
			} else
				std::cout << "[F] ";

			std::cout << tPath + "/" + file << std::endl;
		}
		closedir(pdir);
	}
	return new CFolder;
}

CFolder* CFolderScanner::Update(CFolder* iOldFolder)
{
	return iOldFolder;
}

void CFolderScanner::SetScanPath(std::string& iPath)
{
	mPath = iPath;
}
