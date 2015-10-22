/*
 * Vertice.h
 *
 *  Created on: 17 de Abril de 2012
 *      Author: Cristiano Carvalheiro
 *      		Daniel Teixeira
 *      		Luis Guilherme Martins
 * Description: Definicao da classe e respectivos atributos e metodos
 *
 */
#ifndef VERTICE_H_
#define VERTICE_H_

#include <vector>
#include "Aresta.h"

using namespace std;
/**
 * @brief Classe que abstrai o objecto Vertice
 */
class Vertice
{
private:
	static unsigned int nroVertices;
	unsigned int id;
	bool visitado;

public:
	double posX, posY;
	vector<Aresta> arestas;

	/**
	 * @brief Contrutor por defeito da classe Vertice
	 */
	Vertice() {};
	/**
	 * @brief Contrutor do vertice
	 * @param posix Posicao do vertice no eixo dos xx
	 * @param posiy Posicao do vertice no eixo dos yy
	 */
	Vertice (double, double);
	/**
	 * @brief Devolve o ID do vertice
	 * @return ID do vertice
	 */
	unsigned int getID() const;
	/**
	 * @brief Devolve o par de coordenadas x e y do vertice
	 * @return Coordenadas do vertice
	 */
	pair<unsigned int, unsigned int> getCoordenadas() const;
	/**
	 * @brief Verifica se o vertice ja foi visitado
	 * @return TRUE se o vertice foi visitado, FALSE em caso contrario
	 */
	bool isVisitado() const;
	/**
	 * @brief Define o novo estado de  visitado do Vertice
	 * @param visit Novo estado de visitado (booleano)
	*/	
	void setVisitado(bool);
	/**
	 * @brief Devolve o iterador para o primeiro elemento do vector de arestas
	 * @return Iterador para o primeiro elemento do vector de arestas
	 */
	vector<Aresta>::iterator getArestaIt();
	/**
	 * @brief Devolve o iterador para o ultimo elemento do vector de arestas
	 * @return Iterador para o ultimo elemento do vector de arestas
	 */
	vector<Aresta>::iterator getArestaFim();
	/**
	 * @brief Devolve o numero de arestas que saem do vertice
	 * @return Numero de arestas que saem do vertice
	 */
	unsigned int getNroArestas() const;
	/**
	 * @brief Devolve uma aresta especifica
	 * @param indice Indice da aresta pretendida
	 * @return Aresta que sai do vertice
	 */
	Aresta getAresta(unsigned int) const;
	/**
	 * @brief Devolve o tamanho da aresta seleccionada
	 * @param idaresta ID da aresta
	 * @return Tamanho da aresta seleccionada
	 */
	double getTamanhoAresta(unsigned int) const;
	/**
	 * @brief Devolve o ID da aresta que liga o vertice actual ao vertice de destino
	 * @param vdest Vertice de destino
	 * @return ID da aresta
	 */
	unsigned int getIdAresta(unsigned int) const;
	friend class Graph_Builder;
	friend class Gestor;

};



#endif /* VERTICE_H_ */
