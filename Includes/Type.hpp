#pragma once

#include "IOperand.hpp"
#include "AbstractRuntimeException.hpp"
#include <limits>
#include <sstream>
#include <string>

template <class T>
class Type : public IOperand
{
public:
	Type(const T &value, eOperandType type);
	Type(const T &value, std::string str, eOperandType type);
	Type(Type const &x);
	Type &operator=(Type const &x);
	~Type();

	eOperandType getType() const noexcept override;
	int			 getPrecision() const noexcept override;

	IOperand const *operator+(IOperand const &rhs) const override;
	IOperand const *operator-(IOperand const &rhs) const override;
	IOperand const *operator/(IOperand const &rhs) const override;
	IOperand const *operator*(IOperand const &rhs) const override;
	IOperand const *operator%(IOperand const &rhs) const override;
	IOperand const *operator|(IOperand const &rhs) const override;
	IOperand const *operator&(IOperand const &rhs) const override;
	IOperand const *operator^(IOperand const &rhs) const override;
	bool 			operator==(IOperand const &rhs) const override;

	std::string	const &toString() const override;

private:
	inline T 	getNumber(std::string const &x) const;

	std::string		str;
	T				value;
	eOperandType	type;

};

/*
 *  CONSTRUCTORS AND DESTRUCTORS
 */

template<class T>
Type<T>::Type(const T &value, eOperandType type) : value(value), type(type)
{
	str = std::to_string(value);
}

template<class T>
Type<T>::Type(const T &value, std::string x, eOperandType type) : str(std::move(x)), value(value), type(type)
{
}

template<class T>
Type<T>::Type(Type const &x) : value(x.value), type(x.type), str(x.str)
{
}

template<class T>
Type<T>::~Type()
{
}

/*
 *  OPERATORS
 */

template<class T>
Type<T> &Type<T>::operator=(Type const &x)
{
	if (&x == this)
		return *this;
	value = x.value;
	type = x.type;
	str = x.str;
	return *this;
}

template<class T>
IOperand const *Type<T>::operator+(const IOperand &rhs) const
{
	T	second = getNumber(rhs.toString());
	
	const T	res = value + second;

	if (second < 0 && value < 0 && res > 0)
		throw AbstractRuntimeException("Underflow on " + toString() +  " + " + rhs.toString());
	else if (second > 0 && value > 0 && res < 0)
		throw AbstractRuntimeException("Overflow on " + toString() +  " + " + rhs.toString());
	return new Type<T>(res, type);
}

template<class T>
IOperand const *Type<T>::operator-(IOperand const &rhs) const
{
	T	second = getNumber(rhs.toString());
	
	const T	res = value - second;

	if (value < 0 && second > 0 && res > 0)
		throw AbstractRuntimeException("Underflow on " + toString() +  " - " + rhs.toString());
	else if (value > 0 && second < 0 && res < 0)
		throw AbstractRuntimeException("Overflow on " + toString() +  " - " + rhs.toString());
	return new Type<T>(res, type);
}

template<class T>
IOperand const *Type<T>::operator/(IOperand const &rhs) const
{
	T	second = getNumber(rhs.toString());
	
	if (second == 0)
		throw AbstractRuntimeException("Division by zero");
	const T	res = value / second;
	return new Type<T>(res, type);
}

template<class T>
IOperand const *Type<T>::operator*(IOperand const &rhs) const
{
	T	second = getNumber(rhs.toString());
	const T	res = value * second;

	if (value != 0 && second != 0 && value != res / second)
		throw AbstractRuntimeException(((value > 0 && second < 0) || (value < 0 && second > 0)
			? "Underflow on "
			: "Overflow on ") + toString() +  " * " + rhs.toString());
	return new Type<T>(res, type);
}

template<class T>
bool 			Type<T>::operator==(IOperand const &rhs) const
{
	return value == getNumber(rhs.toString());
}

template<class T>
IOperand const *Type<T>::operator%(IOperand const &rhs) const
{
	T	second = getNumber(rhs.toString());

	if (second == 0)
		throw AbstractRuntimeException("Module by zero");
	const T	res = value % second;
	return new Type<T>(res, type);
}

template<>
inline IOperand const *Type<float>::operator%(IOperand const &) const
{
	throw AbstractRuntimeException("Module on floating point value");
}

template<>
inline IOperand const *Type<double>::operator%(IOperand const &) const
{
	throw AbstractRuntimeException("Module on floating point value");
}

template<class T>
IOperand const *Type<T>::operator|(const IOperand &rhs) const
{
	T	second = getNumber(rhs.toString());

	return new Type<T>(value | second, type);
}

template<>
inline IOperand const *Type<float>::operator|(const IOperand &) const
{
	throw AbstractRuntimeException("OR on floating point value");
}

template<>
inline IOperand const *Type<double>::operator|(const IOperand &) const
{
	throw AbstractRuntimeException("OR on floating point value");
}

template<class T>
IOperand const *Type<T>::operator&(IOperand const &rhs) const
{
	T	second = getNumber(rhs.toString());

	return new Type<T>(value & second, type);
}

template<>
inline IOperand const *Type<float>::operator&(const IOperand &) const
{
	throw AbstractRuntimeException("AND on floating point value");
}

template<>
inline IOperand const *Type<double>::operator&(const IOperand &) const
{
	throw AbstractRuntimeException("AND on floating point value");
}

template<class T>
IOperand const *Type<T>::operator^(IOperand const &rhs) const
{
	T	second = getNumber(rhs.toString());

	return new Type<T>(value ^ second, type);
}

template<>
inline IOperand const *Type<float>::operator^(const IOperand &) const
{
	throw AbstractRuntimeException("XOR on floating point value");
}

template<>
inline IOperand const *Type<double>::operator^(const IOperand &) const
{
	throw AbstractRuntimeException("XOR on floating point value");
}

/*
 *  GETTERS
 */

template<class T>
eOperandType Type<T>::getType() const noexcept
{
	return type;
}

template<class T>
int Type<T>::getPrecision() const noexcept
{
	return static_cast<int>(type);
}

/*
 *  Get numeric value from string
 */

template<class T>
inline T 	 Type<T>::getNumber(std::string const &x) const
{
	T 					res;
	std::stringstream	toT(x);

	toT >> res;
	return res;
}


/*
** sstream int8_t read as first character on string. So speciliazation for it
*/ 

template<>
inline int8_t 	 Type<int8_t>::getNumber(std::string const &x) const
{
	int 				res;
	std::stringstream	toT(x);

	toT >> res;
	return res;
}

template<class T>
std::string const &Type<T>::toString() const
{
	return str;
}

