#pragma once

/*!
 * \ingroup parse
 */

/*!
 * \file
 * \brief File contain main grammar
 */

#include "../Operations/IOperation.hpp"
#include "../Operations/Operations.hpp"
#include "ValueGrammar.hpp"

using	  OneCommand = std::shared_ptr<IOperation>; ///< Shared_ptr used, becouse i don't know how to use phoenix and unique_ptr :C
using     Commands = std::vector<OneCommand>; ///< Massive of commands.

/*!
 * @tparam IteratorT is iterator type that is used.
 * @tparam SkipperT is type of grammar of skipping characters that is used. (SkipperGrammar.hpp)
 */

template<typename IteratorT, typename SkipperT>
class CommandGrammar // Grammar to parse commands
		: public qi::grammar<IteratorT, SkipperT>
{
public:
	CommandGrammar(Commands &commands);
	~CommandGrammar();

	CommandGrammar(CommandGrammar const &x) = delete;
	CommandGrammar &operator=(CommandGrammar const &x) = delete;

	static unsigned				  		line;///< counting lines to give it in constructor of Operation
	qi::rule<IteratorT, SkipperT> 		rule;///< main rule.
	qi::rule<IteratorT, SkipperT> 		argFunc;///< rule that parse operations with arguments.
	qi::rule<IteratorT, SkipperT> 		other;///< rule that parse operations without arguments
	ValueGrammar<IteratorT, SkipperT>	values;///< Grammar that parse arguments and return string representation of value
};


template<typename IteratorT, typename SkipperT>
unsigned CommandGrammar<IteratorT, SkipperT>::line = 0;

template<typename IteratorT, typename SkipperT>
CommandGrammar<IteratorT, SkipperT>::CommandGrammar(Commands &commands)
		: CommandGrammar::base_type(rule, "Command Grammar"), values(++line)
{
	/*
	 *  Expression in square brackets is executed only if everything is fine
	 */
	argFunc %=   (qi::omit[qi::lit("assert") > qi::no_skip[(qi::char_(' ') | '\t')]] > values
						[phx::push_back(phx::ref(commands), phx::construct<OneCommand>(phx::new_<Assert>(phx::at_c<0>(qi::_1), line, phx::at_c<1>(qi::_1))))]) |
				 (qi::omit[qi::lit("push") > qi::no_skip[(qi::char_(' ') | '\t')]] > values
						[phx::push_back(phx::ref(commands), phx::construct<OneCommand>(phx::new_<Push>(phx::at_c<0>(qi::_1), phx::at_c<1>(qi::_1))))]);
	other   %=	 (qi::lit("dump") [phx::push_back(phx::ref(commands), phx::construct<OneCommand>(phx::new_<Dump>(line)))] |
				 qi::lit("add")   [phx::push_back(phx::ref(commands), phx::construct<OneCommand>(phx::new_<Plus>(line)))] |
				 qi::lit("sub")   [phx::push_back(phx::ref(commands), phx::construct<OneCommand>(phx::new_<Minus>(line)))] |
				 qi::lit("mul")   [phx::push_back(phx::ref(commands), phx::construct<OneCommand>(phx::new_<Multiply>(line)))] |
				 qi::lit("div")   [phx::push_back(phx::ref(commands), phx::construct<OneCommand>(phx::new_<Division>(line)))] |
				 qi::lit("mod")   [phx::push_back(phx::ref(commands), phx::construct<OneCommand>(phx::new_<Modulo>(line)))] |
				 qi::lit("print") [phx::push_back(phx::ref(commands), phx::construct<OneCommand>(phx::new_<Print>(line)))] |
				 qi::lit("exit")  [phx::push_back(phx::ref(commands), phx::construct<OneCommand>(phx::new_<Exit>(line)))] |
				 qi::lit("pop")   [phx::push_back(phx::ref(commands), phx::construct<OneCommand>(phx::new_<Pop>(line)))] |
				 qi::lit("or")    [phx::push_back(phx::ref(commands), phx::construct<OneCommand>(phx::new_<BinaryOr>(line)))] |
				 qi::lit("xor")   [phx::push_back(phx::ref(commands), phx::construct<OneCommand>(phx::new_<BinaryXor>(line)))] |
			  	 qi::lit("and")   [phx::push_back(phx::ref(commands), phx::construct<OneCommand>(phx::new_<BinaryAnd>(line)))])
			  	 > qi::eoi |
			  	 qi::eoi; // qi::eoi, becouse skipper grammary skip whitespaces and comments, so empty line is ok.

	rule %= qi::expect[(other | argFunc)]; // qi::expect mean that one of the rule must be true.
	argFunc.name("command argument");
	other.name("command");
	qi::on_error(rule,
				 std::cerr << phx::val("Error. Expected ") << qi::_4 << " at line " << line << " col: " << qi::_3 - qi::_1
						   << " : \"" << phx::construct<std::string>(qi::_3, qi::_2) << "\"" << std::endl);
	// qi::_1 is iterator where parse started
	// qi::_2 is iterator to string end.
	// qi::_3 is iterator where parse failed.
	// qi::_4 is a string what expected
}

template<typename IteratorT, typename SkipperT>
CommandGrammar<IteratorT, SkipperT>::~CommandGrammar()
{
}

