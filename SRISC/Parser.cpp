#include "parser.h"
#include <stack>
#include <iostream>

enum instruction_set
{
	__LIT = 0x00,
	__ADD = 0x01,
	__DIV = 0x02,
	__MUL = 0x03,
	__MIN = 0x04,
	__DUP = 0x05
};

// Arbitrary set for overloading
enum generic_instruction_set
{	
	__I0 = 0x10,
	__I1 = 0x11,
	__I2 = 0x12,
	__I3 = 0x13,	
	__I4 = 0x14,
	__I5 = 0x15,
	__I6 = 0x16,
	__I7 = 0x17,
	__I8 = 0x18,
	__I9 = 0x19,
	__IA = 0x20,
	__IB = 0x21,	
	__IC = 0x22,
};



stack_parser::stack_parser(): _currentInstruction(0)
{
	_innerStack.empty();
}


stack_parser::~stack_parser()
{
}



void stack_parser::dump_stack()
{
	std::stack<char> temp;
	while (!_innerStack.empty()) {
		const auto top = _innerStack.top(); _innerStack.pop();
		std::cout << "[" << int(top)<< "]";
		temp.push(top);
	}
	while (!temp.empty()) {
		const auto top = temp.top(); temp.pop();
		_innerStack.push(top);
	}
	std::cout << std::endl;
}


void stack_parser::load_machine_code(const std::string str)
{
	std::cout << "Loading " << std::endl;
	_buffer = str;
	_buffer_pos = _buffer.begin();

}
 
bool stack_parser::parse_next()
{
	if (_buffer_pos == _buffer.end()) return false;
	
	switch(*_buffer_pos)
	{
		case __LIT:
			std::cout << "Literal->" << std::endl;
			++_buffer_pos;
			_innerStack.push(*_buffer_pos);
			
		break;
		case __DUP:
		{
			std::cout << "Duplicate->" << std::endl;
			_innerStack.push(_innerStack.top());		
			__Dup(_innerStack.top());
		}

			break;


		case __ADD:  // 
		{
			std::cout << "Add->" << std::endl;
			const unsigned char a = _innerStack.top();
			_innerStack.pop();
			const unsigned char b = _innerStack.top();
			_innerStack.pop();
			const unsigned char c = (a + b);
			_innerStack.push(c);
			// just for testing, we've already done the work
			__Add(a, b);
		}
			break;


		case __MIN:
			{
			std::cout << "Minus->" << std::endl;
			const unsigned char a = _innerStack.top();
			_innerStack.pop();
			const unsigned char b = _innerStack.top();
			_innerStack.pop();
			const unsigned char c = (b - a);
			_innerStack.push(c);
			__Min(a, b);
			}
			break;
		default:
			printf("Unknown instruction  %x", *_buffer_pos);
			break;
	}
	++_buffer_pos;

	return true;

}
 
void stack_parser::Push(unsigned char item)
{
	std::cout << "Pushing " + item << std::endl;
	if(_innerStack.size()<_maxStack)
	{
		_innerStack.push(item);
		return;

	}
	throw std::exception();
}
