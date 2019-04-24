#ifndef ABSTRACTVM_VALUEGRAMMAR_HPP
#define ABSTRACTVM_VALUEGRAMMAR_HPP

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix.hpp>
#include <boost/variant.hpp>

namespace spirit = boost::spirit;
namespace qi =     spirit::qi;
namespace phx =    boost::phoenix;

template<typename IteratorT, typename SkipperT>
class ValueGrammar
		: public qi::grammar<IteratorT, SkipperT> // Grammar to parse types
{
public:
	ValueGrammar(int line);
	~ValueGrammar();

private:
	ValueGrammar(ValueGrammar const &x) = default;
	ValueGrammar &operator=(ValueGrammar const &x) = default;

	qi::rule<IteratorT, int(), SkipperT> Int8;
	qi::rule<IteratorT, short(), SkipperT> Int16;
	qi::rule<IteratorT, int(), SkipperT> Int32;
	qi::rule<IteratorT, float(), SkipperT> Float;
	qi::rule<IteratorT, double(), SkipperT> Double;
	qi::rule<IteratorT, SkipperT> rule;
};

template<typename IteratorT, typename SkipperT>
ValueGrammar<IteratorT, SkipperT>::~ValueGrammar()
{
}

template<typename IteratorT, typename SkipperT>
ValueGrammar<IteratorT, SkipperT>::ValueGrammar(int line)
			: ValueGrammar::base_type(rule, "Types Grammar")
	{
		Int8 %=  (qi::lexeme[qi::omit[qi::lit("int8(")] > qi::int_[qi::_pass = (qi::_1 > -129 && qi::_1 < 128)] > qi::omit[qi::char_(')')]]);
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
					 std::cerr << phx::val("Error. Expected ") << qi::_4 <<" at line : " << line << ": \""
								  << phx::construct<std::string>(qi::_3,qi::_2) << "\"\n");
	}

#endif
