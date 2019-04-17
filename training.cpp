#include <boost/spirit/include/qi.hpp>
#include <string>
namespace qi = boost::spirit::qi;

#include "IOperand.hpp"

bool	checkLine(std::string &line)
{
	std::string::iterator it = line.begin();
	const auto char_number_ = [](const int &attr, auto &, bool &pass) {
		pass = (attr > -129 && attr < 128);
	};

	auto types = qi::lexeme[qi::lit("int8(") >> qi::int_[char_number_] >> qi::char_(')') |
							qi::lit("int16(") >> qi::short_ >> qi::char_(')')  |
							qi::lit("int32(") >> qi::int_ >> qi::char_(')')  |
							qi::lit("float(") >> qi::float_ >> qi::char_(')')  |
							qi::lit("double(") >> qi::double_ >> qi::char_(')') ];

	return qi::phrase_parse(it, line.end(),
								"push" >> types |
								"pop" |
								"dump" |
								"assert" >> types |
								"add" |
								"sub" |
								"mul" |
								"div" |
								"mod" |
								"print" |
								"exit",
								qi::space) && it == line.end();
}

int main()
{
	std::string line;

	while (true)
	{
		std::getline(std::cin, line);
		std::cout << checkLine(line) << std::endl;
	}
}
