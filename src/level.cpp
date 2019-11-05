#include "level.hpp"

#include "resources/resourcesmanager.hpp"
#include "resources/RSJparser.tcc"
#include <iostream>
#include <fstream>
#include "block.hpp"
#include "special/specialblockfactory.hpp"

#include "game.hpp"


Level::Level(Game &_game) : game(_game), switchlevel(&Level::switchLevel, this)
{
    others = new physics::ICollidable*[LevelOther::LOCOUNT];
    for (int i=0;i<LOCOUNT;++i)
        others[i] = nullptr;

    globalBounds.top = 0;
    globalBounds.left = 0;
}

Level::~Level()
{
    for (physics::ICollidable *col : collidable)
        delete col;

    for (physics::ICollidable *col : trigerrable)
        delete col;

    for (int i=0;i<LOCOUNT;++i)
        delete others[i];

    delete[] others;
}

bool Level::initLevel(int id)
{
    collidable.clear();
    trigerrable.clear();
    ela.init(); end=false;
    for (int i=0;i<LOCOUNT;++i){
        if(others[i] != nullptr)
            delete others[i];
    }

    for (int i=0;i<LOCOUNT;++i)
        others[i] = nullptr;


    if(id>=_GAME_NBLVL) return false;
    else
    {
        std::cout << "Loading " << _LEVEL_PATH[id] << std::endl;
        loadMap(std::string("resources/maps/")+_LEVEL_PATH[id]);
        return true;
    }
}

void Level::loadMap(const std::string path)
{
    std::ifstream file(path, std::ifstream::in);
    std::istream *stream = &file;

    RSJresource rsc = (*stream);

    /** music **/
    try{
        game.audioManager.setMusic(resources::ResourcesManager::instance().musics.getAsset(rsc["properties"]["music"].as<std::string>()));
    }catch(resources::AssetsManagerException e)
    {
        std::cerr << "Error while loading the music " << rsc["properties"]["music"].as<std::string>() << std::endl;
    }

    for (int i = 0;; i++)
    {
        if (rsc["layers"][i]["name"].as<std::string>() == "collider")
        {
            int size = _TILE_HEIGHT; //rsc["tileheight"].as<int>();
            int width = rsc["layers"][i]["width"].as<int>();
            int height = rsc["layers"][i]["height"].as<int>();

            globalBounds.width = width * _TILE_WIDTH;
            globalBounds.height = height * _TILE_HEIGHT;

            game.scene.player.sprite->setPosition(rsc["properties"]["player_pos_x"].as<int>() * size, rsc["properties"]["player_pos_y"].as<int>() * size);

            /** manage background */
            sf::FloatRect rect;
            rect.height = height;
            rect.width = width;

            game.scene.background.setImage(resources::ResourcesManager::instance().textures.getAsset(rsc["properties"]["background"].as<std::string>()));
            game.scene.background.setSize(width * size + (2 * _CAMERA_WIDTH), height * size + (2 * _CAMERA_HEIGHT));
            /* end background */

            int x = 0, y = 0;

            for (int h = 0; h < height; ++h)
            {
                for (int w = 0; w < width; ++w)
                {
                    int id = rsc["layers"][i]["data"][h * width + w].as<int>() - 1;
                    if (id >= 0)
                    {
                        if(id>=_BEGIN_SPECIALTILE)
                        {
                            if(id==_BEGIN_SPECIALTILE+special::SpecialBlockFactory::SpecialBlockID::BEGIN) game.scene.player.sprite->setPosition(x,y);
                            else
                            {   
                                auto pair = special::SpecialBlockFactory::getBlock(id, game);
                                pair.first->setPosition(x, y);
                                if(id==_BEGIN_SPECIALTILE+special::SpecialBlockFactory::CASTLE)
                                    others[LevelOther::CASTLE] = pair.first;
                                else if(pair.second)
                                    collidable.push_back(pair.first);
                                else
                                    trigerrable.push_back(pair.first);
                            }
                            
                        }
                        else
                        {
                            auto pair = resources::ResourcesManager::instance().mapTileSet.getAsset(id);
                            Block *block = new Block(pair.first, resources::ResourcesManager::instance().textures.getAsset(pair.second));
                            block->setPosition(x, y);
                            collidable.push_back(block);
                        }
                    }
                    x += size;
                }
                y += size;
                x = 0;
            }
            break;
        }
    }
    file.close();

    std::cout << "Map loaded" << std::endl;
}

void Level::initLevel()
{
    loadMap("resources/maps/map0.json");
    /*sf::Sprite sprite(resources::ResourcesManager::instance().textures.getAsset("block"));
    sprite.setPosition(255,200);
    collidable.push_back(std::move(sprite));

    sprite = sf::Sprite(sprite);
    sprite.setPosition(255,280);
    collidable.push_back(std::move(sprite));

    sprite = sf::Sprite(sprite);
    sprite.setPosition(350,255);
    collidable.push_back(std::move(sprite));

    sprite = sf::Sprite(sprite);
    sprite.setPosition(150,255);
    collidable.push_back(std::move(sprite));*/

    //** todo: ajout de 4 gros collidable autour du niveau
}

void Level::switchLevel()
{
    for(;;){
        sf::sleep(sf::seconds(1));
        std::cout << "AAAAAAAAAAAAAAAAAAAAAA" << std::endl;
    }
}



void Level::endLevel(int newlevel)
{
    end = true;
}

void Level::update(const double dt)
{
    for (physics::ICollidable *col : collidable)
        col->update(dt);
    for (physics::ICollidable *col : trigerrable)
        col->update(dt);
    for (int i=0;i<LOCOUNT;++i)
    {
        if(others[i]!=nullptr)
            others[i]->update(dt);
    }

    if(end)
    { //anim
        ela.update(dt);
        switch(ela.state)
        {
            case EndLevelAnim::MOVING:
                if((others[CASTLE]->getPosition().x-game.scene.player.getPosition().x)<=58){
                    ela.state = EndLevelAnim::EXPLOSION;    
                    AnimatedBlock* bloc = new AnimatedBlock(resources::ResourcesManager::instance().animations.getAsset("explosion"),false);
                    bloc->setPosition(others[CASTLE]->getPosition().x-150, others[CASTLE]->getPosition().y-128);
                    others[EXPLOSION] = bloc;
                    ((AnimatedBlock*)dynamic_cast<AnimatedBlock*>(others[CASTLE]))->setPlaying(true);
                }
                else
                {
                    
                }
                break;
            case EndLevelAnim::WAIT:
                std::cout << "waiting" << std::endl;
                game.scene.player.state = Player::death;
                break;
            case EndLevelAnim::GO:
                Event evt;
                evt.type = Event::NEXT_LEVEL;
                std::cout << "GO" << std::endl;
                game.addEvent(evt);
                break;
            default:
            break;
        }
    }
}

void Level::updatePhysics(const double dt)
{
    for (physics::ICollidable *col : collidable)
        col->updatePhysics(dt);
    for (physics::ICollidable *col : trigerrable)
        col->updatePhysics(dt);
}

bool inView(const sf::Vector2f& pos, const sf::View &view){
	if(pos.x > view.getCenter().x + view.getSize().x || pos.y > view.getCenter().y + view.getSize().y){
		return false;
	}
	return true;
}

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (physics::ICollidable *col : collidable){
        if(inView(col->getPosition(), game.view))
            target.draw(*col, states);
    }

    for (physics::ICollidable *col : trigerrable)
        target.draw(*col, states);

    for (int i=0;i<LOCOUNT;++i)
    {
        if(others[i]!=nullptr)
            target.draw(*(others[i]),states);
    }
}