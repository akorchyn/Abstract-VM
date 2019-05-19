#ifndef ABSTRACTVM_IOPERATION_HPP
#define ABSTRACTVM_IOPERATION_HPP

#include <vector>
#include <memory>
#include "IOperandGenerator.hpp"

enum class Operations
{
	Push,
	Pop,
	Dump,
	Assert,
	Add,
	Sub,
	Mul,
	Div,
	Mod,
	Print,
	Exit
};

class IOperation
{
public:
	virtual ~IOperation() = default;
	virtual void execute(TypeStack &) const = 0;
};

#endif
