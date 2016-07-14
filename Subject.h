#ifndef _SUBJECT_
#define _SUBJECT_
#include "Observer.h"
#include <vector>
#include <algorithm>

// implementation of subject in observer pattern, inherited by model
class Subject {
public:
	void subscribe(Observer*); // subscribe an observer to model
	void unsubscribe(const Observer*); // unsubscribe
protected:
	void notify(); // called when model is updated
private:
	std::vector<Observer*> observers_; // internal list of subject observers
};

#endif