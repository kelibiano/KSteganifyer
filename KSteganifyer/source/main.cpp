/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                   *
 *******************************************************************************
 * main.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 ******************************************************************************/

#include "IWorkItem.h"
#include "IWIComposite.h"
#include "CFolder.h"
#include "CFile.h"
#include "IWIIterator.h"

#include <iostream>

/******************************************************************************/
/* int main(int argc, char ** argv)                                           */
/******************************************************************************/
int main(int argc, char ** argv)
{
	Core::IWIComposite * pComposite = new Utils::CFolder();
	Core::IWorkItem * pFile1 = new Utils::CFile(pComposite);
	Core::IWorkItem * pFile2 = new Utils::CFile(pComposite);
	Core::IWIIterator * pIterator = new Core::IWIIterator(pComposite);
	for (; !pIterator->End(); pIterator->Next())
	{
		Core::IWorkItem * pWorkItem = pIterator->Current();
		int level = pIterator->GetLevel();
		for (int i = 0; i < level; i++)
			std::cout << " ";
		std::cout << pWorkItem->GetName() << std::endl;
	}
	delete
	delete pComposite;
	delete pFile1;
	delete pFile2;
	return 0;
}

