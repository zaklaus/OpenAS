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

#include <util\sq_funcdef.h>
#include <system\oas_game.h>

#pragma once
extern Game* g;

SQInteger sq_testf(SQVM *squirrelVM)
{
	g->GetLogManager()->AddLog("SQTest","Testing SQ embed",time(NULL));
	return 1;
}

SQInteger sq_print(SQVM *v)
{
	const SQChar* msg;
	sq_getstring(v, -1, &msg);
	printf("%s", msg);
	return 1;
}

SQInteger sq_str(SQVM *v)
{
	SQFloat lvalue;
	
	sq_getfloat(v, -1, &lvalue);

	SQChar msg[128] = "";

	sprintf(msg, "%s", lvalue);

	sq_pushstring(v, msg, sizeof(msg));

	return 1;
}

SQInteger sq_entityRotate(SQVM *v)
{
	Game* g = Game::GetGame();

	SQInteger ID;
	SQFloat x, y, z;

	sq_getinteger(v, -4, &ID);
	sq_getfloat(v, -3, &x); sq_getfloat(v, -2, &y); sq_getfloat(v, -1, &z);

	Entity* e = g->GetEntityManager()->GetEntity(ID);

	if (e)
	{
		e->SetRotation(x, y, z);
		sq_pushbool(v, true);
		return 1;
	}
	sq_pushbool(v, false);
	return 1;
}

SQInteger sq_entityTranslate(SQVM *v)
{
	Game* g = Game::GetGame();

	SQInteger ID;
	SQFloat x, y, z;

	sq_getinteger(v, -4, &ID);
	sq_getfloat(v, -3, &x); sq_getfloat(v, -2, &y); sq_getfloat(v, -1, &z);

	Entity* e = g->GetEntityManager()->GetEntity(ID);

	if (e)
	{
		e->SetPosition(x, y, z);
		sq_pushbool(v, true);
		return 1;
	}
	sq_pushbool(v, false);
	return 1;
}

SQInteger sq_entityCreate(SQVM *v)
{
	Game* g = Game::GetGame();

	SQFloat posx, posy, posz, rotx, roty, rotz;
	const SQChar* ename; const SQChar* sname; const SQChar* mname;

	sq_getstring(v, -9, &ename); sq_getstring(v, -8, &sname); sq_getfloat(v, -7, &posx); sq_getfloat(v, -6, &posy); sq_getfloat(v, -5, &posz); sq_getfloat(v, -4, &rotx); sq_getfloat(v, -3, &roty); sq_getfloat(v, -2, &rotz); sq_getstring(v, -1, &mname);

	sq_pushinteger(v, g->GetEntityManager()->CreateEntity(ename, sname, OpenAS::Util::Vector3D(posx, posy, posz), OpenAS::Util::Vector3D(rotx, roty, rotz), mname));

	return 1;
}
SQInteger sq_entityDestroy(SQVM *v)
{
	Game* g = Game::GetGame();

	SQInteger ID;
	sq_getinteger(v, -1, &ID);

	if (g->GetEntityManager()->GetEntity(ID) != NULL)
	{
		g->GetEntityManager()->DestroyEntity(ID);
		sq_pushbool(v, true);
	}
	else sq_pushbool(v, false);

	return 1;
}

SQInteger sq_entityGetByName(SQVM *v)
{
	Game *g = Game::GetGame();

	const SQChar* name;
	sq_getstring(v, -1, &name);

	Entity* ID = g->GetEntityManager()->GetEntityByName(name);

	if (ID != NULL)
	{
		sq_pushinteger(v, ID->GetID());
	}
	else
	{
		sq_pushinteger(v, -1);
	}
	return 1;
}

SQInteger sq_entityGetPosition(SQVM *v)
{
	Game* g = Game::GetGame();

	SQInteger ID; sq_getinteger(v, -1, &ID);
	SQFloat pos[3] = { 0, 0, 0 };

	Entity* e = g->GetEntityManager()->GetEntity(ID);

	if (e)
	{
		pos[0] = e->GetPosition().x;
		pos[1] = e->GetPosition().y;
		pos[2] = e->GetPosition().z;	
	}
	sq_newarray(v, 3);
	sq_set(v, -1); sq_pushfloat(v, pos[2]); sq_set(v, -2); sq_pushfloat(v, pos[1]); sq_set(v, -3); sq_pushfloat(v, pos[0]);
	
	return 1;
}
SQInteger sq_entityGetRotation(SQVM *v)
{
	Game* g = Game::GetGame();

	SQInteger ID; sq_getinteger(v, -1, &ID);
	SQFloat pos[3] = { 0, 0, 0 };

	Entity* e = g->GetEntityManager()->GetEntity(ID);

	if (e)
	{
		pos[0] = e->GetRotation().x;
		pos[1] = e->GetRotation().y;
		pos[2] = e->GetRotation().z;
	}

	sq_pushfloat(v, pos[2]); sq_pushfloat(v, pos[1]); sq_pushfloat(v, pos[0]);
	return 1;
}

