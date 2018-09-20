#ifndef FLOCK_H
#define FLOCK_H

#include "boid.h"
#include "mathUtils.h"
#include "display.h"

using namespace std;

class flock
{
	GLfloat position_buffer_data[600] = {};
	GLuint vertex_buffer;
public:
	vector<boid > flk;
	vector<obstacle > obsts;
	position_struct goal_pos;
	velocity_struct wind;

	/**
	* creates a flock
	*/
	flock();
	void initialize();

	/**
	* returns total number of boids in tbe flock
	*/
	int getTotalBoids();

	/**
	* returns a vector containing all boids in the flock
	*/
	vector<boid > getBoids();

	/**
	* adds a boid to the flock
	*/
	void add_boid();

	/**
	* adds a boid b to the flock
	* @param b 	boid to be added to the flock
	*/
	void add_boid(boid b);

	/**
	* creates n boids with random initial positions and velocities
	* @param n 		number of boids
	*/
	void spawn(int n=1000);

	/**
	* returns total number of obstacles
	*/
	int getTotalObstacles();

	/**
	* sets the position of goal to p
	*/
	void set_goal(position_struct &p);

	/**
	* updates goal position randomly
	*/
	void update_goal();

	/**
	* adds an obstacle to the flock
	*/
	void add_obstacle();

	/**
	* add an obstacle o to the flock
	*/
	void add_obstacle(obstacle o);

	/**
	* updates position and velocities of all the boids in the flock
	*/
	void update();

	/**
	* renders the flock using OpenGl
	*/
	void render();

	void new_render();
};

#endif