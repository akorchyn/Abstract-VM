#include <string>
#include <sstream>
#include <iostream>
#include "Grammar/CommandGrammar.hpp"
#include "Grammar/SkipperGrammar.hpp"

bool	parseLine(std::string &line, Commands &commands)
{
	std::string::iterator															it = line.begin();
	SkipperGrammar<std::string::iterator>											Spaces;
	CommandGrammar<std::string::iterator, SkipperGrammar<std::string::iterator> >	CommandGrammar{commands};
	return (qi::phrase_parse(it, line.end(), CommandGrammar, Spaces) && it == line.end());
}

void	parseInput(std::istream *input)
{
	std::string line;
	Commands    commands;
	TypeStack	st;

	while (!input->eof())
	{	
		std::getline(*input, line);
		parseLine(line, commands);
	}
	for (auto &x : commands)
		x->execute(st);
	delete input;
}

std::istream 	*getInputFromConsole()
{
	std::iostream		*input = new std::stringstream();
	std::string 		line;

	std::getline(std::cin, line);
	while (!std::cin.eof() && line != ";;")
	{
		*input << line << std::endl;
		std::getline(std::cin, line);
	}
	return input;
}

int main(int argc, char **)
{
	std::ios::sync_with_stdio(false);
	
	if (argc == 1)
		parseInput(getInputFromConsole());
}
