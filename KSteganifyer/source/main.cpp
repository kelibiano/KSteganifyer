/*
 * main.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 */

#include "IWorkItem.h"
#include "IWIComposite.h"
#include "CWICompositeImpl.h"
#include "IWIIterator.h"

int main(int argc, char ** argv)
{
	Core::IWIComposite * pComposite = new Core::CWICompositeImpl();
	return 0;
}

