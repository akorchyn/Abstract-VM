#pragma once

#include <string>

class AbstractRuntimeException : public std::runtime_error
{
public:
	AbstractRuntimeException(const std::string &x) noexcept;
	AbstractRuntimeException(AbstractRuntimeException const &x) noexcept;
	~AbstractRuntimeException();
	AbstractRuntimeException &operator=(AbstractRuntimeException const &x) noexcept;
};
