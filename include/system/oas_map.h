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

#ifndef OAS_MAP_H
#define OAS_MAP_H

#include <parser\oas_mapparser.h>
#include <system\oas_platform.h>
#include <system\oas_defaults.h>
#include <util\oas_stringutil.h>
#include <util\oas_generic.h>
#include <vector>

namespace OpenAS
{
	namespace System
	{
		class OAS_API Light
		{
		public:
			//
			//glEnable(GL_LIGHT0); float ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f }; float diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f }; float specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f }; float position[] = { 0.0f, 1.0f, 0.0f, 1.0f };
			//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight); glLightfv(GL_LIGHT0, GL_POSITION, position);
			//

			Util::Vector3D pos, amb, diff, spec;

			int exflag = 1;
			int lightID = -1;

			Light(Util::Vector3D _pos, Util::Vector3D _amb, Util::Vector3D _diff, Util::Vector3D _spec)
			{
				pos = _pos;
				amb = _amb;
				diff = _diff;
				spec = _spec;
			};
		};

		class OAS_API Map
		{
		private:
			char m_szMapName[256];
			char m_szMapAuthor[256];
			char m_szMapVersion[256];
			char m_szMapFileName[256];
			std::vector<Light> m_cLights;
			bool m_lstatus[8];
			int m_lid[8];
			int m_iEntities[MAX_ENTITIES];
			int m_iMapID;
			bool m_bLoaded;
		public:
			Map(int id, const char* mapfile);

			void UnloadThisMap();

			void LoadThisMap();
			char* GetMapName() { return (char*)&m_szMapName; };
			char* GetMapAuthor() { return (char*)&m_szMapAuthor; };
			char* GetMapVersion() { return (char*)&m_szMapVersion; };
			Light* GetLight(int i){ return &m_cLights[i]; };
			Light* GetLightByGL(int i){ if (m_lid[i] != -1){ return &m_cLights[m_lid[i]]; } else return NULL; };
			std::vector<Light>* GetLights(){ return &m_cLights; };
			int GetMapID() {return m_iMapID;};
			bool GetLightState(int id){ return m_lstatus[id]; };
			void SetLightState(int id, bool state){ m_lstatus[id] = state; };
			int EnableLight(int id);
			int DisableLight(int id);
			int AddLight(LightData sData){
				Light* l = new Light(sData.pos, sData.amb, sData.diff, sData.spec);
				m_cLights.push_back(*l);

				delete l;
				l = NULL;
				return m_cLights.size();
			};
			void RemoveLight(int id){ DisableLight(id); m_cLights.erase(m_cLights.begin() + id); };
		};
	}
}


#endif