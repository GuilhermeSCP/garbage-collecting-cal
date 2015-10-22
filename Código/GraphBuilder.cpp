/*
 * GraphBuilder.cpp
 *
 *  Created on: 17 de Abril de 2012
 *      Author: Cristiano Carvalheiro
 *      		Daniel Teixeira
 *      		Luis Guilherme Martins
 * Description: Implementacao da classe e respectivos e metodos
 *
 */

#include "GraphBuilder.h"

map<ullint, Vertice *> GraphBuilder::mapaVertices;
map<ullint, GraphBuilder::Rua> GraphBuilder::mapaRuas;

double GraphBuilder::calculaDistanciaReal(double d) {
	return ((d * (PI / 180.0)) * EARTH_RADIUS);
}

double GraphBuilder::calculaDistancia(Vertice * v1, Vertice* v2) {
	double r;
	r = (double) (sqrt(
			pow(v2->posX - v1->posX, 2) + pow(v2->posY - v1->posY, 2)));
	return r;
}

void GraphBuilder::lerMapa(ifstream & nos, ifstream & ruas) {
	string reader = "", street_name = "";
	ullint node_code = 0, street_code = 0;
	double pos_x = 0.0, pos_y = 0.0;
	unsigned int index = 0, prev_index = 0;
	bool one_way = false;
	Vertice * temp_vertex = NULL;

	while (!nos.eof()) {
		reader = "";
		getline(nos, reader);

		if (reader.size() != 0) {
			index = reader.find(';');

			if (index != string::npos) {
				node_code = (ullint) strtoll(reader.substr(0, index).c_str(),
						NULL, 10);
				prev_index = index + 1;
				index = reader.find(';', prev_index);

				if (index != string::npos) {
					pos_y = -atof(reader.substr(prev_index, index).c_str());
					prev_index = index + 1;
					index = reader.find(';', prev_index);

					if (index != string::npos) {
						pos_x = atof(reader.substr(prev_index, index).c_str());

						temp_vertex = new Vertice(calculaDistanciaReal(pos_x),
								calculaDistanciaReal(pos_y));
						mapaVertices.insert(
								pair<ullint, Vertice *>(node_code,
										temp_vertex));
					}
				}
			}
		}
	}

	nos.close();

	while (!ruas.eof()) {
		reader = "";
		street_name = "";
		getline(ruas, reader);

		if (reader.size() != 0) {
			index = reader.find(';');

			if (index != string::npos) {
				street_code = (ullint) strtoll(reader.substr(0, index).c_str(),
						NULL, 10);
				prev_index = index + 1;
				index = reader.find(';', prev_index);

				if (index != string::npos) {
					street_name = reader.substr(prev_index, index - prev_index);
					prev_index = index + 1;

					if (reader.substr(prev_index) == "True")
						one_way = true;
					else
						one_way = false;

					mapaRuas.insert(
							pair<ullint, Rua>(street_code,
									Rua(street_name, 0, 0, one_way)));
				}
			}
		}
	}

	ruas.close();
}

void GraphBuilder::ligarVertice(ifstream & subRuas) {
	string reader = "", street_name = "";
	ullint street_code = 0, source_code = 0, dest_code = 0;
	unsigned int prev_index = 0, index = 0;
	map<ullint, Vertice *>::iterator source_it, dest_it;
	map<ullint, Rua>::iterator street_it;
	double weight = 0;
	bool one_way = false;

	// Reads adjacency info
	while (!subRuas.eof()) {
		weight = 0;
		reader = "";
		street_name = "";
		getline(subRuas, reader);
		if (reader.size() != 0) {
			index = reader.find(';');

			// Reads the edge code
			if (index != string::npos) {
				street_code = (ullint) strtoll(reader.substr(0, index).c_str(),
						NULL, 10);
				prev_index = index + 1;
				index = reader.find(';', prev_index);

				// Reads the origin vertex code
				if (index != string::npos) {
					source_code =
							(ullint) strtoll(
									reader.substr(prev_index,
											index - prev_index).c_str(), NULL,
									10);
					prev_index = index + 1;
					index = reader.find(';', prev_index);

					// Reads the destination vertex code
					if (index != string::npos) {
						dest_code =
								(ullint) strtoll(
										reader.substr(prev_index,
												index - prev_index).c_str(),
										NULL, 10);

						source_it = mapaVertices.find(source_code);
						dest_it = mapaVertices.find(dest_code);
						street_it = mapaRuas.find(street_code);

						if ((source_it != mapaVertices.end())
								&& (dest_it != mapaVertices.end())
								&& (street_it != mapaRuas.end())) {
							street_name = street_it->second.nome;
							one_way = street_it->second.sentidoUnico;
							weight = calculaDistancia(source_it->second,
									dest_it->second);

							source_it->second->arestas.push_back(
									Aresta(street_name, weight,
											dest_it->second));
							if (!one_way) {
								dest_it->second->arestas.push_back(
										Aresta(street_name, weight,
												source_it->second));
							}
						}
					}
				}
			}
		}
	}
}

void GraphBuilder::construirGrafo(vector<Vertice*> & vectorVertices,
		ifstream & nos, ifstream & ruas, ifstream & subRuas) {
	map<ullint, Vertice *>::iterator it, end_it;

	mapaRuas.clear();
	mapaVertices.clear();
	vectorVertices.clear();

	lerMapa(nos, ruas);
	ligarVertice(subRuas);

	setCoordenadas();

	it = mapaVertices.begin();
	end_it = mapaVertices.end();

	for (; it != end_it; ++it) {
		vectorVertices.push_back(it->second);
	}

	sort(vectorVertices.begin(), vectorVertices.end(), comparar);

	mapaRuas.clear();
	mapaVertices.clear();
}

void GraphBuilder::setCoordenadas() {
	unsigned int min_x = numeric_limits<unsigned int>::max(), min_y =
			numeric_limits<unsigned int>::max();
	unsigned int cur_x = 0, cur_y = 0;
	map<ullint, Vertice *>::iterator it = mapaVertices.begin(), end_it =
			mapaVertices.end();

	for (; it != end_it; ++it) {
		cur_x = (*it).second->posX;
		cur_y = (*it).second->posY;

		if (cur_x < min_x)
			min_x = cur_x;

		if (cur_y < min_y)
			min_y = cur_y;
	}

	it = mapaVertices.begin();
	min_x *= -1;
	min_y *= -1;

	for (; it != end_it; ++it) {
		(*it).second->posX += min_x;
		(*it).second->posY += min_y;
	}
}

bool GraphBuilder::comparar(Vertice * v1, Vertice * v2) {
	return v1->getID() < v2->getID();
}
