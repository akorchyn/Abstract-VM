#include "IOperationsGenerator.hpp"

IOperationsGenerator::IOperationsGenerator()
{
	func[Operations::Pop] = &IOperationsGenerator::createPop;
	func[Operations::Dump] = &IOperationsGenerator::createDump;
	func[Operations::Print] = &IOperationsGenerator::createPrint;
}

IOperationsGenerator::IOperationsGenerator(IOperationsGenerator const &x) : func(x.func)
{
}

IOperation *IOperationsGenerator::createPop(int line) const
{
	return new Pop(line);
}

IOperation *IOperationsGenerator::createDump(int) const
{
	return new Dump();
}

IOperation *IOperationsGenerator::createPrint(int line) const
{
	return new Print(line);
}

IOperation *IOperationsGenerator::creatWithArgument(std::string &value, eOperandType type, int line, Operations funcType)
{
	return (funcType == Operations::Push)
			? static_cast<IOperation  *>(new Push(value, type))
			: static_cast<IOperation  *>(new Assert(value, type, line));
}

IOperation *IOperationsGenerator::createWithoutArgument(int line, Operations funcType) noexcept
{
	return (this->*func[funcType])(line);
}
