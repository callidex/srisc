#include "Parser.h"
#include <stack>
#include <iostream>

enum instruction_set
{
	__LIT = 0x00,
	__ADD = 0x01,
	__DIV = 0x02,
	__MUL = 0x03,
	__MIN = 0x04
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
	
	_currentInstruction = *_buffer_pos;
	std::cout << " " << int(_currentInstruction) << " ";


	switch(_currentInstruction)
	{
		case __LIT:
			std::cout << "Literal->";
			++_buffer_pos;
			_innerStack.push(*_buffer_pos);
			
		break;

		case __ADD:  // 
		{
			std::cout << "Add->";
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
		default:
			std::cout << std::endl << "Unknown instruction " << std::endl;
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
