#ifndef _SUBJECT_
#define _SUBJECT_
#include "Observer.h"
#include <memory>
#include <vector>
#include <algorithm>

class Subject {
public:
	void subscribe(std::shared_ptr<Observer>);
	void unsubscribe(const std::shared_ptr<Observer>);
protected:
	void notify();
private:
	std::vector<std::shared_ptr<Observer>> observers_;
};

#endif