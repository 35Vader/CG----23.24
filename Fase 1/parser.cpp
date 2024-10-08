#include "headers/parser.h"
#include "headers/tinyxml2.h"
#include "./headers/ponto.h"

using namespace std;
using namespace tinyxml2;



vector<string> dividir(const string& s, char delimiter)
{
    std::vector<string> tokens;
    std::string token;
    std::istringstream ss(s);
    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

vector<string> obter_arquivos(char* caminho)
{
    std::vector<string> arquivos;
    XMLDocument doc;
    tinyxml2::XMLError flag = doc.LoadFile(caminho);
    if(!flag)
    {
        XMLElement *pRoot, *pParm;
        pRoot = doc.FirstChildElement();
        if(pRoot)
        {
            pParm = pRoot->FirstChildElement();
            int i = 0; // para ordenar as entradas
            std::string arquivo;
            while(pParm)
            {
                arquivo = pParm->Attribute("file");
                arquivos.push_back(arquivo);
                pParm = pParm->NextSiblingElement();
                i++;
            }
            int it;
        }
    }
    return arquivos;
}

std::vector<MeuPonto> obterPontos(char* caminho)
{
    int i;
    vector<string> arquivos = obter_arquivos(caminho);
    std::vector<MeuPonto> pontos;
    for(i = 0; i < arquivos.size(); i++)
    {
        ifstream infile;
        infile.open(arquivos[i]);
        if(infile.is_open())
        {
            std::string linha;
            while(std::getline(infile, linha))
            {
                std::vector<string> tokens;
                tokens = dividir(linha, ' ');

                MeuPonto *p = new MeuPonto(
                    stof(tokens[0], nullptr),
                    stof(tokens[1], nullptr),
                    stof(tokens[2], nullptr)
                );
                pontos.push_back(*p);
            }
            infile.close();
        }
    }
    return pontos;
}