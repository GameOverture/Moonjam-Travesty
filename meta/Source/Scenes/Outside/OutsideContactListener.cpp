#include "pch.h"
#include "OutsideContactListener.h"
#include "Player.h"
#include "Outside.h"

OutsideContactListener::OutsideContactListener()
{
}

/*virtual*/ OutsideContactListener::~OutsideContactListener()
{
}

/// Called when two fixtures begin to touch.
/*virtual*/ void OutsideContactListener::BeginContact(b2Contact *contact)
{
	IHyBody2d *pBodyA = reinterpret_cast<IHyBody2d *>(contact->GetFixtureA()->GetUserData().pointer);
	IHyBody2d *pBodyB = reinterpret_cast<IHyBody2d *>(contact->GetFixtureB()->GetUserData().pointer);

	IHyBody2d *pPlayer = nullptr;
	if(pBodyA->GetTag() == TAG_Player)
		pPlayer = pBodyA;
	if(pBodyB->GetTag() == TAG_Player)
		pPlayer = pBodyB;

	IHyBody2d *pGround = nullptr;
	if(pBodyA->GetTag() == TAG_Ground)
		pGround = pBodyA;
	if(pBodyB->GetTag() == TAG_Ground)
		pGround = pBodyB;

	IHyBody2d *pCum = nullptr;
	if(pBodyA->GetTag() == TAG_Cum)
		pCum = pBodyA;
	if(pBodyB->GetTag() == TAG_Cum)
		pCum = pBodyB;

	if(pPlayer && pGround)
		m_EventQueue.push(PHYSEVENT_OnGround);
	if(pPlayer && pCum)
		m_EventQueue.push(PHYSEVENT_EnterCum);
}

/// Called when two fixtures cease to touch.
/*virtual*/ void OutsideContactListener::EndContact(b2Contact *contact) /*override*/
{
	IHyBody2d *pBodyA = reinterpret_cast<IHyBody2d *>(contact->GetFixtureA()->GetUserData().pointer);
	IHyBody2d *pBodyB = reinterpret_cast<IHyBody2d *>(contact->GetFixtureB()->GetUserData().pointer);

	IHyBody2d *pPlayer = nullptr;
	if(pBodyA->GetTag() == TAG_Player)
		pPlayer = pBodyA;
	if(pBodyB->GetTag() == TAG_Player)
		pPlayer = pBodyB;

	IHyBody2d *pGround = nullptr;
	if(pBodyA->GetTag() == TAG_Ground)
		pGround = pBodyA;
	if(pBodyB->GetTag() == TAG_Ground)
		pGround = pBodyB;

	IHyBody2d *pCum = nullptr;
	if(pBodyA->GetTag() == TAG_Cum)
		pCum = pBodyA;
	if(pBodyB->GetTag() == TAG_Cum)
		pCum = pBodyB;

	if(pPlayer && pGround)
		m_EventQueue.push(PHYSEVENT_LeaveGround);
	if(pPlayer && pCum)
		m_EventQueue.push(PHYSEVENT_LeaveCum);
}

/// This is called after a contact is updated. This allows you to inspect a
/// contact before it goes to the solver. If you are careful, you can modify the
/// contact manifold (e.g. disable contact).
/// A copy of the old manifold is provided so that you can detect changes.
/// Note: this is called only for awake bodies.
/// Note: this is called even when the number of contact points is zero.
/// Note: this is not called for sensors.
/// Note: if you set the number of contact points to zero, you will not
/// get an EndContact callback. However, you may get a BeginContact callback
/// the next step.
/*virtual*/ void OutsideContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) /*override*/
{
}

/// This lets you inspect a contact after the solver is finished. This is useful
/// for inspecting impulses.
/// Note: the contact manifold does not include time of impact impulses, which can be
/// arbitrarily large if the sub-step is small. Hence the impulse is provided explicitly
/// in a separate data structure.
/// Note: this is only called for contacts that are touching, solid, and awake.
/*virtual*/ void OutsideContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) /*override*/
{
}

void OutsideContactListener::ProcessQueue(Outside &outsideRef)
{
	while(m_EventQueue.empty() == false)
	{
		EventType eEventRef = m_EventQueue.front();
		switch(eEventRef)
		{
		case PHYSEVENT_OnGround:	outsideRef.m_PlayerRef.OnTouchGround(); break;
		case PHYSEVENT_LeaveGround:	outsideRef.m_PlayerRef.OnLeaveGround(); break;
		case PHYSEVENT_EnterCum:	outsideRef.m_PlayerRef.SetMoveModifer(0.1f); break;
		case PHYSEVENT_LeaveCum:	outsideRef.m_PlayerRef.SetMoveModifer(1.0f); break;
		}
		m_EventQueue.pop();
	}
}
