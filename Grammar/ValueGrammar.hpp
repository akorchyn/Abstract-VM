#ifndef ABSTRACTVM_VALUEGRAMMAR_HPP
#define ABSTRACTVM_VALUEGRAMMAR_HPP

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix.hpp>
#include <boost/variant.hpp>
#include "../IOperandGenerator.hpp"
#include <memory>

namespace spirit = boost::spirit;
namespace qi =     spirit::qi;
namespace phx =    boost::phoenix;

template<typename IteratorT, typename SkipperT>
class ValueGrammar
		: public qi::grammar<IteratorT, SkipperT> // Grammar to parse types
{
public:
	ValueGrammar(int line, eOperandType &type);
	~ValueGrammar();

private:
	ValueGrammar(ValueGrammar const &x) = default;
	ValueGrammar &operator=(ValueGrammar const &x) = default;

	qi::rule<IteratorT, std::string(), SkipperT> Int8_;
	qi::rule<IteratorT, std::string(), SkipperT> Int16_;
	qi::rule<IteratorT, std::string(), SkipperT> Int32_;
	qi::rule<IteratorT, std::string(), SkipperT> Float_;
	qi::rule<IteratorT, std::string(), SkipperT> Double_;
	qi::rule<IteratorT, SkipperT> rule;
};

template<typename IteratorT, typename SkipperT>
ValueGrammar<IteratorT, SkipperT>::~ValueGrammar()
{
}

template<typename IteratorT, typename SkipperT>
ValueGrammar<IteratorT, SkipperT>::ValueGrammar(int line, eOperandType &t)
			: ValueGrammar::base_type(rule, "Types Grammar")
	{
		t = eOperandType::Int8;
		Int8_   %= (qi::lexeme[qi::omit[qi::lit("int8(")] > qi::raw[qi::int_[qi::_pass = (qi::_1 > -129 && qi::_1 < 128)]] > qi::omit[qi::char_(')')]]);
		Int16_  %= (qi::lexeme[qi::omit[qi::lit("int16(")] > qi::raw[qi::short_[phx::ref(t) = eOperandType::Int16]] > qi::omit[qi::char_(')')]]);
		Int32_  %= (qi::lexeme[qi::omit[qi::lit("int32(")] > qi::raw[qi::int_[phx::ref(t) = eOperandType::Int32]] > qi::omit[qi::char_(')')]]);
		Float_  %= (qi::lexeme[qi::omit[qi::lit("float(")] > qi::raw[qi::float_[phx::ref(t) = eOperandType::Float]] > qi::omit[qi::char_(')')]]);
		Double_ %= (qi::lexeme[qi::omit[qi::lit("double(")] > qi::raw[qi::double_[phx::ref(t) = eOperandType::Double]] > qi::omit[qi::char_(')')]]);

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
