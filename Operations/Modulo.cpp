#include "Modulo.hpp"

Modulo::Modulo(int line) : line(line)
{
}

void Modulo::execute(TypeStack& stack) const
{
	if (stack.size() < 2)
		throw AbstractRuntimeException(std::string("Modulo error: Line ") + std::to_string(line) + ": Stack size less then 2");

	IOperandGenerator	gen;
	const IOperand * tmp, *rht = stack.top();
	stack.pop_back();
	const IOperand * lft = stack.top();
	stack.pop_back();

	try {
		if (lft->getType() > rht->getType())
		{
			tmp = gen.createOperand(lft->getType(), rht->toString());
			stack.push_back(*lft % *tmp);
		}
		else
		{
			tmp = gen.createOperand(rht->getType(), lft->toString());
			stack.push_back(*tmp % *rht);
		}
		delete lft, delete rht, delete tmp;
	}
	catch (AbstractRuntimeException & x) {
		delete lft, delete rht, delete tmp;
		throw AbstractRuntimeException("Modulo error: " + x.what());
	}
}
