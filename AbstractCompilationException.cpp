#include "AbstractCompilationException.hpp"

AbstractCompilationException::AbstractCompilationException(const char *msg, int line, int column, const std::string &errorText) noexcept
{
	msg_ += std::string("Error. Expected ") + msg + " at line " + std::to_string(line) + " col: " + std::to_string(column)
			+ " : \"" + errorText + "\"";
}

AbstractCompilationException::AbstractCompilationException(AbstractCompilationException const &x) noexcept
{
	msg_ = x.msg_;
}

AbstractCompilationException &AbstractCompilationException::operator=(AbstractCompilationException const &x) noexcept
{
	if (&x == this)
		return *this;
	msg_ = x.msg_;
	return *this;
}

AbstractCompilationException::~AbstractCompilationException() noexcept
{
}

const char *AbstractCompilationException::what() const noexcept
{
	return msg_.c_str();
}
