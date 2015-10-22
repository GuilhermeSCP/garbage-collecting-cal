/*
 * Aresta.h
 *
 *  Created on: 17 de Abril de 2012
 *      Author: Cristiano Carvalheiro
 *      		Daniel Teixeira
 *      		Luis Guilherme Martins
 * Description: Definicao da classe e respectivos atributos e metodos
 *
 */
#ifndef ARESTA_H_
#define ARESTA_H_

#include <string>

using namespace std;

class Vertice;
/**
 * @brief Classe que abstrai o objecto Aresta
 */
class Aresta
{
private:
	static unsigned int nroArestas;
	unsigned int id;
	string nome;
	Vertice * destino;
	double tamanho;

public:
	/**
	 * @brief Constructor por defeito da classe Aresta
	 */
	Aresta() {};
	/**
	 * @brief Construtor da classe Aresta
	 * @param nom Nome da aresta
	 * @param tam Tamanho da aresta
	 * @param dest Apontador para o vertice de destino
	 */
	Aresta(string nom, double tam, Vertice *dest);
	/**
	 * @brief Devolve o tamanho da aresta
	 * @return Tamanho da aresta
	 */
	double getTamanho() const;
	/**
	 * @brief Devolve o vertice de destino da aresta
	 * @return Apontador para o vertice de destino
	 */
	Vertice * getDestino() const;
	/**
	 * @brief Devolve o nome da aresta
	 * @return Nome da aresta
	 */
	string getNome() const;
	/**
	 * @brief Devolve o ID da aresta
	 * @return ID da aresta
	 */
	unsigned int getID() const;
	friend class GraphBuilder;
	friend class Gestor;
};

#endif /* ARESTA_H_ */
