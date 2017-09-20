#include <cstdio>
#include "Parser.h"
#include <fstream>

int main()
{
    printf("hello from SRISC!\n");

	std::ifstream t("file.txt", std::ios::binary);
	const std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	DemoStackParser p;
	p.load_machine_code(str);


	while(p.parse_next())
	{

		p.dump_stack();
	}

    return 0;
}











