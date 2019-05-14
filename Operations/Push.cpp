#include "Push.hpp"

Push::Push(std::string const &x) : value(x), type(eOperandType::Int8)
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
