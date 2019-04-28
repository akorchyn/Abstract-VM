#ifndef ABSTRACTVM_ABSTRACTCOMPILATIONEXCEPTION_HPP
#define ABSTRACTVM_ABSTRACTCOMPILATIONEXCEPTION_HPP

#include <exception>
#include <string>

class AbstractCompilationException : public std::exception
{
public:
	AbstractCompilationException(const char *msg, int line, int column, const std::string &errorText) noexcept;
	AbstractCompilationException(AbstractCompilationException const &x) noexcept;
	AbstractCompilationException &operator=(AbstractCompilationException const &x) noexcept;
	~AbstractCompilationException() noexcept;

	const char *what() const noexcept override;

private:
	std::string msg_;
};


#endif
