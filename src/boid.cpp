#include "boid.h"
#include "mathUtils.h"
#include <cmath>
#include <iostream>
using namespace std;

float m1,m2,m3,m4,m5,ra,md;

obstacle::obstacle()
{
	mass=0.0;
}

obstacle::obstacle(position_struct p,float m)
{
	pos.set(p);
	mass=m;
}

position_struct obstacle::get_position()
{
	position_struct p(pos.x,pos.y,pos.z);
	return p;
}

boid::boid(float radius,float m,float min_dis)
{
	radius_of_influence=radius;
	if(min_dis>radius)
	{
		minimum_distance=radius;
	}
	else
	{
		minimum_distance=min_dis;
	}
	mass=random_number(.98*m,1.02*m);
	max_position.add(0.5,0.5,0.5);
	max_speed = 0.02;
}

boid::boid(position_struct p, velocity_struct v,float radius, float m,float min_dis)
{
	pos.set(p);
	vel.set(v);
	radius_of_influence=radius;
	if(min_dis>radius)
	{
		minimum_distance=radius;
	}
	else
	{
		minimum_distance=min_dis;
	}
	mass=random_number(.98*m,1.02*m);
	max_position.add(0.5,0.5,0.5);
	max_speed = 0.02;
}

position_struct boid::get_position()
{
	position_struct temp(pos.x,pos.y,pos.z);
	return temp;
}

velocity_struct boid::get_velocity()
{
	velocity_struct temp(vel.x,vel.y,vel.z);
	return temp;
}

float boid::get_mass()
{
	return mass;
}

void boid::set_position(position_struct &p)
{
	pos.set(p);
}

void boid::set_velocity(velocity_struct &v)
{
	vel.set(v);
	limit_velocity();
}

void boid::add_position(velocity_struct &p)
{
	pos.add(p);
}

void boid::add_velocity(velocity_struct &v)
{
	vel.add(v);
	limit_velocity();
}

velocity_struct boid::cohesion(vector<boid> &arr)
{
	int number_of_boids=arr.size();
	position_struct cm;
	float total_mass=0,total_neighbours=0;

	for(int i=0;i<number_of_boids;++i)
	{
		position_struct p = arr[i].pos;
		float m=arr[i].get_mass();
		if(p.x!=pos.x || p.y!=pos.y || p.z!=pos.z)
		{
			if(getDistance(p,pos)<=ra && isInVision(vel, pos, p))
			{
				total_neighbours+=1;
				total_mass+=m;
				cm.add(m*p.x, m*p.y, m*p.z);
			}
		}
	}
	
	if(total_neighbours==0)
	{
		velocity_struct v;
		// cout<<"cohesion 0"<<endl;
		return v;
	}
	cm.divide(total_mass);
	velocity_struct steer((cm.x - pos.x ),(cm.y - pos.y ),(cm.z - pos.z ));
	steer.normalise();
	// cout<<"cohesion "<<(cm.x-pos.x)/15<<" "<<(cm.y-pos.y)/15<<" "<<(cm.z-pos.z)/15<<endl;
	return steer;
}

velocity_struct boid::alignment(vector<boid> &arr)
{
	int number_of_boids=arr.size();
	velocity_struct cv;
	float total_vel=0,total_neighbours=0,total_mass=0;
	for(int i=0;i<number_of_boids;++i)
	{
		position_struct p = arr[i].pos;
		velocity_struct v = arr[i].vel;
		float m=arr[i].get_mass();
		if(p.x!=pos.x || p.y!=pos.y || p.z!=pos.z)
		{
			if(getDistance(p,pos)<=ra && isInVision(vel, pos, p))
			{
				total_neighbours+=1;
				total_mass+=m;
				cv.add(m*v.x, m*v.y, m*v.z);
			}
		}
	}
	
	if(total_neighbours==0)
	{
		velocity_struct v;
		// cout<<"alignment 0"<<endl;
		return v;
	}
	cv.divide(total_mass);

	velocity_struct steer((cv.x-vel.x),(cv.y-vel.y),(cv.z-vel.z));
	steer.normalise();
	// steer.subtract(vel);
	// cout<<"alignment "<<(cv.x-pos.x)/60<< " "<<(cv.y-pos.y)/60<<" "<<(cv.z-pos.z)/60<<endl;
	return steer;
}

velocity_struct boid::separation(vector<boid> &arr)
{
	vector<obstacle> obs;
	int number_of_boids=arr.size();
	int number_of_obstacles=obs.size();
	velocity_struct cv;
	float total_vel=0,total_neighbours=0;
	for(int i=0;i<number_of_boids;++i)
	{
		position_struct p = arr[i].pos;
		if(p.x!=pos.x || p.y!=pos.y || p.z!=pos.z)
		{
			float dis = getDistance(p,pos);
			// if(dis<=md && isInVision(vel, pos, p))
			if(dis<=md)
			{
				total_neighbours+=1;
				cv.subtract(pos.x-p.x,pos.y-p.y,pos.z-p.z);
			}
		}
	}

	for(int i=0;i<number_of_obstacles;++i)
	{
		position_struct p = obs[i].pos;
		float dis = getDistance(p,pos);
		if(dis<=md)
		{
			total_neighbours+=1;
			cv.subtract(pos.x-p.x,pos.y-p.y,pos.z-p.z);
		}
	}
	
	if(total_neighbours==0)
	{
		// cout<<"separation 0"<<endl;
		velocity_struct v;
		return v;
	}

	velocity_struct steer(cv.x,cv.y,cv.z);
	steer.normalise();
	// cout<<"separation "<<cv.x<<" "<<cv.y<<" "<<cv.z<<endl;
	return steer;
}

