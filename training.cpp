#include <boost/spirit/include/qi.hpp>
#include <boost/bind.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/iterator.hpp>
#include <boost/variant.hpp>
#include <string>
#include <vector>
#include <boost/phoenix/phoenix.hpp>
#include "AbstractException.hpp"

namespace spirit = boost::spirit;
namespace qi = spirit::qi;
namespace phoenix = boost::phoenix;

using     Commands = std::vector<std::string>;

template<typename IteratorT>
class SkipperGrammar : public qi::grammar<IteratorT> // ignoring '\t' ' ' '\n' symbols and comment "; ... \n
{
public:
	SkipperGrammar()
			: SkipperGrammar::base_type(rule)
	{
		lineCommentRule = qi::omit[qi::char_(';') >> *(qi::char_)];
		spaceRule = qi::space;
		rule = spaceRule | lineCommentRule;
	}

	qi::rule<IteratorT> lineCommentRule;
	qi::rule<IteratorT> spaceRule;
	qi::rule<IteratorT> rule;
};

template<typename IteratorT, typename SkipperT>
class ValueGrammar : public qi::grammar<IteratorT, SkipperT> // Grammar to parse types
{
public:
	ValueGrammar()
			:ValueGrammar::base_type(rule, "Types Grammar")
	{
		const auto char_number_ = [](const int &attr, auto &, bool &pass) {
			pass = (attr > -129 && attr < 128);
		}; // lambda to check char limits

		Int8 %=  qi::lexeme[qi::omit[qi::lit("int8(")] > qi::int_[char_number_] > qi::omit[qi::char_(')')]];
		Int16 %= qi::lexeme[qi::omit[qi::lit("int16(")] > qi::short_ > qi::omit[qi::char_(')')]];
		Int32 %= qi::lexeme[qi::omit[qi::lit("int32(")] > qi::int_ > qi::omit[qi::char_(')')]];
		Float %= qi::lexeme[qi::omit[qi::lit("float(")] > qi::float_ > qi::omit[qi::char_(')')]];
		Double %= qi::lexeme[qi::omit[qi::lit("double(")] > qi::double_ > qi::omit[qi::char_(')')]];

		rule %= qi::expect[Int8 | Int16 | Int32 | Float | Double];

		Int8.name("int8(...)");
		Int16.name("int16(...)");
		Int32.name("int32(...)");
		Float.name("float(...)");
		Double.name("double(...)");
		rule.name("Valid type");
		qi::on_error(rule,
					 std::cerr << phoenix::val("Error. Expected ")
								  << qi::_4 <<" at: \""
								  << phoenix::construct<std::string>(qi::_3,qi::_2)
								  << "\"\n");
	}

	qi::rule<IteratorT, char(), SkipperT> Int8;
	qi::rule<IteratorT, short(), SkipperT> Int16;
	qi::rule<IteratorT, int(), SkipperT> Int32;
	qi::rule<IteratorT, float(), SkipperT> Float;
	qi::rule<IteratorT, double(), SkipperT> Double;
	qi::rule<IteratorT, SkipperT> rule;
};

template<typename IteratorT, typename SkipperT>
class CommandGrammar : public qi::grammar<IteratorT, SkipperT>
{
public:
	CommandGrammar()
			: CommandGrammar::base_type(rule, "Command Grammar")
	{
		static unsigned line = 0;
		argFunc %= qi::lit("assert") > values
				|  qi::lit("push") > values;
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
				phoenix::throw_(AbstractException(phoenix::construct<const char *>(_4), line, qi::_3 - qi::_1,
						phoenix::construct<std::string>(qi::_3, qi::_2))));
	}

	qi::rule<IteratorT, SkipperT> rule;
	qi::rule<IteratorT, SkipperT> argFunc;
	qi::rule<IteratorT, SkipperT> other;

	ValueGrammar<IteratorT, SkipperT>	values;
};

bool	parseLine(std::string &line)
{
	std::string::iterator															it = line.begin();
	SkipperGrammar<std::string::iterator>											Spaces;
	CommandGrammar<std::string::iterator, SkipperGrammar<std::string::iterator> >	CommandGrammar;
	return (qi::phrase_parse(it, line.end(), CommandGrammar, Spaces) && it == line.end());
}


int main(int , char **)
{
	std::string line;
//	Commands commands;

	while (!std::cin.eof())
	{
		std::getline(std::cin, line);

		std::cout << parseLine(line) << std::endl;
	}
}
