#include "AudioListener.h"
#include "GameObject.h"

void AudioListener::Awake()
{
	if (m_MainPtr == nullptr)
	{
		m_MainPtr = this;
	}
	else
	{
		delete m_MainPtr->m_GameObject;
		m_MainPtr = this;
		Print("Multiple instances of AudioListener. Initial instances are replaced.");
	}
}

void AudioListener::OnDestroy()
{
	m_MainPtr = nullptr;
}
