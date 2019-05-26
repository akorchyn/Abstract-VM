#pragma once

/*!
 * \file
 * \brief Header file with class that construct Type.
 *
 * This class constructs Type with template that depends of eOperandType.
 */

#include <map>
#include "Type.hpp"
#include <sstream>

/*!
 * \brief Class that create Type
 *
 * This class generate type depending of eOperandType.
 * This class uses factory method.
 */

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
	///< creationFunction is function that create Type and used in factory pattern.

	IOperand const *createInt8(std::string const &value) const;
	IOperand const *createInt16(std::string const &value) const;
	IOperand const *createInt32(std::string const &value) const;
	IOperand const *createFloat(std::string const &value) const;
	IOperand const *createDouble(std::string const &value) const;

	std::map<eOperandType, creationFunction>	func; ///< Return function depending of eOperandType.
};
