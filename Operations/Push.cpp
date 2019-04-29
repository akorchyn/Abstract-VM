#include "Push.hpp"

Push::Push(const std::string &value, eOperandType type) : value(value), type(type)
{
}

void Push::execute(TypeStack &stack) const
{
	IOperandGenerator		generator;
	std::unique_ptr<const IOperand> ptr(generator.createOperand(type, value));

	stack.push_back(std::move(ptr));
}

Push::~Push()
{
}
