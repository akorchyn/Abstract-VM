#include "../../Includes/IOperandGenerator.hpp"
#include <iostream>

IOperandGenerator::IOperandGenerator()
{
	func[eOperandType::Int8] = &IOperandGenerator::createInt8;
	func[eOperandType::Int16] = &IOperandGenerator::createInt16;
	func[eOperandType::Int32] = &IOperandGenerator::createInt32;
	func[eOperandType::Float] = &IOperandGenerator::createFloat;
	func[eOperandType::Double] = &IOperandGenerator::createDouble;
}

IOperandGenerator::IOperandGenerator(IOperandGenerator const &x) : func(x.func)
{
}

IOperand const *IOperandGenerator::createInt8(std::string const &num) const
{
	int					tmp;
	std::istringstream	converter(num);

	converter >> tmp;
	return new Type<int8_t>(static_cast<int8_t>(tmp), num, eOperandType::Int8);
}

IOperand const *IOperandGenerator::createInt16(std::string const &num) const
{
	int16_t				tmp;
	std::istringstream	converter(num);

	converter >> tmp;
	return new Type<int16_t>(tmp, num, eOperandType::Int16);
}

IOperand const *IOperandGenerator::createInt32(std::string const &num) const
{
	int32_t				tmp;
	std::istringstream	converter(num);

	converter >> tmp;
	return new Type<int32_t>(tmp, num, eOperandType::Int32);
}

IOperand const *IOperandGenerator::createFloat(std::string const &num) const
{
	float				tmp;
	std::istringstream	converter(num);

	converter >> tmp;
	return new Type<float>(tmp, num, eOperandType::Float);
}

IOperand const *IOperandGenerator::createDouble(std::string const &num) const
{
	double				tmp;
	std::istringstream	converter(num);

	converter >> tmp;
	return new Type<double>(tmp, num, eOperandType::Double);
}

IOperand const *IOperandGenerator::createOperand(eOperandType type, std::string const &value)
{
	return (this->*(func[type]))(value);
}