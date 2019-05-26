#pragma once

#include <vector>
#include <memory>
#include "../IOperandGenerator.hpp"

/*!
 * \file
 * \brief file contain definition of Operations interface.
 */

/*!
 * This class is interface of operations.
 */

class IOperation
{
public:
	virtual ~IOperation() = default;

	/*!
	 * @param stack contains Type with different templates, as IOperand
	 * @return true, if it is not a exit.
	 * \throw AbstractRuntimeError if command failed.
	 * \todo More elegant way to stop operations if exit is executed.
	 * \warning I don't comment classes that inherit from it, because they are small and don't changes too much.
	 */
	virtual bool execute(TypeStack &stack) const = 0;
};
