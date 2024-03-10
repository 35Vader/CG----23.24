#include "../../include/ponto.h"

Ponto::Ponto (float x, float y, float z) : x(x), y(y), z(z) {}

float Ponto::getX() const {
	return this -> x;
}

float Ponto::getY() const {
	return this -> y;
}

float Ponto::getZ() const {
	return this -> z;
}
