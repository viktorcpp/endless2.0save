/*
var test_var = 100;
var test_array =
[
	'first',
	{ 'objvar':100 }
];

var test_object =
{
	'testvar2':20
};

var CFG =
{
	appname:"SOME NAME",
	window:
	{
		width:       1920,
		height:      1080,
		bBorderless: true,
		bFullscreen: false
	},
	render:
	{
		bUseVsync:    true,
        iMSAA:        1, // 0-none; 1-16 more powerfull MSAA
        iMSAAQuality: 1, // can't be more than can your device
        fZNear:       0.001,
        fZFar:        10000.0,
        fFOV:         90
	},
	SOUND:
    {
        iMaxChannels: 100,
        
        VOL:
        {
            fDopplerScale:   1.0,
            fDistanceFactor: 1.0,
            fRolloffScale:   1.0
        }
    },
	PHYSICS:
    {
        iStackSize:     1048576,
        fWorldSize:     100000.0,
        fCollTolerance: 0.1,
		fGravity:
		{
			x: 0.0,
			y: -9.81,
			z: 0.0
		},
        fTimestep:      120.0,
		iTOIEventSize: 512000
    }
};

var func = function()
{
	var a = 10;
	var b = 10;
	test_var *= 2;
}
//*/