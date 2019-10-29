#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <SFML/Audio.hpp>

namespace audio{

class AudioManager{
private:
    sf::Music* music;

    bool isPlaying;

public:
    AudioManager();
    ~AudioManager();

    void setMusic(sf::Music&);
    //void setCenter(int x, int y);

    void start();
    void stop();
};

}

#endif