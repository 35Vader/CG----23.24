
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <math.h>
using namespace std;



void criarPlano(float comprimento, float largura, const char* arquivo) {
    ofstream f (arquivo, ios::out | ios::trunc);
    float cx = comprimento / 2;
    float cz = largura / 2;

    if(f.is_open()){
        f << cx << ' ' << 0.0 << ' ' << cz << '\n'
          << cx << ' ' << 0.0 << ' ' << -cz << '\n'
          << -cx << ' ' << 0.0 << ' ' << -cz << '\n'
          << cx << ' ' << 0.0 << ' ' << cz << '\n'
          << -cx << ' ' << 0.0 << ' ' << -cz << '\n'
          << -cx << ' ' << 0.0 << ' ' << cz << '\n';
    }
    f.close();
}

void criarCaixa(float comprimento, float largura, float altura, int divisoes, const char* arquivo) {
    int i, j;
    float cx = comprimento / 2;
    float cz = largura / 2;
    float cy = altura / 2;
    float rx = comprimento / divisoes;
    float rz = largura / divisoes;
    float ry = altura / divisoes;

    ofstream f (arquivo, ios::out | ios::trunc);
    if (f.is_open()) {
        for (i = 0; i < divisoes; i++) {
            for (j = 0; j < divisoes; j++) {
      //face da frente
      f << -cx + j*rx << ' ' << -cy + i*ry << ' ' << cz << '\n'
        << -cx + j*rx + rx << ' ' << -cy + i*ry << ' ' << cz << '\n'
        << -cx + j*rx + rx << ' ' << -cy + i*ry + ry << ' ' <<  cz << '\n'

        << -cx + j*rx << ' ' << -cy + i*ry << ' ' << cz << '\n'
        << -cx + j*rx + rx << ' ' << -cy + i*ry + ry << ' ' << cz << '\n'
        << -cx + j*rx << ' ' << -cy + i*ry << ' ' << cz << '\n';

        // face de cima
      f << -cx + j*rx << ' ' << cy << ' ' << cz - i*rz << '\n'
        << -cx + j*rx + rx << ' ' << cy << ' ' << cz - i*rz << '\n'
        << -cx + j*rx + rx << ' ' << cy << ' ' << cz - i*rz - rz << '\n'

        << -cx + j*rx << ' ' << cy << ' ' <<  cz - i*rz << '\n'
        << -cx + j*rx + rx << ' ' << cy << ' ' <<  cz - i*rz - rz << '\n'
        << -cx + j*rx << ' ' <<  cy << ' ' << cz - i*rz - rz << '\n';

      // face de trás
      f << -cx + j*rx << ' ' << -cy + i*ry << ' ' << -cz << '\n'
        << -cx + j*rx + rx << ' ' << -cy + i*ry + ry << ' ' << -cz << '\n'
        << -cx + j*rx + rx << ' ' << -cy + i*ry << ' ' << -cz << '\n'

        << -cx + j*rx << ' ' << -cy + i*ry << ' ' << -cz << '\n'
        << -cx + j*rx << ' ' << -cy + i*ry + ry << ' ' << -cz << '\n'
        << -cx + j*rx + rx << ' ' << -cy + i*ry + ry << ' ' << -cz << '\n';
      // face de baixo
      f << -cx + j*rx << ' ' << -cy << ' ' << cz - i*rz << '\n'
        << -cx + j*rx + rx << ' ' << -cy << ' ' << cz - i*rz - rz << '\n'
        << -cx + j*rx + rx << ' ' << -cy << ' ' << cz - i*rz << '\n'

        << -cx + j*rx << ' ' << -cy << ' ' << cz - i*rz << '\n'
        << -cx + j*rx << ' ' << -cy << ' ' << cz - i*rz - rz << '\n'
        << -cx + j*rx + rx << ' ' << -cy << ' ' << cz - i*rz - rz << '\n';
      // face da esquerda
      f << -cx << ' ' << -cy + i*ry << ' ' << cz - j*rz << '\n'
        << -cx << ' ' << -cy + i*ry +ry << ' ' << cz - j*rz - rz << '\n'
        << -cx << ' ' << -cy + i*ry << ' ' << cz - j*rz - rz << '\n'

        << -cx << ' ' << -cy + i*ry << ' ' << cz - j*rz << '\n'
        << -cx << ' ' << -cy + i*ry +ry << ' ' << cz - j*rz << '\n'
        << -cx << ' ' << -cy + i*ry +ry << ' ' << cz - j*rz - rz  << '\n';
      // face da direita
      f << cx << ' ' << -cy + i*ry +ry << ' ' << cz - j*rz - rz << '\n'
        << cx << ' ' << -cy + i*ry << ' ' << cz - j*rz << '\n'
        << cx << ' ' << -cy + i*ry << ' ' << cz - j*rz - rz << '\n'

        << cx << ' ' << -cy + i*ry << ' ' << cz - j*rz << '\n'
        << cx << ' ' << -cy + i*ry +ry << ' ' << cz - j*rz - rz << '\n'
        << cx << ' ' << -cy + i*ry +ry << ' ' << cz - j*rz << '\n';
      }

    }

  }
  f.close();

}