SQInteger sq_inputGetKey(SQVM *v)
{
	Game* g = Game::GetGame();
	
	const SQChar* key;
	sq_getstring(v, -1, &key);

	SQBool state = false;
	state = g->GetSDLApplication()->GetInput()->GetKey(g->GetSDLApplication()->GetKeyByName(key));
	//printf("%d | %d\n\n",SDL_GetKeyFromName("Up"),SDLK_UP);
	if (state == false)
		sq_pushbool(v, false);
	else
		sq_pushbool(v, true);

	return 1;
}

SQInteger sq_inputGetKeyUp(SQVM *v)
{
	Game* g = Game::GetGame();

	const SQChar* key;
	sq_getstring(v, -1, &key);

	SQBool state = false;
	state = g->GetSDLApplication()->GetInput()->GetKeyUp(g->GetSDLApplication()->GetKeyByName(key));
	//printf("%d | %d\n\n",SDL_GetKeyFromName("Up"),SDLK_UP);
	if (state == false)
		sq_pushbool(v, false);
	else
		sq_pushbool(v, true);

	return 1;
}

SQInteger sq_inputGetMouseX(SQVM *v)
{
	Game* g = Game::GetGame();
	SQInteger x = g->GetSDLApplication()->GetInput()->GetMouseX();
	sq_pushinteger(v, x);
	return 1;
}

SQInteger sq_inputGetMouseY(SQVM *v)
{
	Game* g = Game::GetGame();
	SQInteger Y = g->GetSDLApplication()->GetInput()->GetMouseY();
	sq_pushinteger(v, Y);
	return 1;
}

SQInteger sq_inputGetKeyDown(SQVM *v)
{
	Game* g = Game::GetGame();

	const SQChar* key;
	sq_getstring(v, -1, &key);

	SQBool state = false;
	
	state = g->GetSDLApplication()->GetInput()->GetKeyDown(g->GetSDLApplication()->GetKeyByName(key));
	//printf("%d\n\n", state);
	if (state == false)
		sq_pushbool(v, false);
	else
		sq_pushbool(v, true);

	return 1;
}

SQInteger sq_camSetPosition(SQVM *v)
{
	Game* g = Game::GetGame();
	SQFloat x, y, z;

	sq_getfloat(v, -3, &x); sq_getfloat(v, -2, &y); sq_getfloat(v, -1, &z);

	g->GetSDLApplication()->SetPosition(x, y, z);

	sq_pushbool(v, true);
	return 1;
}
SQInteger sq_camSetRotation(SQVM *v)
{
	Game* g = Game::GetGame();
	SQFloat x, y, z;

	sq_getfloat(v, -3, &x); sq_getfloat(v, -2, &y); sq_getfloat(v, -1, &z);

	g->GetSDLApplication()->SetRotation(x, y, z);

	sq_pushbool(v, true);
	return 1;
}

SQInteger sq_drawRect(SQVM *v)
{
	SQInteger h, w, x, y, r, _g, b, a;
	SDL_Rect rect;
	sq_getinteger(v, -1, &a);
	sq_getinteger(v, -2, &b);
	sq_getinteger(v, -3, &_g);
	sq_getinteger(v, -4, &r);
	sq_getinteger(v, -5, &h);
	sq_getinteger(v, -6, &w);
	sq_getinteger(v, -7, &y);
	sq_getinteger(v, -8, &x);

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	Game* eg = Game::GetGame();

	//SDL_FillRect(eg->GetSDLApplication()->GetSurface(), &rect, SDL_MapRGBA(eg->GetSDLApplication()->GetSurface()->format, r, _g, b, a));
	//printf("\n%d %d %d %d : %d %d %d\n",x,y,w,h,r,_g,b);
	return 1;
}

SQInteger sq_lightEnable(SQVM *v)
{
	Game* ga = Game::GetGame();

	SQInteger ID;
	sq_getinteger(v, -1, &ID);

	if (ga->GetMapManager()->GetCurrentMap()->GetLightState(ID) == false)
	{
		sq_pushinteger(v,g->GetMapManager()->GetCurrentMap()->EnableLight(ID));
		return 1;
	}

	sq_pushinteger(v, -1);

	return 1;
}

SQInteger sq_lightDisable(SQVM *v)
{
	Game* g = Game::GetGame();

	SQInteger ID;
	sq_getinteger(v, -1, &ID);

	if (g->GetMapManager()->GetCurrentMap()->GetLightState(ID) == true)
	{
		sq_pushinteger(v, g->GetMapManager()->GetCurrentMap()->DisableLight(ID));
		return 1;
	}

	sq_pushinteger(v, 0);

	return 1;
}

SQInteger sq_timeGetDelta(SQVM *v)
{
	Game* g = Game::GetGame();

	sq_pushfloat(v, g->GetSDLApplication()->GetDelta());

	return 1;
}