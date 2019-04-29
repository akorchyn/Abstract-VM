#ifndef ABSTRACTVM_DUMP_HPP
#define ABSTRACTVM_DUMP_HPP

#include <iostream>
#include <algorithm>
#include "../IOperand.hpp"
#include "../IOperation.hpp"

class Dump : public  IOperation
{
public:
	Dump() = default;
	Dump(const Dump &x) = default;
	Dump &operator=(const Dump &x) = default;
	~Dump() = default;

	void	execute(TypeStack &stack) const override;
};

#endif
