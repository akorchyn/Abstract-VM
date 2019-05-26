#pragma once

#include "SkipperGrammar.hpp"
#include "../IOperand.hpp"
#include <boost/phoenix.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <memory>

/*!
 * \ingroup parse
 */

/*!
 * \file
 * \brief contain grammar of arguments.
 */

namespace spirit = boost::spirit;
namespace qi =     spirit::qi;
namespace phx =    boost::phoenix;

/*!
 * @tparam IteratorT, SkipperT same as in CommandGrammar.hpp
 *
 * \brief Parse arguments.
 *
 * This grammar parse arguments, check valid and return string value of type.
 *
 * \warning Really big numbers of float or double is parsed only in exponent form.(1e180) It is Spirit feature.
 */

template<typename IteratorT, typename SkipperT>
class ValueGrammar
: public qi::grammar<IteratorT, std::pair<std::string, eOperandType>(), SkipperT> // Grammar to parse types
{
public:
	ValueGrammar(int line);
	~ValueGrammar();
	ValueGrammar(ValueGrammar const &x) = delete;
	ValueGrammar &operator=(ValueGrammar const &x) = delete;

	qi::rule<IteratorT, std::string(), SkipperT> Int8_; ///< Parse numeric char value
	qi::rule<IteratorT, std::string(), SkipperT> Int16_; ///< Parse numeric short value
	qi::rule<IteratorT, std::string(), SkipperT> Int32_; ///< Parse numeric int value
	qi::rule<IteratorT, std::string(), SkipperT> Float_; ///< Parse numeric float value
	qi::rule<IteratorT, std::string(), SkipperT> Double_; ///< Parse numeric double value
	qi::rule<IteratorT, std::pair<std::string,eOperandType>(), SkipperT> rule; ///< Uses all previous rules to parse any argument.
};


template<typename IteratorT, typename SkipperT>
ValueGrammar<IteratorT, SkipperT>::~ValueGrammar()
{
}

template<typename IteratorT, typename SkipperT>
ValueGrammar<IteratorT, SkipperT>::ValueGrammar(int line)
			: ValueGrammar::base_type(rule, "Types Grammar")
	{


		/*
		 * How work any of my argument rule
		 * We parse type name (int8(, int16(...)
		 * then type(short, int...)
		 * if ok, we get string representation of type and set it to return value.
		 * then check closing brackets and all after.
		 * If all ok. We return this value, other way parser throws exception.
		 */
		Int8_   = qi::lexeme[qi::omit[qi::lit("int8(")]
						> qi::raw[qi::int_[qi::_pass = (qi::_1 > -129 && qi::_1 < 128)]][qi::_val = phx::construct<std::string>(phx::begin(qi::_1), phx::end(qi::_1))]
						> qi::omit[qi::char_(')')]]; // Because we haven't parser to check char as number. We parse as int and check range

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

		// qi::expect, because one of the rule muse be valid.
		rule = qi::expect[(
				Int8_[qi::_val = phx::construct<std::pair<std::string, eOperandType>>(qi::_1, eOperandType::Int8)]    |
				Int16_[qi::_val = phx::construct<std::pair<std::string, eOperandType>>(qi::_1, eOperandType::Int16)]  |
				Int32_[qi::_val = phx::construct<std::pair<std::string, eOperandType>>(qi::_1, eOperandType::Int32)]  |
				Float_[qi::_val = phx::construct<std::pair<std::string, eOperandType>>(qi::_1, eOperandType::Float)]  |
				Double_[qi::_val = phx::construct<std::pair<std::string, eOperandType>>(qi::_1, eOperandType::Double)])];
		// if one of the rules is correct we create pair<value(std::string), type(eOperandType)> and return it.


		Int8_.name("int8(...)");
		Int16_.name("int16(...)");
		Int32_.name("int32(...)");
		Float_.name("float(...)");
		Double_.name("double(...)");
		rule.name("Valid type");
		qi::on_error(rule,
					 std::cerr << phx::val("Error. Expected ") << qi::_4 <<" at line " << line << ": \""
								  << phx::construct<std::string>(qi::_3,qi::_2) << "\"\n");
		// qi::_2 - is iterator to end.
		// qi::_3 - is iterator where parse failed.
		// qi::_4 - is string what expected.
	}
