/*
 * Vertice.cpp
 *
 *  Created on: 17 de Abril de 2012
 *      Author: Cristiano Carvalheiro
 *      		Daniel Teixeira
 *      		Luis Guilherme Martins
 * Description: Implementacao da classe e respectivos e metodos
 *
 */

#include "Vertice.h"

unsigned int Vertice::nroVertices = 0;

Vertice::Vertice(double posix, double posiy)
{
	id = nroVertices;
	++nroVertices;

	visitado = false;
	posX = posix;
	posY = posiy;
}
unsigned int Vertice::getID() const
{
	return id;
}
pair<unsigned int, unsigned int> Vertice::getCoordenadas() const
{
	return pair<unsigned int, unsigned int> ((unsigned int) posX, (unsigned int) posY);
}
bool Vertice::isVisitado() const
{
	return visitado;
}
void Vertice::setVisitado(bool visit)
{
	visitado = visit;
}
vector<Aresta>::iterator Vertice::getArestaIt()
{
	return arestas.begin();
}
vector<Aresta>::iterator Vertice::getArestaFim()
{
	return arestas.end();
}
unsigned int Vertice::getNroArestas() const {
	return arestas.size();
}


Aresta Vertice::getAresta(unsigned int indice) const
{
	return arestas[indice];
}
unsigned int Vertice::getIdAresta(unsigned int vdest) const
{
	vector<Aresta>::const_iterator it = arestas.begin(), itfinal = arestas.end();
	unsigned int resultado = 0;

	for(; it != itfinal; ++it) {
		if(it->getDestino()->getID() == vdest) {
			resultado = it->getID();
			break;
		}
	}

	return resultado;
}
double Vertice::getTamanhoAresta(unsigned int idaresta) const
{
	vector<Aresta>::const_iterator it = arestas.begin(), itfinal = arestas.end();
	double resultado = 0.0;

	for(; it != itfinal; ++it) {
		if(it->getID() == idaresta) {
			resultado = it->getTamanho();
			break;
		}
	}

	return resultado;
}
