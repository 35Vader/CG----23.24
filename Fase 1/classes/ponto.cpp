#include "../../include/ponto.h"

MeuPonto::MeuPonto (float x, float y, float z) : x(x), y(y), z(z) {}

float MeuPonto::getX() const {
	return this -> x;
}

float MeuPonto::getY() const {
	return this -> y;
}

float MeuPonto::getZ() const {
	return this -> z;
}
