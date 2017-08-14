#pragma once
#include <H/Source.h>
#include <H/GameScene.h>

namespace gm{

class BodyContact;
class Vec2Position;

class Body : public cocos2d::Node
{
	public:
		static Body *create(b2Body *body, const std::string &script);

		//game methods
		//transforms
		virtual void setPosition(const Vec2& position) override;
		virtual void setPosition(float x, float y) override;

		virtual void setRotation(float angle) override;

		//only for node, box body will not affected
		void setDrawPosition(const Vec2& position);
		void setDrawPosition(float x, float y);

		void setDrawRotation(float angle);

		//state
		virtual void update(float fDelta) override;
		virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;

		//misc
		inline b2Body *getB2Body(){return boxBody;};
		inline ComponentJS *getComponentJS(){return jsComponent;};

		//physics
		void onContactPreSolve(b2Contact *contact);
		void onContactBegin(b2Contact *contact);
		void onContactEnd(b2Contact *contact);

		//wrappers to b2Body methods
		//TODO: move definations in another place
		inline void setLinearVelocity(const Vec2& v)
				{boxBody->SetLinearVelocity(b2Vec2(v.x/GSInst->getPhysWorldScale(), v.y/GSInst->getPhysWorldScale()));};
		inline Vec2 getLinearVelocity()
				{auto v = boxBody->GetLinearVelocity(); return Vec2(v.x*GSInst->getPhysWorldScale(), v.y*GSInst->getPhysWorldScale());};
		inline void setAngularVelocity(float omega)
				{boxBody->SetAngularVelocity(CC_DEGREES_TO_RADIANS(omega));};
		inline float getAngularVelocity()
				{ return CC_RADIANS_TO_DEGREES(boxBody->GetAngularVelocity());};
		inline void applyForce(const Vec2& force, const Vec2& point)
				{ boxBody->ApplyForce(b2Vec2(force.x/GSInst->getPhysWorldScale(), force.y/GSInst->getPhysWorldScale()), b2Vec2(point.x/GSInst->getPhysWorldScale(), point.y/GSInst->getPhysWorldScale()), true);};
		inline void applyForceToCenter(const Vec2& force)
				{ boxBody->ApplyForceToCenter(b2Vec2(force.x/GSInst->getPhysWorldScale(), force.y/GSInst->getPhysWorldScale()), true);};
		inline void applyTorque(float32 torque)
				{ boxBody->ApplyTorque(CC_DEGREES_TO_RADIANS(torque), true);};
		inline void applyLinearImpulse(const Vec2& impulse, const Vec2& point)
				{ boxBody->ApplyLinearImpulse(b2Vec2(impulse.x/GSInst->getPhysWorldScale(), impulse.y/GSInst->getPhysWorldScale()), b2Vec2(point.x/GSInst->getPhysWorldScale(), point.y/GSInst->getPhysWorldScale()), true);};
		inline void applyAngularImpulse(float impulse)
				{ boxBody->ApplyAngularImpulse(CC_DEGREES_TO_RADIANS(impulse), true);};
		inline void setFixedRotation(bool flag)
				{ boxBody->SetFixedRotation(flag);};

		cocos2d::Vector<BodyContact*> getContacts();

		cocos2d::Vector<Vec2Position*> getVertices();
	private:
		Body();
		~Body();

		bool init(b2Body *body, const std::string &script);

		b2Body *boxBody;
		ComponentJS *jsComponent;

		std::map<b2Contact*, BodyContact*> contacts;
	protected:

};

//For JS bind
class Vec2Position : public Ref, Vec2
{
	public:
		Vec2Position(float xx, float yy) : Vec2(xx, yy){};
		inline float getX(){return x;};
		inline float getY(){return y;};
};

class ManifoldPoint : public Ref
{
	public:
		static ManifoldPoint *create(const b2ManifoldPoint &point);

		Vec2 getLocalPoint();
		float getNormalImpulse();
		float getTangentImpulse();
	private:
		bool init(const b2ManifoldPoint &point);

		Vec2 localPoint;		///< usage depends on manifold type
		float normalImpulse;	///< the non-penetration impulse
		float tangentImpulse;	///< the friction impulse
};

class BodyContact : public Ref
{
	public:
		static BodyContact *create(b2Contact *contact);
		~BodyContact();

		//contact
		bool isTouching();
		void setEnabled(bool flag);
		bool isEnabled();
		void setFriction(float friction);
		float getFriction();
		void resetFriction();
		void setRestitution(float restitution);
		float getRestitution();
		void resetRestitution();
		void setTangentSpeed(float speed);
		float getTangentSpeed();
		Body *getBodyA();
		Body *getBodyB();
		Body *getAnotherBody(Body *own);

		//manifold
		Vec2 getLocalPoint();
		Vec2 getLocalNormal();
		cocos2d::Vector<ManifoldPoint*> getManifoldPoints();
	private:
		bool init(b2Contact *contact);
		BodyContact();
		b2Contact *contact;
};

inline bool BodyContact::isTouching(){
	return contact->IsTouching();
};
inline void BodyContact::setEnabled(bool flag){
	contact->SetEnabled(flag);
};
inline bool BodyContact::isEnabled(){
	return contact->IsEnabled();
};
inline void BodyContact::setFriction(float friction){
	contact->SetFriction(friction);
};
inline float BodyContact::getFriction(){
	return contact->GetFriction();
};
inline void BodyContact::resetFriction(){
	contact->ResetFriction();
};
inline void BodyContact::setRestitution(float restitution){
	contact->SetRestitution(restitution);
};
inline float BodyContact::getRestitution(){
	return contact->GetRestitution();
};
inline void BodyContact::resetRestitution(){
	contact->ResetFriction();
};
inline void BodyContact::setTangentSpeed(float speed){
	contact->SetTangentSpeed(speed);
};
inline float BodyContact::getTangentSpeed(){
	return contact->GetTangentSpeed();
};
inline Body *BodyContact::getBodyA(){
	Body *body = static_cast<Body*>(contact->GetFixtureA()->GetBody()->GetUserData());
	if(body) return body;

	return nullptr;
};
inline Body *BodyContact::getBodyB(){
	Body *body = static_cast<Body*>(contact->GetFixtureB()->GetBody()->GetUserData());
	if(body) return body;

	return nullptr;
};
inline Body *BodyContact::getAnotherBody(Body *own){
	if(getBodyA() == own) return getBodyB();
	if(getBodyB() == own) return getBodyA();

	return nullptr;
};

inline Vec2 BodyContact::getLocalPoint(){
	auto p = contact->GetManifold()->localPoint;
	return Vec2(p.x, p.y);
};

inline Vec2 BodyContact::getLocalNormal(){
	auto p = contact->GetManifold()->localNormal;
	return Vec2(p.x, p.y);
};

inline Vec2 ManifoldPoint::getLocalPoint(){
	auto p = localPoint;
	return Vec2(p.x, p.y);
};

inline float ManifoldPoint::getNormalImpulse(){
	return normalImpulse;
};

inline float ManifoldPoint::getTangentImpulse(){
	return tangentImpulse;
};
}
