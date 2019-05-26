#include <iostream>
#include <fstream>

// visit https://turingmachinesimulator.com/ to check solutions.
// 1. only single-letter statements are used on the site.
// 2. use '_' symbol for blank spaces implementation.

int main()
{
	std::cout << "Enter file name to convert in \"file_name\".out format\n";
	std::string input;
	std::cin >> input;
	std::ifstream in;
	in.open(input);
	std::ofstream out;
	out.open("converted_" + input);
	out << "Name: " << input.substr(0, input.size() - 4) << '\n';
  	std::string start;
  	getline(in, start);
  	out << "init: " << start.substr(7,start.length()) << '\n';
  	std::string reject, accept, blank;
  	getline(in, accept);
  	out << accept << '\n';
  	getline(in, reject);
  	//out << reject << '\n';
  	getline(in, blank);
  	//out << blank << '\n';
  	std::string state;
  	while (in >> state)
	{
		out << "\n";
		out << state << ',';
		in >> state;
		out << state << "\n";
		in >> state;
		in >> state;
		out << state << ',';
		in >> state;
		out << state << ',';
		in >> state;
		if (state == "^") state = "-";
		out << state << "\n";
  	}
}
