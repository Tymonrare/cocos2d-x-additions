#include "H/ContactListener.h"
#include "H/Source.h"
#include <H/b2tojs.h>

PhysWorldContactListener::PhysWorldContactListener(){
}


PhysWorldContactListener::~PhysWorldContactListener()
{
}
b2Contact *ccontact;
void PhysWorldContactListener::BeginContact(b2Contact * contact)
{
	void *adata = contact->GetFixtureA()->GetBody()->GetUserData(),
		*bdata = contact->GetFixtureB()->GetBody()->GetUserData();

	if (gm::Body *body = static_cast<gm::Body*>(adata))
		body->onContactBegin(contact);
	if (gm::Body *body = static_cast<gm::Body*>(bdata))
		body->onContactBegin(contact);
}

void PhysWorldContactListener::EndContact(b2Contact * contact)
{
	void *adata = contact->GetFixtureA()->GetBody()->GetUserData(),
		*bdata = contact->GetFixtureB()->GetBody()->GetUserData();

	if (gm::Body *body = static_cast<gm::Body*>(adata))
		body->onContactEnd(contact);
	if (gm::Body *body = static_cast<gm::Body*>(bdata))
		body->onContactEnd(contact);
}

void PhysWorldContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	void *adata = contact->GetFixtureA()->GetBody()->GetUserData(),
		*bdata = contact->GetFixtureB()->GetBody()->GetUserData();

	if (gm::Body *body = static_cast<gm::Body*>(adata))
		body->onContactPreSolve(contact);
	if (gm::Body *body = static_cast<gm::Body*>(bdata))
		body->onContactPreSolve(contact);
}
