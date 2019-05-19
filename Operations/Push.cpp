#include "Push.hpp"

#include <iostream>
Push::Push(std::string const & x) : value(x), type(eOperandType::Int8)
{
	std::cout << x << std::endl;
}

void Push::execute(TypeStack &stack) const
{
	IOperandGenerator generator;
	stack.emplace_back(generator.createOperand(type, value));
}

Push::~Push()
{
}
