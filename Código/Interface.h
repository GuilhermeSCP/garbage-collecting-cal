/*
 * Interface.h
 *
 *  Created on: 17 de Abril de 2012
 *      Author: Cristiano Carvalheiro
 *      		Daniel Teixeira
 *      		Luis Guilherme Martins
 * Description: Definicao da classe e respectivos atributos e metodos
 *
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "Gestor.h"
#include <iomanip>
#include <conio.h>
#include <fstream>
/**
 * @brief Classe responsavel pela interface e interacao com o utilizador
 */
class Interface {
private:
	Gestor* gestor;
	string verticesFile;
	string arestasFile;
	string adjacentesFile;
	static int porta;

	/**
	 * @brief Funcao para carregar o mapa para o gestor atraves do construtor
	 */
	boolean carregarMapa();

	/**
	 * @brief Funcao de interface para gerir os pontos de recolha, opcoes de adicionar ou remover
	 */
	void gerirPontosRecolha();

	/**
	 * @brief Funcao para definir a estacao de recolha, de onde os camioes partem
	 */
	void definirEstacao();

	/**
	 * @brief Funcao para calcular as rotas de recolha, mostrando o resultado no final
	 */
	void calcularRota();

	/**
	 * @brief Funcao para gerir a frota de camioes, opcoes de adicionar ou remover
	 */
	void gerirFrota();

	/**
	 * @brief Funcao para aumentar o numero da porta
	 */
	static void proximaPorta();

public:

	/**
	 * @brief Contrutor por defeito da classe Interface
	 */
	Interface() {
		verticesFile = "nodes.txt";
		arestasFile = "roads.txt";
		adjacentesFile = "subroads.txt";
	}
	;

	/**
	 * @brief Funcao para mostrar a interface do menu principal do programa
	 */
	void menuPrincipal();
};


#endif /* INTERFACE_H_ */
