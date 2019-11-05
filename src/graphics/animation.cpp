#include "graphics/animation.hpp"

namespace graphics{

Animation::Animation(const int _width,const int _height,const int _off_w, const int _off_h,const sf::Texture& _texture, const sf::Vector2i _nbFrames,sf::Time _fT,const bool _loop):
width(_width),height(_height),offset_w(_off_w),offset_h(_off_h),
texture(_texture), nbFrames(_nbFrames), frameTime(_fT), loop(_loop)
{

}

}