#include <H/b2tojs.h>

using namespace gm;

BodyContact *BodyContact::create(b2Contact *contact){
	BodyContact *ret = new (std::nothrow) BodyContact();

	if (ret && ret->init(contact))
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);

	return ret;

}

bool BodyContact::init(b2Contact *contact){
	this->contact = contact;

	return true;
}

BodyContact::BodyContact(){
}
BodyContact::~BodyContact(){
}
