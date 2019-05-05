#include "Push.hpp"

Push::Push(strOpPair x) : value(x.first), type(x.second)
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
