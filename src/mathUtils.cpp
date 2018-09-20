#include "mathUtils.h"
#include "boid.h"
#include <cmath>
#include <ctime>
using namespace std;

float getDistance(const position_struct &p1, const position_struct &p2)
{
	float a=p1.x-p2.x,b=p1.y-p2.y,c=p1.z-p2.z;
	return sqrt(a*a+b*b+c*c);
}

float speed(const velocity_struct &v)
{
	return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

float random_number(float a, float b)
{
	/*typedef std::mt19937 rng_type;
	std::uniform_int_distribution<rng_type::result_type> udist(a, b);
	rng_type rng;

	rng_type::result_type const seedval = time(0)*100; // get this from somewhere
	rng.seed(seedval);  
	rng_type::result_type random_number = udist(rng);
*/


	/*std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(a,b); // distribution in range [1, 6]
*/

	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(a, b);
    return dist(mt);

    // std::cout << dist6(rng) << std::endl;
	// return random_number;
}

position_struct random_position(float x,float y, float z)
{
	position_struct p;
	p.x = random_number(-x,x);
	p.y = random_number(-y,y);
	p.z = random_number(-z,z);
	return p;
}

velocity_struct random_velocity(float x,float y, float z)
{
	velocity_struct v;
	v.x = random_number(-x,x);
	v.y = random_number(-y,y);
	v.z = random_number(-z,z);
	return v;
}

bool isInVision(const velocity_struct &v, const position_struct &p, const position_struct &q)
{
	float x=q.x-p.x, y=p.y-q.y, z=p.z-q.z;
	if((x*v.x+y*v.y+z*v.z)>=-0.5*sqrt((x*x+y*y+z*z)*(v.x*v.x+v.y*v.y+v.z*v.z)))
	{
		return true;
	}
	return false;
}