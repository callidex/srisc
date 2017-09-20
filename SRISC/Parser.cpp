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


StackParser::StackParser(): _currentInstruction(0)
{
	_innerStack.empty();
}


StackParser::~StackParser()
{
}



void StackParser::dump_stack()
{
	std::stack<char> temp;
	while (!_innerStack.empty()) {
		char top = _innerStack.top(); _innerStack.pop();
		std::cout << "[" << std::hex <<  top << "]";
		temp.push(top);
	}
	while (!temp.empty()) {
		char top = temp.top(); temp.pop();
		_innerStack.push(top);
	}
}

void StackParser::load_machine_code(const std::string str)
{
	std::cout << "Loading " << std::endl;
	_buffer = str;
	_buffer_pos = _buffer.begin();

	std::cout << "BUFFER" << std::endl << _buffer << std::endl;
}
 
bool StackParser::parse_next()
{
	std::cout << "Parsing "<< std::endl;
	if (_buffer_pos == _buffer.end()) return false;
	
	_currentInstruction = *_buffer_pos;
	std::cout << std::hex << _currentInstruction << " ";


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
			const auto a = _innerStack.top();
			_innerStack.pop();
			const auto b = _innerStack.top();
			_innerStack.push(static_cast<char>(a + b));
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
 
void StackParser::Push(char item)
{
	std::cout << "Pushing " + item << std::endl;
	if(_innerStack.size()<_maxStack)
	{
		_innerStack.push(item);
		return;

	}
	throw std::exception();
}
