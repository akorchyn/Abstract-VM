#pragma once

#include "../IOperand.hpp"
#include "../AbstractRuntimeException.hpp"
#include "IOperation.hpp"

class BinaryOr : public  IOperation
{
public:
	BinaryOr(int line);
	BinaryOr(const BinaryOr& x) = delete;
	BinaryOr& operator=(const BinaryOr& x) = delete;
	~BinaryOr() = default;

	bool	execute(TypeStack& stack) const override;

private:
	int				line;
};

