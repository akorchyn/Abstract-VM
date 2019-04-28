//#include <boost/bind.hpp>
#include <string>
#include <iostream>
//#include <boost/phoenix/phoenix.hpp>
//#include "AbstractCompilationException.hpp"
//#include "Grammar/SkipperGrammar.hpp"
//#include "Grammar/CommandGrammar.hpp"
//
//namespace spirit = boost::spirit;
//namespace qi =     spirit::qi;
//namespace phx =    boost::phoenix;
//
//using     Commands = std::vector<std::string>;
//
//bool	parseLine(std::string &line)
//{
//	std::string::iterator															it = line.begin();
//	SkipperGrammar<std::string::iterator>											Spaces;
//	CommandGrammar<std::string::iterator, SkipperGrammar<std::string::iterator> >	CommandGrammar;
//	return (qi::phrase_parse(it, line.end(), CommandGrammar, Spaces) && it == line.end());
//}

#include "IOperandGenerator.hpp"
int main(int , char **)
{
	std::string line;
	IOperandGenerator	gen;
//	Commands commands;

	while (!std::cin.eof())
	{
		std::getline(std::cin, line);
		const IOperand	*x = gen.createOperand(eOperandType::Int32, line);
		std::getline(std::cin, line);
		const IOperand	*y = gen.createOperand(eOperandType::Int32, line);

		const IOperand *z = *x % *y;
		std::cout << z->toString() << std::endl;
	}
}
