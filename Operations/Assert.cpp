#include "Assert.hpp"

Assert::Assert(const std::string &x, int line) : value(x), type(eOperandType::Int8), line(line)
{
}

bool Assert::execute(TypeStack &stack) const
{
	if (stack.empty())
		throw AbstractRuntimeException(std::string("Assert error: Line ") + std::to_string(line) + ". Assert at empty stack");
	if (type != stack.back()->getType() || value != stack.back()->toString())
		throw AbstractRuntimeException(std::string("Assert error: Line " + std::to_string(line) + ". Assert failed"));
	return true;
}
