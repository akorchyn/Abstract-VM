#include <iomanip>
#include "../../Includes/Operations/Dump.hpp"

const char *Dump::types[5] = {"Int8", "Int16", "Int32", "Float", "Double"};

Dump::Dump(int)
{}

bool Dump::execute(TypeStack &stack) const
{
	std::cout << "Start Stack Dump" << std::endl;
	std::cout << std::left;
	if (stack.empty())
		std::cout << "Empty stack" << std::endl;
	else
		std::for_each(stack.begin(), stack.end(), [](const std::unique_ptr<const IOperand> &x)
		{
			std::cout << std::setw(7) << types[x->getPrecision()] << " " << x->toString() << std::endl;
		});
	std::cout << "End Stack Dump" << std::endl;
	return true;
}
