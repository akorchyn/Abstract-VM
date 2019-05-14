#ifndef ABSTRACTVM_PUSH_HPP
#define ABSTRACTVM_PUSH_HPP

#include "../IOperation.hpp"
#include "../IOperand.hpp"
#include "../IOperandGenerator.hpp"

class Push : public IOperation
{
public:
	Push(std::string const & );
	Push(const Push &x) = delete;
	Push &operator=(const Push &x) = delete;
	~Push();

	void	execute(TypeStack &stack) const override;

private:
	std::string		value;
	eOperandType	type;
};


#endif
