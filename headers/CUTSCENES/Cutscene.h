#pragma once

class Cutscene {
public:
    virtual ~Cutscene() = default;
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
    virtual bool isFinished() const = 0;
    virtual void setFinish() = 0;
};
