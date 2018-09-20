#ifndef DS_H
#define DS_H

#include<cmath>
using namespace std;


/**
* To store velocity of the boid
*/
struct velocity_struct
{
	float x;
	float y;
	float z;

	/**
	* initializes velocity to zero
	*/
	velocity_struct()
	{
		x=0.0;y=0.0;z=0.0;
	}

	/**
	* initializes velocity to given value
	* @param a 		x component of velocity
	* @param b 		y component of velocity
	* @param c 		z component of velocity
	*/
	velocity_struct(float a, float b, float c)
	{
		x=a;y=b;z=c;
	}

	/**
	* adds velocity v to current velocity
	* @param v 		velocity to be added to current velocity
	*/
	void add(velocity_struct &v)
	{
		x+=v.x;
		y+=v.y;
		z+=v.z;
	}

	/**
	* adds velocity gicen to current velocity
	* @param a 		x component of velocity
	* @param b 		y component of velocity
	* @param c 		z component of velocity
	*/
	void add(float a,float b,float c)
	{
		x+=a;
		y+=b;
		z+=c;
	}

	/**
	* subtracts velocity v to current velocity
	* @param v 		velocity to be subtracted to current velocity
	*/
	void subtract(velocity_struct &v)
	{
		x-=v.x;
		y-=v.y;
		z-=v.z;
	}

	/**
	* subtract velocity gicen to current velocity
	* @param a 		x component of velocity
	* @param b 		y component of velocity
	* @param c 		z component of velocity
	*/
	void subtract(float a,float b,float c)
	{
		x-=a;
		y-=b;
		z-=c;
	}

	/**
	* divides velocity by different values in different directions
	* @param a 		x component of velocity
	* @param b 		y component of velocity
	* @param c 		z component of velocity
	*/
	void divide(float a,float b,float c)
	{
		x/=a;
		y/=b;
		z/=c;
	}

	/**
	* divides velocity by a uniform value in all different directions
	* @param a 		dividing factor
	*/
	void divide(float a)
	{
		x/=a;
		y/=a;
		z/=a;
	}

	/**
	* multiplies velocity by different values in different directions
	* @param a 		multiplying factors
	*/
	void multiply(float a)
	{
		x*=a;
		y*=a;
		z*=a;
	}

	/**
	* sets position to given value
	* @param v 		new position
	*/
	void set(velocity_struct &v)
	{
		x=v.x;
		y=v.y;
		z=v.z;
	}

	/***
	* sets position to given values
	* @param a 		x component of position
	* @param b 		y component of position
	* @param c 		z component of position
	*/
	void set(float a, float b, float c)
	{
		x=a;
		y=b;
		z=c;
	}

	/**
	* converts distance to unity retaining same direction
	*/
	void normalise()
	{
		float nor = sqrt(x*x+y*y+z*z);
		x/=nor;
		y/=nor;
		z/=nor;
	}
};

/**
* To store position of the boid
*/
struct position_struct
{
	float x;
	float y;
	float z;

	/**
	* initializes position to zero
	*/
	position_struct()
	{
		x=0.0;y=0.0;z=0.0;
	}

	/**
	* initializes position to given value
	* @param a 		x component of position
	* @param b 		y component of position
	* @param c 		z component of position
	*/
	position_struct(float a, float b, float c)
	{
		x=a;y=b;z=c;
	}

	/**
	* adds position p to current position
	* @param p		position to be added to current position
	*/
	void add(position_struct &p)
	{
		x+=p.x;
		y+=p.y;
		z+=p.z;
	}

	/**
	* adds velocity v to current position
	* @param v		velocity to be added to current position
	*/
	void add(velocity_struct &v)
	{
		x+=v.x;
		y+=v.y;
		z+=v.z;
	}

	/**
	* adds position gicen to current position
	* @param a 		x component of position
	* @param b 		y component of position
	* @param c 		z component of position
	*/
	void add(float a,float b,float c)
	{
		x+=a;
		y+=b;
		z+=c;
	}

	/**
	* subtract position gicen to current position
	* @param a 		x component of position
	* @param b 		y component of position
	* @param c 		z component of position
	*/
	void subtract(float a,float b,float c)
	{
		x-=a;
		y-=b;
		z-=c;
	}

	/**
	* divides position by different values in different directions
	* @param a 		x component of position
	* @param b 		y component of position
	* @param c 		z component of position
	*/
	void divide(float a,float b,float c)
	{
		x/=a;
		y/=b;
		z/=c;
	}

	/**
	* divides position by a uniform value in all different directions
	* @param a 		dividing factor
	*/
	void divide(float a)
	{
		x/=a;
		y/=a;
		z/=a;
	}

	/**
	* multiplies position by different values in different directions
	* @param a 		multiplying factors
	*/
	void multiply(float a)
	{
		x*=a;
		y*=a;
		z*=a;
	}

	/**
	* sets position to given value
	* @param 		new position
	*/
	void set(position_struct p)
	{
		x=p.x;
		y=p.y;
		z=p.z;
	}

	/**
	* converts speed to unity retaining same direction
	*/
	void normalise()
	{
		float nor = sqrt(x*x+y*y+z*z);
		x/=nor;
		y/=nor;
		z/=nor;
	}
};

#endif