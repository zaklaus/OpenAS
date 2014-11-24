local i = 0;
local x=2.0,y=1.4,z=-2.0;
local rotY = 0.0;
local rotX = 0.0;
local rotZ = 0.0;
local mouseX = 0;
local lmouseX = 0;
local mouseY = 0;
local lmouseY = 0;
local walkbias = 0.0;
local bob = 0.0;
local aw = 0;
local sprint = 1;
local delta = 1.0;
local bezdakRotY = 0.0;
local bezdakx = 0.0, bezdaky = 0.6, bezdakz = 0.0;
local bezdak = -1;
local quake = 0;

function onStart()
{
	print("Logic is initialized.");
	//print(me);
	//camSetPosition(0.0,0.0,1.0);
	//print(str(myID));
	camSetPosition(x,y,z);
	
	//lightEnable(0);
}


function onUpdate()
{
	if(bezdak==-1)
	{
		bezdak = entityGetByName("MorganFreeman");
	}
	mouseX = inputGetMouseX();
	mouseY = inputGetMouseY();

	aw++;

	if(aw>45)
	{
		aw = 0;
		//print("\n\nX: "+mouseX.tostring()+" | Y: "+mouseY.tostring() + " | ROTY: "+rotY.tostring());
		//print("\nDelta Time: "+delta.tostring());
	}

	bezdakRotY = 360.0 - rotY;

	if(inputGetKey("Up") || inputGetKey("W"))
	{
		x -= sin(rotY*(3.14/180)) * 0.05 * sprint * delta;
		z -= cos(rotY*(3.14/180)) * 0.05 * sprint * delta;
		y += sin(rotX*(3.14/180)) * 0.05 * sprint * delta;
		if(bob >=359)
		{
			bob = 0;
		}
		else
			bob+=5;

	}
	if(inputGetKey("LeftShift"))
	{
		sprint = 1.5;
	}

	if(inputGetKeyUp("LeftShift"))
	{
		sprint = 1;
	}
	if (inputGetKey("Down") || inputGetKey("S"))
	{
		
		x += sin(rotY*(3.14/180)) * 0.035 * delta;
		z += cos(rotY*(3.14/180)) * 0.035 * delta;
	}
	if(inputGetKey("D"))
	{
		x += sin((rotY+90)*(3.14/180)) * 0.040 * delta;
		z += cos((rotY+90)*(3.14/180)) * 0.040 * delta;	
	}
	if(inputGetKey("A"))
	{
		x -= sin((rotY+90)*(3.14/180)) * 0.040 * delta;
		z -= cos((rotY+90)*(3.14/180)) * 0.040 * delta;	
	}
	if (inputGetKey("Left"))
	{
		
		rotY += 2;
	}
	if (inputGetKey("Right"))
	{
		
		rotY += -2;
	}
	if(inputGetKey("PageUp"))
	{
		rotX += 1;
	}
if(inputGetKey("PageDown"))
	{
		rotX -= 1;
	}

	rotX += -(mouseY.tofloat()-lmouseY.tofloat());

	if(rotX>60.0)
		rotX=60.0;
	if(rotX<=-60.0)
		rotX=-60.0;
	rotY += -(mouseX.tofloat()-lmouseX.tofloat());

	if(quake>=359)
	{
		quake = 0;
	} else quake += 3;

	camSetPosition(x,y+walkbias,z);
	camSetRotation(rotX,rotY,rotZ);

	i = i + 1;

	bezdakx -= sin(i*(3.14/180)) * 0.05;
	bezdakz -= cos(i*(3.14/180)) * 0.05;	

	//drawRect(0,0,800,600,255,128,0,1);
	//local rot = entityGetRotation(me);
	entityRotate(bezdak,0,i+90.0,0);	
	entityTranslate(bezdak,bezdakx,bezdaky,bezdakz);
	lmouseX = mouseX;
	lmouseY = mouseY;
}