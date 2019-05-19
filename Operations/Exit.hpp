#ifndef ABSTRACTVM_EXIT_HPP
#define ABSTRACTVM_EXIT_HPP

#include <iostream>
#include <algorithm>
#include "../IOperand.hpp"
#include "../IOperation.hpp"

class Exit : public IOperation
{
public:
	Exit() = default;
	Exit(const Exit &x) = default;
	Exit &operator=(const Exit &x) = default;
	~Exit() = default;

	bool	execute(TypeStack &stack) const override;
};

#endif
