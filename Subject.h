#ifndef _SUBJECT_
#define _SUBJECT_
#include "Observer.h"
#include <vector>
#include <algorithm>

class Subject {
public:
	void subscribe(Observer*);
	void unsubscribe(const Observer*);
protected:
	void notify();
private:
	std::vector<Observer*> observers_;
};

#endif