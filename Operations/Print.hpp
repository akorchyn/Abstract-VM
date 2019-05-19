#ifndef ABSTRACTVM_PRINT_HPP
#define ABSTRACTVM_PRINT_HPP

#include "../IOperand.hpp"
#include "../AbstractRuntimeException.hpp"
#include "../IOperation.hpp"
#include <sstream>
#include <iostream>

class Print : public  IOperation
{
public:
	Print(int line);
	Print(const Print &x) = default;
	Print &operator=(const Print &x) = default;
	~Print() = default;

	bool	execute(TypeStack &stack) const override;

private:
	int 	line;
};

#endif
