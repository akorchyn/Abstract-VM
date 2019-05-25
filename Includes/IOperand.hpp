#pragma once

#include <string>
#include <limits>
#include <memory>
#include <list>

enum class eOperandType
{
	Int8,
	Int16,
	Int32,
	Float,
	Double
};

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

using TypeStack = std::list<std::unique_ptr<const IOperand>>;

