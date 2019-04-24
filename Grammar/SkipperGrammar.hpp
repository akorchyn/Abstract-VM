#ifndef ABSTRACTVM_SKIPPERGRAMMAR_HPP
#define ABSTRACTVM_SKIPPERGRAMMAR_HPP

#include <boost/spirit/include/qi.hpp>

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

	qi::rule<IteratorT> lineCommentRule;
	qi::rule<IteratorT> spaceRule;
	qi::rule<IteratorT> rule;
};

template<typename IteratorT>
SkipperGrammar<IteratorT>::~SkipperGrammar()
{
}

template<typename IteratorT>
SkipperGrammar<IteratorT>::SkipperGrammar()
		: SkipperGrammar::base_type(rule)
{
	lineCommentRule = qi::omit[qi::char_(';') >> *(qi::char_)];
	spaceRule = qi::space;
	rule = spaceRule | lineCommentRule;
}

#endif
