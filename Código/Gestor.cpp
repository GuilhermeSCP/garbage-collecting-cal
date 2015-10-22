/*
 * Gestor.cpp
 *
 *  Created on: 17 de Abril de 2012
 *      Author: Cristiano Carvalheiro
 *      		Daniel Teixeira
 *      		Luis Guilherme Martins
 * Description: Implementacao da classe e respectivos e metodos
 *
 */

#include "Gestor.h"

bool Gestor::setLixeira(unsigned int vertice)
{
	if(vertice >= vertices.size())
		return false;
	else if(vertice == lixeira)
		return true;
	else if(binary_search(pontosDeRecolha.begin(), pontosDeRecolha.end(), vertice))
		return false;
	else {
		pontosDeRecolha.clear();
		pontosAcessiveis = Algoritmo::procuraEmProfundidade(vertice, vertices);
		sort(pontosAcessiveis.begin(), pontosAcessiveis.end());
		lixeira = vertice;
		return true;
	}
}

bool Gestor::adicionarPontodeRecolha(unsigned int vertice)
{
	bool acessivel = binary_search(pontosAcessiveis.begin(), pontosAcessiveis.end(), vertice);
	bool defenido = binary_search(pontosDeRecolha.begin(), pontosDeRecolha.end(), vertice);

	if(vertice == lixeira)
		return false;

	if(pontosDeRecolha.empty() && acessivel) {
		pontosDeRecolha.push_back(vertice);
		sort(pontosDeRecolha.begin(), pontosDeRecolha.end());
		return true;
	} else if (defenido) {
		return false;
	} else if (acessivel) {
		pontosDeRecolha.push_back(vertice);
		sort(pontosDeRecolha.begin(), pontosDeRecolha.end());
		return true;
	} else {
		return false;
	}
}

bool Gestor::removePontodeRecolha(unsigned int vertice)
{
	vector<unsigned int>::iterator it = pontosDeRecolha.begin(), end_it = pontosDeRecolha.end();
	if((it = find(it, end_it, vertice)) != end_it) {
		pontosDeRecolha.erase(it);
		return true;
	} else
		return false;
}

Gestor::Gestor(string node_input, string street_input, string substreet_input, int port)
{
	lixeira = 0;
	camioes.push_back(Veiculo());

	ifstream node, street, substreet;
	node.open(node_input.c_str());
	street.open(street_input.c_str());
	substreet.open(substreet_input.c_str());

	if(node.is_open() && street.is_open() && substreet.is_open()) {
		GraphBuilder::construirGrafo(vertices, node, street, substreet);
	}

	grafoViewer = new GraphViewer(800, 800, false, port);
	grafoViewer->createWindow(800, 800);
	grafoViewer->defineVertexColor("blue");
	grafoViewer->defineEdgeColor("black");

	vector<Vertice *>::iterator it_v, end_it_v;
	vector<Aresta>::iterator it_e, end_it_e;

	it_v = vertices.begin();
	end_it_v = vertices.end();

	for(; it_v != end_it_v; ++it_v) {
		grafoViewer->addNode((*it_v)->getID(), (*it_v)->getCoordenadas().first, (*it_v)->getCoordenadas().second);
	}

	it_v = vertices.begin();
	end_it_v = vertices.end();

	for(; it_v != end_it_v; ++it_v) {
		it_e = (*it_v)->arestas.begin();
		end_it_e = (*it_v)->arestas.end();
		for(; it_e != end_it_e; ++it_e) {

			grafoViewer->addEdge(it_e->getID(), (*it_v)->getID(), it_e->getDestino()->getID(), EdgeType::DIRECTED);
		}
	}

	Algoritmo::floydWarshallCaminhoMaisCurto(caminho, caminhoAux, vertices);

	pontosAcessiveis = Algoritmo::procuraEmProfundidade(lixeira, vertices);
	sort(pontosAcessiveis.begin(), pontosAcessiveis.end());
}

Gestor::Gestor() {}

void Gestor::actualizarGrafo()
{
	vector<Vertice *>::iterator v_it, v_end_it;
		v_it = vertices.begin();
		v_end_it = vertices.end();

		for(; v_it != v_end_it; ++v_it) {
			grafoViewer->setVertexColor((*v_it)->getID(), "blue");
		}

		grafoViewer->setVertexColor(lixeira, "green");

		vector<unsigned int>::iterator it, end_it;
		it = pontosDeRecolha.begin();
		end_it = pontosDeRecolha.end();

		for(; it != end_it; ++it) {
			grafoViewer->setVertexColor((*it), "red");
		}

		grafoViewer->rearrange();
}