void criarEsfera (float radius, int slices, int stacks, const char* file){

    float h_stack = (M_PI/stacks); //altura de cada stack
    float a_slices = 2*M_PI / slices;
    int i, j;
    float alfa, beta = 0;

    ofstream f (file,ios::out| ios::trunc );
    if(f.is_open()){


    for(j=1; j<=stacks; j++){

        alfa = 0;
        for(i=1; i<=slices; i++){
          f << (radius * sin(beta) * sin(alfa)) << ' ' <<
                     (radius * cos(beta)) << ' ' <<
                     (radius * sin(beta) * cos(alfa)) << '\n'
            << (radius * sin(beta + h_stack) * sin(alfa)) << ' ' <<
                     (radius * cos(beta + h_stack)) << ' ' <<
                     (radius * sin(beta + h_stack) * cos(alfa)) << '\n'
            << (radius * sin(beta + h_stack) * sin(alfa + a_slices)) << ' ' <<
                     (radius * cos(beta + h_stack)) << ' ' <<
                     (radius * sin(beta + h_stack) * cos(alfa + a_slices)) << '\n'
             << (radius * sin(beta) * sin(alfa)) << ' ' <<
                 (radius * cos(beta)) << ' ' <<
                (radius * sin(beta) * cos(alfa)) << '\n'
            << (radius * sin(beta + h_stack) * sin(alfa + a_slices)) << ' ' <<
                (radius * cos(beta + h_stack)) << ' ' <<
                (radius * sin(beta + h_stack) * cos(alfa + a_slices)) << '\n'
             << (radius * sin(beta) * sin(alfa + a_slices)) << ' ' <<
                (radius * cos(beta)) << ' ' <<
                (radius * sin(beta) * cos(alfa + a_slices)) << '\n';
        alfa = i*a_slices;
        }
        beta = j * h_stack;
      }
    }
    f.close();

}




void criarCone(float radius, float height, int slices, int stacks, const char* file){
    int i, j;
    float alt_stacks = height/stacks;
    float ang_slices = 2 * M_PI / slices;
		float tempangulo;
		float tempradius;
    ofstream f (file,ios::out| ios::trunc );
    if(f.is_open()){

  	//base
        for(i=0; i<slices; i++){
          tempangulo = i*ang_slices;
          f << radius * sin(tempangulo) << ' ' << 0 << ' '<< radius * cos(tempangulo) << '\n'
            << 0 << ' ' << 0 << ' ' << 0 << '\n'
            << radius * sin(tempangulo + ang_slices) << ' ' << 0 << ' ' << radius * cos(tempangulo + ang_slices) << '\n';

					}

		//lados
		tempradius = radius/stacks;
			for(j=0; j<stacks; j++){
				for(i=0; i<slices; i++){
					tempangulo = i*ang_slices;
          f << (radius - j*tempradius)*sin(tempangulo) << ' ' << alt_stacks*j << ' ' << (radius - j*tempradius)*cos(tempangulo) << '\n'

           << (radius - j*tempradius)*sin(tempangulo + ang_slices) << ' ' <<  alt_stacks*j << ' ' << (radius - j*tempradius)*cos(tempangulo + ang_slices) << '\n'

           << (radius - j*tempradius - tempradius)*sin(tempangulo + ang_slices) << ' ' << alt_stacks*j + alt_stacks << ' ' << (radius - j*tempradius - tempradius)*cos(tempangulo + ang_slices) << '\n'

           << (radius - j*tempradius)*sin(tempangulo) << ' ' << alt_stacks*j << ' ' << (radius - j*tempradius)*cos(tempangulo) << '\n'

           << (radius - j*tempradius - tempradius)*sin(tempangulo + ang_slices) << ' ' << alt_stacks*j + alt_stacks << ' ' << (radius - j*tempradius - tempradius)*cos(tempangulo + ang_slices) << '\n'

           << (radius - j*tempradius - tempradius)*sin(tempangulo) << ' ' << alt_stacks*j + alt_stacks << ' ' << (radius - j*tempradius - tempradius)*cos(tempangulo) << '\n';


				}
			}
    }
    f.close();

}



