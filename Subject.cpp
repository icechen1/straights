#include "Subject.h"
using namespace std;

// requires: view must inherit from Observer
// modifies: observer list
// ensures: view is now an observer of the subject
void Subject::subscribe(Observer* view)
{
	// check if view is already a subscriber
	if (std::find(observers_.begin(), observers_.end(), view) != observers_.end()) {
		return;
	}
	observers_.push_back(view);
}

// requires: view must inherit from Observer and is currently subscribed to this subject
// modifies: observer list
// ensures: view is now not an observer of the subject
void Subject::unsubscribe(const Observer* view)
{
	observers_.erase(remove(observers_.begin(), observers_.end(), view), observers_.end());
}

// ensures: all observers gets notified of changesw via update()
void Subject::notify()
{
	for (Observer* view : observers_) {
		view->update();
	}
}
