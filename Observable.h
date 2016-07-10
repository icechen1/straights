#ifndef _OBSERVABLE_
#define _OBSERVABLE_
#include "View.h"
#include <memory>
#include <vector>
#include <algorithm>
class Observable {
public:
	void subscribe(std::shared_ptr<View>);
	void unsubscribe(const std::shared_ptr<View>);
protected:
	void notify();
private:
	std::vector<std::shared_ptr<View>> observers_;
};

#endif