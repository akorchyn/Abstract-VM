#include "Pop.hpp"

Pop::Pop(int line) : line(line)
{
}

void Pop::execute(TypeStack &stack) const
{
	if (stack.empty())
		throw AbstractRuntimeException(std::string("Line ") + std::to_string(line) + ". Pop at empty stack");
	stack.pop_back();
}