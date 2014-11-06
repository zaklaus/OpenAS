local i = 0;
local x=2.0,y=0.9,z=-2.0;
local rotY = 0.0;
local aw = 0;

function onStart()
{
	print("Logic is initialized.");
	//print(me);
	//camSetPosition(0.0,0.0,1.0);
	//print(str(myID));
	camSetPosition(x,y,z);
}


function onUpdate()
{
	aw++;

	if(aw>16)
	{
		aw = 0;
		//print("\n\nX: "+x.tostring()+" | Z: "+z.tostring() + " | ROTY: "+rotY.tostring());
	}

	if(inputGetKey("Up"))
	{
		
		x -= sin(rotY*(3.14/180)) * 0.05;
		z -= cos(rotY*(3.14/180)) * 0.05;
	}
	if (inputGetKey("Down"))
	{
		
		x += sin(rotY*(3.14/180)) * 0.035;
		z += cos(rotY*(3.14/180)) * 0.035;
	}
	if (inputGetKey("Left"))
	{
		
		rotY += 2;
	}
	if (inputGetKey("Right"))
	{
		
		rotY += -2;
	}

	camSetPosition(x,y,z);
	camSetRotation(0.0,rotY,0.0);
	i = i + 1;
	//drawRect(0,0,800,600,255,128,0,1);
	//local rot = entityGetRotation(me);
	//entityRotate(me,i+2,0,0);	
}