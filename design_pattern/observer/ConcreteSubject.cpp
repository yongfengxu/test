#include "ConcreteSubject.h"

void ConcreteSubject::Attach(IObserver* observer)
{
	m_OberserList.push_back(observer);
}

void ConcreteSubject::Detach(IObserver* observer)
{
/*
	list<IObserver*>::iterator iter;
	for (iter = m_OberserList.begin(); iter != m_OberserList.end(); )
	{
		if (*iter == observer)
		{
			m_OberserList.erase(iter);
			continue;	
		}
		++iter;
	}
*/

	if (NULL != observer)
	{
		m_OberserList.remove(observer);
	}

}

void ConcreteSubject::Notify()
{
/* for c++ 11
	for (auto it: m_OberserList)
	{
		it->Update(_state);
	}
*/

	list<IObserver*>::iterator iter;
	for (iter = m_OberserList.begin(); iter != m_OberserList.end(); ++iter)
	{
		(*iter)->Update(this);
	}
}

void ConcreteSubject::SetState(int st)
{
	_state = st;
}

int ConcreteSubject::GetState()
{
	return _state;
}


