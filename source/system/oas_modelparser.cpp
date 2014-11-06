/*
The MIT License

Copyright (c) 2014 Aurora Internet

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <parser\oas_modelparser.h>
#include <system\oas_game.h>
#include <gl\GL.h>

#define GL_BGR 0x80E0
#define GL_BGRA 0x80E1

using namespace OpenAS;

int Parser::LoadTexBMP(const char* imagepath)
{
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath, "rb");

	if (fread(header, 1, 54, file) != 54){ // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}
	if (header[0] != 'B' || header[1] != 'M'){
		printf("Not a correct BMP file\n");
		return 0;
	}

	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	printf("Generating texture ID: %d\n", textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	return textureID;
}

std::string OAS_API Parser::loadMTL(
	const char * path,
	int pos
	//const char * mat,
	//std::string& texture
	)
{
	FILE * file = fopen(path, "r");
	int matLock = 1;		// SHOULD BE 0 : ( 1 FOR DEBUG )
	int i = 0;
	while (1){
		char lineHeader[128];

		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "newmtl") == -1)	// DEBUG : OFF
		{
			//char matf[128] = "";
			//fscanf(file, "%s", &matf);

			//if (!strcmp(matf,mat))
			//	matLock = 1;
		}
		if (strcmp(lineHeader, "map_Kd") == 0)
		{
			if (i==pos)
			{
				std::string gz;
				char t[128];
				fscanf(file, "%s", &t);
				gz = t;
				return gz;
			}
			i++;
		}
		
	}
};

std::string OAS_API Parser::loadOBJ(
	const char * path,
	std::vector < Util::Vector3D > & out_vertices,
	std::vector < Util::Vector2D > & out_uvs,
	std::vector < Util::Vector3D > & out_normals,
	std::vector < int > & out_mtlPos
	//std::vector < std::string > & out_mtl,
	//std::string& mtlfile
	)
{
	Game* g = Game::GetGame();

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< Util::Vector3D > temp_vertices;
	std::vector< Util::Vector2D > temp_uvs;
	std::vector< Util::Vector3D > temp_normals;

	FILE * file = fopen(path, "r");
	if (file == NULL){
		g->GetLogManager()->AddErrorLog("ERR_OBJ_FILE", path, time(NULL), g->GetLogManager()->GetDebugFlag(), LOG_FILE);
		return false;
	}

	std::string mtlPath;
	//std::vector<std::string*> mtl;
	

	int fOff = -1;

	int l = 0;
	while (1){

		char lineHeader[128];
		
		

		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0){
			Util::Vector3D vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0){
			Util::Vector2D uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0){
			Util::Vector3D normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "mtllib") == 0)
		{
			char t[128] = "";
			fscanf(file, "%s", &t);
			//printf("\n%s\n", t);
			mtlPath = t;
		}
		else if (strcmp(lineHeader, "usemtl") == 0)
		{
			//printf("Material found!: ");
			if (fOff == -1)
				fOff = l;

			//std::string t(128, ' ');
			char t[128] = "";
			fscanf(file, "%s", &t);

			printf("%s\n", t);

			//std::string s("a");

			//out_mtl.push_back(t);
			out_mtlPos.push_back(l - fOff);
		}
		else if (strcmp(lineHeader, "f") == 0){
			
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9){
				g->GetLogManager()->AddErrorLog("ERR_OBJ_PARSER", path, time(NULL), g->GetLogManager()->GetDebugFlag(), LOG_FILE);
				return false;
		}
		vertexIndices.push_back(vertexIndex[0]);
		vertexIndices.push_back(vertexIndex[1]);
		vertexIndices.push_back(vertexIndex[2]);
		uvIndices.push_back(uvIndex[0]);
		uvIndices.push_back(uvIndex[1]);
		uvIndices.push_back(uvIndex[2]);
		normalIndices.push_back(normalIndex[0]);
		normalIndices.push_back(normalIndex[1]);
		normalIndices.push_back(normalIndex[2]);

			for (unsigned int i = 0; i < vertexIndices.size(); i++){
				unsigned int vertexIndex = vertexIndices[i];
				Util::Vector3D vertex = temp_vertices[vertexIndex - 1];
				out_vertices.push_back(vertex);
			}
			for (unsigned int i = 0; i < uvIndices.size(); i++){
				unsigned int uvIndex = uvIndices[i];
				Util::Vector2D uv = temp_uvs[uvIndex - 1];
				out_uvs.push_back(uv);
			}
			for (unsigned int i = 0; i < vertexIndices.size(); i++){
				unsigned int normalIndex = normalIndices[i];
				Util::Vector3D normal = temp_normals[normalIndex - 1];
				out_normals.push_back(normal);
			}
		}
		l++;
	}
	return mtlPath;

		//return true;
}