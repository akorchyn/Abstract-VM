#pragma once

#include <iostream>
#include <algorithm>
#include "../IOperand.hpp"
#include "../IOperation.hpp"

class Exit : public IOperation
{
public:
	Exit(int line);
	Exit(const Exit &x) = default;
	Exit &operator=(const Exit &x) = default;
	~Exit() = default;

	bool	execute(TypeStack &stack) const override;
};

