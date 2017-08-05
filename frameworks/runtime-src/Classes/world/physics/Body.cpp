#include <cocos2d_specifics.cpp>
#include <H/b2tojs.h>
#include <ScriptingCore.h>
#include <H/GameScene.h>

using namespace gm;

Body::Body(){
}
Body::~Body(){
}

Body *Body::create(b2Body *body, const std::string &script){
	Body *ret = new (std::nothrow) Body();

	if (ret && ret->init(body, script))
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);

	return ret;

}
bool Body::init(b2Body *body, const std::string &script){
	boxBody = body;
	body->SetUserData(this);

	auto c = ComponentJS::create(gm::path::body_components + script);

	if(c->getScriptObject()) log("%s component added", script.c_str());
	else log("%s component adding error", script.c_str());

	c->setName("bodyComponent");
	addComponent(c);
	jsComponent = c;

	return true;
}

void Body::setPosition(float x, float y){
	boxBody->SetTransform(b2Vec2(x/GSInst->getPhysWorldScale(), y/GSInst->getPhysWorldScale()), boxBody->GetAngle());
	setDrawPosition(x, y);
}	

void Body::setPosition(const Vec2& position)
{
	setPosition(position.x, position.y);
}

void Body::setRotation(float angle){
	boxBody->SetTransform(boxBody->GetPosition(), CC_DEGREES_TO_RADIANS(angle));
	setDrawRotation(angle);
}	
void Body::setDrawRotation(float angle){
	Node::setRotation(angle);
}

void Body::setDrawPosition(float x, float y){
	Node::setPosition(x, y);
}	

void Body::setDrawPosition(const Vec2& position)
{
	setDrawPosition(position.x, position.y);
}

void Body::draw(Renderer *renderer, const Mat4& transform, uint32_t flags) {
	//auto b2p = boxBody->GetPosition();
	//Node::setPosition(Vec2(b2p.x*GSInst->getPhysWorldScale(), b2p.y*GSInst->getPhysWorldScale()));
	//auto b2r = boxBody->GetAngle();
	//Node::setRotation(CC_RADIANS_TO_DEGREES(-b2r));

	Node::draw(renderer, transform, flags);
}
void Body::update(float fDelta)
{
	Node::update(fDelta);
}

void Body::onContactPreSolve(b2Contact *contact){
	if (JSObject *script = static_cast<JSObject*>(jsComponent->getScriptObject()))
	{
		jsval dataVal = INT_TO_JSVAL(contacts.size());
		JS::RootedValue retval(ScriptingCore::getInstance()->getGlobalContext());
		ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(script), "onContactPreSolve", 1, &dataVal, &retval);
	}
}
void Body::onContactBegin(b2Contact *contact){
	auto ref = BodyContact::create(contact);
	ref->retain();

	contacts.insert(std::pair<b2Contact*, BodyContact*>(contact, ref));

	if (JSObject *script = static_cast<JSObject*>(jsComponent->getScriptObject()))
	{
		jsval dataVal = INT_TO_JSVAL(contacts.size());
		JS::RootedValue retval(ScriptingCore::getInstance()->getGlobalContext());
		ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(script), "onContactBegin", 1, &dataVal, &retval);
	}
}
void Body::onContactEnd(b2Contact *contact){
	auto iter = contacts.find(contact);
	iter->second->release();

	contacts.erase(iter);

	if (JSObject *script = static_cast<JSObject*>(jsComponent->getScriptObject()))
	{
		jsval dataVal = INT_TO_JSVAL(contacts.size());
		JS::RootedValue retval(ScriptingCore::getInstance()->getGlobalContext());
		ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(script), "onContactEnd", 1, &dataVal, &retval);
	}
}

cocos2d::Vector<BodyContact*> Body::getContacts(){
	cocos2d::Vector<BodyContact*> ret;
	for(auto i : contacts)
		ret.pushBack(i.second);

	return ret;
}


ManifoldPoint *ManifoldPoint::create(const b2ManifoldPoint &point){
	ManifoldPoint *ret = new (std::nothrow) ManifoldPoint();

	if (ret && ret->init(point))
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);

	return ret;

}
bool ManifoldPoint::init(const b2ManifoldPoint &point){
	localPoint = Vec2(point.localPoint.x, point.localPoint.y);
	normalImpulse = point.normalImpulse;
	tangentImpulse = point.tangentImpulse;
}

cocos2d::Vector<ManifoldPoint*> BodyContact::getManifoldPoints(){
	Vector<ManifoldPoint*> points;
	auto b2points = contact->GetManifold()->points;
	for(int i = contact->GetManifold()->pointCount - 1;i > 0;i--){
		points.pushBack(ManifoldPoint::create(b2points[i]));
	}
	return points;
}
/*
void Body::onContact(BodyContact *contact){
	return;
	if (JSObject *script = static_cast<JSObject*>(jsComponent->getScriptObject()))
	{
		jsval dataVal = OBJECT_TO_JSVAL(js_get_or_create_jsobject<gm::BodyContact>(ScriptingCore::getInstance()->getGlobalContext(), (gm::BodyContact*)contact));
		JS::RootedValue retval(ScriptingCore::getInstance()->getGlobalContext());
		ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(script), "onContact", 1, &dataVal, &retval);
	}
}
*/
