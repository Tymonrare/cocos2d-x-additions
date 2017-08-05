#pragma once
#include <Box2D/Box2D.h>
#include <H/Source.h>

struct ContactPoint
{
	b2Fixture* fixtureA;
	b2Fixture* fixtureB;
	b2Vec2 normal;
	b2Vec2 position;
	b2PointState state;
	float32 normalImpulse;
	float32 tangentImpulse;
	float32 separation;
};

const int32 k_maxContactPoints = 2048;

class PhysWorldContactListener : public b2ContactListener
{
public:
	PhysWorldContactListener();
	~PhysWorldContactListener();

	virtual void JointDestroyed(b2Joint* joint) { B2_NOT_USED(joint); }

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) { B2_NOT_USED(contact); }

private:
	int32 m_pointCount;
	ContactPoint m_points[k_maxContactPoints];
	b2Profile m_maxProfile, m_totalProfile;
};


