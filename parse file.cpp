#include <iostream>
#include <sstream>
#include <cstddef>
#include <fstream>
#include <vector>
#include "IOperand.hpp"
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

template<typename IteratorT>
class SkipperGrammar : public qi::grammar<IteratorT>
{
public:
	SkipperGrammar()
			: SkipperGrammar::base_type(rule)
	{
		lineCommentRule = ';' >> *(qi::char_ -qi::eol) >> qi::eol;
		spaceRule = qi::space;
		rule = spaceRule | lineCommentRule;
	}

	qi::rule<IteratorT> lineCommentRule;
	qi::rule<IteratorT> spaceRule;
	qi::rule<IteratorT> rule;
};



int main()
{
	std::string line;

	while (true)
	{
		std::getline(std::cin, line);
		std::cout << parseLine(line) << std::endl;
	}
}
