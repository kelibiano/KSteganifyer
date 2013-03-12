/*
 * CFile.cpp
 *
 *  Created on: 12.03.2013
 *      Author: yacine.haoues
 */

#include "CFile.h"
#include "IWIComposite.h"

using namespace Utils ;

CFile::CFile()
{

}

CFile::CFile(Core::IWIComposite * iParent):
		CWorkItemImpl(iParent)
{
}

CFile::~CFile()
{
}

std::string CFile::GetName() const
{
	return "File";
}

