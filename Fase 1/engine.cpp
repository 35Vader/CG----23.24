#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include "headers/parser.h"

float angulo_alpha = -M_PI / 4, angulo_beta = -M_PI / 4, passo = 2.0;
float posicao_x = 10, posicao_y = 10, posicao_z = 10;
float direcao_x, direcao_y, direcao_z;
pointsStruct meusPontos;
int modo_desenho = GL_LINE;

float calcularNorma(float x, float y, float z) {
    return sqrt(x*x + y*y + z*z);
}

void normalizar(float* x, float* y, float* z) {
    float xx = *x, yy = *y, zz = *z;
    float norma = calcularNorma(xx, yy, zz);
    *x = xx / norma;
    *y = yy / norma;
    *z = zz / norma;
}

void alterarTamanho(int largura, int altura) {
    if (altura == 0)
        altura = 1;

    float razao_aspecto = largura * 1.0 / altura;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, largura, altura);
    gluPerspective(45.0f, razao_aspecto, 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
}

void desenharPontos() {
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 1);
    for (unsigned int i = 0; i < meusPontos.size(); i++) {
        glVertex3f(meusPontos[i].coordenada_x, meusPontos[i].coordenada_y, meusPontos[i].coordenada_z);
    }
    glEnd();
}

void renderizarCena(void) {
    float view_x, view_y, view_z;
    view_x = cos(angulo_beta) * sin(angulo_alpha);
    view_y = sin(angulo_beta);
    view_z = cos(angulo_beta) * cos(angulo_alpha);

    normalizar(&view_x, &view_y, &view_z);
    direcao_x = view_x;
    direcao_y = view_y;
    direcao_z = view_z;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(posicao_x, posicao_y, posicao_z,
              posicao_x + direcao_x, posicao_y + direcao_y, posicao_z + direcao_z,
              0.0f, 1.0f, 0.0f);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, modo_desenho);
    desenharPontos();

    glutSwapBuffers();
}

void processarTeclas(unsigned char tecla, int xx, int yy) {
    switch (tecla) {
        case 'd':
            angulo_alpha -= M_PI / 64;
            break;
        case 'a':
            angulo_alpha += M_PI / 64;
            break;
        case 'w':
            posicao_x += passo * direcao_x;
            posicao_y += passo * direcao_y;
            posicao_z += passo * direcao_z;
            break;
        case 's':
            posicao_x -= passo * direcao_x;
            posicao_y -= passo * direcao_y;
            posicao_z -= passo * direcao_z;
            break;
        case 'm':
            if (modo_desenho == GL_LINE) {
                modo_desenho = GL_POINT;
                break;
            } else if (modo_desenho == GL_POINT) {
                modo_desenho = GL_FILL;
                break;
            } else if (modo_desenho == GL_FILL) {
                modo_desenho = GL_LINE;
                break;
            }
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void processarTeclasEspeciais(int tecla, int xx, int yy) {
    switch (tecla) {
        case GLUT_KEY_UP:
            angulo_beta += M_PI / 64;
            if (angulo_beta > M_PI / 3)
                angulo_beta = M_PI / 3;
            break;
        case GLUT_KEY_DOWN:
            angulo_beta -= M_PI / 64;
            if (angulo_beta < -M_PI / 3)
                angulo_beta = -M_PI / 3;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void ajuda() {
    printf(" ┌-------------------------------------------------AJUDA---------------------------------------------┐\n");
    printf(" |                                                                                                  |\n");
    printf(" |   ‣$ ./MeuPrograma <ARQUIVO_ENTRADA_XML>                                                        |\n");
    printf(" |                                                                                                  |\n");
    printf(" |                                                                                                  |\n");
    printf(" |      Controles :                                                                               |\n");
    printf(" |         mover para frente: w                                                                   |\n");
    printf(" |         mover para trás: s                                                                     |\n");
    printf(" |         olhar para a esquerda: a                                                              |\n");
    printf(" |         olhar para a direita: d                                                               |\n");
    printf(" |         olhar para cima: SETA PARA CIMA                                                        |\n");
    printf(" |         olhar para baixo: SETA PARA BAIXO                                                     |\n");
    printf(" |         alternar modo de desenho: m                                                           |\n");
    printf(" |                                                                                                  |\n");
    printf(" └--------------------------------------------------------------------------------------------------┘\n");
}

int main(int argc, char **argv) {
    std::string arg = argv[1];
    if (!arg.compare("-ajuda")) {
        ajuda();
        return 1;
    }

    std::string pasta = "cenas/";
    pasta.append(arg);
    char *caminho = new char[pasta.size() + 1];
    std::copy(pasta.begin(), pasta.end(), caminho);
    caminho[pasta.size()] = '\0';

    meusPontos = obter_meus_pontos(caminho);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3D ENGINE @ CG 18/19");

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glutDisplayFunc(renderizarCena);
    glutReshapeFunc(alterarTamanho);

    glutKeyboardFunc(processarTeclas);
    glutSpecialFunc(processarTeclasEspeciais);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glutMainLoop();

    return 1;
}
