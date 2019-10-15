#ifndef EVENT_HPP
#define EVENT_HPP

class Event{

public:
    
    struct PlayerDamage{
        float damage;
    };

    enum EventType
    {
        PLAYER_DAMAGE,

        COUNT
    };

    EventType type;

    union
    {
        PlayerDamage playerDamage;
    };

};

#endif