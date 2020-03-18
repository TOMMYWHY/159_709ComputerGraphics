// Project Header
#include "geometry.h"

// --------------------------------------------------------------------------------
// Create Cube with Positions and Normals (Interleaved)
void createCubeInterleaved(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes) {
	// ---- Top ----
	// Left-Top-Back - 0
	buffer.push_back(glm::vec4(-1.0f,  1.0f, -1.0f,  1.0f)); // Position
	buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f)); // Normal

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
	buffer.push_back(glm::vec4(-1.0f, -1.0f, -1.0f,  1.0f)); // Position
	buffer.push_back(glm::vec4( 0.0f, -1.0f,  0.0f,  0.0f)); // Normal

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
	buffer.push_back(glm::vec4(-1.0f,  1.0f, -1.0f,  1.0f)); // Position
	buffer.push_back(glm::vec4(-1.0f,  0.0f,  0.0f,  0.0f)); // Normal

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
	buffer.push_back(glm::vec4( 1.0f,  1.0f, -1.0f,  1.0f)); // Position
	buffer.push_back(glm::vec4( 1.0f,  0.0f,  0.0f,  0.0f)); // Normal

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
	buffer.push_back(glm::vec4(-1.0f,  1.0f,  1.0f,  1.0f)); // Position
	buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f)); // Normal

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
	buffer.push_back(glm::vec4(-1.0f,  1.0f, -1.0f,  1.0f)); // Position
	buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f)); // Normal

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
// Create Cube with Positions and Normals
void createCubeSeparate(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes) {
	// Vertexes

	// ---- Top ----
	buffer.push_back(glm::vec4(-1.0f,  1.0f, -1.0f,  1.0f)); // Left-Top-Back - 0
	buffer.push_back(glm::vec4( 1.0f,  1.0f, -1.0f,  1.0f)); // Right-Top-Back - 1
	buffer.push_back(glm::vec4(-1.0f,  1.0f,  1.0f,  1.0f)); // Left-Top-Front - 2
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  1.0f)); // Right-Top-Front - 3

	// ---- Bottom ----	
	buffer.push_back(glm::vec4(-1.0f, -1.0f, -1.0f,  1.0f)); // Left-Bottom-Back - 4
	buffer.push_back(glm::vec4( 1.0f, -1.0f, -1.0f,  1.0f)); // Right-Bottom-Back - 5
	buffer.push_back(glm::vec4(-1.0f, -1.0f,  1.0f,  1.0f)); // Left-Bottom-Front - 6
	buffer.push_back(glm::vec4( 1.0f, -1.0f,  1.0f,  1.0f)); // Right-Bottom-Front - 7

	// ---- Left ----
	buffer.push_back(glm::vec4(-1.0f,  1.0f, -1.0f,  1.0f)); // Left-Top-Back - 8
	buffer.push_back(glm::vec4(-1.0f, -1.0f, -1.0f,  1.0f)); // Left-Bottom-Back - 9	
	buffer.push_back(glm::vec4(-1.0f,  1.0f,  1.0f,  1.0f)); // Left-Top-Front - 10
	buffer.push_back(glm::vec4(-1.0f, -1.0f,  1.0f,  1.0f)); // Left-Bottom-Front - 11

	// ---- Right ----
	buffer.push_back(glm::vec4( 1.0f,  1.0f, -1.0f,  1.0f)); // Right-Top-Back - 12
	buffer.push_back(glm::vec4( 1.0f, -1.0f, -1.0f,  1.0f)); // Right-Bottom-Back - 13
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  1.0f)); // Right-Top-Front - 14
	buffer.push_back(glm::vec4( 1.0f, -1.0f,  1.0f,  1.0f)); // Right-Bottom-Front - 15

	// ---- Front ----
	buffer.push_back(glm::vec4(-1.0f,  1.0f,  1.0f,  1.0f)); // Left-Top-Front - 16
	buffer.push_back(glm::vec4( 1.0f,  1.0f,  1.0f,  1.0f)); // Right-Top-Front - 17
	buffer.push_back(glm::vec4(-1.0f, -1.0f,  1.0f,  1.0f)); // Left-Bottom-Front - 18
	buffer.push_back(glm::vec4( 1.0f, -1.0f,  1.0f,  1.0f)); // Right-Bottom-Front - 19

	// ---- Back ----
	buffer.push_back(glm::vec4(-1.0f,  1.0f, -1.0f,  1.0f)); // Left-Top-Back - 20
	buffer.push_back(glm::vec4( 1.0f,  1.0f, -1.0f,  1.0f)); // Right-Top-Back - 21
	buffer.push_back(glm::vec4(-1.0f, -1.0f, -1.0f,  1.0f)); // Left-Bottom-Back - 22
	buffer.push_back(glm::vec4( 1.0f, -1.0f, -1.0f,  1.0f)); // Right-Bottom-Back - 23


	// ---- Normals ----
	// Top
	buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));

	// Bottom
	buffer.push_back(glm::vec4( 0.0f, -1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f, -1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f, -1.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f, -1.0f,  0.0f,  0.0f));

	// Left
	buffer.push_back(glm::vec4(-1.0f,  0.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4(-1.0f,  0.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4(-1.0f,  0.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4(-1.0f,  0.0f,  0.0f,  0.0f));

	// Right
	buffer.push_back(glm::vec4( 1.0f,  0.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  0.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  0.0f,  0.0f,  0.0f));
	buffer.push_back(glm::vec4( 1.0f,  0.0f,  0.0f,  0.0f));

	// Front
	buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));

	// Back
	buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));
	buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));


	//  ----Indexes ----
	// Top
	indexes.push_back(glm::ivec3(0, 2, 3));
	indexes.push_back(glm::ivec3(0, 3, 1));

	// Bottom
	indexes.push_back(glm::ivec3(4, 6, 7));
	indexes.push_back(glm::ivec3(4, 7, 5));

	// Left
	indexes.push_back(glm::ivec3(8,  9, 11));
	indexes.push_back(glm::ivec3(8, 11, 10));

	// Right
	indexes.push_back(glm::ivec3(14, 15, 13));
	indexes.push_back(glm::ivec3(14, 13, 12));

	// Front
	indexes.push_back(glm::ivec3(16, 18, 19));
	indexes.push_back(glm::ivec3(16, 19, 17));

	// Back
	indexes.push_back(glm::ivec3(21, 23, 22));
	indexes.push_back(glm::ivec3(21, 22, 20));
}

