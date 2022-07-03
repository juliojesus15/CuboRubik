#ifndef RUBIK_H
#define RUBIK_H

#include <algorithm>
#include <iostream>
#include <vector>

#include "value.h"
#include "cube.h"
#include "group.h"
#include "params.h"
#include "solver.h"
#include "animation_values.h"

typedef std::vector< char > VecChar;
typedef std::vector< glm::vec3 > VecVertex;
typedef std::map< char, Cube* > ContainerCubes;
typedef std::map< char, VecChar > ContainerVecChar;

typedef std::map<char, std::vector< std::vector<char> > > SolverInput;


class RubikCube {
public:	
	VecChar corners;
	VecChar borders;
	VecChar centers;
	ContainerCubes cubes;			// Contenedor de todos los cubos instanciados <cube_id, Cube *>
	ContainerVecChar groups;	// Contenedor de vectores con los cube_ids asignados a cada grupo(Camada) <group_id, vec(cube_ids) >	

	RubikCube();	
	
	// OpenGL
	void init_cubes();
	void draw_cubes(GLFWwindow* window);
	void delete_buffer_cubes();

	// Solver
	SolverInput map_groups();
	void do_movements(GLFWwindow* window, std::vector<std::string> steps);

	// Animaciones
	void render_move_group(GLFWwindow* window, char group_id, bool clockwise);
	void render_animation_1(GLFWwindow* window);

private:
	// Camadas*
	VecChar update_group(VecChar to_update, bool clockwise);
	void update_neighborhood(char group_id, bool clockwise);
	bool compute_move_group(glm::vec3 axis, glm::vec3 position, char group_id, bool rounded);

	// Animaciones
	void compute_animacion_1(VecVertex borders_pos, VecVertex corner_pos, VecVertex center_pos, bool scale, bool rounded);

	// Utils* 
	void set_corners();
	void set_borders();
	void set_centers();
	std::vector< VecChar > swappers_clockwise(char group_id);
	std::vector< VecChar > swappers_inverted(char group_id);

	// Consola
	void print_content(std::vector< VecChar > mapper, VecChar ids, bool border, bool content);
	void print_rubik(bool content);
};

RubikCube::RubikCube() {		
	std::vector<char> ids = values::cube_ids;
	std::vector<glm::vec3> positions = values::random_cube_positions(-3.0f, -10.0f, 10.0f);
	std::vector<std::vector<Feature> > colors = values::cube_features;

	for (int i = 0; i < ids.size(); i++) {
		Cube* tmp_cube = new Cube(ids[i], colors[i]);
		tmp_cube->transformation_t(positions[i]);
		this->cubes[ids[i]] = tmp_cube;
	}
	this->groups = group::default_groups;
	print_rubik(false);
}

/* 
	* FUNCIONES PARA IMPRIMIR EN CONSOLA * 
*/
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

// Animacion1*
// -------------------------------------------------------------------------------

void RubikCube::compute_animacion_1(VecVertex borders_pos, VecVertex corner_pos, VecVertex center_pos, bool scale, bool rounded) {
	float threshold = 0.05f;
	for (auto i = 0; i < centers.size(); i++) {
		char cube_id = centers[i];
		cubes[cube_id]->transformation_ts(center_pos[i], threshold, scale, rounded);
	}

	for (auto i = 0; i < borders.size(); i++) {
		char cube_id = borders[i];
		cubes[cube_id]->transformation_ts(borders_pos[i], threshold, scale, rounded);
	}

	for (auto i = 0; i < corners.size(); i++) {
		char cube_id = corners[i];
		cubes[cube_id]->transformation_ts(corner_pos[i], threshold, scale, rounded);
	}
}

