#ifndef ABSTRACTVM_ABSTRACTRUNTIMEEXCEPTION_HPP
#define ABSTRACTVM_ABSTRACTRUNTIMEEXCEPTION_HPP

#include <string>

class AbstractRuntimeException : public std::exception
{
public:
	AbstractRuntimeException(const std::string &&x) noexcept;
	AbstractRuntimeException(AbstractRuntimeException const &x) noexcept;
	~AbstractRuntimeException();

	AbstractRuntimeException &operator=(AbstractRuntimeException const &x) noexcept;

	const char *what() const noexcept override;

private:
	std::string		msg;
};


#endif
