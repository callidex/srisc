#pragma once
#include <iterator>
#include <stack>
#include <iostream>

class StackParser
{
public:
	StackParser();
	virtual ~StackParser();
	
	void load_machine_code(std::string str);
	bool parse_next();

	void dump_stack();
 

	virtual void __Add(char a, char b) = 0;


private: 
	const size_t _maxStack = 10;
	void Push(char item);
	std::stack<char> _innerStack;
	std::string _buffer;
	std::string::iterator _buffer_pos;
	char _currentInstruction;



};


class DemoStackParser : public StackParser
{
public:
	void __Add(char a, char b) override
	{
		// this will get called when the base parser has done and is ready
		std::cout << "Add called with " << std::dec << a << " " << b << std::endl;

	}
	//void __Div(char a, char b) override;
	//void __Mul(char a, char b) override;
	//void __Min(char a, char b) override;
	~DemoStackParser() {};
};
