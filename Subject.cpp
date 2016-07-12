#include "Subject.h"
using namespace std;

void Subject::subscribe(Observer* view)
{
	// check if view is already a subscriber
	if (std::find(observers_.begin(), observers_.end(), view) != observers_.end()) {
		return;
	}
	observers_.push_back(view);
}

void Subject::unsubscribe(const Observer* view)
{
	observers_.erase(remove(observers_.begin(), observers_.end(), view), observers_.end());
}

void Subject::notify()
{
	for (Observer* view : observers_) {
		view->update();
	}
}
