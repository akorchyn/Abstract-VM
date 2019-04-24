#ifndef ABSTRACTVM_TYPE_HPP
#define ABSTRACTVM_TYPE_HPP

#include "IOperand.hpp"
#include <string>

template <class T>
class Type : public IOperand
{
public:
	Type(const T &value, eOperandType type);
	Type(Type const &x);
	Type &operator=(Type const &x);
	~Type();

	eOperandType getType() const;
	int			 getPrecision() const;

	IOperand const *operator+(IOperand const &rhs) const;
	IOperand const *operator-(IOperand const &rhs) const;
	IOperand const *operator/(IOperand const &rhs) const;
	IOperand const *operator*(IOperand const &rhs) const;
	IOperand const *operator%(IOperand const &rhs) const;

	std::string	const &toString() const;

private:
	T				value;
	eOperandType	type;
};

template<class T>
Type<T>::Type(const T &value, eOperandType type) : value(value), type(type)
{
}

template<class T>
Type<T>::Type(Type const &x) : value(x.value), type(x.type)
{
}

template<class T>
Type<T> &Type<T>::operator=(Type const &x)
{
	if (&x == this)
		return *this;
	value = x.value;
	type = x.type;
	return *this;
}

template<class T>
Type<T>::~Type()
{
}


#endif