velocity_struct boid::bound_position()
{
	velocity_struct temp;
	float deceleration = 1;
	if(pos.x>max_position.x)
	{
		temp.x-=deceleration*(pos.x-max_position.x);
	}
	else
	{
		if(pos.x<-max_position.x)
		{
			temp.x-=deceleration*(pos.x-max_position.x);
		}
	}
	if(pos.y>max_position.y)
	{
		temp.y-=deceleration*(pos.y-max_position.y);
	}
	else
	{
		if(pos.y<-max_position.y)
		{
			temp.y-=deceleration*(pos.y-max_position.y);
		}
	}
	if(pos.z>max_position.z)
	{
		temp.z-=deceleration*(pos.z-max_position.z);
	}
	else
	{
		if(pos.z<-max_position.z)
		{
			temp.z-=deceleration*(pos.z-max_position.z);
		}
	}
	return temp;
}

velocity_struct boid::goal_seeking(position_struct &goal_pos)
{
	velocity_struct temp_v(goal_pos.x - pos.x, goal_pos.y - pos.y, goal_pos.z - pos.z);
	temp_v.normalise();
	return temp_v;
}

void boid::limit_velocity()
{
	float sp = speed(vel);
	if(sp>max_speed)
	{
		vel.divide(sp/max_speed);
	}
}

velocity_struct boid::get_update(vector<boid> &flk, std::vector<obstacle> &obsts, position_struct &goal_pos, velocity_struct &wind)
{
	// float m1=0.08,m2=.06,m3=0.003,m4=.05;
	
	velocity_struct vel_temp;
	/*if(random_number(0,50)>2.5)
	{
		velocity_struct temp = cohesion(flk);
		temp.multiply(m1);
		vel_temp.add(temp);
	}
	else
	{
		velocity_struct temp = cohesion(flk);
		temp.multiply(m1);
		vel_temp.subtract(temp);
	}
	{
		velocity_struct temp = separation(flk);
		temp.multiply(m3);
		vel_temp.add(temp);
	}
	*/
	{
		velocity_struct temp = main_rule(flk,obsts);
		vel_temp.add(temp);
	}
	
	{
		velocity_struct temp = bound_position();
		temp.multiply(m4);
		vel_temp.add(temp);
	}
	{
		velocity_struct temp = goal_seeking(goal_pos);
		temp.multiply(m5);
		vel_temp.add(temp);
	}
	{
		velocity_struct temp(wind.x + random_number(-0.01*wind.x,0.01*wind.x), wind.y + random_number(-0.01*wind.y,0.01*wind.y), wind.z + random_number(-0.01*wind.z,0.01*wind.z));
		vel_temp.add(temp);
	}
	{
		vel_temp.add(random_number(-0.00006,0.00006),random_number(-0.00006,0.00006),random_number(-0.00006,0.00006));
	}
	
	return vel_temp;
}


velocity_struct boid::main_rule(vector<boid> &arr, vector<obstacle> &obs)
{

	// vector<obstacle> obs;
	int number_of_boids=arr.size()/2;
	int number_of_obstacles=obs.size();
	position_struct cm;
	velocity_struct cv;
	velocity_struct sep_v;
	float total_mass=0;
	int total_neighbours=0,total_sep_nei=0;

	for(int i=0;i<number_of_boids;i+=1)
	{
		position_struct p = arr[i].pos;
		velocity_struct v = arr[i].vel;
		float m=arr[i].get_mass();
		if(p.x!=pos.x || p.y!=pos.y || p.z!=pos.z)
		{
			float distance = getDistance(p,pos);
			if(distance<=ra && isInVision(vel, pos, p))
			{
				total_neighbours+=1;
				total_mass+=m;

				cm.add(m*p.x, m*p.y, m*p.z);
				cv.add(m*v.x, m*v.y, m*v.z);

				if(distance<=md)
				{
					total_sep_nei+=1;
					sep_v.subtract(pos.x-p.x,pos.y-p.y,pos.z-p.z);
				}
			}
			if (total_neighbours > 5)
			{
			//	break;
			}
		}
	}

	for(int i=0;i<number_of_obstacles;++i)
	{
		position_struct p = obs[i].pos;
		float dis = getDistance(p,pos);
		if(dis<=md && isInVision(vel, pos, p))
		{
			total_sep_nei+=1;
			sep_v.subtract(pos.x-p.x,pos.y-p.y,pos.z-p.z);
		}
	}
	
	if(total_neighbours+total_sep_nei==0)
	{
		velocity_struct v;
		// cout<<"cohesion 0"<<endl;
		return v;
	}
	velocity_struct steer;
	if(total_neighbours!=0)
	{
		cm.divide(total_mass);
		steer.set((cm.x - pos.x ),(cm.y - pos.y ),(cm.z - pos.z ));
		steer.normalise();
		steer.multiply(m1);

		cv.divide(total_mass);
		cv.subtract(vel);
		cv.normalise();
		cv.multiply(m2);
	}
	if(total_sep_nei!=0)
	{
		sep_v.normalise();
		sep_v.multiply(m3);	
	}
	
	steer.add(cv);
	steer.add(sep_v);
	// cout<<"cohesion "<<(cm.x-pos.x)/15<<" "<<(cm.y-pos.y)/15<<" "<<(cm.z-pos.z)/15<<endl;
	return steer;

}


void boid::print()
{
	cout<<pos.x<<" "<<pos.y<<" "<<pos.z<<"        "<<vel.x<<" "<<vel.y<<" "<<vel.z<<endl;
}