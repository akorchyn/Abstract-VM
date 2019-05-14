#ifndef ABSTRACTVM_COMMANDGRAMMAR_HPP
#define ABSTRACTVM_COMMANDGRAMMAR_HPP

#include "ValueGrammar.hpp"
#include "../IOperationsGenerator.hpp"

namespace spirit = boost::spirit;
namespace qi =     spirit::qi;
namespace phx =    boost::phoenix;

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

	static unsigned				  line;
	qi::rule<IteratorT, SkipperT> rule;
	qi::rule<IteratorT, SkipperT> argFunc;
	qi::rule<IteratorT, SkipperT> other;
	ValueGrammar<IteratorT, SkipperT>	values;
};

template<typename IteratorT, typename SkipperT>
unsigned CommandGrammar<IteratorT, SkipperT>::line = 0;

template<typename IteratorT, typename SkipperT>
CommandGrammar<IteratorT, SkipperT>::CommandGrammar(Commands &commands)
		: CommandGrammar::base_type(rule, "Command Grammar"), values(++line)
{
	argFunc %=   qi::omit[qi::lit("assert") > qi::no_skip[qi::char_(' ') | '\t']] > values
						|
				 qi::omit[qi::lit("push") > qi::no_skip[qi::char_(' ') | '\t']] > values
						;
	other   %=	(qi::lit("dump") [phx::push_back(commands, phx::new_<Dump>())] |
				 qi::lit("add") |
				 qi::lit("sub") |
				 qi::lit("mul") |
				 qi::lit("div") |
				 qi::lit("mod") |
				 qi::lit("print") [phx::push_back(commands, phx::new_<Print>(line))] |
				 qi::lit("exit") |
				 qi::lit("pop") [phx::push_back(commands, phx::new_<Pop>(line))])
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