void RubikCube::render_animation_1(GLFWwindow* window) {
	float size = 0.1;
	VecVertex borders_pos = animation::get_border_position(size, true);
	VecVertex corner_pos = animation::get_corner_position(size, true);
	VecVertex center_pos = animation::get_center_position(size, true);

	set_corners();
	set_borders();
	set_centers();

	for (int i = 0; i < 9; i++) {
		compute_animacion_1(borders_pos, corner_pos, center_pos, true, false);
		draw_cubes(window);
	}
	compute_animacion_1(borders_pos, corner_pos, center_pos, true, true);
	draw_cubes(window);

	borders_pos = animation::get_border_position(size, false);
	corner_pos = animation::get_corner_position(size, false);
	center_pos = animation::get_center_position(size, false);

	for (int i = 0; i < 9; i++) {
		compute_animacion_1(borders_pos, corner_pos, center_pos, false, false);
		draw_cubes(window);
	}
	compute_animacion_1(borders_pos, corner_pos, center_pos, true, true);
	draw_cubes(window);
}


// Solver*
// -------------------------------------------------------------------------------

// Realiza un mapeo de los grupos del rubik para una entrada al solver
SolverInput RubikCube::map_groups() {
	SolverInput mapped_group;
	for (auto it = groups.begin(); it != groups.end(); ++it) {
		char key = it->first;
		std::vector <VecChar> value = {};

		VecChar group_content = it->second;
		std::vector <VecChar> container  {
			{group_content[0], group_content[1], group_content[2]},
			{group_content[7], group_content[8], group_content[3]},
			{group_content[6], group_content[5], group_content[4]}
		};
		for (int i = 0; i < container.size(); i++) {
			VecChar row = container[i];
			VecChar tmp = {};
			for (int j = 0; j < row.size(); j++) {
				char cube_id = row[j];
				char color = cubes[cube_id]->get_color(key);
				tmp.push_back(color);
			}
			value.push_back(tmp);
		}
		mapped_group[key] = value;
	}
	return mapped_group;
}

// El vector steps contiene la lista de transformaciones que debe realizarse
void RubikCube::do_movements(GLFWwindow* window, std::vector<std::string> steps) {
	std::map<std::string, std::pair<char, bool> > movements = group::movements;
	for (int i = 0; i < steps.size(); i++) {
		std::string step = steps[i];		
		char group_id = movements[step].first;
		bool clockwise = movements[step].second;
		if (step[1] == '2') {
			render_move_group(window, group_id, clockwise);
			render_move_group(window, group_id, clockwise);
		}
		else {
			render_move_group(window, group_id, clockwise);
		}
	}
}


// Camadas* 
// -------------------------------------------------------------------------------

// Actualiza el grupo(camada) sobre la cual se aplico la transformacion
VecChar RubikCube::update_group(VecChar to_update, bool clockwise) {
	int rotation_value = clockwise ? 6 : 2;
	char center = to_update.back();
	to_update.pop_back();
	std::rotate(to_update.begin(), to_update.begin() + rotation_value, to_update.end());
	to_update.push_back(center);
	return to_update;
}

// Actualiza los grupos vecinos de un grupo especifico(group_id)
void RubikCube::update_neighborhood(char group_id, bool clockwise) {
	VecChar neighborhood = clockwise ? group::rotation_clockwise(group_id) : group::rotation_inverted(group_id);
	std::vector< VecChar > swappers = clockwise ? swappers_clockwise(group_id) : swappers_inverted(group_id);

	// Obteniendo la orientacion actual del color de cada cubo
	std::vector< VecChar > colors;
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
		VecChar group = groups[group_id];

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
	// Grupo (Camada) a la cual hemos aplicado la transformacion
	VecChar group = groups[group_id];
	// Actualizamos la rotacion sobre el grupo que se aplico la transformacion (group_id)	
	groups[group_id] = update_group(group, clockwise);
}

// Realizamos los calculos sobre los vertices de los cubos que pertenecen a un grupo (Group_id -> U, D, R, ...)
bool RubikCube::compute_move_group(glm::vec3 axis, glm::vec3 position, char group_id, bool rounded) {
	VecChar tmp_group = groups[group_id];
	for (auto i = 0; i < tmp_group.size(); i++) {
		char key = tmp_group[i];
		cubes[key]->transformation_rt(axis, position, rounded);
	}
	return true;
}

