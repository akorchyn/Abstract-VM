#ifndef ABSTRACTVM_COMMANDGRAMMAR_HPP
#define ABSTRACTVM_COMMANDGRAMMAR_HPP

#include "ValueGrammar.hpp"

namespace spirit = boost::spirit;
namespace qi =     spirit::qi;
namespace phx =    boost::phoenix;

template<typename IteratorT, typename SkipperT>
class CommandGrammar // Grammar to parse commands
		: public qi::grammar<IteratorT, SkipperT>
{
public:
	CommandGrammar();
	~CommandGrammar();

private:
	CommandGrammar(CommandGrammar const &x) = default;
	CommandGrammar &operator=(CommandGrammar const &x) = default;

	qi::rule<IteratorT, SkipperT> rule;
	qi::rule<IteratorT, SkipperT> argFunc;
	qi::rule<IteratorT, SkipperT> other;
};

template<typename IteratorT, typename SkipperT>
CommandGrammar<IteratorT, SkipperT>::CommandGrammar()
		: CommandGrammar::base_type(rule, "Command Grammar")
{
	static unsigned line = 0;
	ValueGrammar<IteratorT, SkipperT>	values(line);

	argFunc %= qi::lit("assert") > qi::no_skip[qi::char_(' ') | '\t'] > values
			   |  qi::lit("push") > qi::no_skip[qi::char_(' ') | '\t'] > values;
	other %=	(qi::lit("dump") |
				 qi::lit("add") |
				 qi::lit("sub") |
				 qi::lit("mul") |
				 qi::lit("div") |
				 qi::lit("mod") |
				 qi::lit("print") |
				 qi::lit("exit") |
				 qi::lit("pop"))
				> qi::eoi |
				qi::eoi;
	rule %= qi::expect[(other | argFunc)];
	argFunc.name("command argument");
	other.name("command");
	line++;
	qi::on_error(rule,
				 std::cerr << phx::val("Error. Expected ") << qi::_4 << " at line " << line << " col: " << qi::_3 - qi::_1
						   << " : \"" << phx::construct<std::string>(qi::_3, qi::_2) << "\"" << std::endl);
}

template<typename IteratorT, typename SkipperT>
CommandGrammar<IteratorT, SkipperT>::~CommandGrammar()
{
}

#endif