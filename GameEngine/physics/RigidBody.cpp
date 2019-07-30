#include "RigidBody.h"
#include "PhysicsEngine.h"

RigidBody::RigidBody(GameObject * _g) : m_gameObject(_g) {
}

RigidBody::~RigidBody() {
	PhysicsEngine::getInstance().deleteRigidBody(this);
}
