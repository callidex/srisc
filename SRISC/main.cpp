#include <cstdio>
#include "parser.h"
#include <fstream>

int main(int argc, const char * argv[])
{
    printf("hello from SRISC!\n");

	if(argc<2)
	{
		printf("point me at a file to parse!\n");
		return 0;
	}
	std::ifstream t(argv[1], std::ios::binary);
	const std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	demo_stack_parser p;
	p.load_machine_code(str);


	while(p.parse_next())
	{

		p.dump_stack();
	}

    return 0;
}
