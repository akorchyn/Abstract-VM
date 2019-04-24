#include "IOperandGenerator.hpp"

IOperandGenerator::IOperandGenerator()
{
	func[Int8] = &IOperandGenerator::createInt8;
	func[Int16] = &IOperandGenerator::createInt16;
	func[Int32] = &IOperandGenerator::createInt32;
	func[Float] = &IOperandGenerator::createFloat;
	func[Double] = &IOperandGenerator::createDouble;
}

IOperandGenerator::IOperandGenerator(IOperandGenerator const &x) : func(x.func)
{
}

IOperand const *IOperandGenerator::createInt8(std::string const &) const
{
	return nullptr;
}

IOperand const *IOperandGenerator::createInt16(std::string const &) const
{
	return nullptr;
}

IOperand const *IOperandGenerator::createInt32(std::string const &) const
{
	return nullptr;
}

IOperand const *IOperandGenerator::createFloat(std::string const &) const
{
	return nullptr;
}

IOperand const *IOperandGenerator::createDouble(std::string const &) const
{
	return nullptr;
}

IOperand const *IOperandGenerator::createOperand(eOperandType type, std::string const &value)
{
	return (this->*(func[type]))(value);
}
