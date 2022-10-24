void manrot(char[] file , int degree)
{
	//declaration of the dead


	// defining the angle in radiant
	const double cnAngle = degree x (M_PI / 180.0);
	// conversion from file path
	Bitmap bm = new Bitmap(file);
	// general iterators
	int i, j;
	// calculated indices in Cartesian coordinates
	int x, y;
	double fDistance, fPolarAngle;
	// for use in neighbouring indices in Cartesian coordinates
	int iFloorX, iCeilingX, iFloorY, iCeilingY;
	// calculated indices in Cartesian coordinates with trailing decimals
	double fTrueX, fTrueY;
	// for interpolation
	double fDeltaX, fDeltaY;
	// pixel colours
	Color clrTopLeft, clrTopRight, clrBottomLeft, clrBottomRight;
	// interpolated top pixels
	double fTopRed, fTopGreen, fTopBlue;
	// interpolated bottom pixels
	double fBottomRed, fBottomGreen, fBottomBlue;
	// final interpolated colour components
	int iRed, iGreen, iBlue;
	int iCentreX, iCentreY;
	int iWidth, iHeight;
	iWidth = bm.Width;
	iHeight = bm.Height;

	iCentreX = iWidth / 2;
	iCentreY = iHeight / 2;
	// 
	Bitmap bmSourceToDestination = new Bitmap(iWidth, iHeight);
	Bitmap bmDestinationFromSource = new Bitmap(iWidth, iHeight);
	Bitmap bmBilinearInterpolation = new Bitmap(iWidth, iHeight);

	for (i = 0; i < iHeight; ++i)
	{
		for (j = 0; j < iWidth; ++j)
		{
			bmSourceToDestination.SetPixel(j, i, Color.Black);
			// since we're looping, we might as well do for the others
			bmDestinationFromSource.SetPixel(j, i, Color.Black);
			bmBilinearInterpolation.SetPixel(j, i, Color.Black);
		}
	}
				
