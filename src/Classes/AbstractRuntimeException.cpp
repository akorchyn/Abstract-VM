#include "../../Includes/AbstractRuntimeException.hpp"

AbstractRuntimeException::AbstractRuntimeException(const std::string &x) noexcept : std::runtime_error(x)
{
}

AbstractRuntimeException::AbstractRuntimeException(AbstractRuntimeException const &x) noexcept : std::runtime_error(x)
{
}

AbstractRuntimeException::~AbstractRuntimeException()
{
}

AbstractRuntimeException &AbstractRuntimeException::operator=(AbstractRuntimeException const &x) noexcept
{
	std::runtime_error::operator=(x);
	return *this;
}

