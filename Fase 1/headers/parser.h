#ifndef parser_h
#define parser_h

#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <sstream>
#include <vector>
using namespace std;
using namespace tinyxml2;


typedef struct {
  float coordenada_x;
  float coordenada_y;
  float coordenada_z;
} MeuPonto;

typedef std::vector<MeuPonto> MeusPontos; 

vector<string> dividir(const string& s, char delimitador);
vector<string> obter_arquivos(char* caminho);
vector<MeuPonto> obter_meus_pontos(char* caminho);

#endif
