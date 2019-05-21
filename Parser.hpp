#ifndef ABSTRACTVM_PARSER_HPP
#define ABSTRACTVM_PARSER_HPP

#include "Grammar/CommandGrammar.hpp"
#include "Grammar/SkipperGrammar.hpp"

class Parser
{
public:
	Parser();
	Parser(std::unique_ptr<std::istream> input);
	Parser(Parser const &x) = delete;
	Parser &operator=(Parser const &x) = delete;
	~Parser() = default;

	bool	parseInput(Commands &commands);
	bool	parseLine(std::string &line, Commands &commands);

private:
	void		getInputFromConsole();
	std::unique_ptr<std::istream> input;
};


#endif
