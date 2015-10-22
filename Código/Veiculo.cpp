/*
 * Veiculo.cpp
 *
 *  Created on: 17 de Abril de 2012
 *      Author: Cristiano Carvalheiro
 *      		Daniel Teixeira
 *      		Luis Guilherme Martins
 * Description: Implementacao da classe e respectivos e metodos
 *
 */

#include "Veiculo.h"

using namespace std;

int Veiculo::numVeiculos=0;

Veiculo::Veiculo()
{
	distanciaPercorrida = 0.0;
	nroParagens = 0;
	valido = false;
	id=numVeiculos;
	numVeiculos++;
}

unsigned int Veiculo::getID() const
{
	return id;
}

void Veiculo::setID(unsigned int id)
{
	this->id=id;
}

unsigned int Veiculo::getParagens() const
{
	return nroParagens;
}

double Veiculo::getDistanciaPercorrida() const
{
	return distanciaPercorrida;
}

void Veiculo::setDistanciaPercorrida(double distancia)
{
	distanciaPercorrida=distancia;
}

void Veiculo::setParagens(unsigned int paragens)
{
	nroParagens = paragens;
}

void Veiculo::setCaminho(vector<unsigned int> caminho)
{
	this->caminho = caminho;
}

vector<unsigned int> Veiculo::getCaminho() const
{
	return caminho;
}

void Veiculo::setValido(bool valido)
{
	this->valido = valido;
}

bool Veiculo::isValido() const
{
	return valido;
}

