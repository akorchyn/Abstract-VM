#ifndef ABSTRACTVM_IOPERATIONSGENERATOR_HPP
#define ABSTRACTVM_IOPERATIONSGENERATOR_HPP

#include "IOperation.hpp"
#include <map>
#include "Operations/Assert.hpp"
#include "Operations/Dump.hpp"
#include "Operations/Pop.hpp"
#include "Operations/Push.hpp"
#include "Operations/Print.hpp"

class IOperationsGenerator
{
public:
	IOperationsGenerator();
	IOperationsGenerator(IOperationsGenerator const &x);
	IOperationsGenerator &operator=(IOperationsGenerator const &x) = default;
	~IOperationsGenerator() = default;

	IOperation *createWithoutArgument(int line, Operations funcType) noexcept;
	IOperation *creatWithArgument(std::string &value, eOperandType type, int line, Operations funcType);

private:
	using FunctionWithoutArgs = IOperation *(IOperationsGenerator::*)(int line) const;

	IOperation	*createPop(int line) const;
	IOperation	*createDump(int line) const;
	IOperation	*createPrint(int line) const;

	IOperation	*createPush(std::string &value, eOperandType type, int line, Operations funcType) const;
	IOperation	*createAssert(std::string &value, eOperandType type, int line, Operations funcType) const;

	std::map<Operations, FunctionWithoutArgs>	func;
};


#endif
