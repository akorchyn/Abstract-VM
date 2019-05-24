#include "Assert.hpp"

Assert::Assert(std::string x, int line, eOperandType type) : value(std::move(x)), type(type), line(line)
{
}

bool Assert::execute(TypeStack &stack) const
{
	if (stack.empty())
		throw AbstractRuntimeException(std::string("Assert error: Line ") + std::to_string(line) + ": Assert at empty stack");
	IOperandGenerator				gen;
	std::unique_ptr<const IOperand>	rht(gen.createOperand(type, value));

	if (type != stack.back()->getType() || !(*rht == *stack.back()))
		throw AbstractRuntimeException(std::string("Assert error: Line " + std::to_string(line) + ": Assert failed"));
	return true;
}
