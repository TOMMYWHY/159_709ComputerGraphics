// Project Header
#include "geometry.h"

// --------------------------------------------------------------------------------
// Create Tetrahedron with Positions and Normals
void createTetrahedron(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes) {
	// Left-Bottom-Back
	glm::vec3 v0 = glm::vec3(-0.5f, -sqrt(1.0f/12.0f), -sqrt(1.0f/12.0f));

	// Right-Bottom-Back
	glm::vec3 v1 = glm::vec3( 0.5f, -sqrt(1.0f/12.0f), -sqrt(1.0f/12.0f));

	// Centre-Bottom-Front
	glm::vec3 v2 = glm::vec3( 0.0f, -sqrt(1.0f/12.0f),   sqrt(1.0f/3.0f));

	// Center-Top-Centre
	glm::vec3 v3 = glm::vec3( 0.0f,    sqrt(1.0/3.0f),              0.0f);


	// ---- Bottom ----
	// Left-Bottom-Back
	buffer.push_back(glm::vec4(v0, 1.0f));
	buffer.push_back(glm::vec4(glm::normalize(glm::cross(v0-v2, v1-v2)), 0.0f));

	// Right-Bottom-Back
	buffer.push_back(glm::vec4(v1, 1.0f));
	buffer.push_back(glm::vec4(glm::normalize(glm::cross(v0-v2, v1-v2)), 0.0f));

	// Centre-Bottom-Front
	buffer.push_back(glm::vec4(v2, 1.0f));
	buffer.push_back(glm::vec4(glm::normalize(glm::cross(v0-v2, v1-v2)), 0.0f));

	// ---- Left ----
	// Left-Bottom-Back
	buffer.push_back(glm::vec4(v0, 1.0f));
	buffer.push_back(glm::vec4(glm::normalize(glm::cross(v0-v3, v2-v3)), 0.0f));

	// Centre-Bottom-Front
	buffer.push_back(glm::vec4(v2, 1.0f));
	buffer.push_back(glm::vec4(glm::normalize(glm::cross(v0-v3, v2-v3)), 0.0f));

	// Center-Top-Centre
	buffer.push_back(glm::vec4(v3, 1.0f));
	buffer.push_back(glm::vec4(glm::normalize(glm::cross(v0-v3, v2-v3)), 0.0f));

	// ---- Right ----
	// Right-Bottom-Back
	buffer.push_back(glm::vec4(v1, 1.0f));
	buffer.push_back(glm::vec4(glm::normalize(glm::cross(v2-v3, v1-v3)), 0.0f));

	// Center-Top-Centre
	buffer.push_back(glm::vec4(v3, 1.0f));
	buffer.push_back(glm::vec4(glm::normalize(glm::cross(v2-v3, v1-v3)), 0.0f));

	// Centre-Bottom-Front
	buffer.push_back(glm::vec4(v2, 1.0f));
	buffer.push_back(glm::vec4(glm::normalize(glm::cross(v2-v3, v1-v3)), 0.0f));

	// ---- Back ----
	// Left-Bottom-Back
	buffer.push_back(glm::vec4(v0, 1.0f));
	buffer.push_back(glm::vec4(glm::normalize(glm::cross(v1-v3, v0-v3)), 0.0f));

	// Center-Top-Centre
	buffer.push_back(glm::vec4(v3, 1.0f));
	buffer.push_back(glm::vec4(glm::normalize(glm::cross(v1-v3, v0-v3)), 0.0f));

	// Right-Bottom-Back
	buffer.push_back(glm::vec4(v1, 1.0f));
	buffer.push_back(glm::vec4(glm::normalize(glm::cross(v1-v3, v0-v3)), 0.0f));

	// Indexes
	indexes.push_back(glm::ivec3( 0,  1,  2));
	indexes.push_back(glm::ivec3( 3,  4,  5));
	indexes.push_back(glm::ivec3( 6,  7,  8));
	indexes.push_back(glm::ivec3( 9, 10, 11));
}


