#include "Parser.hpp"

Parser::Parser()
{
	getInputFromConsole();
}

Parser::Parser(std::unique_ptr<std::istream> input) : input(std::move(input))
{
}

bool Parser::parseInput(Commands &commands)
{
	std::string line;
	bool		validParse = static_cast<bool>(input);

	while (input && !input->eof())
	{
		std::getline(*input, line);
		if (!parseLine(line, commands))
			validParse = false;
	}
	return validParse;
}

bool Parser::parseLine(std::string &line, Commands &commands)
{
	std::string::iterator															it = line.begin();
	SkipperGrammar<std::string::iterator>											Spaces;
	CommandGrammar<std::string::iterator, SkipperGrammar<std::string::iterator> >	CommandGrammar(commands);
	return (qi::phrase_parse(it, line.end(), CommandGrammar, Spaces) && it == line.end());
}

void		Parser::getInputFromConsole()
{
	std::string line;
	bool		endStream = false;

	auto tmp = std::make_unique<std::stringstream>();
	std::getline(std::cin, line);
	while (!std::cin.eof())
	{
		if (line == ";;")
		{
			endStream = true;
			break;
		}
		*tmp << line << std::endl;
		std::getline(std::cin, line);
	}
	if (!endStream)
	{
		std::cerr << "Console Input Error: Stream must end by ;;" << std::endl;
		input = nullptr;
	}
	else
		input = std::move(tmp);
}
