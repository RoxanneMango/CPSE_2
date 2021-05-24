#ifndef COMMAND_LIST_H
#define COMMAND_LIST_H

/*

#include <memory>
#include <vector>

#include "command.h"

class CommandList
{
private:
	unsigned int max;
	unsigned int sizee;

	int index;
	int num;
	
	bool isDecremented;
	
public:
	std::vector<Command *> list;
	
	CommandList(unsigned int max) : list(max+1, NULL), max(max), sizee(0), index(0), num(0), isDecremented(false)
	{}
	~CommandList()
	{
		reset();
	}
	
	PlaceCommand * get()
	{ 
		return list[index ? index-1 : 0];
	}
	
	unsigned int size()
	{
		return num;
	}
	
	void push_back(PlaceCommand * command)
	{
		if(isDecremented)
		{
			isDecremented = false;
		}
		
		if( (index >= max) && (index >= sizee) )
		{
			index = 0;
		}
		
		list[index] = command;
		
		if(sizee < max)
		{
			sizee += 1;
			index = sizee;
			num = sizee;
		}
		else
		{
			if(index < sizee)
			{
				index += 1;
			}
			if(num < max)
			{
				num += 1;
			}
		}
	}
	
	void reset()
	{
		for(PlaceCommand *& command : list)
		{
			free(command);
		}
		isDecremented = false;
		sizee = 0;
		index = 0;
		num = 0;
	}
	
	bool isBegin()
	{ 
		return num <= 0; 
	}
	bool isEnd()
	{
		return num >= sizee;
	}
	
	int operator++(int)
	{
		index = index < sizee ? index+1 : 1;
		num++;
		sizee++;
		return index;
	}
	int operator--(int)
	{
		isDecremented = true;
		index = index ? index-1 : sizee-1;
		num--;
		sizee--;
		return index;
	}
};

*/

#endif // COMMAND_LIST_H