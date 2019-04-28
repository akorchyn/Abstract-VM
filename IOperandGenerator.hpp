#ifndef ABSTRACTVM_IOPERANDGENERATOR_HPP
#define ABSTRACTVM_IOPERANDGENERATOR_HPP

#include <map>
#include "Type.hpp"
#include <sstream>

class IOperandGenerator
{
public:
	IOperandGenerator();
	IOperandGenerator(IOperandGenerator const &x);
	IOperandGenerator &operator=(IOperandGenerator const &x) = default;
	~IOperandGenerator() = default;

	IOperand const *createOperand(eOperandType type, std::string const &value);

private:
	using creationFunction = const IOperand *(IOperandGenerator::*)(const std::string &) const;
	// Function that create different types

	IOperand const *createInt8(std::string const &value) const;
	IOperand const *createInt16(std::string const &value) const;
	IOperand const *createInt32(std::string const &value) const;
	IOperand const *createFloat(std::string const &value) const;
	IOperand const *createDouble(std::string const &value) const;

	std::map<eOperandType, creationFunction>	func;
};


#endif
