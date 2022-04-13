#pragma once

class Particle
{
public:
	Particle(float mass,float radius);
	~Particle();
private:
	float mass;
	float radius;
};