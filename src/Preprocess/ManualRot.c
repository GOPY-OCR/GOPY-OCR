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
	// assigning pixels of destination image from source image
	// with bilinear interpolation
	for (i = 0; i < iHeight; ++i)
	{
		for (j = 0; j < iWidth; ++j)
		{
			// convert raster to Cartesian
			x = j - iCentreX;
			y = iCentreY - i;

			// convert Cartesian to polar
			fDistance = Math.Sqrt(x * x + y * y);
			fPolarAngle = 0.0;
			if (x == 0)
			{
				if (y == 0)
				{
					// centre of image, no rotation needed
					bmBilinearInterpolation.SetPixel(j, i, bm.GetPixel(j, i));
					continue;
				}
				else if (y < 0)
				{
					fPolarAngle = 1.5 * Math.PI;
				}
				else
				{
					fPolarAngle = 0.5 * Math.PI;
				}
			}
			else
			{
				fPolarAngle = Math.Atan2((double)y, (double)x);
			}

			// the crucial rotation part
			// "reverse" rotate, so minus instead of plus
			fPolarAngle -= cnAngle;

			// convert polar to Cartesian
			fTrueX = fDistance * Math.Cos(fPolarAngle);
			fTrueY = fDistance * Math.Sin(fPolarAngle);

			// convert Cartesian to raster
			fTrueX = fTrueX + (double)iCentreX;
			fTrueY = (double)iCentreY - fTrueY;

			iFloorX = (int)(Math.Floor(fTrueX));
			iFloorY = (int)(Math.Floor(fTrueY));
			iCeilingX = (int)(Math.Ceiling(fTrueX));
			iCeilingY = (int)(Math.Ceiling(fTrueY));

			// check bounds
			if (iFloorX < 0 || iCeilingX < 0 || iFloorX >= iWidth || iCeilingX >= iWidth || iFloorY < 0 || iCeilingY < 0 || iFloorY >= iHeight || iCeilingY >= iHeight) continue;

			fDeltaX = fTrueX - (double)iFloorX;
			fDeltaY = fTrueY - (double)iFloorY;

			clrTopLeft = bm.GetPixel(iFloorX, iFloorY);
			clrTopRight = bm.GetPixel(iCeilingX, iFloorY);
			clrBottomLeft = bm.GetPixel(iFloorX, iCeilingY);
			clrBottomRight = bm.GetPixel(iCeilingX, iCeilingY);

			// linearly interpolate horizontally between top neighbours
			fTopRed = (1 - fDeltaX) * clrTopLeft.R + fDeltaX * clrTopRight.R;
			fTopGreen = (1 - fDeltaX) * clrTopLeft.G + fDeltaX * clrTopRight.G;
			fTopBlue = (1 - fDeltaX) * clrTopLeft.B + fDeltaX * clrTopRight.B;

			// linearly interpolate horizontally between bottom neighbours
			fBottomRed = (1 - fDeltaX) * clrBottomLeft.R + fDeltaX * clrBottomRight.R;
			fBottomGreen = (1 - fDeltaX) * clrBottomLeft.G + fDeltaX * clrBottomRight.G;
			fBottomBlue = (1 - fDeltaX) * clrBottomLeft.B + fDeltaX * clrBottomRight.B;

			// linearly interpolate vertically between top and bottom interpolated results
			iRed = (int)(Math.Round((1 - fDeltaY) * fTopRed + fDeltaY * fBottomRed));
			iGreen = (int)(Math.Round((1 - fDeltaY) * fTopGreen + fDeltaY * fBottomGreen));
			iBlue = (int)(Math.Round((1 - fDeltaY) * fTopBlue + fDeltaY * fBottomBlue));

			// make sure colour values are valid
			if (iRed < 0) iRed = 0;
			if (iRed > 255) iRed = 255;
			if (iGreen < 0) iGreen = 0;
			if (iGreen > 255) iGreen = 255;
			if (iBlue < 0) iBlue = 0;
			if (iBlue > 255) iBlue = 255;

			bmBilinearInterpolation.SetPixel(j, i, Color.FromArgb(iRed, iGreen, iBlue));
		}
	}
	bmBilinearInterpolation.Save("rotationbilinearinterpolation.jpg", System.Drawing.Imaging.ImageFormat.Jpeg);

