#pragma config(Sensor, dgtl4,  ,               sensorQuadEncoder)
#pragma config(Motor,  port1,           launcherLeftTwo, tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port2,           launcherLeft,  tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port3,           leftFront,     tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port4,           leftBack,      tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port5,           rightFront,    tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port6,           rightBack,     tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port7,           elevator,      tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port8,           intakeWheels,  tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port9,           launcherRight, tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port10,          launcherRightTwo, tmotorVex393HighSpeed, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//Translation: Motor, what port it's in, which part it's assigned to.

// Autonomy task, will be more fleshed out.
task autonomous()
{
	//Turns on elevator and launcher
	motor[elevator] = 30;
	motor[launcherLeft] = -68;
	motor[launcherRight] = 68;
	motor[launcherLeftTwo] = -68;
	motor[launcherRightTwo] = 68;
	wait1Msec(15000);//Waits 15 seconds
	//Turns elevator and launcher off
	motor[elevator] = 0;
	motor[launcherLeft] = 0;
	motor[launcherRight] = 0;
	motor[launcherLeftTwo] = 0;
	motor[launcherRightTwo] = 0;
}

//main task
task main()
{
	//Calls autonmous mode for 15000 miliseconds(15 seconds)
	StartTask(autonomous);
	wait1Msec(15000);
	bool	primaryloop = true;
	bool intake = false;


	//Primary control loop
	while(primaryloop)

	{
		//Forward/Backward movement
		motor[leftBack] = vexRT[Ch3];
		motor[leftFront] = vexRT[Ch3];
		motor[rightBack] = vexRT[Ch2];
		motor[rightFront] = vexRT[Ch2];

		//Raise Elevator, fast
		if(vexRT[Btn6U] == 1 && vexRT[Btn6D] == 0)//RobotC is a finnicky mistress -.-
		{
			motor[elevator] = 120;
		}

		//Raise elvator slowly, for accurate adjustment of the flaps
		else if(vexRT[Btn6D] == 1 && vexRT[Btn6U] == 0)
		{
			motor[elevator] =40;
		}

		//Activates launcher
		//High Launcher Speed
		else if (vexRT[Btn8U] == 1)
		{
			motor[launcherLeft] = -70;
			motor[launcherRight] = 70;
			motor[launcherLeftTwo] = -70;
			motor[launcherRightTwo] = 70;
		}
		//Medium Launcher Speed
		else if (vexRT[Btn8R] == 1)
		{
			motor[launcherLeft] = -65;
			motor[launcherRight] = 65;
			motor[launcherLeftTwo] = -65;
			motor[launcherRightTwo] = 65;
		}
		//Low Speed
		else if (vexRT[Btn8D] == 1)
		{
			motor[launcherLeft] = -40;
			motor[launcherRight] = 40;
			motor[launcherLeftTwo] = -40;
			motor[launcherRightTwo] = 40;
		}

		//Deactivates launcher
		else if(vexRT[Btn8L] == 1)
		{
			motor[launcherLeft] = 0;
			motor[launcherRight] = 0;
			motor[launcherLeftTwo] = 0;
			motor[launcherRightTwo] = 0;
		}

		//Toggling intake system
		else if (vexRT[Btn7R])
		{
			//If the intake system is off...
			if (intake == false)
			{
				//Turn it on
				motor[intakeWheels] = 100;
				//Remember it's on
				intake = true;
			}
			//If the intake system is on...
			else if (intake == true)
			{
				//Turn it off
				motor[intakeWheels] = 0;
				//Remember it's off
				intake = false;
			}
		}
		//Sets elevator to zero and starts the loop over
		else
		{
			motor[elevator] = 0;
		}
	}
}


/* Comment section
====================
RobotC error messages are about as useful as Jar Jar Binks - T
RobotC is about as logical as the movie Inception - J
Inception is a pretty logical movie, just convuluted - T
*/