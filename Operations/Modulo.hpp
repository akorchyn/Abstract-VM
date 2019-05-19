#ifndef ABSTRACTVM_MODULO_HPP
#define ABSTRACTVM_MODULO_HPP

#include "../IOperand.hpp"
#include "../AbstractRuntimeException.hpp"
#include "../IOperation.hpp"

class Modulo : public  IOperation
{
public:
	Modulo(int line);
	Modulo(const Modulo& x) = delete;
	Modulo& operator=(const Modulo& x) = delete;
	~Modulo() = default;

	bool	execute(TypeStack& stack) const override;

private:
	int				line;
};

#endif
