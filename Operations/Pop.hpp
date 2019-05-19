#ifndef ABSTRACTVM_POP_HPP
#define ABSTRACTVM_POP_HPP

#include "../IOperand.hpp"
#include "../AbstractRuntimeException.hpp"
#include "../IOperation.hpp"

class Pop : public  IOperation
{
public:
	Pop(int line);
	Pop(const Pop &x) = default;
	Pop &operator=(const Pop &x) = default;
	~Pop() = default;

	bool	execute(TypeStack &stack) const override;

private:
	int 	line;
};


#endif
