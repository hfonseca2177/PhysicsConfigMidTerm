#include <physics/random_helpers.h> // function definitions, and glm includes


namespace nPhysics
{
	// Generate a random number between 0 and 1
	float getRandom()
	{
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}
	// Generate a random number between zero and a given high value
	float getRandom(float high)
	{
		return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / high);
	}
	// Generate a random number in a given range
	float getRandom(float low, float high)
	{
		return low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (high - low));
	}

	// Generate a glm::vec3 with a random direction and specified length
	glm::vec3 getRandomVec3(float length)
	{
		// play around with the range of alpha and delta to get arcs, hemispheres, etc...
		float alpha = getRandom(glm::pi<float>());
		float delta = getRandom(-glm::pi<float>(), glm::pi<float>());
		float sinAlpha = glm::sin(alpha);
		float cosAlpha = glm::cos(alpha);
		float sinDelta = glm::sin(delta);
		float cosDelta = glm::cos(delta);
		// play around with ordering to change the directionality of hemispheres, arcs, etc...
		// eg. (x,y,z), (y,z,x), (x,z,y)
		return glm::vec3(length * sinAlpha * cosDelta, length * sinAlpha * sinDelta, length * cosAlpha);
	}

	glm::mat3 getRandomOrthonormalBasis()
	{
		return orthonormalBasisWithParams(getRandomXVector(), getRandomZVector());
	}

	// Use as-is.  Do not change.
	glm::vec3 getRandomXVector()
	{
		return glm::vec3(getRandom(0.1f, 1.f), 0.f, getRandom(0.1f, 1.f));
	}

	// Use as-is.  Do not change.
	glm::vec3 getRandomZVector()
	{
		return glm::vec3(-getRandom(0.1f, 1.f), 0.f, getRandom(0.1f, 1.f));
	}

	glm::mat3 orthonormalBasisWithParams(const glm::vec3& xVec, const glm::vec3& zVec)
	{
		// TODO: Generate an orthonormal basis, using xVec and zVec.
		//       The input vectors may be manipulated, however the 
		//       returned axes must essentially be:
		//       x-axis: sourced from xVec
		//       y-axis: generated using math!
		//       z-axis: sourced from zVec

		// Generate y, by crossing z and x.
		glm::vec3 x(xVec);
		glm::vec3 z(zVec);
		glm::vec3 y(glm::cross(z, x));
		// Ensure z is orthogonal to both x and y.
		z = glm::cross(x, y);
		// Normalize everything.
		x = glm::normalize(x);
		y = glm::normalize(y);
		z = glm::normalize(z);
		// Return the result.
		return glm::mat3(x, y, z);
	}
}