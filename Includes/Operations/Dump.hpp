#pragma once

#include <iostream>
#include <algorithm>
#include "../IOperand.hpp"
#include "IOperation.hpp"

class Dump : public IOperation
{
public:
	Dump(int line);
	Dump(const Dump &x) = default;
	Dump &operator=(const Dump &x) = default;
	~Dump() = default;

	static const char *types[5];

	bool	execute(TypeStack &stack) const override;
};

