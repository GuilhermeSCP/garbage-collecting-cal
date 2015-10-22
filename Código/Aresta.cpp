/*
 * Aresta.cpp
 *
 *  Created on: 17 de Abril de 2012
 *      Author: Cristiano Carvalheiro
 *      		Daniel Teixeira
 *      		Luis Guilherme Martins
 * Description: Implementacao da classe e respectivos e metodos
 *
 */

#include "Aresta.h"

unsigned int Aresta::nroArestas = 0;

Aresta::Aresta(string nom, double tam, Vertice *dest)
{
	id = nroArestas;
	++nroArestas;
	nome = nom;
	tamanho = tam;
	destino = dest;
}
double Aresta::getTamanho() const
{
	return tamanho;
}
Vertice *Aresta::getDestino() const
{
	return destino;
}
string Aresta::getNome() const
{
	return nome;
}
unsigned int Aresta::getID() const
{
	return id;
}
