#include "AbstractRuntimeException.hpp"

AbstractRuntimeException::AbstractRuntimeException(const std::string &&x) noexcept : msg(x)
{
}

AbstractRuntimeException::AbstractRuntimeException(AbstractRuntimeException const &x) noexcept : msg(x.msg)
{
}

AbstractRuntimeException::~AbstractRuntimeException()
{
}

AbstractRuntimeException &AbstractRuntimeException::operator=(AbstractRuntimeException const &x) noexcept
{
	if (&x == this)
		return *this;
	msg = x.msg;
	return *this;
}

const char *AbstractRuntimeException::what() const noexcept
{
	return msg.c_str();
}
