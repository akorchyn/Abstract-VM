#pragma once

#include "../IOperand.hpp"
#include "../AbstractRuntimeException.hpp"
#include "IOperation.hpp"

class Multiply : public  IOperation
{
public:
	Multiply(int line);
	Multiply(const Multiply& x) = delete;
	Multiply& operator=(const Multiply& x) = delete;
	~Multiply() = default;

	bool	execute(TypeStack& stack) const override;

private:
	int				line;
};

