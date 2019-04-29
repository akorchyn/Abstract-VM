#include <string>
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

int main(int , char **)
{
	std::string line;
	TypeStack	st;
	Commands commands;

	while (!std::cin.eof())
	{
		std::getline(std::cin, line);
		parseLine(line, commands);
	}
	for (auto const &x : commands)
	{
		x->execute(st);
	}
}