void help(){
printf ( " ┌------------------------------------------- PRIMITIVES -------------------------------------------┐\n");
printf ( " |                                                                                                  |\n");
printf ( " |                                                                                                  |\n");
printf ( " |   ‣ PLANE                                                                                        |\n");
printf ( " |       $ ./generator plane <COMPRIMENTO> <LARGURA> <OUTPUT_FILE>                                  |\n");
printf ( " |                                                                                                  |\n");
printf ( " |   ‣ BOX                                                                                          |\n");
printf ( " |                                                                                                  |\n");
printf ( " |       $ ./generator box <COMPRIMENTO> <LARGURA> <ALTURA> [<DIVISOES>] <OUTPUT_FILE>              |\n");
printf ( " |                                                                                                  |\n");
printf ( " |   ‣ SPHERE                                                                                       |\n");
printf ( " |                                                                                                  |\n");
printf ( " |       $ ./generator sphere <RAIO> <SLICES> <STACKS> <OUTPUT_FILE>                                |\n");
printf ( " |                                                                                                  |\n");
printf ( " |   ‣ CONE                                                                                         |\n");
printf ( " |                                                                                                  |\n");
printf ( " |       $ ./generator cone <RAIO_BASE> <ALTURA> <SLICES> <STACKS> <OUTPUT_FILE>                    |\n");
printf ( " |                                                                                                  |\n");
printf ( " |                                                                                                  |\n");
printf ( " |                                                                                                  |\n");
printf ( " └--------------------------------------------------------------------------------------------------┘\n");
}



int main(int argc, char **argv) {
std::string str = argv[1];
std::string folder = "models/";
  if (!str.compare("plane")){
    if (argc != 5)
      printf("Entrada inválida. Tente -help para obter ajuda.\n");
    else {
      folder.append(argv[4]);
      const char* file = folder.c_str();

      criarPlano(stof(argv[2]),stof(argv[2]),file);

    }
  }
  else if (!str.compare("box")){
    if (argc != 7)
      printf("Entrada inválida. Tente -help para obter ajuda.\n");
    else {
      folder.append(argv[6]);
      const char* file = folder.c_str();
      criarCaixa(stof(argv[2]),stof(argv[3]),stof(argv[4]),stof(argv[5]),file);
    }
  }
  else if (!str.compare("sphere")){
    if (argc != 6)
      printf("Entrada inválida. Tente -help para obter ajuda.\n");
    else {
      folder.append(argv[5]);
      const char* file = folder.c_str();
      criarEsfera(stof(argv[2]),stof(argv[3]),stof(argv[4]),file);
    }
  }
  else if (!str.compare("cone")){
    if (argc != 7)
      printf("Entrada inválida. Tente -help para obter ajuda.\n");
    else {
      folder.append(argv[6]);
      const char* file = folder.c_str();
      criarCone(stof(argv[2]),stof(argv[3]),stof(argv[4]),stof(argv[5]),file);
    }
  }
  else if (!str.compare("-help"))
     help();
  else printf("Comando não encontrado. Tente -help para obter ajuda.\n");

  return 1;

}
