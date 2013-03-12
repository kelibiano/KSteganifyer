/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                   *
 *******************************************************************************
 * CFolder.cpp
 *
 *  Created on: 12.03.2013
 *      Author: yacine.haoues
 ******************************************************************************/

#include "CFolder.h"

using namespace Utils;

/******************************************************************************/
/* CFolder::CFolder()                                                         */
/******************************************************************************/
CFolder::CFolder()
{

}

/******************************************************************************/
/* CFolder::~CFolder()                                                        */
/******************************************************************************/
CFolder::~CFolder()
{
}

/******************************************************************************/
/* Utils::CFolder::CFolder(IWIComposite* iParent)                             */
/******************************************************************************/
Utils::CFolder::CFolder(IWIComposite* iParent):
		CWICompositeImpl(iParent)
{
}

/******************************************************************************/
/* std::string CFolder::GetName() const                                       */
/******************************************************************************/
std::string CFolder::GetName() const
{
	return "Folder";
}
