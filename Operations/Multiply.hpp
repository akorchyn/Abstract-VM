#ifndef ABSTRACTVM_MULTIPLY_HPP
#define ABSTRACTVM_MULTIPLY_HPP

#include "../IOperand.hpp"
#include "../AbstractRuntimeException.hpp"
#include "../IOperation.hpp"

class Multiply : public  IOperation
{
public:
	Multiply(int line);
	Multiply(const Multiply& x) = delete;
	Multiply& operator=(const Multiply& x) = delete;
	~Multiply() = default;

	void	execute(TypeStack& stack) const override;

private:
	int				line;
};

#endif
