#ifndef ABSTRACTVM_IOPERATION_HPP
#define ABSTRACTVM_IOPERATION_HPP

#include <vector>
#include <memory>
#include "IOperandGenerator.hpp"

class IOperation
{
public:
	virtual ~IOperation() = default;
	virtual bool execute(TypeStack &) const = 0;
};

#endif
