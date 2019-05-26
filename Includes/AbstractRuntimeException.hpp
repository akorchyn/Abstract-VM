#pragma once

/*!
 * \file
 * \brief Realization of custom exception.
 */

/*!
 * \brief Nothing interesting
 *
 * This class have nothing special, is used as std::runtime_error.
 */

#include <string>

class AbstractRuntimeException : public std::runtime_error
{
public:
	AbstractRuntimeException(const std::string &x) noexcept;
	AbstractRuntimeException(AbstractRuntimeException const &x) noexcept;
	~AbstractRuntimeException();
	AbstractRuntimeException &operator=(AbstractRuntimeException const &x) noexcept;
};
