#include <string>
#include <iostream>
#include "IOperandGenerator.hpp"
//#include "Grammar/CommandGrammar.hpp"
//#include "Grammar/SkipperGrammar.hpp"

//bool	parseLine(std::string &line, Commands &commands)
//{
//	std::string::iterator															it = line.begin();
//	SkipperGrammar<std::string::iterator>											Spaces;
//	CommandGrammar<std::string::iterator, SkipperGrammar<std::string::iterator> >	CommandGrammar{commands};
//	return (qi::phrase_parse(it, line.end(), CommandGrammar, Spaces) && it == line.end());
//}
#include <vector>s
#include "Operations/Division.hpp"

int main(int , char **)
{
	std::ios::sync_with_stdio(false);
	std::string line;
	TypeStack	st;
	IOperandGenerator	gen;

	if (!std::cin.eof())
	{
		std::getline(std::cin, line);
		st.push_back(gen.createOperand(eOperandType::Int16, "44"));
		st.push_back(gen.createOperand(eOperandType::Int32, "33"));
		Division(5).execute(st);
		std::cout << st.back()->toString() << "   " << static_cast<int>(st.back()->getType()) << std::endl;
	}
}
