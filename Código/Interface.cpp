/*
 * Interface.cpp
 *
 *  Created on: 17 de Abril de 2012
 *      Author: Cristiano Carvalheiro
 *      		Daniel Teixeira
 *      		Luis Guilherme Martins
 * Description: Implementacao da classe e respectivos e metodos
 *
 */

#include "Interface.h"

int Interface:: porta = 7772;

boolean Interface::carregarMapa() {
	ifstream nodes_is, roads_is, subroads_is;
	system("CLS");

	verticesFile = "nodes.txt";
	arestasFile = "roads.txt";
	adjacentesFile = "subroads.txt";

	nodes_is.open(verticesFile.c_str());
	roads_is.open(arestasFile.c_str());
	subroads_is.open(adjacentesFile.c_str());

	if ((!nodes_is.is_open()) || (!roads_is.is_open())
			|| (!subroads_is.is_open())) {
		nodes_is.close();
		roads_is.close();
		subroads_is.close();
		return false;
	} else {
		nodes_is.close();
		roads_is.close();
		subroads_is.close();
	}

		system("CLS");
		cout << "A carregar o mapa..." << endl;

		gestor = new Gestor(verticesFile, arestasFile, adjacentesFile, porta);

		gestor->actualizarGrafo();

		cout << "Mapa Carregado!" << endl << endl;
		system("PAUSE");

		return true;
}



void Interface::proximaPorta()
{
	++porta;
}

void Interface::calcularRota()
{
	system("CLS");
	gestor->calcularRota();
	cout << "\t\t-- Rotas calculadas --\n\n";
	gestor->mostraStats();
	//gestor->mostraCaminhos();
	system("PAUSE");
}

void Interface::gerirPontosRecolha() {
	int op = 0;
	string tmp = "";
	boolean validInput = true;
	boolean validTmp = false;
	unsigned int vertice;
	boolean result;

	do {
		system("CLS");

		cout << "\t\t-- Gerir Pontos de Recolha --\n\n"
				<< "\t1 - Adicionar ponto de recolha\n"
				<< "\t2 - Remover ponto de recolha\n"
				<< "\t3 - Voltar\n";

		if (!validInput) {
			validInput = true;
			cout << "Comando desconhecido. Tente novamente!\n";
		}

		cout << "Introduza o numero da opcao: ";

		do {
			getline(cin, tmp);
		} while (tmp.size() == 0);

		op = atoi(tmp.c_str());

		switch (op) {
		case 1:
			validTmp = false;
			while (!validTmp) {
				system("CLS");

				do {
					cout
							<< "Introduza o numero do vertice que pretende que seja a ponto de recolha: ";
					getline(cin, tmp);
					vertice = atoi(tmp.c_str());
				} while (vertice < 0);

				if ((vertice >= 0) && (vertice <= gestor->getVerticeMaxID()))
					validTmp = true;
				else {
					cout << "Esse vertice nao existe\n\n";
					system("PAUSE");
				}
			}

			result = gestor->adicionarPontodeRecolha(vertice);

			if (result) {
				cout << "Vertice " << vertice
						<< " passou a ser um ponto de recolha.\n\n";
			} else {
				cout << "Nao e possivel efectuar a operacao nesse vertice.\n\n";
			}
			gestor->actualizarGrafo();
			system("PAUSE");

			break;
		case 2:
			validTmp = false;
			while (!validTmp) {
				system("CLS");
				do {
					cout
							<< "Introduza o numero do vertice que pretende que deixe de ser ponto de recolha: ";
					getline(cin, tmp);
					vertice = atoi(tmp.c_str());
				} while (vertice < 0);

				if ((vertice >= 0) && (vertice <= gestor->getVerticeMaxID()))
					validTmp = true;
				else {
					cout << "Esse vertice nao existe\n\n";
					system("PAUSE");
				}
			}

			result = gestor->removePontodeRecolha(vertice);

			if (result) {
				cout << "Vertice " << vertice
						<< " deixou de ser um ponto de recolha.\n\n";
			} else {
				cout << "Nao e possivel efectuar a operacao nesse vertice.\n\n";
			}
			gestor->actualizarGrafo();
			system("PAUSE");

			break;
		case 3:
			system("CLS");
			return;
			break;
		default:
			validInput = false;
			break;
		}
		gestor->actualizarGrafo();
	} while (op != 3);
}

