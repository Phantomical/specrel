#include "Medium.h"

Medium::Medium(double ri) :
	RefractiveIndex(ri)
{

}

//Vacuum has a refractive index of 1 (C/C = 1)
const Medium Medium::Vacuum = Medium(1.0);
