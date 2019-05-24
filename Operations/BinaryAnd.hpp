#pragma once

#include "../IOperand.hpp"
#include "../AbstractRuntimeException.hpp"
#include "../IOperation.hpp"

class BinaryAnd : public  IOperation
{
public:
	BinaryAnd(int line);
	BinaryAnd(const BinaryAnd& x) = delete;
	BinaryAnd& operator=(const BinaryAnd& x) = delete;
	~BinaryAnd() = default;

	bool	execute(TypeStack& stack) const override;

private:
	int				line;
};
