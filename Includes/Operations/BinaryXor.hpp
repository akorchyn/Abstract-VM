#pragma once

#include "../IOperand.hpp"
#include "../AbstractRuntimeException.hpp"
#include "IOperation.hpp"

class BinaryXor : public  IOperation
{
public:
	BinaryXor(int line);
	BinaryXor(const BinaryXor& x) = delete;
	BinaryXor& operator=(const BinaryXor& x) = delete;
	~BinaryXor() = default;

	bool	execute(TypeStack& stack) const override;

private:
	int				line;
};
