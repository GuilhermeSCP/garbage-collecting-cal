/*
 * GraphBuilder.h
 *
 *  Created on: 17 de Abril de 2012
 *      Author: Cristiano Carvalheiro
 *      		Daniel Teixeira
 *      		Luis Guilherme Martins
 * Description: Definicao da classe e respectivos atributos e metodos
 *
 */

#ifndef GRAPHBUILDER_H_
#define GRAPHBUILDER_H_

#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include "Vertice.h"

using namespace std;

typedef unsigned long long int ullint;


typedef unsigned long long int ullint;
const double PI = 4.0 * atan(1.0);
const int EARTH_RADIUS = 6371000;
/**
 * @brief Classe que agrupa todas as funcoes necessarias a criacao do grafo
 */
class GraphBuilder
{
private:
	/**
	 * @brief Classe que agrupa todas as funcoes necessarias a criacao do objecto Rua
	 */
	class Rua
	{
	private:
		string nome;
		bool sentidoUnico;
	public:
		/**
		 * @brief Construtor por defeito da classe Rua
		 */
		Rua() {};
		/**
		 * @brief Construtor da classe Rua
		 *
		 * @param _nome Nome da Rua
		 * @param origem ID do Vertice de origem
		 * @param destino ID do Vertice de destino
		 * @param su Booleano que identifica se a rua e ou nao de sentido unico
		 */
		Rua(string _nome, ullint _origem, ullint _destino, bool su): nome(_nome), sentidoUnico(su){};
		friend class GraphBuilder;
	};
	/**
	 * @brief Redefine o valor das coordenadas para todos os vertices
	 */
	static void setCoordenadas();
	/**
	 * @brief Compara dois vertices
	 *
	 * @param v1 Primeiro Vertice
	 * @param v2 Segundo vertice
	 *
	 * @return TRUE se o ID do primeiro Vertice for menor que o ID do segundo, FALSE em caso contrario
	 */
	static bool comparar(Vertice * v1, Vertice * v2);
	/**
	 * @brief Calcula a distancia real
	 *
	 * @param d Distancia
	 *
	 * @return Distancia real
	 */
	static double calculaDistanciaReal(double d);
	/**
	 * @brief Calcula a distancia entre dois vertices
	 *
	 * @param v1 Primeiro Vertice
	 * @param v2 Segundo Vertice
	 *
	 * @return Distancia entre os 2 vertices
	 */
	static double calculaDistancia(Vertice * v1, Vertice* v2);
	/**
	 * @brief Le os ficheiros dos nos e das arestas
	 *
	 * @param nos Stream do ficheiro dos nos
	 * @param ruas Stream do ficheiro das ruas
	 */
	static void lerMapa(ifstream & nos, ifstream & ruas);
	/**
	 * @brief Liga todos os vertices
	 *
	 * @param subRuas Stream do ficheiro das adjacencias
	 */
	static void ligarVertice(ifstream & subRuas);
	static map<ullint, Vertice *> mapaVertices;
	static map<ullint, Rua> mapaRuas;

public:
	/**
	 * @brief Constroi o grafo completo
	 *
	 * @param vectorVertices Vector dos vertices
	 * @param nos Stream do ficheiro dos nos
	 * @param ruas Stream do ficheiro das ruas
	 * @param subRuas Stream do ficheiro das adjacencias
	 */
	static void construirGrafo(vector<Vertice *> & vectorVertices, ifstream & nos, ifstream & ruas, ifstream & subRuas);
};


#endif /* GRAPHBUILDER_H_ */
