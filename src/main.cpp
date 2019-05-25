#include <fstream>
#include "../Includes/Parser.hpp"
#include <errno.h>
#include <filesystem>

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

	if (errno || std::filesystem::is_directory(filename))
	{
		std::cerr << "File error: " << filename << ": " << strerror(errno ? errno : EISDIR) << std::endl;
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
			bool isConsoleInput = std::string("-") == argv[i];
			int  size = (isConsoleInput ? 7 : std::strlen(argv[i])) + 10; // The amount of '-' symbols
			if (argc > 2)
				std::cout << std::string(size, '-') << std::endl
						  << std::right << std::setw(size) << (isConsoleInput ? "Console" : argv[i]) << std::endl
						  << std::string(size, '-') << std::endl << std::flush;

			Parser parser = isConsoleInput ? Parser() : Parser(openFile(argv[i]));
			if (parser.parseInput(commands))
				execute(commands);
			else
				std::cerr.flush();
			commands.clear();
		}
}