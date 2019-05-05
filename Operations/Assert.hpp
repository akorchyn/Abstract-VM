#ifndef ABSTRACTVM_ASSERT_HPP
#define ABSTRACTVM_ASSERT_HPP

#include "../IOperand.hpp"
#include "../AbstractRuntimeException.hpp"
#include "../IOperation.hpp"

class Assert : public  IOperation
{
public:
	Assert(strOpPair x, int line);
	Assert(const Assert &x) = delete;
	Assert &operator=(const Assert &x) = delete;
	~Assert() = default;

	void	execute(TypeStack &stack) const override;

private:
	std::string		value;
	eOperandType	type;
	int				line;
};

#endif
