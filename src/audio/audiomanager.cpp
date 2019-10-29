#include "audio/audiomanager.hpp"

namespace audio
{

AudioManager::AudioManager():isPlaying(false),music(nullptr)
{
    sf::Listener::setDirection(0,0,-1);
}

AudioManager::~AudioManager()
{
    //do not destroy resources, it's done by the assets manager
}

void AudioManager::setMusic(sf::Music& _music)
{
    music=&_music;
}

void AudioManager::setCenter(const sf::Vector2f& pos)
{
    sf::Listener::setPosition(pos.x, pos.y,0.1);
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
