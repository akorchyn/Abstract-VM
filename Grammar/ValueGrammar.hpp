#pragma once

#include "SkipperGrammar.hpp"
#include "../IOperand.hpp"
#include <boost/phoenix.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <memory>

namespace spirit = boost::spirit;
namespace qi =     spirit::qi;
namespace phx =    boost::phoenix;

template<typename IteratorT, typename SkipperT>
class ValueGrammar
: public qi::grammar<IteratorT, std::pair<std::string, eOperandType>(), SkipperT> // Grammar to parse types
{
public:
	ValueGrammar(int line);
	~ValueGrammar();
	ValueGrammar(ValueGrammar const &x) = delete;
	ValueGrammar &operator=(ValueGrammar const &x) = delete;

	qi::rule<IteratorT, std::string(), SkipperT> Int8_;
	qi::rule<IteratorT, std::string(), SkipperT> Int16_;
	qi::rule<IteratorT, std::string(), SkipperT> Int32_;
	qi::rule<IteratorT, std::string(), SkipperT> Float_;
	qi::rule<IteratorT, std::string(), SkipperT> Double_;
	qi::rule<IteratorT, std::pair<std::string,eOperandType>(), SkipperT> rule;
};


template<typename IteratorT, typename SkipperT>
ValueGrammar<IteratorT, SkipperT>::~ValueGrammar()
{
}

template<typename IteratorT, typename SkipperT>
ValueGrammar<IteratorT, SkipperT>::ValueGrammar(int line)
			: ValueGrammar::base_type(rule, "Types Grammar")
	{

		// Parse literal "int8(" then int [-128 to 127] and represent number as string(phx::construct), then literal ")".
		Int8_   = qi::lexeme[qi::omit[qi::lit("int8(")]
						> qi::raw[qi::int_[qi::_pass = (qi::_1 > -129 && qi::_1 < 128)]][qi::_val = phx::construct<std::string>(phx::begin(qi::_1), phx::end(qi::_1))]
						> qi::omit[qi::char_(')')]];

		Int16_  = (qi::lexeme[qi::omit[qi::lit("int16(")]
						> qi::raw[qi::short_][qi::_val = phx::construct<std::string>(phx::begin(qi::_1), phx::end(qi::_1))]
						> qi::omit[qi::char_(')')]]);

		Int32_  = (qi::lexeme[qi::omit[qi::lit("int32(")]
						> qi::raw[qi::int_][qi::_val = phx::construct<std::string>(phx::begin(qi::_1), phx::end(qi::_1))]
						> qi::omit[qi::char_(')')]]);

		Float_  = (qi::lexeme[qi::omit[qi::lit("float(")]
						> qi::raw[qi::float_][qi::_val = phx::construct<std::string>(phx::begin(qi::_1), phx::end(qi::_1))]
						> qi::omit[qi::char_(')')]]);

		Double_ = (qi::lexeme[qi::omit[qi::lit("double(")]
						> qi::raw[qi::double_][qi::_val = phx::construct<std::string>(phx::begin(qi::_1), phx::end(qi::_1))]
						> qi::omit[qi::char_(')')]]);

		// One of the rule must be valid
		rule = qi::expect[(
				Int8_[qi::_val = phx::construct<std::pair<std::string, eOperandType>>(qi::_1, eOperandType::Int8)]    |
				Int16_[qi::_val = phx::construct<std::pair<std::string, eOperandType>>(qi::_1, eOperandType::Int16)]  |
				Int32_[qi::_val = phx::construct<std::pair<std::string, eOperandType>>(qi::_1, eOperandType::Int32)]  |
				Float_[qi::_val = phx::construct<std::pair<std::string, eOperandType>>(qi::_1, eOperandType::Float)]  |
				Double_[qi::_val = phx::construct<std::pair<std::string, eOperandType>>(qi::_1, eOperandType::Double)])];


		Int8_.name("int8(...)");
		Int16_.name("int16(...)");
		Int32_.name("int32(...)");
		Float_.name("float(...)");
		Double_.name("double(...)");
		rule.name("Valid type");
		qi::on_error(rule,
					 std::cerr << phx::val("Error. Expected ") << qi::_4 <<" at line " << line << ": \""
								  << phx::construct<std::string>(qi::_3,qi::_2) << "\"\n");
	}
