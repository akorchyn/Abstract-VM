#include "Push.hpp"

Push::Push(std::string x, eOperandType type) : value(std::move(x)), type(type)
{
}

bool Push::execute(TypeStack &stack) const
{
	IOperandGenerator generator;
	stack.emplace_back(generator.createOperand(type, value));
	return true;
}

Push::~Push()
{
}
