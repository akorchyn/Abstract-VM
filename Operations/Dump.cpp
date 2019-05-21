#include "Dump.hpp"

Dump::Dump(int)
{}

bool Dump::execute(TypeStack &stack) const
{
	std::cout << "Start Stack Dump" << std::endl;
	if (stack.empty())
		std::cout << "Empty stack" << std::endl;
	else
		std::for_each(stack.begin(), stack.end(), [](const std::unique_ptr<const IOperand> &x){
			std::cout << x->toString() << std::endl;
		});
	std::cout << "End Stack Dump" << std::endl;
	return true;
}
