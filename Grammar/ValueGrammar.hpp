#ifndef ABSTRACTVM_VALUEGRAMMAR_HPP
#define ABSTRACTVM_VALUEGRAMMAR_HPP

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix.hpp>
#include <boost/variant.hpp>
#include "../IOperandGenerator.hpp"

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

	qi::rule<IteratorT, IOperand const *, SkipperT> Int8_;
	qi::rule<IteratorT, IOperand const *, SkipperT> Int16_;
	qi::rule<IteratorT, IOperand const *, SkipperT> Int32_;
	qi::rule<IteratorT, IOperand const *, SkipperT> Float_;
	qi::rule<IteratorT, IOperand const *, SkipperT> Double_;
	qi::rule<IteratorT, IOperand const *, SkipperT> rule;

	IOperandGenerator			  gen;
};

template<typename IteratorT, typename SkipperT>
ValueGrammar<IteratorT, SkipperT>::~ValueGrammar()
{
}

template<typename IteratorT, typename SkipperT>
ValueGrammar<IteratorT, SkipperT>::ValueGrammar(int line)
			: ValueGrammar::base_type(rule, "Types Grammar")
	{
		Int8_   %= (qi::lexeme[qi::omit[qi::lit("int8(")] > qi::raw[qi::int_[qi::_pass = (qi::_1 > -129 && qi::_1 < 128)]] > qi::omit[qi::char_(')')]]) [qi::_val = gen.createOperand(Int8, qi::_1)];
		Int16_  %= (qi::lexeme[qi::omit[qi::lit("int16(")] > qi::raw[qi::short_] > qi::omit[qi::char_(')')]])                                           [qi::_val = gen.createOperand(Int16, qi::_1)];
		Int32_  %= (qi::lexeme[qi::omit[qi::lit("int32(")] > qi::raw[qi::int_] > qi::omit[qi::char_(')')]])                                             [qi::_val = gen.createOperand(Int32, qi::_1)];
		Float_  %= (qi::lexeme[qi::omit[qi::lit("float(")] > qi::raw[qi::float_] > qi::omit[qi::char_(')')]])                                           [qi::_val = gen.createOperand(Float, qi::_1)];
		Double_ %= (qi::lexeme[qi::omit[qi::lit("double(")] > qi::raw[qi::double_] > qi::omit[qi::char_(')')]])                                         [qi::_val = gen.createOperand(Double, qi::_1)];

		rule %= qi::expect[Int8_ | Int16_ | Int32_ | Float_ | Double_];

		Int8_.name("int8(...)");
		Int16_.name("int16(...)");
		Int32_.name("int32(...)");
		Float_.name("float(...)");
		Double_.name("double(...)");
		rule.name("Valid type");
		qi::on_error(rule,
					 std::cerr << phx::val("Error. Expected ") << qi::_4 <<" at line : " << line << ": \""
								  << phx::construct<std::string>(qi::_3,qi::_2) << "\"\n");
	}

#endif
