#pragma once

#include <boost/utility/value_init.hpp>
#include "../Operations/IOperation.hpp"
#include "../Operations/Operations.hpp"
#include "ValueGrammar.hpp"

using	  OneCommand = std::shared_ptr<IOperation>;
using     Commands = std::vector<OneCommand>;

template<typename IteratorT, typename SkipperT>
class CommandGrammar // Grammar to parse commands
		: public qi::grammar<IteratorT, SkipperT>
{
public:
	CommandGrammar(Commands &commands);
	~CommandGrammar();

	CommandGrammar(CommandGrammar const &x) = delete;
	CommandGrammar &operator=(CommandGrammar const &x) = delete;

	static unsigned				  		line;
	qi::rule<IteratorT, SkipperT> 		rule;
	qi::rule<IteratorT, SkipperT> 		argFunc;
	qi::rule<IteratorT, SkipperT> 		other;
	ValueGrammar<IteratorT, SkipperT>	values;
};


template<typename IteratorT, typename SkipperT>
unsigned CommandGrammar<IteratorT, SkipperT>::line = 0;

template<typename IteratorT, typename SkipperT>
CommandGrammar<IteratorT, SkipperT>::CommandGrammar(Commands &commands)
		: CommandGrammar::base_type(rule, "Command Grammar"), values(++line)
{
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
			  	 qi::eoi;


	rule %= qi::expect[(other | argFunc)];
	argFunc.name("command argument");
	other.name("command");
	qi::on_error(rule,
				 std::cerr << phx::val("Error. Expected ") << qi::_4 << " at line " << line << " col: " << qi::_3 - qi::_1
						   << " : \"" << phx::construct<std::string>(qi::_3, qi::_2) << "\"" << std::endl);
}

template<typename IteratorT, typename SkipperT>
CommandGrammar<IteratorT, SkipperT>::~CommandGrammar()
{
}

