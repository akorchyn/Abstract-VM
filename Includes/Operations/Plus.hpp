#pragma once

#include "../IOperand.hpp"
#include "../AbstractRuntimeException.hpp"
#include "IOperation.hpp"

class Plus : public  IOperation
{
public:
	Plus(int line);
	Plus(const Plus& x) = delete;
	Plus& operator=(const Plus& x) = delete;
	~Plus() = default;

	bool	execute(TypeStack& stack) const override;

private:
	int				line;
};
