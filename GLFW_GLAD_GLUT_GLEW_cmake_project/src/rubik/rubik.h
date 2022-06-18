#ifndef RUBIK_H
#define RUBIK_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "value.h"
#include "cube.h"
#include "group.h"
#include "params.h"
#include "solver.h"

typedef std::map<char, Cube* > Cubes;
typedef std::vector< std::vector<char> > SolverFace;

class RubikCube {
public:	
	Cubes cubes;			// Contenedor de todos los cubos instanciados <cube_id, Cube *>
	group::VecGroup groups;	// Contenedor de vectores con los cube_ids asignados a cada grupo(Camada) <group_id, vec(cube_ids) >	
	
	RubikCube();	
	void render_transformation(GLFWwindow* window, char group_id, bool clockwise);
	void do_movements(GLFWwindow* window, std::vector<std::string> steps);
	
	// OpenGL
	void init_cubes();
	void draw_cubes();
	void delete_buffer_cubes();

	// Solver
	SolverFace map_groups(char group);

private:
	// Transformaciones 
	std::vector<char> update_group(std::vector<char> to_update, bool clockwise);
	void update_neighborhood(char group_id, bool clockwise);
	void transformation(char group_id, bool clockwise);

	// Consola
	void print_content(std::vector< std::vector<char> > mapper, std::vector<char> ids, bool border, bool content);
	void print_rubik(bool content);
};

RubikCube::RubikCube() {
	std::vector<char> ids = values::cube_ids;
	std::vector<glm::vec3> positions = values::cube_positions;
	std::vector<std::vector<Feature> > colors = values::cube_features;

	for (int i = 0; i < ids.size(); i++) {
		Cube* tmp_cube = new Cube(ids[i], colors[i]);
		tmp_cube->translation(positions[i]);
		this->cubes[ids[i]] = tmp_cube;
	}
	this->groups = group::default_groups();
	//print_rubik(false);
}

void RubikCube::init_cubes() {
	for (auto i = cubes.begin(); i != cubes.end(); ++i) {
		char key = i->first;
		cubes[key]->init_GL();
	}
}

void RubikCube::draw_cubes() {
	for (auto i = cubes.begin(); i != cubes.end(); ++i) {
		char key = i->first;
		cubes[key]->draw_GL();
	}
}

void RubikCube::delete_buffer_cubes() {
	for (auto i = cubes.begin(); i != cubes.end(); ++i) {
		char key = i->first;
		cubes[key]->delete_buffer_GL();
	}
}

// Clokcwise -> True: sentido horario || False: Sentido Antihorario 
// Group_id  -> Grupo que aplicaremos la transformacíon, el caracter indica una key del map definido en group.h 
void RubikCube::transformation(char group_id, bool clockwise) {
	group::MapGroup axis = clockwise ? group::rotation_axis_clockwise() : group::rotation_axis_inverted();
	group::MapGroup position = clockwise ? group::translation_pos_clockwise() : group::translation_pos_inverted();

	std::vector<char> cube_ids = groups[group_id];
	for (int i = 0; i < cube_ids.size(); i++) {
		char key = cube_ids[i];
		cubes[key]->transformation(axis[group_id], position[group_id]);
	}
}

