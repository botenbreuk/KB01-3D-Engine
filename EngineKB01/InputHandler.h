#ifndef __INPUTHANDLER_H__
#define __INPUTHANDLER_H__

class InputHandler
{
public:
	virtual ~InputHandler() = 0;
	virtual void InitInput() = 0;
};

#endif