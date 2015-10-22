/*
 * Gestor.h
 *
 *  Created on: 17 de Abril de 2012
 *      Author: Cristiano Carvalheiro
 *      		Daniel Teixeira
 *      		Luis Guilherme Martins
 * Description: Definicao da classe e respectivos atributos e metodos
 *
 */

#ifndef GESTOR_H_
#define GESTOR_H_

#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "Algoritmo.h"
#include "GraphBuilder.h"
#include "graphviewer.h"
#include "Veiculo.h"

const string CORES [] = {"pink", "red", "yellow" "green", "magenta", "red", "blue", "cyan", "red", "orange", "green"};
/**
 * @brief Classe responsavel pela gestao do programa
 */
class Gestor
{
public:
	vector<Vertice *> vertices;
	vector<Veiculo> camioes;
	int ** caminho;
	int ** caminhoAux;
	GraphViewer * grafoViewer;
	unsigned int lixeira;
	vector<unsigned int> pontosAcessiveis;
	vector<unsigned int> pontosDeRecolha;

	/**
	 * @brief Contrutor por defeito da classe Gestor
	 */
	Gestor();

	/**
	 * @brief Contrutor da classe gestor
	 * @param nodes Nome do ficheiro de vertices
	 * @param roads Nome do ficheiro de ruas
	 * @param subroads Nome do ficheiro de adjacencias
	 * @param porta Porta a usar
	 */
	Gestor(string nodes, string roads, string subroads, int porta);

	/**
	 * @brief Funcao para adicionar um novo ponto de recolha
	 * @param vertice Numero do vertice para passar a ponto de recolha
	 * @return TRUE se conseguir passar o vertice a ponto de recolha, FALSE se acontecer o contrario
	 */
	bool adicionarPontodeRecolha(unsigned int vertice);

	/**
	 * @brief Funcao para remover um ponto de recolha
	 * @param vertice Numero do vertice para deixar de ser ponto de recolha
	 * @return TRUE se conseguir remover o ponto de recolha, FALSE se acontecer o contrario
	 */
	bool removePontodeRecolha(unsigned int vertice);

	/**
	 * @brief Funcao para definir a estacao de recolha
	 * @param vertice Numero do vertice para passar a ser estacao de recolha
	 * @return TRUE se conseguir passar o vertice a estacao de recolha, FALSE se acontecer o contrario
	 */
	bool setLixeira(unsigned int vertice);

	/**
	 * @brief Funcao que retorna o maior id de vertices existente
	 * @return Maior id existente
	 */
	unsigned int getVerticeMaxID() const;

	/**
	 * @brief Funcao que actualiza o estado do grafo
	 */
	void actualizarGrafo();

	/**
	 * @brief Funcao que adiciona 1 ou mais camioes a frota
	 * @param quant Quantidade de camioes a serem adicionados
	 */
	void adicionarVeiculo(unsigned int quant);

	/**
	 * @brief Funcao que remove 1 ou mais camioes a frota
	 * @param quant Quantidade de camioes a serem removidos
	 * @return TRUE se conseguir remover a quant camioes a frota, FALSE se acontecer o contrario
	 */
	bool removeVeiculo(unsigned int quant);

	/**
	 * @brief Funcao que calcula todas as rotas dos camioes para recolher o lixo
	 */
	void calcularRota();

	/**
	 * @brief Funcao responsavel pela animacao dos caminhos na API graphviewer
	 */
	void mostraCaminhos();

	/**
	 * @brief Funcao que mostra na consola as estatisticas da rota calculada
	 */
	void mostraStats();

	/**
	 * @brief Funcao que calcula as estatisticas da rota calculada
	 */
	void calculaStats();

	/**
	 * @brief Funcao que remove os vertices repetidos dos proximos camioes a utilizar
	 * @param verts Vector de vertices a analisar
	 * @param camiao Indice do camiao que esta a ser utilizado
	 */
	void removeVerticeRepetido(vector<unsigned int> verts, unsigned int camiao);

	/**
	 * @brief Funcao que retorna o numero de camieos que existem
	 * @return Numero de camioes existentes na frota
	 */
	unsigned int getNumCamioes();
};

#endif /* GESTOR_H_ */
