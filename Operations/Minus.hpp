#ifndef ABSTRACTVM_MINUS_HPP
#define ABSTRACTVM_MINUS_HPP

#include "../IOperand.hpp"
#include "../AbstractRuntimeException.hpp"
#include "../IOperation.hpp"

class Minus : public  IOperation
{
public:
	Minus(int line);
	Minus(const Minus& x) = delete;
	Minus& operator=(const Minus& x) = delete;
	~Minus() = default;

	void	execute(TypeStack& stack) const override;

private:
	int				line;
};

#endif