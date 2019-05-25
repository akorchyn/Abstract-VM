#include "../../Includes/Parser.hpp"

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
	unsigned	exitNumber = 0;

	while (input && !input->eof())
	{
		std::getline(*input, line);
		if (!parseLine(line, commands))
			validParse = false;
		else if (!exitNumber && !commands.empty() && dynamic_cast<Exit*>(commands.back().get()))
			exitNumber = commands.size();
	}
	input && input->seekg(-1, std::ios_base::end);
	if (input && (exitNumber == 0 || input->get() != -1))
	{
		std::cerr << (exitNumber == 0 ? "Error: Exit instruction was not found"
									 : "Error: No newline at the end of file") << std::endl;
		return false;
	}
	else if (input && exitNumber != commands.size())
		std::cerr << "Warning: Founded commands after exit. " << commands.size() - exitNumber << " commands will be ignored" << std::endl;
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
