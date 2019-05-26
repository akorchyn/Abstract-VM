#pragma once

/*!
 * \defgroup parse Parsing
 * \brief This module contains all that used in parsing.
 *
 * It contains four classes. Three is spirit::qi grammar and one parser.
 */

/*!
 * \file
 * \brief Header contains declaration one of the main class.
 */

#include "Grammar/CommandGrammar.hpp"
#include "Grammar/SkipperGrammar.hpp"

/*!
 * \brief Class that parse input.
 *
 * This class parse input by using spirit::qi and phoenix.
 * Have two opportunity to parse. From istream or from console.
 * If created without arguments, it would start reading from console.
 */

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