void Gestor::adicionarVeiculo(unsigned int quant) {
	for (size_t i = 0; i < quant; i++)
		camioes.push_back(Veiculo());
}

bool Gestor::removeVeiculo(unsigned int quant) {
	unsigned int tmp = getNumCamioes();

	if (tmp <= quant)
		return false;
	else {
		for (size_t i = 0; i < quant; i++)
			camioes.erase(camioes.begin());
		return true;
	}
}

unsigned int Gestor::getNumCamioes() {
	return camioes.size();
}

unsigned int Gestor::getVerticeMaxID() const
{
	return (vertices.size() - 1);
}

void Gestor::calcularRota()
{
	vector<unsigned int> res, final_res, verticesRecolha, aux;
	vector<unsigned int>::iterator it, final_it, aux_it;
	unsigned int numCamioes, proximoVertice, tamanhoAux, res_size, aresta, verticesActuais;
	double distanciaMinima, distancia;

	numCamioes = camioes.size();
	verticesRecolha = pontosDeRecolha;

	aux.push_back(lixeira);

	for (size_t i = 0; i < numCamioes; ++i) {
		camioes[i].setValido(false);
		camioes[i].setCaminho(aux);
	}

	while(!verticesRecolha.empty()) {

		for(size_t i = 0; i < numCamioes; ++i) {
			aux = camioes[i].getCaminho();
			camioes[i].setValido(true);
			tamanhoAux = aux.size();
			distanciaMinima = numeric_limits<double>::max();
			it = verticesRecolha.begin();
			final_it = verticesRecolha.end();

			if(!verticesRecolha.empty()) {

				// Determina a distancia actual entre o
				// vertice e todos os outros
				for(; it != final_it; ++it) {
					res = Algoritmo::getCaminho(aux[tamanhoAux - 1], (*it), caminho, caminhoAux, vertices);
					distancia = 0.0;
					res_size = res.size();
					for(size_t j = 0; j < (res_size - 1); ++j) {
						aresta = vertices[res[j]]->getIdAresta(res[j + 1]);
						distancia += vertices[res[j]]->getTamanhoAresta(aresta);
					}

					// Se esta distancia for menor que a anterior
					// e actualizado
					if(distancia <= distanciaMinima) {
						distanciaMinima = distancia;
						proximoVertice = (*it);
						aux_it = it;
					}
				}

				aux.push_back(proximoVertice);
				camioes[i].setCaminho(aux);
				verticesRecolha.erase(aux_it);
			}
		}
	}

	// coloca o vertice final para todos os camioes
	for (size_t i = 0; i < numCamioes; ++i) {
		aux = camioes[i].getCaminho();
		aux.push_back(lixeira);
		camioes[i].setCaminho(aux);
	}

	// Determina o caminho real para cada camiao
	for (size_t i = 0; i < numCamioes; ++i) {
		if(!camioes[i].isValido())
			continue;

		final_res.clear();
		aux = camioes[i].getCaminho();
		verticesActuais = aux.size();

		final_res.push_back(lixeira);

		for (size_t j = 0; j < (verticesActuais - 1); ++j) {
			res = Algoritmo::getCaminho(aux[j], aux[j + 1],
					caminho, caminhoAux, vertices);
			res.erase(res.begin());
			copy(res.begin(), res.end(), back_inserter(final_res));
		}

		// remove os pontos que o camiao actual recolheu por la passar
		// que pertenciam a uma rota de outro camiao
		removeVerticeRepetido(final_res, i);
		camioes[i].setCaminho(final_res);
	}

	calculaStats();
}

void Gestor::mostraStats()
{
	unsigned int nroCamioesUsados = 0;
	double distanciaPercorrida = 0.0, nroParagens = 0.0;

	for(size_t i = 0; i < camioes.size(); ++i) {
		if(!camioes[i].isValido())
			continue;

		vector<unsigned int> caminhoPercorrido = camioes[i].getCaminho();

		cout << "-- Estatisticas da rota resultante --\n\n" << endl;
		cout  << "\tTruck " << i << ":\n";
		cout << "Distancia viajada: " << camioes[i].getDistanciaPercorrida() << " m" << endl;
		cout << "Numero de nos visitados: " << camioes[i].getParagens() << endl;
		cout << "Nos visitados: ";
		for (size_t c = 0; c < caminhoPercorrido.size(); c++) {
			cout << caminhoPercorrido[c] << " ";
		}
		cout << endl << endl;

		++nroCamioesUsados;
		distanciaPercorrida += camioes[i].getDistanciaPercorrida();
		nroParagens += camioes[i].getParagens();
	}

	cout  << "\n\n\t\tResultados totais\n\n\n";
	cout << "Numero de camioes disponiveis: " << camioes.size() << endl;
	cout << "Numero de camioes utilizados: " << nroCamioesUsados << endl;
	cout << "Distancia percorrida total: " << distanciaPercorrida << " m" << endl;
	cout << "Total de nos visitados: " << nroParagens << endl;
}

