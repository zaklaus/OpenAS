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

#include <system\oas_model.h>
#include <system\oas_sdl2application.h>
#include <parser\oas_modelparser.h>
#include <gl\GL.h>
#include <system\oas_game.h>

using namespace OpenAS::System;

Material::Material(const std::string& texturePath)
{
	this->texture = texturePath;
	
	this->textureID = Parser::LoadTexBMP(texturePath.c_str());
}

void Model::LoadModel(const char* dir, const char* path)
{

	Game* g = Game::GetGame();

	std::string mtlpath;
	//mtl.push_back(MaterialName("test"));
	mtlpath = Parser::loadOBJ(path, this->vertices, this->uvs, this->normals, this->mtlPosX);
	
	//printf("Materials found: %d\n", this->mtlPosX.size());
	//printf("MTL Path: %s\n", mtlpath.c_str());
	for (int i = 0; i < this->mtlPosX.size(); i++)
	{
		std::string tmp_texpath;

		char matpath[128]="", texpath[128]="";

		sprintf(matpath,"%s\\%s%s", g->GetSettings()->models.c_str(),dir, mtlpath.c_str());

		tmp_texpath = Parser::loadMTL(matpath,i);

		sprintf(texpath, "%s\\%s%s", g->GetSettings()->models.c_str(), dir, tmp_texpath.c_str());

		//printf("%s", tmp_texpath.c_str());

		Material* m = new Material(texpath);

		this->materials.push_back(*m);
		delete m;
		m = NULL;
	}
	
	this->listID = glGenLists(1);
	glNewList(this->listID, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for (int j = 0; j < this->vertices.size(); j++){
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glNormal3f(this->normals.at(j).x, this->normals.at(j).y, this->normals.at(j).z);
		glTexCoord2f(this->uvs.at(j).x, this->uvs.at(j).y);
		glVertex3f(this->vertices.at(j).x, this->vertices.at(j).y, this->vertices.at(j).z);
	}
	glEnd();
	glEndList();
	
}