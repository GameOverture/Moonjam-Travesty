#include "pch.h"
#include "InsideContactListener.h"
#include "Player.h"
#include "Inside.h"

InsideContactListener::InsideContactListener()
{
}

/*virtual*/ InsideContactListener::~InsideContactListener()
{
}

/// Called when two fixtures begin to touch.
/*virtual*/ void InsideContactListener::BeginContact(b2Contact *contact)
{
	IHyBody2d *pBodyA = reinterpret_cast<IHyBody2d *>(contact->GetFixtureA()->GetUserData().pointer);
	IHyBody2d *pBodyB = reinterpret_cast<IHyBody2d *>(contact->GetFixtureB()->GetUserData().pointer);

	if(pBodyA->GetTag() == TAG_Computer || pBodyB->GetTag() == TAG_Computer)
		m_EventQueue.push(PHYSEVENT_EnterComputer);

	if(pBodyA->GetTag() == TAG_Kitchen || pBodyB->GetTag() == TAG_Kitchen)
		m_EventQueue.push(PHYSEVENT_EnterKitchen);
		
	if(pBodyA->GetTag() == TAG_Homework || pBodyB->GetTag() == TAG_Homework)
		m_EventQueue.push(PHYSEVENT_EnterHomework);

	if(pBodyA->GetTag() == TAG_Exit || pBodyB->GetTag() == TAG_Exit)
		m_EventQueue.push(PHYSEVENT_ExitHouse);
}

/// Called when two fixtures cease to touch.
/*virtual*/ void InsideContactListener::EndContact(b2Contact *contact) /*override*/
{
	IHyBody2d *pBodyA = reinterpret_cast<IHyBody2d *>(contact->GetFixtureA()->GetUserData().pointer);
	IHyBody2d *pBodyB = reinterpret_cast<IHyBody2d *>(contact->GetFixtureB()->GetUserData().pointer);

	if(pBodyA->GetTag() == TAG_Computer || pBodyB->GetTag() == TAG_Computer)
		m_EventQueue.push(PHYSEVENT_LeaveComputer);

	if(pBodyA->GetTag() == TAG_Kitchen || pBodyB->GetTag() == TAG_Kitchen)
		m_EventQueue.push(PHYSEVENT_LeaveKitchen);

	if(pBodyA->GetTag() == TAG_Homework || pBodyB->GetTag() == TAG_Homework)
		m_EventQueue.push(PHYSEVENT_LeaveHomework);
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
/*virtual*/ void InsideContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) /*override*/
{
}

/// This lets you inspect a contact after the solver is finished. This is useful
/// for inspecting impulses.
/// Note: the contact manifold does not include time of impact impulses, which can be
/// arbitrarily large if the sub-step is small. Hence the impulse is provided explicitly
/// in a separate data structure.
/// Note: this is only called for contacts that are touching, solid, and awake.
/*virtual*/ void InsideContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) /*override*/
{
}

void InsideContactListener::ProcessQueue(Inside &insideRef)
{
	while(m_EventQueue.empty() == false)
	{
		EventType eEventRef = m_EventQueue.front();
		switch(eEventRef)
		{
		case PHYSEVENT_EnterComputer:	insideRef.OnEnterComputer(); break;
		case PHYSEVENT_LeaveComputer:	insideRef.OnLeaveComputer(); break;
		case PHYSEVENT_EnterKitchen:	insideRef.OnEnterKitchen(); break;
		case PHYSEVENT_LeaveKitchen:	insideRef.OnLeaveKitchen(); break;
		case PHYSEVENT_EnterHomework:	insideRef.OnEnterHomework(); break;
		case PHYSEVENT_LeaveHomework:	insideRef.OnLeaveHomework(); break;
		case PHYSEVENT_ExitHouse:		insideRef.OnExitHouse(); break;
		}
		m_EventQueue.pop();
	}
}

