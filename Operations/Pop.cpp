#include "Pop.hpp"

Pop::Pop(int line) : line(line)
{
}

bool Pop::execute(TypeStack &stack) const
{
	if (stack.empty())
		throw AbstractRuntimeException(std::string("Pop error: Line ") + std::to_string(line) + ". Pop at empty stack");
	stack.pop_back();
	return true;
}
