/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                   *
 *******************************************************************************
 * main.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 ******************************************************************************/

#include "Core/IWorkItem.h"
#include "Core/IWIComposite.h"
#include "Core/IWIIterator.h"
#include "File/CFolder.h"
#include "File/CFolderScanner.h"
#include <dirent.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/******************************************************************************/
/* int main(int argc, char ** argv)                                           */
/******************************************************************************/
int main(int argc, char ** argv)
{
	NFile::CFolderScanner * pScanner = new NFile::CFolderScanner(".");
	NCore::IWIComposite * pComposite = pScanner->Scan(NFile::Recursive);
	NCore::IWIIterator * pIterator = new NCore::IWIIterator(pComposite);
	for (; !pIterator->End(); pIterator->Next())
	{
		NCore::IWorkItem * pItem = pIterator->Current();
		std::cout << pItem->ToString() << std::endl;
	}
	delete pIterator;
	delete pComposite;
	return 0;
}