// Render 
void RubikCube::render_transformation(GLFWwindow* window, char group_id, bool clockwise) {
	for (int i = 0; i < 9; i++) {
		// Aplicamos las transformaciones
		transformation(group_id, clockwise);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		draw_cubes();
		params::sleep();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// Actualizamos los grupos
	update_neighborhood(group_id, clockwise);
	// Print (Opcional)
	print_rubik(false);
}

// Actualiza el grupo(camada) sobre la cual se aplico la transformacion
std::vector<char> RubikCube::update_group(std::vector<char> to_update, bool clockwise) {
	int rotation_value = clockwise ? 6 : 2;
	char center = to_update.back();
	to_update.pop_back();
	std::rotate(to_update.begin(), to_update.begin() + rotation_value, to_update.end());
	to_update.push_back(center);
	return to_update;
}

// Actualiza los grupos vecinos de un grupo especifico(group_id)
void RubikCube::update_neighborhood(char group_id, bool clockwise) {
	std::vector<char> neighborhood = clockwise ? group::rotation_clockwise(group_id) : group::rotation_inverted(group_id);

	// Grupo (Camada) a la cual hemos aplicado la transformacion
	std::vector<char> group = groups[group_id];

	// U B D F U
	std::vector< std::vector<char> > swappers_clockwise = {
		{ group[0], group[2] }, { group[1], group[3] }, { group[2], group[4] }, // U -> B
		{ group[2], group[4] }, { group[3], group[5] }, { group[4], group[6] }, // B -> D
		{ group[4], group[6] }, { group[5], group[7] }, { group[6], group[0] }, // D -> F
		{ group[6], group[0] }, { group[7], group[1] }, { group[0], group[2] },	// F -> U
	};

	// U F D B U
	std::vector< std::vector<char> > swappers_inverted = {
		{ group[2], group[0] }, { group[1], group[7] }, { group[0], group[6] }, // U -> F
		{ group[0], group[6] }, { group[7], group[5] }, { group[6], group[4] }, // F -> D
		{ group[6], group[4] }, { group[5], group[3] }, { group[4], group[2] }, // D -> B
		{ group[4], group[2] }, { group[3], group[1] }, { group[2], group[0] },	// B -> U
	};

	std::vector< std::vector<char> > swappers = clockwise ? swappers_clockwise : swappers_inverted;

	// Obteniendo la orientacion actual del color de cada cubo
	std::vector< std::vector<char> > colors;
	for (int i = 0; i < neighborhood.size() - 3; i++) {
		int idx = cubes[swappers[i][0]]->find_color(neighborhood[i]);
		colors.push_back({
			cubes[swappers[i][0]]->container_colors[idx].first,
			cubes[swappers[i][0]]->container_colors[idx].second,
		});
	}

	// Acualizamos los cube_ids en cada grupo vecino correspondiente
	for (int i = 0; i < neighborhood.size() - 3; i++) {
		// Grupo vecino al que aplicaremos el cambio
		char group_id = neighborhood[i + 3];
		// Obteniendo el grupo al que aplicaremos los cambios
		group = groups[group_id];

		// current_cube_id (Grupo Actual) reemplazara a neighbour_cube_id(Grupo vecino)
		char current_cube_id = swappers[i][0];
		char neighbour_cube_id = swappers[i][1];

		// Buscando la posicion del elemento que cambiaremos (neighbour_cube_id)
		std::vector<char>::iterator itr = std::find(group.begin(), group.end(), neighbour_cube_id);
		int index = std::distance(group.begin(), itr);

		// Actualizamos el cube_id en su nuevo grupo 
		groups[group_id][index] = current_cube_id;

		// Actualizamos la orientacion del color ej. lado blanco(del cubo) presente en grupo UP pasa a lado blanco en el grupo BACK				
		int tmp = cubes[current_cube_id]->find_color(colors[i][0], colors[i][1]);
		cubes[current_cube_id]->container_colors[tmp].second = group_id;
	}
	// Actualizamos la rotacion sobre el grupo que se aplico la transformacion (group_id)	
	group = groups[group_id];
	groups[group_id] = update_group(group, clockwise);
}

// Solver
SolverFace RubikCube::map_groups(char group_id) {
	std::vector<char> group = groups[group_id];
	SolverFace container = {
		{group[0], group[1], group[2]},
		{group[7], group[8], group[3]},
		{group[6], group[5], group[4]}
	};
	
	SolverFace solver_face;
	for (int i = 0; i < container.size(); i++) {
		std::vector<char> row = container[i];		
		std::vector<char> tmp = {};
		for (int j = 0; j < row.size(); j++) {
			char cube = row[j];			
			char color = cubes[cube]->get_color(group_id);
			tmp.push_back(color);
		}
		solver_face.push_back(tmp);
	}
	return solver_face;
}

// El vector steps contiene la lista de transformaciones que debe realizarse
void RubikCube::do_movements(GLFWwindow* window, std::vector<std::string> steps) {
	group::MapMovements movements = group::movements();	
	for (int i = 0; i < steps.size(); i++) {
		std::string step = steps[i];	

		std::cout << "Paso " << i + 1 << ": " << step << std::endl;

		char group_id = movements[step].first;
		bool clockwise = movements[step].second;
		if (step[1] == '2') {						
			render_transformation(window, group_id, clockwise);			
			render_transformation(window, group_id, clockwise);			
		}
		else {
			render_transformation(window, group_id, clockwise);
		}		
	}
}

// CONSOLA
void RubikCube::print_content(std::vector< std::vector<char> > mapper, std::vector<char> group_id, bool border, bool content) {
	std::map<char, char*> console_color = color::console_colors;
	for (int i = 0; i < mapper.size(); i++) {
		std::vector<char> row = mapper[i];
		std::string border_left = border ? "            |" : "|";
		std::cout << border_left;
		for (int j = 0; j < row.size(); j++) {
			char cube = row[j];
			char group = group_id[j];
			char color = cubes[cube]->get_color(group);
			char* console = console_color[color];
			printf(console, content ? cubes[cube]->id : color);
		}
		std::cout << std::endl;
	}
}

// content -> true: visualizar el id del cubo, false, visualizar solo el color 
void RubikCube::print_rubik(bool content) {
	std::vector<char> mapper = groups['U'];
	std::vector<char> ids = { 'U', 'U', 'U' };
	std::vector< std::vector<char> > top = {
		{mapper[0], mapper[1], mapper[2]},
		{mapper[7], mapper[8], mapper[3]},
		{mapper[6], mapper[5], mapper[4]}
	};
	print_content(top, ids, true, content);
	
	std::vector<char> left = groups['L'];
	std::vector<char> front = groups['F'];
	std::vector<char> right = groups['R'];
	std::vector<char> back = groups['B'];
	ids = { 'L', 'L', 'L', 'F', 'F', 'F', 'R', 'R', 'R', 'B', 'B', 'B' };
	std::vector< std::vector<char> > mid = {
		{left[0], left[1], left[2], front[0], front[1], front[2], right[0], right[1], right[2], back[0], back[1], back[2]},
		{left[7], left[8], left[3], front[7], front[8], front[3], right[7], right[8], right[3], back[7], back[8], back[3]},
		{left[6], left[5], left[4], front[6], front[5], front[4], right[6], right[5], right[4], back[6], back[5], back[4]}
	};
	print_content(mid, ids, false, content);
	
	mapper = groups['D'];
	ids = { 'D', 'D', 'D' };
	std::vector< std::vector<char> > down = {
		{mapper[0], mapper[1], mapper[2]},
		{mapper[7], mapper[8], mapper[3]},
		{mapper[6], mapper[5], mapper[4]}
	};
	print_content(down, ids, true, content);
	std::cout << std::endl;	
}

#endif