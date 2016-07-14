#ifndef _OBSERVER_
#define _OBSERVER_

// implementation of the observer pattern, must be inherited by view
class Observer {
public:
	virtual void update() = 0; // abstract method called by subject on notify
};

#endif