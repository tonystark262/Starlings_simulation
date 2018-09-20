#ifndef BOID_H
#define BOID_H

#include "ds.h"
#include "mathUtils.h"
#include <vector>
extern float m1,m2,m3,m4, m5, ra, md;
using namespace std;

class obstacle
{
public:
	position_struct pos;
	float mass;

	/**
	* Creates an empty obstacle
	*/
	obstacle();

	/**
	* Creates an obstacle at given position and of given mass
	* @param p 		position of obstacle
	* @param m 		mass of obstacle
	*/
	obstacle(position_struct p,float m=0.0);

	/**
	* Returns the position of the obstacle
	*/
	position_struct get_position();

	/**
	* Returns mass of the obstacle
	*/
	float get_mass();
};


class boid
{
public:
	/**
	* current position of boid
	*/
	position_struct pos;

	/**
	* current velocity of boid
	*/
	velocity_struct vel;

	/**
	* distance upto which boid can see
	*/
	float radius_of_influence;

	/**
	* mass of boid
	*/
	float mass;

	/**
	* minimum distance between two boids
	*/
	float minimum_distance;

	/**
	* Boundary of the world (assumed to be a cuboid)
	*/
	position_struct max_position;

	/**
	* Maximum speed a boid can fly with
	*/
	float max_speed;

	/**
	* returns velocity direction due to cohesion
	*/
	velocity_struct cohesion(vector<boid> &arr);

	/**
	* returns velocity direction due to alignment property
	*/
	velocity_struct alignment(vector<boid> &arr);

	/**
	* returns velocity direction due to seperation property
	*/
	velocity_struct separation(vector<boid> &arr);

	/**
	* combines all rules in a single function
	*/
	velocity_struct main_rule(vector<boid> &arr, vector<obstacle> &obs);

	/**
	* returns velocity direction for bounding position
	*/
	velocity_struct bound_position();

	/**
	* returns velocity for goal seeking behaviour
	*/
	velocity_struct goal_seeking(position_struct &goal_pos);

	/**
	* limits velocity to max_speed
	*/
	void limit_velocity();

	/**
	* Create a new boid
	* @param radius 	radius of influnce
	* @param m 			mass
	* @param min_dis 	minimum distance
	*/
	boid(float radius=ra,float m=5.0,float min_dis=md);

	
	/**
	* Create a new boid
	* @param p 			initial position
	* @param v 			initial velocity
	* @param radius 	radius of influnce
	* @param m 			mass
	* @param min_dis 	minimum distance
	*/
	boid(position_struct p,velocity_struct v,float radius=ra, float m=5.0,float min_dis=md);

	/**
	* returns current position of the boid
	*/
	position_struct get_position();

	/**
	* returns current velocity of the boid
	*/
	velocity_struct get_velocity();

	/**
	* returns mass of the boid
	*/
	float get_mass();

	/**
	* sets current position of boid to p
	* @param p new position 
	*/
	void set_position(position_struct &p);

	/**
	* sets current velocity of boid to p
	* @param p new velocity 
	*/
	void set_velocity(velocity_struct &v);

	/**
	* adds v to current velocity
	* @param v velocity to be added to current velocity
	*/
	void add_velocity(velocity_struct &v);

	/**
	* adds v to current position
	* @param v position to be added to current position
 	*/
	void add_position(velocity_struct &p);

	/**
	* calculates the force to be applied to the boid
	* @param flk 	  	vector containing all boids
	* @param obsts 	  	vector containing all obstacles
	* @param goal_pos 	position of goal
	* @param wind 		velocity due to wind
	*/
	velocity_struct get_update(vector<boid> &flk, std::vector<obstacle> &obsts, position_struct &goal_pos, velocity_struct &wind);
	
	/**
	* prints current position and velocity of the boid
	*/
	void print();
};


#endif