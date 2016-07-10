#ifndef _OBSERVABLE_
#define _OBSERVABLE_
#include "View.h"
#include <memory>
class Observable {
public:
	void subscribe(std::shared_ptr<View>);
	void unsubscribe(const std::shared_ptr<View>);
protected:
	void notify();
};

#endif