#ifndef ABSTRACTVM_ABSTRACTEXCEPTION_HPP
#define ABSTRACTVM_ABSTRACTEXCEPTION_HPP

#include <exception>
#include <string>

class AbstractException : public std::exception
{
public:
	AbstractException(const char *msg, int line, int column, const std::string &errorText) noexcept;
	AbstractException(AbstractException const &x) noexcept;
	AbstractException &operator=(AbstractException const &x) noexcept;
	~AbstractException() noexcept;

	const char *what() const noexcept override;

private:
	std::string msg_;
};


#endif
