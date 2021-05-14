
CFG.AppName  = "SOME NAME";
CFG.DataPath = "../data/";
CFG.Window = 
{
	iWidth:       1920,
	iHeight:      1080,
	bBorderless: true,
	bFullscreen: false
};
CFG.Render = 
{
	bUseVsync:       false,
	iMSAA:           1, // 0-none; 1-16 more powerfull MSAA
	iMSAAQuality:    1, // can't be more than can your device
	fZNear:          0.001,
	fZFar:           10000.0,
	fFOV:            45.0,
	fCamRotateSpeed: 20.0 // camera rotation speed will be divided by this value
};
CFG.Sound = 
{
	iMaxChannels: 100,
	
	Volume:
	{
		fDopplerScale:   1.0,
		fDistanceFactor: 1.0,
		fRolloffScale:   1.0
	}
};

CFG.Physics = 
{
	Gravity:
	{
		x: 0.0,
		y: -9.81,
		z: 0.0
	},
	fTimestep: 120.0
};
