#include "Observable.h"
using namespace std;

void Observable::subscribe(shared_ptr<View>)
{
}

void Observable::unsubscribe(const shared_ptr<View>)
{
}

void Observable::notify()
{
}
