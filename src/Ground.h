#pragma once


class Ground
{
	private:
		Ground() { };

	public:
		double zCoord = 0.0;
	Ground(const Ground&) = delete;

	static Ground& getGround()
	{
		static Ground myInput;
		return myInput;
	};

};