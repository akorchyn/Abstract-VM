#pragma once

#include <boost/spirit/include/qi.hpp>
#include <string>

/*!
 * \ingroup parse
 */

/*!
 * \file
 * \brief Contain grammar of skipping.
 */

namespace spirit = boost::spirit;
namespace qi = spirit::qi;

template<typename IteratorT>
class SkipperGrammar : public qi::grammar<IteratorT> // ignoring '\t' ' ' '\n' symbols and comment "; ... \n
{
public:
	SkipperGrammar();
	~SkipperGrammar();

private:
	SkipperGrammar(SkipperGrammar const &x) = default;
	SkipperGrammar &operator=(SkipperGrammar const &x) = default;

	qi::rule<IteratorT> lineCommentRule; ///< Rule that handle comments (';*')
	qi::rule<IteratorT> spaceRule;///< Rule that handle whitespaces
	qi::rule<IteratorT> rule;///< Main rule
};

template<typename IteratorT>
SkipperGrammar<IteratorT>::~SkipperGrammar()
{
}

template<typename IteratorT>
SkipperGrammar<IteratorT>::SkipperGrammar()
		: SkipperGrammar::base_type(rule)
{
	lineCommentRule = qi::char_(';') >> *(qi::char_); // because i parse line by line. I just skip all chars after ';'
	spaceRule = qi::space;
	rule = qi::omit[spaceRule | lineCommentRule];
}