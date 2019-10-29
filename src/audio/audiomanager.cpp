#include "audio/audiomanager.hpp"

namespace audio
{

AudioManager::AudioManager():isPlaying(false),music(nullptr)
{
}

AudioManager::~AudioManager()
{
    //do not destroy resources
}

void AudioManager::setMusic(sf::Music& _music)
{
    music=&_music;
}

void AudioManager::start()
{
    if(!isPlaying)
    {
        isPlaying=true;
        if(music!=nullptr) music->play();
    }
}

void AudioManager::stop()
{
    if(isPlaying)
    {
        isPlaying = false;
        music->stop();
    }
}  

} // namespace audio