void Interface::definirEstacao() {
	int vertice = 0;
	string tmp = "";
	boolean validInput = true;

	system("CLS");

	cout << "\t\t-- Definir Estacao de Recolha --\n\n";

	validInput = false;

	while (!validInput) {
		system("CLS");
		cout
				<< "Introduza o numero do vertice que pretende que seja a estacao: ";
		while (!(cin >> vertice)) {
			cin.clear();
			cin.ignore(1024, '\n');
			cout
					<< "Introduza o numero do vertice que pretende que seja a estacao: ";
		}

		if ((vertice >= 0) && (vertice <= gestor->getVerticeMaxID()))
			validInput = true;
		else {
			cout << "Esse vertice nao existe\n\n";
			system("PAUSE");
		}
	}

	if (gestor->setLixeira(vertice)) {
		cout << "\nEstacao situada no vertice " << vertice << ".\n\n";
		gestor->actualizarGrafo();
	} else
		cout << "Nao e possivel colocar esse vertice como estacao principal.\n";

	system("PAUSE");
}

void Interface::gerirFrota() {
	int op = 0;
	string tmp = "";
	boolean validInput = true;
	boolean validQuant = false;
	unsigned int quant = 0;



	do {
		system("CLS");

		cout << "\t\t-- Gerir Frota --\n\n"
					<< "\t1 - Adicionar Camiao\n"
					<< "\t2 - Remover Camiao\n"
					<< "\t3 - Voltar\n";

		if (!validInput) {
			validInput = true;
			cout << "Comando desconhecido. Tente novamente!\n";
		}

		cout << "Introduza o numero da opcao: ";

		do {
			getline(cin, tmp);
		} while (tmp.size() == 0);

		op = atoi(tmp.c_str());

		switch (op) {
		case 1:
			validQuant = false;
			while (!validQuant) {
				system("CLS");
				cout
						<< "Introduza o numero de camioes que pretende adicionar: ";
				while (!(cin >> quant)) {
					cin.clear();
					cin.ignore(1024, '\n');
					cout
							<< "Introduza o numero de camioes que pretende adicionar: ";
				}
					validQuant = true;
			}

			if (quant != 0) {
				gestor->adicionarVeiculo(quant);
				cout << quant << " camiao(oes) adicionado(s) a frota.\n\n";
			} else
				cout << "Nao adicionou camioes a frota.\n\n";

			cout << gestor->getNumCamioes() << " camioes na frota.\n\n";

			system("PAUSE");
			break;
		case 2:
			validQuant = false;
			while (!validQuant) {
				system("CLS");
				cout << "Introduza o numero de camioes que pretende remover: ";
				while (!(cin >> quant)) {
					cin.clear();
					cin.ignore(1024, '\n');
					cout
							<< "Introduza o numero de camioes que pretende remover: ";
				}
				validQuant = true;
			}

			if (quant != 0) {
				boolean res = gestor->removeVeiculo(quant);

				if (res)
					cout << quant << " camiao(oes) removido(s) da frota.\n\n";
				else
					cout << "Impossivel remover " << quant
							<< " camiao(oes) da frota.\n\n";
			} else
				cout << "Nao removeu camioes a frota.\n";

			cout << gestor->getNumCamioes() << " camioes na frota.\n\n";

			system("PAUSE");
			break;
		case 3:
			system("CLS");
			return;
			break;
		default:
			validInput = false;
			break;
		}
	} while (op != 3);
}

void Interface::menuPrincipal() {
	cout << "\n\n\t\t -- Bem Bindo --\n\n\n";

	system("PAUSE");



	if (!carregarMapa()) {
		system("CLS");

		cout << "Problema a carregar mapa!\n"
				<< "Por favor certifique-se que os ficheiros do mapa estão correctamente "
				<< "instalados e volte a iniciar o programa.";

		system("PAUSE");

		return;
	}
	else {

		int op = 0;
		string tmp = "";
		boolean validInput = true;

		do {
			system("CLS");

			cout << "\t\t-- Software de Recolha do Lixo --\n\n"
				<< "\t1 - Definir estacao de recolha\n"
				<< "\t2 - Gerir pontos de recolha\n" << "\t3 - Gerir frota\n"
				<< "\t4 - Calcular Rotas\n" << "\t5 - Sair\n";

			if(!validInput) {
				validInput = true;
				cout << "Comando desconhecido. Tente novamente!\n";
			}
			cout << "Introduza o numero da opcao: ";

			do {
				getline(cin, tmp);
			} while (tmp.size() == 0);

			op = atoi(tmp.c_str());

			switch (op) {
			case 1:
				definirEstacao();
				break;
			case 2:
				gerirPontosRecolha();
				break;
			case 3:
				gerirFrota();
				break;
			case 4:
				calcularRota();
				break;
			case 5:
				system("CLS");
				return;
				break;
			default:
				validInput = false;
				break;
			}
		} while (op != 5);
	}
}
