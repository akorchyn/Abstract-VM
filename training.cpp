#include <boost/spirit/include/qi.hpp>
#include <boost/bind.hpp>
#include <string>
#include <vector>
#include "IOperand.hpp"

namespace qi = boost::spirit::qi;

void	push(boost::fusion::vector<boost::variant<boost::fusion::vector<int, char>,
		boost::fusion::vector<short, char>, boost::fusion::vector<float, char>,
		boost::fusion::vector<double, char> >, boost::optional<std::vector<char, std::allocator<char> > >
> x)
{
	std::cout << boost::fusion::at_c<0>(x) << std::endl;
}
bool	parseLine(std::string &line)
{
	std::string::iterator it = line.begin();

	const auto char_number_ = [](const int &attr, auto &, bool &pass) {
		pass = (attr > -129 && attr < 128);
	}; // lambda to check that number in char limits


	//Rule to parse supported data types
	auto types = qi::lexeme[qi::lit("int8(") >> qi::int_[char_number_] >> qi::char_(')') |
						 	qi::lit("int16(") >> qi::short_ >> qi::char_(')')  |
						 	qi::lit("int32(") >> qi::int_ >> qi::char_(')')  |
						 	qi::lit("float(") >> qi::float_ >> qi::char_(')')  |
						 	qi::lit("double(") >> qi::double_ >> qi::char_(')') ];

	auto comment = ';' >> *qi::char_; // Rule to parse commentary

	return qi::phrase_parse(it, line.end(),
								comment |
								("push" >> types >> -comment) [boost::bind(&push, _1)]|
								"pop" >> -comment |
								"dump" >> -comment |
								"assert" >> types >> -comment |
								"add" >> -comment |
								"sub" >> -comment |
								"mul" >> -comment |
								"div" >> -comment |
								"mod" >> -comment |
								"print" >> -comment |
								"exit" >> -comment |
								"",
								qi::space) && it == line.end();
}

int main()
{
	std::string line;

	while (true)
	{
		std::getline(std::cin, line);
		std::cout << parseLine(line) << std::endl;
	}
}
