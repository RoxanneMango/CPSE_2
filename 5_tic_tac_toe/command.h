#ifndef COMMAND_H
#define COMMAND_H

/*

template<typename A, typename B>
class Command
{
public:
	A actor;
	B reactor;
	int index;

	Command(A actor, B reactor, int index) : actor(actor), reactor(reactor), index(index)
	{}
	virtual ~Command()
	{}
	
	virtual void undo() = 0;
	virtual void redo() = 0;
};

class PlaceCommand : public Command<char, char *>
{
public:
	PlaceCommand(char actor, char * reactor, int index) :  Command<char,char *>(actor, reactor, index)
	{}
	virtual ~PlaceCommand()
	{}
	void undo() override { reactor[index] = ' '; }
	void redo() override { reactor[index] = actor; }
};

*/

#endif // COMMAND_H