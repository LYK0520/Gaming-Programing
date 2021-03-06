#include "AnimatedSprite.hpp"
#include "Animation.hpp"

#include <cassert>

AnimatedSprite::FuncType AnimatedSprite::defaultFunc = []() -> void {};
//构造函数通过传参对内部变量进行赋值
AnimatedSprite::AnimatedSprite(Animation *animation, Status status, const sf::Time &deltaTime, bool loop, int repeat)
    : on_finished(defaultFunc), _delta(deltaTime), _loop(loop),
      _repeat(repeat), _status(status)
{
    setAnimation(animation);
}
//这个函数只在新旧纹理不同的情况下才会更新为新纹理
//并将帧重设为新动画的第一个帧
//注意，新动画中必须至少存在一个帧图像
void AnimatedSprite::setAnimation(Animation *animation)
{
    if (_animation != animation)
    {
        _animation = animation;
        _elapsed = sf::Time::Zero;
        _currentFrame = 0;
        setFrame(0, true);
    }
}

Animation *AnimatedSprite::getAnimation() const
{
    return _animation;
}
void AnimatedSprite::setFrameTime(sf::Time deltaTime)
{
    _delta = deltaTime;
}
sf::Time AnimatedSprite::getFrameTime() const
{
    return _delta;
}
void AnimatedSprite::setLoop(bool loop)
{
    _loop = loop;
}
bool AnimatedSprite::getLoop() const
{
    return _loop;
}
void AnimatedSprite::setRepeate(int nb)
{
    _repeat = nb;
}
int AnimatedSprite::getRepeate() const
{
    return _repeat;
}
void AnimatedSprite::play()
{
    _status = Playing;
}
void AnimatedSprite::pause()
{
    _status = Paused;
}
void AnimatedSprite::stop()
{
    _status = Stopped;
    _currentFrame = 0;
    setFrame(0, true);
}
AnimatedSprite::Status AnimatedSprite::getStatus() const
{
    return _status;
}
//此函数将当前帧更改为从_animation动画序列中获取的新帧
void AnimatedSprite::setFrame(size_t index)
{
    assert(_animation);
    _currentFrame = index % _animation->size();
    setFrame(_currentFrame, true);
}

//此函数用于改变所显示纹理图像的颜色掩码
//为此，将纹理图像的4个内部顶点的颜色参数设置为新颜色值
void AnimatedSprite::setColor(const sf::Color &color)
{
    _vertices[0].color = color;
    _vertices[1].color = color;
    _vertices[2].color = color;
    _vertices[3].color = color;
}
void AnimatedSprite::update(const sf::Time &deltaTime)
{
    if (_status == Playing && _animation)
    {
        _elapsed += deltaTime;
        if (_elapsed > _delta)
        {
            _elapsed -= _delta;
            if (_currentFrame + 1 < _animation->size())
            {
                ++_currentFrame;
            }
            else
            {
                _currentFrame = 0;
                if (!_loop)
                {
                    --_repeat;
                    if (_repeat <= 0)
                    {
                        _status = Stopped;
                        on_finished();
                    }
                }
            }
        }
        setFrame(_currentFrame, false);
    }
}
//此函数的目的是将内部Animation类对象_animation第index帧的
//属性（位置和纹理坐标）赋值给当前动画帧的4个顶点
void AnimatedSprite::setFrame(size_t index, bool resetTime)
{
    if (_animation)
    {
        sf::IntRect rect = _animation->getRect(index);

        _vertices[0].position = sf::Vector2f(0.f, 0.f);
        _vertices[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
        _vertices[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
        _vertices[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

        float left=static_cast<float>(rect.left);
        float right=left+static_cast<float>(rect.width);
        float top=static_cast<float>(rect.top);
        float bottom=top+static_cast<float>(rect.height);

        _vertices[0].texCoords=sf::Vector2f(left,top);
        _vertices[1].texCoords=sf::Vector2f(left,bottom);
        _vertices[2].texCoords=sf::Vector2f(right,bottom);
        _vertices[3].texCoords=sf::Vector2f(right,top);
    }

    if(resetTime)
    {
        _elapsed=sf::Time::Zero;
    }
}
void AnimatedSprite::draw(sf::RenderTarget& target,sf::RenderStates states)const
{
    if(_animation && _animation->_texture)
    {
        states.transform *=getTransform();
        states.texture= _animation->_texture;
        target.draw(_vertices,4,sf::Quads,states);
    }
}
