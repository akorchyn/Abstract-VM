#pragma once

#include "../IOperand.hpp"
#include "../AbstractRuntimeException.hpp"
#include "../IOperation.hpp"

class Assert : public  IOperation
{
public:
	Assert(std::string x, int line, eOperandType type);
	Assert(const Assert &x) = delete;
	Assert &operator=(const Assert &x) = delete;
	~Assert() = default;

	bool	execute(TypeStack &stack) const override;

private:
	std::string		value;
	eOperandType	type;
	int				line;
};
