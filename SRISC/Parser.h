#pragma once
#include <stack>
#include <iostream>

class stack_parser
{
public:
	stack_parser();
	virtual ~stack_parser();
	
	void load_machine_code(std::string str);
	bool parse_next();

	void dump_stack();
 

	virtual void __Add(unsigned char a, unsigned char b) = 0;
	virtual void __Div(unsigned char a, unsigned char b) = 0;
	virtual void __Mul(unsigned char a, unsigned char b) = 0;
	virtual void __Min(unsigned char a, unsigned char b) = 0;


private: 
	const size_t _maxStack = 10;
	void Push(unsigned char item);
	std::stack<unsigned char> _innerStack;
	std::string _buffer;
	std::string::iterator _buffer_pos;
	char _currentInstruction;



};


class demo_stack_parser : public stack_parser
{
public:
	void __Add(unsigned char a, unsigned char b) override
	{
		// this will get called when the base parser has done and is ready
		std::cout << "Add called with " << int(a) << " " << int(b) << std::endl;

	}
	void __Div(unsigned char a, unsigned char b) override
	{
		std::cout << "Div called with " << int(a) << " " << int(b) << std::endl;

	}
	void __Mul(unsigned char a, unsigned char b) override
	{
		std::cout << "Mul called with " << int(a) << " " << int(b) << std::endl;

	}
	void __Min(unsigned char a, unsigned char b) override
	{
		std::cout << "Min called with " << int(a) << " " << int(b) << std::endl;

	}
	~demo_stack_parser() {};
};
