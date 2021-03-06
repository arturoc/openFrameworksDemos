#pragma once

#include "Particle.h"
#include "ofGraphics.h"

class Spring {
public:
    Particle* a;
    Particle* b;
    float length, stiffness;
    Spring(Particle& a, Particle& b, float stiffness, float length = 0)
    :a(&a)
    ,b(&b)
    ,stiffness(stiffness) {
        if(length == 0) {
            length = a.distance(b);
        }
        this->length = length;
    }
    void update() {
        ofVec2f normal = *b - *a;
        float curLength = normal.length();
        float dx = length - curLength;
        dx /= length;
//        dx = tanh(dx);
        dx = 1 / (1 + exp(-dx)) - .5;
        normal *= (stiffness / curLength);
        a->force += normal * -dx;
        b->force += normal * +dx;
    }
    void draw() const {
        ofDrawLine(*a, *b);
    }
};