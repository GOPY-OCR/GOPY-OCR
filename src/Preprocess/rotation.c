#include "rotation.h"

void manual_rot(SDL_Surface **image, double angle)
{
    SDL_Surface *base = *image;
	double angle_radian = -angle * M_PI / 180.0;	// angle in radian
	double tcos = cos(angle_radian);
	double tsin = sin(angle_radian);
	double widthdest = ceil(base->w * fabs(tcos) + base->h * fabs(tsin));
	double heightdest = ceil(base->w * fabs(tsin) + base->h * fabs(tcos));
	SDL_Surface *dest = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                             widthdest,
                                             heightdest,
                                             base->format->BitsPerPixel,
										     base->format->Rmask,
                                             base->format->Gmask,
                                             base->format->Bmask,
                                             base->format->Amask);
	if (dest == NULL)
		return errx(EXIT_FAILURE, "Cannot create the rotated surface");

	int mxdest = dest->w / 2;	// center of dest
	int mydest = dest->h / 2;	// center of dest
	int mx = base->w / 2;		// center of base
	int my = base->h / 2;	    // center of base

	for (int j = 0; j < dest->h; j++) {
		for (int i = 0; i < dest->w; i++)
		{
			/* on détermine la valeur de pixel qui correspond le mieux pour la position
			 * i,j de la surface de dest */

			/* on détermine la meilleure position sur la surface d'base en appliquant
			 * une matrice de rotation inverse
			 */

			int bx = (ceil(tcos * (i - mxdest) + tsin * (j - mydest) + mx));
			int by = (ceil(-tsin * (i - mxdest) + tcos * (j - mydest) + my));
			
            Uint32 *color = getpixel(base, bx, by);
            if (color != NULL)
			    putpixel(dest, i, j, *color);
		}
    }

    SDL_FreeSurface(*image);

    *image = dest;
}

void automatic_rot(SDL_Surface **image) {
    double angle = grid_rotation_detection(*image);
    manual_rot(image, angle);
}
