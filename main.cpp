#include <iostream>
#include <sstream>
#include <cstddef>
#include <fstream>
#include <vector>
#include "IOperand.hpp"
#include "Parser.hpp"
#include <boost/spirit/include/qi.hpp>

void	Console()
{
}

namespace qi = boost::spirit::qi;

bool	parseNumber(const char *x)
{
}

void	parseFile(std::string const &filename)
{
	std::ifstream				file(filename);
	std::vector <IOperand *>	nums;
	std::string					str;
	Parser						parser;
	//bool						isNoError = true;

	if (!file.good())
		throw std::runtime_error(std::runtime_error(strerror(errno)));
	while (!file.eof())
	{
		std::getline(file, str);
//		parser.parseCommand(str, nums);
	}
}

int		main(int ac, char **av)
{
	if (ac == 1)
		Console();
	else
	{
		for (int i = 1; i < ac; i++)
		{
			try
			{
//				parseFile(av[i]);
			}
			catch (std::exception &x)
			{
				std::cerr << "avm: " << av[i] << ": " << x.what() << std::endl;
			}
		}
	}
	return 0;
}

