#include "AudioListener.h"
#include "GameObject.h"

AudioListener::AudioListener()
{
}

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
		Print("Multiple instances of AudioListener. First instances are replaced.");
	}
}

void AudioListener::OnDisable()
{
	m_MainPtr = nullptr;
}
