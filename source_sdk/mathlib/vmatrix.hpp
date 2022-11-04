
#ifndef CSGO_CHEAT_VMATRIX_HPP
#define CSGO_CHEAT_VMATRIX_HPP

struct VMatrix
{
	float *operator[](int i)
	{
		return m[i];
	}

	float m[4][4];
};

#endif //CSGO_CHEAT_VMATRIX_HPP