// --------------------------------------------------------------------------------
// Create Torus with Positions and Normals
void createTorus(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes, float r1, float r2, int sub1, int sub2) {
	// Main Torus Ring
	for(int i1 = 0; i1 < sub1; i1++) {
		// Theta [0, 2pi)
		float theta = i1 * M_PI * 2.0 / sub1;

		// Main Offset
		int offset1 = ((i1 < (sub1 - 1)) ? 1 : -(sub1 - 1)) * sub2;

		// Point on Main Ring
		glm::vec4 p1 = glm::vec4(r1 * glm::cos(theta), 0.0f, r1 * glm::sin(theta), 1.0f);
		glm::vec4 u1 = glm::normalize(glm::vec4(p1.x, p1.y, p1.z, 0.0f));

		// Inner Ring
		for(int i2 = 0; i2 < sub2; i2++) {
			// Phi [0, 2pi)
			float phi = i2 * M_PI * 2.0 / sub2;

			// Inner Offset
			int offset2 = (i2 < (sub2 - 1)) ? 1 : -(sub2 - 1);

			// Point on inner ring
			glm::vec4 p2 = u1 * r2 * glm::cos(phi) + glm::vec4(0.0f, r2 * glm::sin(phi), 0.0f, 1.0f);

			// Compute Normal
			glm::vec4 u2 = glm::normalize(glm::vec4(p2.x, p2.y, p2.z, 0.0f));

			// Add Position and Normal to buffer
			buffer.push_back(p1 + p2);
			buffer.push_back(u2);

			// Calculate index
			int k = i1 * sub2 + i2;

			// Added indexes
			indexes.push_back(glm::ivec3(k, k + offset2,           k + offset1 + offset2));
			indexes.push_back(glm::ivec3(k, k + offset1 + offset2, k + offset1));
		}
	}
}


