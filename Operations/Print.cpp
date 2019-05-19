#include "Print.hpp"

Print::Print(int line) : line(line)
{
}

bool Print::execute(TypeStack &stack) const
{
	std::stringstream	translate;
	int 				ch;

	if (stack.empty())
		throw AbstractRuntimeException(std::string("Print error: Line ") + std::to_string(line) + ". Print on empty stack");
	if (stack.back()->getType() != eOperandType::Int8)
		throw AbstractRuntimeException(std::string("Print error: Line ") + std::to_string(line) + ". Stack top is not a Int8");
	translate << stack.back()->toString();
	translate >> ch;
	std::cout << static_cast<char>(ch);
	return true;
}
