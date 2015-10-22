/*
 * Algoritmo.h
 *
 *  Created on: 17 de Abril de 2012
 *      Author: Cristiano Carvalheiro
 *      		Daniel Teixeira
 *      		Luis Guilherme Martins
 * Description: Definicao da classe e respectivos atributos e metodos
 *
 */

#ifndef ALGORITMO_H_
#define ALGORITMO_H_

#include "Vertice.h"
#include <vector>
#include <list>
#include <limits>
#include <stack>

const int INFINITO = numeric_limits<int>::max();
/**
 * @brief Classe possui o algoritmo utilizado
 */
class Algoritmo
{
private:
	/**
	 * @brief Funcao auxiliar para o algoritmo de Floyd-Warshall
	 * @param origem ID do vertice de origem
	 * @param destino ID do vertice de destino
	 * @param res Vector com o caminho actual
	 * @param ArrayCaminhosAux Matriz auxiliar
	 * @param vertices Vector de vertices
	 */
	static void getCaminhoAux(int ind1, int ind2, vector<unsigned int> & res, int ** & ArrayCaminhosAux, vector<Vertice *> & vertices);
public:

	/**
	 * @brief Calcula o custo entre dois vertices
	 * @param IndOriV ID do vertice de origem
	 * @param IndDesV ID do vertice de destino
	 * @param vertices Vector de vertices
	 * @return O valor do custo entre dois vertices
	 */
	static int custoAresta(unsigned int IndOriV, unsigned int IndDesV, vector<Vertice *> & vertices);

	/**
	 * @brief Calcula o caminho mais curto entre vertices
	 * @param origem ID do vertice de origem
	 * @param destino ID do vertice de destino
	 * @param arrayCaminho Matriz de adjacencias
	 * @param ArrayCaminhosAux Matriz auxiliar de caminhos
	 * @param vertices Vector de vertices
	 * @return Vector com o ID de todos os vertices visitados
	 */
	static vector<unsigned int> getCaminho(const unsigned int & origem, const unsigned int & destino, int ** & arrayCaminho, int ** & ArrayCaminhosAux, vector<Vertice *> & vertices);

	/**
	 * @brief Constroi matrizes usadas pelo algoritmo de Floyd-Warshall
	 * @param arrayCaminho Matriz de adjacencias
	 * @param arrayCaminhoAux Matrix auxiliar
	 * @param vertices Vector de vertices
	 */
	static void floydWarshallCaminhoMaisCurto(int ** & arrayCaminho, int ** & arrayCaminhoAux, vector<Vertice *> & vertices);

	/**
	 * @brief Visita todos os vertices acessiveis apartir da origem usando
	 * a procura em profundidade
	 * @param origem ID do vertice usado como origem
	 * using a depth first search (used to determine accessible vertexes)
	 * @param vertices Vector de vertices
	 * @return Vector com os IDs de todos os vertices acessiveis
	 */	
	static vector<unsigned int> procuraEmProfundidade(unsigned int origem, vector<Vertice *> & vertices);
};

#endif /* ALGORITMO_H_ */
