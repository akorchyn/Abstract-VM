#ifndef ABSTRACTVM_DIVISION_HPP
#define ABSTRACTVM_DIVISION_HPP

#include "../IOperand.hpp"
#include "../AbstractRuntimeException.hpp"
#include "../IOperation.hpp"

class Division : public  IOperation
{
public:
	Division(int line);
	Division(const Division& x) = delete;
	Division& operator=(const Division& x) = delete;
	~Division() = default;

	bool	execute(TypeStack& stack) const override;

private:
	int				line;
};

#endif
