#include "Assert.hpp"

Assert::Assert(std::string x, int line, eOperandType type) : value(std::move(x)), type(type), line(line)
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
