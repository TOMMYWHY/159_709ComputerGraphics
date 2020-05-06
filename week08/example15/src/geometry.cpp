// Project Header
#include "geometry.h"

// --------------------------------------------------------------------------------
// Create Triangle with Positions and Colours
void createTriangle(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes) {
	// Left-Bottom - 0
	buffer.push_back(glm::vec4(-1.0f, -0.577,  0.0f,  1.0f));
	buffer.push_back(glm::vec4( 1.0f,    0.0f,  0.0f,  0.0f));

	// Right-Bottom- 1
	buffer.push_back(glm::vec4( 1.0f, -0.577,  0.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,    1.0f,  0.0f,  0.0f));

	// Right-Top - 2
	buffer.push_back(glm::vec4( 0.0f,  1.155f,  0.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,    0.0f,  1.0f,  0.0f));

	// Top
	indexes.push_back(glm::ivec3(0, 1, 2));
}

// --------------------------------------------------------------------------------
// Create Quadrangle with Positions and Colours
void createQuad(std::vector<glm::vec4> &buffer, std::vector<glm::ivec4> &indexes) {
	// Left-Bottom - 0
	buffer.push_back(glm::vec4(-1.0f, -1.0f,  0.0f,  1.0f));
	buffer.push_back(glm::vec4( 1.0f,  0.0f,  0.0f,  0.0f));

	// Right-Bottom- 1
	buffer.push_back(glm::vec4( 1.0f, -1.0f,  0.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));

	// Right-Top - 2
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  0.0f,  1.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));

	// Left-Top - 3
	buffer.push_back(glm::vec4(-1.0f,  1.0f,  0.0f,  1.0f));
	buffer.push_back(glm::vec4( 1.0f,  0.0f,  1.0f,  0.0f));

	// Top
	indexes.push_back(glm::ivec4(0, 1, 2, 3));
}

// --------------------------------------------------------------------------------
// Create Quadrangles with Positions and Colours
void createQuads(std::vector<glm::vec4> &buffer, std::vector<glm::ivec4> &indexes, int X, int Y) {
	// Rows
	for(int iy = 0; iy < Y+1; iy++) {
		// Columns
		for(int ix = 0; ix < X+1; ix++) {
			// Left-Bottom - 0
			buffer.push_back(glm::vec4(-1.0f + ix * 2.0f/X, -1.0f + iy * 2.0f/Y,  0.0f,  1.0f));
			buffer.push_back(glm::vec4( ix * 1.0f / X,  iy * 1.0f / Y,  0.0f,  0.0f));

			// // Right-Bottom- 1
			// buffer.push_back(glm::vec4(-1.0f + ix/(float)X,   -1.0f + (iy - 1.0f)/Y,  0.0f,  1.0f));
			// buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));

			// // Right-Top - 2
			// buffer.push_back(glm::vec4(-1.0f + ix/(float)X,   -1.0f + iy/(float)Y,  0.0f,  1.0f));
			// buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));

			// // Left-Top - 3
			// buffer.push_back(glm::vec4(-1.0f + (ix - 1.0f)/X, -1.0f + iy/(float)Y,  0.0f,  1.0f));
			// buffer.push_back(glm::vec4( 1.0f,  0.0f,  1.0f,  0.0f));

			// // Index
			// int k = iy * (X+1) + ix;

			// indexes.push_back(glm::ivec4(0, 1, 2, 3));
		}
	}

	// Index
	for(int iy = 0; iy < Y; iy++) {
		for(int ix = 0; ix < X; ix++) {
			int k = iy * (X+1) + ix;

			indexes.push_back(glm::ivec4(k, k+1, k + (X + 1) + 1, k + (X + 1)));
		}
	}
}