void Gestor::mostraCaminhos()
{
	srand(time(0));
	unsigned int numCamioes = camioes.size();
	unsigned int tamanhoCaminho = 0, idAresta = 0;
	vector<unsigned int> caminho;
	string cor = "black";

	Sleep(3000);

	for(size_t i = 0; i < numCamioes; ++i) {
		if(camioes[i].isValido()) {
			caminho = camioes[i].getCaminho();
			tamanhoCaminho = caminho.size();
			cor = CORES[rand() % 11];

			grafoViewer->setVertexColor(caminho[0], "blue");
			grafoViewer->setVertexLabel(caminho[0], "Start");
			grafoViewer->rearrange();

			for(size_t j = 0; j < (tamanhoCaminho - 1); ++j) {
				idAresta = vertices[caminho[j]]->getIdAresta(caminho[j+1]);
				if(j != 0)
					grafoViewer->setVertexColor(caminho[j], cor);
				grafoViewer->setEdgeColor(idAresta, cor);
				grafoViewer->setEdgeThickness(idAresta, 5);
				grafoViewer->rearrange();
				Sleep(300);
			}

			grafoViewer->setVertexColor(caminho[tamanhoCaminho - 1], "orange");
			grafoViewer->setVertexLabel(caminho[tamanhoCaminho - 1], "Finish");
			grafoViewer->rearrange();

			Sleep(1500);

			grafoViewer->setVertexColor(caminho[0], "blue");
			grafoViewer->setVertexLabel(caminho[0], " ");

			for(size_t j = 0; j < (tamanhoCaminho - 1); ++j) {
				idAresta = vertices[caminho[j]]->getIdAresta(caminho[j+1]);
				grafoViewer->setVertexColor(caminho[j + 1], "blue");
				grafoViewer->setEdgeColor(idAresta, "black");
				grafoViewer->setEdgeThickness(idAresta, 1);
			}

			grafoViewer->setVertexColor(caminho[tamanhoCaminho - 1], "blue");
			grafoViewer->setVertexLabel(caminho[tamanhoCaminho - 1], " ");
			grafoViewer->rearrange();
		}

		actualizarGrafo();
		Sleep(1500);
	}
}

void Gestor::calculaStats()
{
	unsigned int distanciaTotal, paragensTotal, aresta, tamanhoCaminho;
	vector<unsigned int> auxiliar;
	vector<Veiculo>::iterator camiao_it = camioes.begin(), camiao_end_it = camioes.end();

	for(; camiao_it != camiao_end_it; ++camiao_it) {
		if(!camiao_it->isValido())
			continue;

		auxiliar = camiao_it->getCaminho();
		paragensTotal = 0;
		distanciaTotal = 0;
		tamanhoCaminho = auxiliar.size();
		paragensTotal = tamanhoCaminho;

		for(size_t i = 0; i < (tamanhoCaminho - 1); ++i) {
			aresta = vertices[auxiliar[i]]->getIdAresta(auxiliar[i + 1]);
			distanciaTotal += vertices[auxiliar[i]]->getTamanhoAresta(aresta);
		}

		camiao_it->setDistanciaPercorrida(distanciaTotal);

		camiao_it->setParagens(paragensTotal);
	}
}

void Gestor::removeVerticeRepetido(vector<unsigned int> vertices, unsigned int camiaoActual)
{
	unsigned int numCamioes = camioes.size();
	unsigned int numVertices = vertices.size();
	vector<unsigned int> aux;
	vector<unsigned int>::iterator it, final_it;

	for(size_t i = camiaoActual + 1; i < numCamioes; ++i) {
		if(!camioes[i].isValido())
			continue;

		aux = camioes[i].getCaminho();
		it = aux.begin();
		final_it = aux.end();

		for(size_t j = 0; j < numVertices; ++j) {
			if(vertices[j] == lixeira)
				continue;

			it = find(aux.begin(), aux.end(), vertices[j]);
			final_it = aux.end();

			if(it != final_it) {
				aux.erase(it);
			}
		}

		if(aux.size() > 2)
			camioes[i].setCaminho(aux);
		else
			camioes[i].setValido(false);
	}
}


