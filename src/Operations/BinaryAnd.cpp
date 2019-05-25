#include "../../Includes/Operations/BinaryAnd.hpp"

BinaryAnd::BinaryAnd(int line) : line(line)
{
}

bool BinaryAnd::execute(TypeStack& stack) const
{
	if (stack.size() < 2)
		throw AbstractRuntimeException(std::string("BinaryAnd error: Line ") + std::to_string(line) + ": Stack size less then 2");

	IOperandGenerator	gen;
	std::unique_ptr<const IOperand> tmp, rht = std::move(stack.back());
	stack.pop_back();
	std::unique_ptr<const IOperand> lft = std::move(stack.back());
	stack.pop_back();

	try {
		if (lft->getType() > rht->getType())
		{
			tmp.reset(gen.createOperand(lft->getType(), rht->toString()));
			stack.emplace_back(*lft & *tmp);
		}
		else
		{
			tmp.reset(gen.createOperand(rht->getType(), lft->toString()));
			stack.emplace_back(*tmp & *rht);
		}
	}
	catch (AbstractRuntimeException & x) {
		throw AbstractRuntimeException(std::string("BinaryAnd error: Line ") + std::to_string(line) + ": "  + x.what());
	}
	return true;
}
