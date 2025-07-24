#pragma once

class Timer {
private:
    float duration;
    float elapsed;
    bool running;

public:
    Timer(float duration = 0)
        : duration(duration), elapsed(0), running(false) {}

    void start(float newDuration = -1) {
        if (newDuration > 0) duration = newDuration;
        elapsed = 0;
        running = true;
    }

    void stop() { running = false; }

    void update(float dt) {
        if (running) elapsed += dt;
        if (elapsed >= duration) {
            running = false;
        }
    }

    float getProgress(){
        return elapsed / duration;
    }

    bool isFinished() const { return !running && elapsed >= duration; }
    bool isRunning() const { return running; }
    
};
