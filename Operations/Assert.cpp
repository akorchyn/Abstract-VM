#include "Assert.hpp"

Assert::Assert(strOpPair x, int line) : value(x.first), type(x.second), line(line)
{
}

void Assert::execute(TypeStack &stack) const
{
	if (stack.empty())
		throw AbstractRuntimeException(std::string("Line ") + std::to_string(line) + ". Assert at empty stack");
	if (type != (*stack.back()).getType() || value != (*stack.back()).toString())
		throw AbstractRuntimeException(std::string("Line " + std::to_string(line) + ". Assert failed"));
}
