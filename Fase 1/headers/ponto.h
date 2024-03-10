#ifndef PROJETO_PONTO_H
#define PROJETO_PONTO_H

class Ponto {
private: 
	float x;
	float y;
	float z;
	
public:
	Ponto (float x, float y, float z);
	float getX() const;
	float getY() const;
	float getZ() const;
};

#endif
