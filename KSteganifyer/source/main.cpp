/*
 * main.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 */

#include "IWorkItem.h"
#include "IWIComposite.h"
#include "CFolder.h"
#include "IWIIterator.h"

int main(int argc, char ** argv)
{
	Core::IWIComposite * pComposite = new Utils::CFolder();
	return 0;
}

