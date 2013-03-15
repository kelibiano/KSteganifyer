/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                  **
********************************************************************************
** CFolderScanner.cpp
**
**  Created on: 13.03.2013
**      Author: yacine.haoues
*******************************************************************************/

#include "File/CFolderScanner.h"
#include "File/CFolder.h"
#include "Config.h"
#include <dirent.h>
#include <stack>
using namespace NFile;

/******************************************************************************/
/* CFolderScanner::CFolderScanner()                                           */
/******************************************************************************/
CFolderScanner::CFolderScanner():
	mPath("")
{
}

/******************************************************************************/
/* CFolderScanner::CFolderScanner(const std::string& iPath)                   */
/******************************************************************************/
CFolderScanner::CFolderScanner(const std::string& iPath):
		mPath(iPath)
{
}

/******************************************************************************/
/* CFolderScanner::~CFolderScanner()                                          */
/******************************************************************************/
CFolderScanner::~CFolderScanner()
{

}

/******************************************************************************/
/* CCFolder* CFolderScanner::Scan(EScanDepth iDepth) const                    */
/******************************************************************************/
CFolder* CFolderScanner::Scan(EScanDepth iDepth) const
{
	return Scan(mPath, iDepth);
}

/******************************************************************************/
/* CFolder* CFolderScanner::Update(CFolder* iOldFolder)                       */
/******************************************************************************/
CFolder* CFolderScanner::Scan(const std::string& iPath, EScanDepth iDepth) const
{
	//TODO : Change items creation to be done by a factory that creates files
	// instances depending on their types.

	/// Initialization
	DIR *pDirectory = NULL;
	struct dirent *pInfos = NULL;
	NFile::CFolder * pRoot = NULL;
	NFile::CFolder * pCurrentContainer = NULL;
	std::stack<std::string> pathStack;
	pathStack.push(iPath);

	/// Till no more paths to treat in the stack
	while (!pathStack.empty()) {
		// get top item and remove
		std::string tPath = pathStack.top();
		pathStack.pop();
		// Check current path otherwise continue
		pDirectory = opendir(tPath.c_str());
		if (!pDirectory)
		{
			pathStack.pop();
			continue;
		}

		// ifSuccessful create folder container
		if(pCurrentContainer)
		{
			// append the folder to the parent
			pCurrentContainer = new CFolder(pCurrentContainer);
		}
		else
		{
			// It is the root one
			pCurrentContainer = new NFile::CFolder();
			pRoot = pCurrentContainer;
		}
		// Set the folder name
		pCurrentContainer->SetName(tPath);

		// Iterating over child items in the currently open folder.
		while ((pInfos = readdir(pDirectory)))
		{
			// create the file name and the and the relative path to the root
			// item
			std::string file(pInfos->d_name);
			std::string absFilePath = tPath + FILE_CONST_PATH_SEP + file;

			// Check the current item if it is not "." or ".."
			if (file != FILE_CONST_CURR_DIR &&
				file != FILE_CONST_UPER_DIR)
			{
				// check if the item is a directory (it will be opened otherwise
				// not successful
				DIR * pcDir = opendir(absFilePath.c_str());
				if(pcDir)
				{
					// close the opened one
					closedir(pcDir);
					delete pcDir;
					pcDir = NULL;

					// if the scan depth is set to "Recursive" then push the
					// path to be treated later.
					if(iDepth == Recursive)
						pathStack.push(absFilePath);
				}
				else
				{
					// the item is a File, Create the file and set the path
					NFile::CFile * pFile = new NFile::CFile(pCurrentContainer);
					pFile->SetName(absFilePath);
				}
			}
		}

		// Close the current dir and do some cleaning
		closedir(pDirectory);
		delete pDirectory;
		pDirectory = NULL;
	}

	// Return the root as a container
	return pRoot;
}

/******************************************************************************/
/* CFolder* CFolderScanner::Update(CFolder* iOldFolder)                       */
/******************************************************************************/
CFolder* CFolderScanner::Update(CFolder* iOldFolder)
{
	return iOldFolder;
}

/******************************************************************************/
/* void CFolderScanner::SetScanPath(std::string& iPath)                       */
/******************************************************************************/
void CFolderScanner::SetScanPath(std::string& iPath)
{
	mPath = iPath;
}

/******************************************************************************/
/* std::string CFolderScanner::ToString()                                     */
/******************************************************************************/
std::string CFolderScanner::ToString()
{
	return "NFile::CFolderScanner";
}
