#include <string>
#include <sstream>
#include <iostream>
#include "AbstractRuntimeException.hpp"
#include "Grammar/CommandGrammar.hpp"
#include "Grammar/SkipperGrammar.hpp"

bool	parseLine(std::string &line, Commands &commands)
{
	std::string::iterator															it = line.begin();
	SkipperGrammar<std::string::iterator>											Spaces;
	CommandGrammar<std::string::iterator, SkipperGrammar<std::string::iterator> >	CommandGrammar(commands);
	return (qi::phrase_parse(it, line.end(), CommandGrammar, Spaces) && it == line.end());
}

bool	parseInput(std::unique_ptr<std::istream> input, Commands &commands)
{
	std::string line;
	bool		validParse = true;

	while (!input->eof())
	{	
		std::getline(*input, line);
		if (!parseLine(line, commands))
			validParse = false;
	}
	return validParse;
}

std::unique_ptr<std::istream> getInputFromConsole()
{
	std::iostream		*input = new std::stringstream();
	std::string 		line;
	bool				endStream = false;

	std::getline(std::cin, line);
	while (!std::cin.eof() && !endStream)
	{
		if (line == ";;")
		{
			endStream = true;
			break;
		}
		*input << line << std::endl;
		std::getline(std::cin, line);
	}
	if (!endStream)
		throw AbstractRuntimeException("Console Input Error: Stream must end by ;;");
	std::unique_ptr<std::istream>	result;
	result.reset(input);
	return result;
}

void	execute(Commands &commands)
{

}

int main(int argc, char **)
{
	std::ios::sync_with_stdio(false);
	Commands 	commands;

	if (argc == 1 && parseInput(getInputFromConsole(), commands))
		execute(commands);
}
