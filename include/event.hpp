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
        LEVEL_END,
        NEXT_LEVEL,
        GAME_END,
        DEATH,

        COUNT
    };

    EventType type;

    union
    {
        PlayerDamage playerDamage;
    };

};

#endif