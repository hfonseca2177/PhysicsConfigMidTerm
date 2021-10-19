#include <extern_includes.h>

namespace nPhysics
{
	float getRandom();
	float getRandom(float high);
	float getRandom(float low, float high);
	glm::vec3 getRandomVec3(float length);
	glm::mat3 getRandomOrthonormalBasis();
	glm::vec3 getRandomXVector();
	glm::vec3 getRandomZVector();
	glm::mat3 orthonormalBasisWithParams(const glm::vec3& xVec, const glm::vec3& zVec);
}
