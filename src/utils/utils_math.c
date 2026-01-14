#include "cub3d.h"

float	fix_angle(float angle)
{
	if (angle >= 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return (angle);
}

float	deg_to_rad(float angle)
{
	angle = angle * M_PI / 180.0;
	return (angle);
}