#include "flock.h"
#include "display.h"

#include <cmath>
#include <iostream>
using namespace std;
int update_iter=0;


flock::flock()
{
	flk.clear();
	obsts.clear();
}

void flock::initialize(){
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, 600 * sizeof(GL_FLOAT), &position_buffer_data[0], GL_DYNAMIC_DRAW);
}

int flock::getTotalBoids()
{
	return flk.size();
}

int flock::getTotalObstacles()
{
	return obsts.size();
}

vector <boid > flock::getBoids()
{
	return flk;
}

void flock::add_boid()
{
	boid temp;
	flk.push_back(temp);
}

void flock::add_boid(boid b){

	flk.push_back(b);
}

void flock::spawn(int n)
{
	for(int i=0;i<n;++i)
	{
		flk.push_back(boid(random_position(),random_velocity()));
	}
}

void flock::add_obstacle()
{
	obstacle temp;
	obsts.push_back(temp);
}

void flock::add_obstacle(obstacle o)
{
	obsts.push_back(o);
}

void flock::set_goal(position_struct &p){
	goal_pos = p;
}

void flock::update_goal(){
	goal_pos.set(random_position(0.25, 0.25, 0.25));
}

void flock::update()
{
	int number_of_boids=flk.size()/2;
	velocity_struct vel_temp[number_of_boids];
	if(random_number(0.0,5.0) < 1.0){
		for(int i=update_iter;i<number_of_boids;i+=2)
		{
			vel_temp[i] = flk[i].get_update(flk, obsts, goal_pos, wind);
		}
	}
	for(int i=update_iter;i<number_of_boids;++i)
	{
		flk[i].add_velocity(vel_temp[i]);
		velocity_struct vl = flk[i].get_velocity();
		vl.divide(2);
		flk[i].add_position(vl);
		// flk[i].print();
	}
	if(random_number(0, 10000) < 125){
		update_goal();
	}
	if(random_number(0, 10000) < 0)
	{
		wind.set(random_number(-0.005,0.005), random_number(-0.005,0.005), random_number(-0.005,0.005));
	}
	update_iter=(update_iter+1)%2;
	// cout<<endl;
}

void flock::render(){
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(5.0);
	int num_boids = getTotalBoids()/2;

	glColor3f(1.0, 1.0, 1.0);
	for(int i = 0; i < num_boids; i++){
		boid b = flk[i];
		const position_struct &p = b.pos;
		const velocity_struct &v = b.vel;

		// for displaying triangles
		// drawTriangle(p, v);

		// for displaying circles
		
		float hdf = (p.z > 0)? (p.z) : (-p.z);
		drawCircle(p.x, p.y, p.z, 0.005 * (1+hdf));
		


		// for displaying as squares
		/*
		float hdf = (p.z > 0)? (p.z) : (-p.z);
		glPointSize(5 + 5.0 * hdf) ;
        glColor3f( 0.5f, 0.5f, 0.1f );
        glBegin( GL_POINTS );
        glVertex3f( p.x, p.y, p.z );
        glEnd();
        */
        // glPopMatrix();
	}

	//obstacle
	glPointSize(5.0);
	glBegin(GL_POINTS);
	int num_obs = getTotalObstacles();
	for(int i = 0; i < num_obs; i++){
		obstacle o = obsts[i];
		position_struct p = o.get_position();
		glVertex3f(p.x, p.y, p.z);
	}
	glEnd();

	// goal_position
	glBegin(GL_POINTS);
	glVertex3f(goal_pos.x, goal_pos.y, goal_pos.z);
	glEnd();
}

void flock::new_render(){
	int num_boids = getTotalBoids();

	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < num_boids; ++i)
	{
		boid b = flk[i];
		const position_struct &p = b.pos;
		// const velocity_struct &v = b.vel;	

		position_buffer_data[3*i] = p.x;
		position_buffer_data[3*i + 1] = p.y;
		position_buffer_data[3*i + 2] = p.z;
	}
	glPointSize(5.0);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(position_buffer_data), position_buffer_data);	

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		0, // attribute. No particular reason for 0, but must match the layout in the shader.
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*)0 // array buffer offset
	);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

	// glVertexAttribDivisor(1,1);
/*	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, 600 * sizeof(GL_FLOAT), &position_buffer_data[0], GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 600 * sizeof(GL_FLOAT), &position_buffer_data[0]);
	glEnable(GL_ARRAY_BUFFER);*/
	glDrawArrays(GL_POINTS, 0, getTotalBoids());
}
