#include "Subject.h"
using namespace std;

void Subject::subscribe(shared_ptr<View> view)
{
	// check if view is already a subscriber
	if (std::find(observers_.begin(), observers_.end(), view) != observers_.end()) {
		return;
	}
	observers_.push_back(view);
}

void Subject::unsubscribe(const shared_ptr<View> view)
{
	observers_.erase(remove(observers_.begin(), observers_.end(), view), observers_.end());
}

void Subject::notify()
{
	for (shared_ptr<View> view : observers_) {
		view->update();
	}
}
