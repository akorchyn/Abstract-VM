#include "../../Includes/Parser.hpp"

/*!
 * \ingroup parse
 * \file
 * \brief Parser methods definition
 */

/*!
 * Used private method: getInputFromConsole. This method could read input from console until find ";;"
 */
Parser::Parser()
{
	getInputFromConsole();
}

Parser::Parser(std::unique_ptr<std::istream> input) : input(std::move(input))
{
}

/*!
 *
 * @param commands[out] push back parsed commands.
 * @return true if parse ok, and false in other way.
 */

bool Parser::parseInput(Commands &commands)
{
	std::string line;
	bool		validParse = static_cast<bool>(input); // Check if input has anything.
	unsigned	exitPosition = 0; // Variable to memorise commands size when exit instruction finds.

	while (input && !input->eof())
	{
		std::getline(*input, line);
		if (!parseLine(line, commands))
			validParse = false;
		else if (!exitPosition && !commands.empty() && dynamic_cast<Exit*>(commands.back().get()))
			exitPosition = commands.size();
	}
	input && input->seekg(-1, std::ios_base::end);
	if (input && (exitPosition == 0 || input->get() != -1))
	{
		std::cerr << (exitPosition == 0 ? "Error: Exit instruction was not found"
									 : "Error: No newline at the end of file") << std::endl;
		return false;
	}
	else if (input && exitPosition != commands.size())
		std::cerr << "Warning: Founded commands after exit. " << commands.size() - exitPosition << " commands will be ignored" << std::endl;
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
