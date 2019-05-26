#pragma once

/**
 * \file
 * \brief File contains template class.
 *
 * Main class. This class is used in all IOperation.
 */

#include "IOperand.hpp"
#include "AbstractRuntimeException.hpp"
#include <limits>
#include <sstream>
#include <string>

/**
 * \brief The class with which the IOperation work. The TypeStack contains this.
 * @tparam T is a standard c++ type. (char, short, int, float, double)
 *
 * @warning This class has specialization for operators(%, |, &, ^) in float, double -> throw exception.
 */

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

/*!
 * @param value is number that represent of type.
 */

template<class T>
Type<T>::Type(const T &value, eOperandType type) : value(value), type(type)
{
	str = std::to_string(value);
}

/*!
 * @param value is number that represent of type.
 * @param x is string representation of value
 *
 * IOperandGenerator uses this constructor
 */

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

/*!
 * \throw AbstractRuntimeException if type template is double or float
 */

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

/*!
 * \throw AbstractRuntimeException if type template is double or float
 */

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

/*!
 * \throw AbstractRuntimeException if type template is double or float
 */

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

/*!
 * \throw AbstractRuntimeException if type template is double or float
 */

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

/*!
 * @return int representation of private field type(eOperandType)
 */

template<class T>
int Type<T>::getPrecision() const noexcept
{
	return static_cast<int>(type);
}

/*!
 * @tparam T is any of int, short, float, double
 * @param x is string that contain valid numeric or floating point value.
 * @return Extract value from string to T
 */

template<class T>
inline T 	 Type<T>::getNumber(std::string const &x) const
{
	T 					res;
	std::stringstream	toT(x);

	toT >> res;
	return res;
}

/*!
 * @param x is string that contain numeric value of char
 *
 * This specialization realized, because stringsteam does not support work with int8, as with numeric value.
 * So we work within as with int. And return as numeric value of char.
 */

template<>
inline int8_t 	 Type<int8_t>::getNumber(std::string const &x) const
{
	int 				res;
	std::stringstream	toT(x);

	toT >> res;
	return res;
}

/*!
 * @return private field str. That contain string representation of value.
 */

template<class T>
std::string const &Type<T>::toString() const
{
	return str;
}