// --------------------------------------------------------------------------------
// Create Tetrahedron with Positions and Colours (Interleaved)
void createTetrahedronInterleaved(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes) {
	// Left-Bottom-Back
	glm::vec3 v0 = glm::vec3(-0.5f, -sqrt(1.0f/12.0f), -sqrt(1.0f/12.0f));

	// Right-Bottom-Back
	glm::vec3 v1 = glm::vec3( 0.5f, -sqrt(1.0f/12.0f), -sqrt(1.0f/12.0f));

	// Centre-Bottom-Front
	glm::vec3 v2 = glm::vec3( 0.0f, -sqrt(1.0f/12.0f),   sqrt(1.0f/3.0f));

	// Center-Top-Centre
	glm::vec3 v3 = glm::vec3( 0.0f,    sqrt(1.0/3.0f),              0.0f);


	// Left-Bottom-Back    - 0
	buffer.push_back(glm::vec4(  v0,             1.0f)); // Position
	buffer.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); // Colour

	// Right-Bottom-Back   - 1
	buffer.push_back(glm::vec4(  v1,             1.0f)); // Position
	buffer.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)); // Colour
	
	// Centre-Bottom-Front - 2
	buffer.push_back(glm::vec4(  v2,             1.0f)); // Position
	buffer.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)); // Colour

	// Center-Top-Centre   - 3
	buffer.push_back(glm::vec4(  v3,             1.0f)); // Position
	buffer.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)); // Colour

	// Indexes
	indexes.push_back(glm::ivec3( 0, 1, 2));
	indexes.push_back(glm::ivec3( 0, 2, 3));
	indexes.push_back(glm::ivec3( 1, 3, 2));
	indexes.push_back(glm::ivec3( 0, 3, 1));
}

// --------------------------------------------------------------------------------
// Create Tetrahedron with Positions and Colours (Separate)
void createTetrahedronSeparate(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes) {
	// Left-Bottom-Back
	glm::vec3 v0 = glm::vec3(-0.5f, -sqrt(1.0f/12.0f), -sqrt(1.0f/12.0f));

	// Right-Bottom-Back
	glm::vec3 v1 = glm::vec3( 0.5f, -sqrt(1.0f/12.0f), -sqrt(1.0f/12.0f));

	// Centre-Bottom-Front
	glm::vec3 v2 = glm::vec3( 0.0f, -sqrt(1.0f/12.0f),   sqrt(1.0f/3.0f));

	// Center-Top-Centre
	glm::vec3 v3 = glm::vec3( 0.0f,    sqrt(1.0/3.0f),              0.0f);

	// Positions
	buffer.push_back(glm::vec4(  v0,             1.0f)); // Left-Bottom-Back    - 0
	buffer.push_back(glm::vec4(  v1,             1.0f)); // Right-Bottom-Back   - 1
	buffer.push_back(glm::vec4(  v2,             1.0f)); // Centre-Bottom-Front - 2
	buffer.push_back(glm::vec4(  v3,             1.0f)); // Center-Top-Centre   - 3

	// Colours
	buffer.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); // Left-Bottom-Back    - 0
	buffer.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)); // Right-Bottom-Back   - 1
	buffer.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)); // Centre-Bottom-Front - 2
	buffer.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)); // Center-Top-Centre   - 3

	// Indexes
	indexes.push_back(glm::ivec3( 0, 1, 2));
	indexes.push_back(glm::ivec3( 0, 2, 3));
	indexes.push_back(glm::ivec3( 1, 3, 2));
	indexes.push_back(glm::ivec3( 0, 3, 1));
}