// Render 
// Clokcwise -> True: sentido horario || False: Sentido Antihorario 
// Group_id  -> Grupo que aplicaremos la transformacíon (U, D, R, ...)
void RubikCube::render_move_group(GLFWwindow* window, char group, bool clockwise) {
	glm::vec3 axis = clockwise ? group::rotation_axis_clockwise[group] : group::rotation_axis_inverted[group];
	glm::vec3 position = clockwise ? group::translation_pos_clockwise[group] : group::translation_pos_inverted[group];

	for (auto i = 0; i < 8; i++) {
		compute_move_group(axis, position, group, false);
		draw_cubes(window);
	}
	compute_move_group(axis, position, group, true);
	draw_cubes(window);

	// Actualizamos los grupos
	update_neighborhood(group, clockwise);

	// Print (Opcional)
	//print_rubik(false);
}


// OpenGL* 
// -------------------------------------------------------------------------------

// Inicializamos la configuracion del VBO, VAO y texturas de cada cubo instanciado
void RubikCube::init_cubes() {
	for (auto i = cubes.begin(); i != cubes.end(); ++i) {
		char key = i->first;
		cubes[key]->init_GL();
	}
}

// Render 
void RubikCube::draw_cubes(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto i = cubes.begin(); i != cubes.end(); ++i) {
		char key = i->first;
		cubes[key]->draw_GL();
	}
	params::sleep();
	glfwSwapBuffers(window);
	glfwPollEvents();
}

// Desasignar todos los recursos una vez que hayan superado su propósito para cada cubo instanciado
void RubikCube::delete_buffer_cubes() {
	for (auto i = cubes.begin(); i != cubes.end(); ++i) {
		char key = i->first;
		cubes[key]->delete_buffer_GL();
	}
}


// Utils* 
// -------------------------------------------------------------------------------

// Retorna un vector con los cube_ids de todas las esquinas
void RubikCube::set_corners() {
	this->corners = {
		groups['F'][0], groups['F'][2],
		groups['F'][4], groups['F'][6],
		groups['B'][0], groups['B'][2],
		groups['B'][4], groups['B'][6]
	};
}

// Retorna un vector con los cube_ids de todas los bordes
void RubikCube::set_borders() {
	this->borders = {
		groups['F'][1], groups['F'][3], groups['F'][5], groups['F'][7],
		groups['B'][1], groups['B'][3], groups['B'][5], groups['B'][7],
		groups['L'][1], groups['L'][5], 
		groups['R'][1], groups['R'][5]
	};
}

// Retorna un vector con los cube_ids de todos los centros
void RubikCube::set_centers() {
	this->centers = {
		groups['F'][8], groups['B'][8],
		groups['R'][8], groups['L'][8],
		groups['U'][8], groups['D'][8]
	};	
}

// Retorna un vector de pares, los cuales realizaran un cambio de grupo al realizar un movimiento en el cubo (sentido horario)
std::vector< VecChar > RubikCube::swappers_clockwise(char group_id) {
	VecChar group = groups[group_id];
	std::vector< VecChar > container = {
		{ group[0], group[2] }, { group[1], group[3] }, { group[2], group[4] }, // U -> B
		{ group[2], group[4] }, { group[3], group[5] }, { group[4], group[6] }, // B -> D
		{ group[4], group[6] }, { group[5], group[7] }, { group[6], group[0] }, // D -> F
		{ group[6], group[0] }, { group[7], group[1] }, { group[0], group[2] }	// F -> U
	};
	return container;
};

// Retorna un vector de pares, los cuales realizaran un cambio de grupo al realizar un movimiento en el cubo (sentido anti horario)
std::vector< VecChar > RubikCube::swappers_inverted(char group_id) {
	VecChar group = groups[group_id];
	std::vector< VecChar > container = {
		{ group[2], group[0] }, { group[1], group[7] }, { group[0], group[6] }, // U -> F
		{ group[0], group[6] }, { group[7], group[5] }, { group[6], group[4] }, // F -> D
		{ group[6], group[4] }, { group[5], group[3] }, { group[4], group[2] }, // D -> B
		{ group[4], group[2] }, { group[3], group[1] }, { group[2], group[0] }	// B -> U
	};
	return container;
};

#endif