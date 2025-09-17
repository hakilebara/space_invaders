#ifndef BULLET_H
#define BULLET_H

class Bullet {
  public:
    Bullet(float x, float y) : x(x), y(y) {}
    float x;
    float y;
    float velocity = 5;
    void Move() {
      y -= velocity;
    }
};

#endif
