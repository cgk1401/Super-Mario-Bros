#pragma once

class BaseEffect{
public:
    virtual void update(float dt) = 0;
    virtual void draw(const Texture& texture) = 0;
    virtual bool isFinished() const = 0;
    virtual ~BaseEffect() = default;
};