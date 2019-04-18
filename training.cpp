#include <boost/spirit/include/qi.hpp>
#include <boost/bind.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/iterator.hpp>
#include <string>
#include <vector>

#include "IOperand.hpp"

namespace qi = boost::spirit::qi;


class ASTValue;
class ASTObject;
class ASTArray;

using ASTVariant = boost::variant<
		boost::recursive_wrapper<ASTObject>,
		boost::recursive_wrapper<ASTArray>,
		std::string>;

using ASTAttributeMapT = std::map<std::string, ASTValue>;
using ASTValuesT	   = std::vector<ASTValue>;





int main()
{
	std::string line;

	while (true)
	{
		std::getline(std::cin, line);
//		std::cout << parseLine(line) << std::endl;
	}
}
