#pragma once

/*!
 * \file
 * \brief The file contains interface of types and their priority.
 */

#include <string>
#include <limits>
#include <memory>
#include <list>

/*!
 * \brief eOperandType shows priority of types.
 * This enum display the types with which VM works.
 * The type with the highest priority is at the end of the enum.
 */
enum class eOperandType
{
	Int8, ///< Type will be int8_t
	Int16, ///< Type will be int16_t
	Int32, ///< Type will be int32_t
	Float, ///< Type will be float
	Double ///< Type will be double
};

/*!
 * \brief Type interface.
 */

class IOperand
{
public:
	virtual ~IOperand() = default;

	virtual int					getPrecision() const noexcept = 0;
	virtual eOperandType		getType() const noexcept = 0;
	virtual std::string const	&toString() const = 0;

	virtual IOperand const *operator+(IOperand const &rhs) const = 0;
	virtual IOperand const *operator-(IOperand const &rhs) const = 0;
	virtual IOperand const *operator*(IOperand const &rhs) const = 0;
	virtual IOperand const *operator/(IOperand const &rhs) const = 0;
	virtual IOperand const *operator%(IOperand const &rhs) const = 0;
	virtual IOperand const *operator|(IOperand const &rhs) const = 0;
	virtual IOperand const *operator&(IOperand const &rhs) const = 0;
	virtual IOperand const *operator^(IOperand const &rhs) const = 0;
	virtual bool  		    operator==(IOperand const &rhs) const = 0;
};

using TypeStack = std::list<std::unique_ptr<const IOperand>>; //!< This type represents stack of IOperand *.

