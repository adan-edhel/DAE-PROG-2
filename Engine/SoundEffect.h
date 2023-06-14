#pragma once
#include <string>
class Mix_Chunk;
class SoundEffect final
{
public:
	explicit SoundEffect( const std::string& path );
	~SoundEffect( );
	SoundEffect(const SoundEffect& other) = delete;
	SoundEffect& operator=(const SoundEffect& rhs) = delete;
	SoundEffect( SoundEffect&& other) = delete;
	SoundEffect& operator=( SoundEffect&& rhs) = delete;

	bool IsLoaded( ) const;
	bool IsPlaying() const;
	bool Play( const int loops = 0 ) const;
	bool PlayOnce(const int loops = 0) const;
	void Stop() const;
	void Pause() const;
	void Resume() const;
	void SetVolume( const int value );
	static void SetGlobalVolume(float value);
	int GetVolume( ) const; 
	static void StopAll( );
	static void PauseAll( );
	static void ResumeAll( );

private:
	Mix_Chunk* m_pMixChunk;
};