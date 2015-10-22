/*
 * Algoritmo.cpp
 *
 *  Created on: 17 de Abril de 2012
 *      Author: Cristiano Carvalheiro
 *      		Daniel Teixeira
 *      		Luis Guilherme Martins
 * Description: Implementacao da classe e respectivos e metodos
 *
 */

#include "Algoritmo.h"

void Algoritmo::getCaminhoAux(int ind1, int ind2, vector<unsigned int> & res, int ** & ArrayCaminhosAux, vector<Vertice *> & vertices)
{
	if (ArrayCaminhosAux[ind1][ind2] != -1) {
		getCaminhoAux(ind1, ArrayCaminhosAux[ind1][ind2],
				res, ArrayCaminhosAux, vertices);

		res.push_back(vertices[ArrayCaminhosAux[ind1][ind2]]->getID());

		getCaminhoAux(ArrayCaminhosAux[ind1][ind2], ind2, res, ArrayCaminhosAux, vertices);
	}
}

int Algoritmo::custoAresta(unsigned int IndOriV, unsigned int IndDesV, vector<Vertice *> & vertices)
{
	for (unsigned int i = 0; i < vertices[IndOriV]->getNroArestas(); i++) {
		if (vertices[IndOriV]->getID() == vertices[IndDesV]->getID())
			return 0;

		if (vertices[IndOriV]->getAresta(i).getDestino()->getID() == vertices[IndDesV]->getID())
			return vertices[IndOriV]->getAresta(i).getTamanho();
	}

	return INFINITO;
}

vector<unsigned int> Algoritmo::getCaminho(const unsigned int & origem, const unsigned int & destino, int ** & arrayCaminho, int ** & ArrayCaminhosAux, vector<Vertice *> & vertices)
{
	int IndOrigem = -1, IndDestino = -1;

	for (unsigned int i = 0; i < vertices.size(); i++) {
		if (vertices[i]->getID() == origem)
			IndOrigem = i;
		if (vertices[i]->getID() == destino)
			IndDestino = i;

		if (IndOrigem != -1 && IndDestino != -1)
			break;
	}

	vector<unsigned int> res;

	if (arrayCaminho[IndOrigem][IndDestino] == INFINITO)
		return res;
	res.push_back(vertices[IndOrigem]->getID());

	if (ArrayCaminhosAux[IndOrigem][IndDestino] != -1) {

		getCaminhoAux(IndOrigem,
				ArrayCaminhosAux[IndOrigem][IndDestino], res,
				ArrayCaminhosAux, vertices);

		res.push_back(
				vertices[ArrayCaminhosAux[IndOrigem][IndDestino]]->getID());

		getCaminhoAux(
				ArrayCaminhosAux[IndOrigem][IndDestino],
				IndDestino, res, ArrayCaminhosAux, vertices);
	}

	res.push_back(vertices[IndDestino]->getID());

	return res;
}

void Algoritmo::floydWarshallCaminhoMaisCurto(int ** & arrayCaminho, int ** & arrayCaminhoAux, vector<Vertice *> & vertices)
{
	arrayCaminho = new int *[vertices.size()];
	arrayCaminhoAux = new int *[vertices.size()];
	for (unsigned int i = 0; i < vertices.size(); i++) {
		arrayCaminho[i] = new int[vertices.size()];
		arrayCaminhoAux[i] = new int[vertices.size()];
		for (unsigned int j = 0; j < vertices.size(); j++) {
			arrayCaminho[i][j] = custoAresta(i, j, vertices);
			arrayCaminhoAux[i][j] = -1;
		}
	}

	for (unsigned int k = 0; k < vertices.size(); k++)
		for (unsigned int i = 0; i < vertices.size(); i++)
			for (unsigned int j = 0; j < vertices.size(); j++) {
				if (arrayCaminho[i][k] == INFINITO || arrayCaminho[k][j]
						== INFINITO)
					continue;

				int val = min(arrayCaminho[i][j],
						arrayCaminho[i][k] + arrayCaminho[k][j]);
				if (val != arrayCaminho[i][j]) {
					arrayCaminho[i][j] = val;
					arrayCaminhoAux[i][j] = k;
				}
			}
}

vector<unsigned int> Algoritmo::procuraEmProfundidade(unsigned int origem, vector<Vertice *> & vertices)
{
	vector<unsigned int> resultado;
	vector<Aresta>::iterator arestasIt, arestasFim;
	vector<Vertice *>::iterator verticeIt, verticeFim;
	stack<Vertice *> pilha;
	Vertice * verticeActual;

	verticeIt = vertices.begin();
	verticeFim = vertices.end();

	for (; verticeIt != verticeFim; ++verticeIt) {
		(*verticeIt)->setVisitado(false);
	}

	verticeActual = vertices[origem];
	resultado.push_back(origem);
	arestasIt = verticeActual->getArestaIt();
	arestasFim = verticeActual->getArestaFim();

	do {
		verticeActual->setVisitado(true);

		if (arestasIt != arestasFim) {

			if (arestasIt->getDestino()->isVisitado()) {
				++arestasIt;
				continue;
			}

			pilha.push(verticeActual);
			verticeActual = arestasIt->getDestino();
			resultado.push_back(verticeActual->getID());
			arestasIt = verticeActual->getArestaIt();
			arestasFim = verticeActual->getArestaFim();

		} else {
			if (!pilha.empty()) {
				verticeActual = pilha.top();
				pilha.pop();
				arestasIt = verticeActual->getArestaIt();
				arestasFim = verticeActual->getArestaFim();

				for(; arestasIt != arestasFim; ++arestasIt) {
					if(!arestasIt->getDestino()->isVisitado()) {
						pilha.push(verticeActual);
						verticeActual = arestasIt->getDestino();
						resultado.push_back(verticeActual->getID());
						arestasIt = verticeActual->getArestaIt();
						arestasFim = verticeActual->getArestaFim();
						break;
					}
				}
			}
		}
	} while (!pilha.empty());

	return resultado;
}