// --------------------------------------------------------------------------------
// Create Cube with Positions and Normals
void createCube(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes) {
    // ---- Top ----
    // Left-Top-Back - 0
    buffer.push_back(glm::vec4(-1.0f,  1.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));

    // Right-Top-Back - 1
    buffer.push_back(glm::vec4( 1.0f,  1.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));

    // Left-Top-Front - 2
    buffer.push_back(glm::vec4(-1.0f,  1.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));

    // Right-Top-Front - 3
    buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));

    // Top
    indexes.push_back(glm::ivec3(0, 2, 3));
    indexes.push_back(glm::ivec3(0, 3, 1));


    // ---- Bottom ----
    // Left-Bottom-Back - 4
    buffer.push_back(glm::vec4(-1.0f, -1.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f, -1.0f,  0.0f,  0.0f));

    // Right-Bottom-Back - 5
    buffer.push_back(glm::vec4( 1.0f, -1.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f, -1.0f,  0.0f,  0.0f));

    // Left-Bottom-Front - 6
    buffer.push_back(glm::vec4(-1.0f, -1.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f, -1.0f,  0.0f,  0.0f));

    // Right-Bottom-Front - 7
    buffer.push_back(glm::vec4( 1.0f, -1.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f, -1.0f,  0.0f,  0.0f));

    // Bottom
    indexes.push_back(glm::ivec3(4, 6, 7));
    indexes.push_back(glm::ivec3(4, 7, 5));

    // ---- Left ----
    // Left-Top-Back - 8
    buffer.push_back(glm::vec4(-1.0f,  1.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4(-1.0f,  0.0f,  0.0f,  0.0f));

    // Left-Bottom-Back - 9
    buffer.push_back(glm::vec4(-1.0f, -1.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4(-1.0f,  0.0f,  0.0f,  0.0f));

    // Left-Top-Front - 10
    buffer.push_back(glm::vec4(-1.0f,  1.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4(-1.0f,  0.0f,  0.0f,  0.0f));

    // Left-Bottom-Front - 11
    buffer.push_back(glm::vec4(-1.0f, -1.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4(-1.0f,  0.0f,  0.0f,  0.0f));

    // Left
    indexes.push_back(glm::ivec3(8,  9, 11));
    indexes.push_back(glm::ivec3(8, 11, 10));


    // ---- Right ----
    // Right-Top-Back - 12
    buffer.push_back(glm::vec4( 1.0f,  1.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4( 1.0f,  0.0f,  0.0f,  0.0f));

    // Right-Bottom-Back - 13
    buffer.push_back(glm::vec4( 1.0f, -1.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4( 1.0f,  0.0f,  0.0f,  0.0f));

    // Right-Top-Front - 14
    buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4( 1.0f,  0.0f,  0.0f,  0.0f));

    // Right-Bottom-Front - 15
    buffer.push_back(glm::vec4( 1.0f, -1.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4( 1.0f,  0.0f,  0.0f,  0.0f));

    // Right
    indexes.push_back(glm::ivec3(14, 15, 13));
    indexes.push_back(glm::ivec3(14, 13, 12));


    // ---- Front ----
    // Left-Top-Front - 16
    buffer.push_back(glm::vec4(-1.0f,  1.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));

    // Right-Top-Front - 17
    buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));

    // Left-Bottom-Front - 18
    buffer.push_back(glm::vec4(-1.0f, -1.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));

    // Right-Bottom-Front - 19
    buffer.push_back(glm::vec4( 1.0f, -1.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));

    // Front
    indexes.push_back(glm::ivec3(16, 18, 19));
    indexes.push_back(glm::ivec3(16, 19, 17));


    // ---- Back ----
    // Left-Top-Back - 20
    buffer.push_back(glm::vec4(-1.0f,  1.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));

    // Right-Top-Back - 21
    buffer.push_back(glm::vec4( 1.0f,  1.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));

    // Left-Bottom-Back - 22
    buffer.push_back(glm::vec4(-1.0f, -1.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));

    // Right-Bottom-Back - 23
    buffer.push_back(glm::vec4( 1.0f, -1.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));

    // Back
    indexes.push_back(glm::ivec3(21, 23, 22));
    indexes.push_back(glm::ivec3(21, 22, 20));
}
// --------------------------------------------------------------------------------
void createSphere(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes) {
    const int Y_SEGMENTS = 50;
    const int X_SEGMENTS = 50;
    const float radius = 2.08;
    const GLfloat  PI = 3.14159265358979323846f;
    for (int y = 0; y <= Y_SEGMENTS; y++)
    {
        for (int x = 0; x <= X_SEGMENTS; x++)
        {
            float xSegment = (double)x / ((double)X_SEGMENTS);
            float ySegment = (double)y / (double)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            buffer.push_back(glm::vec4(xPos*radius,yPos*radius,zPos*radius,1.0f));
//            sphereVertices.push_back(yPos*radius+0.5f);
//            sphereVertices.push_back(zPos*radius);
        }
    }
    /*// ---- Top ----
    // Left-Top-Back - 0
    buffer.push_back(glm::vec4(-1.0f,  1.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));

    // Right-Top-Back - 1
    buffer.push_back(glm::vec4( 1.0f,  1.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));

    // Left-Top-Front - 2
    buffer.push_back(glm::vec4(-1.0f,  1.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));

    // Right-Top-Front - 3
    buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));*/
    for (int i = 0; i < Y_SEGMENTS; i++)
    {
        for (int j = 0; j < X_SEGMENTS; j++)
        {
            indexes.push_back(glm::ivec3(i * (X_SEGMENTS+1) + j, (i + 1) * (X_SEGMENTS + 1) + j, (i + 1) * (X_SEGMENTS + 1) + j + 1 ));

            indexes.push_back(glm::ivec3(i * (X_SEGMENTS + 1) + j, (i + 1) * (X_SEGMENTS + 1) + j + 1, i * (X_SEGMENTS + 1) + j + 1 ));
//            indexes.push_back((i + 1) * (X_SEGMENTS + 1) + j);
//            indexes.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
//
//            indexes.push_back(i * (X_SEGMENTS + 1) + j);
//            indexes.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
//            indexes.push_back(i * (X_SEGMENTS + 1) + j + 1);
        }
    }


}
