#ifndef RACING_CAR_H
#define RACING_CAR_H


class Car {
public:
    Car(float x, float y);
    void move();

private:
    float x;
    float y;
    float speed;
    float angle;
};


#endif //RACING_CAR_H
