/*
 * Veiculo.h
 *
 *  Created on: 17 de Abril de 2012
 *      Author: Cristiano Carvalheiro
 *      		Daniel Teixeira
 *      		Luis Guilherme Martins
 * Description: Definicao da classe e respectivos atributos e metodos
 *
 */

#ifndef VEICULO_H_
#define VEICULO_H_

#include <vector>

using namespace std;

/**
 * @brief Classe que agrupa todas as funcoes necessarias a criacao do objecto Veiculo
 */
class Veiculo
{
private:
	unsigned int id;
	double distanciaPercorrida;
	unsigned int nroParagens;
	vector<unsigned int> caminho;
	bool valido;
	static int numVeiculos;

public:
	/**
	 * @brief Construtor da classe Veiculo
	 */
	Veiculo();
	/**
	 * @brief Devolve o ID do Veiculo
	 *
	 * @return ID do Veiculo
	 */
	unsigned int getID() const;
	/**
	 * @brief Altera o ID do Veiculo
	 *
	 * @param id Novo ID
	 */
	void setID(unsigned int id);
	/**
	 * @brief devolve a distancia percorrida pelo Veiculo
	 *
	 * @return distanciaPercorrida
	 */
	double getDistanciaPercorrida() const;
	/**
	 * @brief Altera a distancia percorrida pelo Veiculo
	 *
	 * @param distancia Nova distancia percorrida
	 */
	void setDistanciaPercorrida(double distancia);
	/**
	 * @brief Devolve o numero de paragens do Veiculo, ou seja, o numero de Vertices visitados pelo Veiculo
	 *
	 * @return Numero de paragens
	 */
	unsigned int getParagens() const;
	/**
	 * @brief Altera o numero de paragens do Veiculo, ou seja, o numero de Vertices visitados pelo Veiculo
	 *
	 * @param paragens Novo numero de paragens
	 */
	void setParagens(unsigned int paragens);
	/**
	 * @brief Devolve um vector com os IDs do vertices percorridos pelo Veiculo
	 *
	 * @return Caminho percorrido pelo Veiculo
	 */
	vector<unsigned int> getCaminho() const;
	/**
	 * @brief Altera o caminho a ser percorrido pelo Veiculo
	 *
	 * @param caminho Novo caminho
	 */
	void setCaminho(vector<unsigned int> caminho);
	/**
	 * @brief Devolve o estado do Veiculo
	 *
	 * @return TRUE se o Veiculo for utilizado, FALSE em caso contrario
	 */
	bool isValido() const;
	/**
	 * @brief Altera o status do Veiculo
	 *
	 * @param valido Novo estado de validade do Veiculo
	 */
	void setValido(bool valido);

};



#endif /* VEICULO_H_ */
