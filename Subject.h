#ifndef _SUBJECT_
#define _SUBJECT_
#include "View.h"
#include <memory>
#include <vector>
#include <algorithm>

class Subject {
public:
	void subscribe(std::shared_ptr<View>);
	void unsubscribe(const std::shared_ptr<View>);
protected:
	void notify();
private:
	std::vector<std::shared_ptr<View>> observers_;
};

#endif