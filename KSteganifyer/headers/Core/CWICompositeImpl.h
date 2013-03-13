/* DISTRIBUTED UNDER GNU PUBLIC LICENCE 2013                                   *
 *******************************************************************************
 * CFolder.h
 *
 *  Created on: Mar 10, 2013
 *      Author: Kelibiano
 ******************************************************************************/

#ifndef CWICOMPOSITEIMPL_H_
#define CWICOMPOSITEIMPL_H_

#include "IWIComposite.h"
#include "CWorkItemImpl.h"
#include <vector>

namespace NCore
{
class IWorkItem;

/**
 * Implementation class for the generic IWIComposite item. This class inherits
 * from CWorkItemImpl to deliver an implementation for the IWorkItem. implements
 * The common useful methods for a composite.
 */
class CWICompositeImpl: public CWorkItemImpl,
						public IWIComposite

{
public:

	/** Class's constructor */
	CWICompositeImpl();

	/**
	 * Classe's constructor with parent as parameter
	 * @param[in] iParent Parent Composite
	 */
	CWICompositeImpl(IWIComposite * iParent);

	/** Class's destructor */
	virtual ~CWICompositeImpl();

	/**
	 * Checks if the current composite item is the root one in the structure
	 * @return bool (is root)
	 */
	virtual bool IsRoot() const;

	/**
	 * Checks if the current item has children or not
	 * @return bool (Has Children)
	 */
	virtual bool HasChildren() const;

	/**
	 * Adds a child to the current composite at the end of the list of children
	 * @param[in] iChild (IWorkItem *)
	 */
	virtual void AddChild(IWorkItem * iChild);

	/**
	 * Returns the parent of the current item or NULL if it has no parent
	 * @return pointer to IWorkItem
	 */
	virtual IWorkItem * GetParent() const;

	/**
	 * Removes the child with the given index from the list of the children
	 * @param[in] iIndex (index of the child to remove)
	 * @return IWorkItem * (pointer to the removed item)
	 *
	 * @note : The item is just removed from the children list without memory
	 * management (The removed item is not deleted from memory)
	 */
	virtual IWorkItem * DeleteChild(const int iIndex);

	/**
	 * Retrieves the child with the given index.
	 * @param[in] iIndex (child index)
	 * @return IWorkItem * (pointer to the child)
	 */
	virtual IWorkItem * GetChild(const int iIndex) const;

private:
	/**
	 * Checks if the current item is a compound (In this case it returns always
	 * true). This method overrides the pure virtual one in the IWorkItem
	 * @return bool (is root)
	 */
	virtual bool IsCompound() const;

private:
	std::vector<IWorkItem*> mItems;
	IWIComposite * mpParent;
};

} /* namespace Core */

#endif /* CWICOMPOSITEIMPL_H_ */
