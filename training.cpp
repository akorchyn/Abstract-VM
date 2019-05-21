#include <fstream>
#include "Parser.hpp"
#include <errno.h>

void	execute(Commands &commands)
{
	TypeStack stack;

	try
	{
		for (const auto &directive : commands)
			if (!directive->execute(stack))
				break;
	}
	catch (AbstractRuntimeException &error)
	{
		std::cerr << error.what() << std::endl;
	}

}

std::unique_ptr<std::istream> openFile(const std::string &filename)
{
	std::unique_ptr<std::ifstream>		file(new std::ifstream(filename));

	if (errno)
	{
		std::cerr << "File error: " << filename << ": " << strerror(errno) << std::endl;
		errno = 0;
		return nullptr;
	}
	return file;
}

int main(int argc, char **argv)
{
	std::ios::sync_with_stdio(false);
	Commands 	commands;

	if (argc == 1 && Parser().parseInput(commands))
		execute(commands);
	else
		for (int i = 1; i < argc; i++)
		{
			Parser	parser(std::move(openFile(argv[i])));

			if (parser.parseInput(commands))
				execute(commands);
			commands.clear();
		}
}
