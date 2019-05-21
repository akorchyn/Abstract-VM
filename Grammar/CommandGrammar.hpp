#ifndef ABSTRACTVM_COMMANDGRAMMAR_HPP
#define ABSTRACTVM_COMMANDGRAMMAR_HPP

#include "ValueGrammar.hpp"
#include "../Operations.hpp"

using     Commands = std::vector<IOperation*>;

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
	argFunc %=   qi::omit[qi::lit("assert") > qi::no_skip[qi::char_(' ') | '\t']] > values
						[phx::push_back(phx::ref(commands), phx::new_<Assert>(std::move(phx::at_c<0>(qi::_1)), line, phx::at_c<1>(qi::_1)))] |
				 qi::omit[qi::lit("push") > qi::no_skip[qi::char_(' ') | '\t']] > values
						[phx::push_back(phx::ref(commands), phx::new_<Push>(std::move(phx::at_c<0>(qi::_1)), phx::at_c<1>(qi::_1)))];
	other   %=	(qi::lit("dump")  [phx::push_back(phx::ref(commands), new Dump(line))] |
				 qi::lit("add")   [phx::push_back(phx::ref(commands), new Plus(line))] |
				 qi::lit("sub")   [phx::push_back(phx::ref(commands), new Minus(line))] |
				 qi::lit("mul")   [phx::push_back(phx::ref(commands), new Multiply(line))] |
				 qi::lit("div")   [phx::push_back(phx::ref(commands), new Division(line))] |
				 qi::lit("mod")   [phx::push_back(phx::ref(commands), new Modulo(line))] |
				 qi::lit("print") [phx::push_back(phx::ref(commands), new Print(line))] |
				 qi::lit("exit")  [phx::push_back(phx::ref(commands), new Exit(line))] |
				 qi::lit("pop")   [phx::push_back(phx::ref(commands), new Pop(line))])
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

#endif
