#include "graphics/animation.hpp"

namespace graphics{

Animation::Animation(int _width,int _height,int _off_w,int _off_h,const sf::Texture& _texture,int _nbFrames,sf::Time _fT,bool _loop):
width(_width),height(_height),offset_w(_off_w),offset_h(_off_h),
texture(_texture), nbFrames(_nbFrames), frameTime(_fT), loop(_loop)
{

}

}