// Speed of light exists because the computer simulating our reality is not powerful enough to perform computation beyond that limit.
#pragma once
constexpr auto DEFAULT_DIMENSION = 256;
constexpr auto DEFAULT_NUMBER_OF_PARTICLES = 7;

class Universe
{
	int (*cellArray)[DEFAULT_DIMENSION];

	struct Particle
	{
		int xCoordinate;
		int xInertia;
		int xPositionChange;
		int yCoordinate;
		int yInertia;
		int yPositionChange;
		bool isBarrier;
	};

	Particle* particleList;

public:
	Universe();
	~Universe();

	void AddParticle(int, int);
	void RemoveParticle(int, int);
	void UpdateParticlePosition();
	float xFieldIndexToCoordinate(int);
	float yFieldIndexToCoordinate(int);
	size_t coordinateToFieldIndex(int);
};

Universe::Universe()
{
	// Create cellArray array and particles
	cellArray = new int[DEFAULT_DIMENSION][DEFAULT_DIMENSION]();
	particleList = new Particle[(2 * ((2 * DEFAULT_DIMENSION) - 1)) + DEFAULT_NUMBER_OF_PARTICLES]();

	// Create barrier along edge of cellArray so that particles don't
	// go out of bound

	int pc = 0;
	for (int x = 0; x < DEFAULT_DIMENSION; ++x)
	{
		//Top bottom
		//cellArray[0][x] = cellArray[DEFAULT_DIMENSION - 1][x] = 1;
		AddParticle(particleList[pc * 2].yCoordinate = coordinateToFieldIndex(0),
			particleList[pc * 2].xCoordinate = coordinateToFieldIndex(x));
		AddParticle(particleList[2 * pc + 1].yCoordinate = coordinateToFieldIndex(DEFAULT_DIMENSION - 1),
			particleList[2 * pc + 1].xCoordinate = coordinateToFieldIndex(x));
		++pc;
	}

	//	Left and right edge
	for (int y = 1; y < DEFAULT_DIMENSION - 1; ++y)
	{
		//cellArray[y][0] = cellArray[y][DEFAULT_DIMENSION - 1] = 1;
		AddParticle(particleList[pc * 2].yCoordinate = coordinateToFieldIndex(y),
			particleList[pc * 2].xCoordinate = coordinateToFieldIndex(0));
		AddParticle(particleList[2 * pc + 1].yCoordinate = coordinateToFieldIndex(y),
			particleList[2 * pc + 1].xCoordinate = coordinateToFieldIndex(DEFAULT_DIMENSION));
		++pc;
	}



	//	Top and bottom edge
	//for (int x = 0; x < DEFAULT_DIMENSION; ++x)
	//	cellArray[0][x] = cellArray[DEFAULT_DIMENSION - 1][x] = 1;

	////	Left and right edge
	//for (int y = 1; y < DEFAULT_DIMENSION - 1; ++y)
	//	cellArray[y][0] = cellArray[y][DEFAULT_DIMENSION - 1] = 1;
	
	// Add particles
	AddParticle(particleList[0].yCoordinate = coordinateToFieldIndex(0), 
		particleList[0].xCoordinate = coordinateToFieldIndex(-2));
	AddParticle(particleList[1].yCoordinate = coordinateToFieldIndex(0), 
		particleList[1].xCoordinate = coordinateToFieldIndex(0));
	AddParticle(particleList[2].yCoordinate = coordinateToFieldIndex(0), 
		particleList[2].xCoordinate = coordinateToFieldIndex(2));
	AddParticle(particleList[3].yCoordinate = coordinateToFieldIndex(2),
		particleList[3].xCoordinate = coordinateToFieldIndex(-2));
	AddParticle(particleList[4].yCoordinate = coordinateToFieldIndex(2),
		particleList[4].xCoordinate = coordinateToFieldIndex(0));
	AddParticle(particleList[5].yCoordinate = coordinateToFieldIndex(2),
		particleList[5].xCoordinate = coordinateToFieldIndex(2));
	AddParticle(particleList[6].yCoordinate = coordinateToFieldIndex(4),
		particleList[6].xCoordinate = coordinateToFieldIndex(4));
}

Universe::~Universe()
{
	delete[] cellArray;
	delete[] particleList;
}

inline void Universe::AddParticle(int yCoordinate, int xCoordinate)
{
	//convert coordinate value to index value
	//what the hell value to give to that cellArray coordinate
	cellArray[yCoordinate + 1][xCoordinate - 1] += 1;
	cellArray[yCoordinate + 1][xCoordinate] += 1;
	cellArray[yCoordinate + 1][xCoordinate + 1] += 1;

	cellArray[yCoordinate][xCoordinate - 1] += 1;
	cellArray[yCoordinate][xCoordinate] += 1;	//	Flaw in logic, what if two particles are heading towards each other?
	cellArray[yCoordinate][xCoordinate + 1] += 1;

	cellArray[yCoordinate - 1][xCoordinate - 1] += 1;
	cellArray[yCoordinate - 1][xCoordinate] += 1;
	cellArray[yCoordinate - 1][xCoordinate + 1] += 1;
}

inline void Universe::RemoveParticle(int yCoordinate, int xCoordinate)
{
	cellArray[yCoordinate + 1][xCoordinate - 1] -= 1;
	cellArray[yCoordinate + 1][xCoordinate] -= 1;
	cellArray[yCoordinate + 1][xCoordinate + 1] -= 1;

	cellArray[yCoordinate][xCoordinate - 1] -= 1;
	cellArray[yCoordinate][xCoordinate] -= 1;
	cellArray[yCoordinate][xCoordinate + 1] -= 1;

	cellArray[yCoordinate - 1][xCoordinate - 1] -= 1;
	cellArray[yCoordinate - 1][xCoordinate] -= 1;
	cellArray[yCoordinate - 1][xCoordinate + 1] -= 1;
}

inline void Universe::UpdateParticlePosition()
{
	// 3 steps: calculate inertia, delete old position, add new position
	for (size_t i = 0; i < DEFAULT_NUMBER_OF_PARTICLES; ++i)
	{
		//	Calculating the inertias on the diagonals
		//	x-o-o
		//	o-o-o
		//	o-o-x
		int tempInertiaDiag = 
			cellArray[particleList[i].yCoordinate + 1][particleList[i].xCoordinate - 1] - 
			cellArray[particleList[i].yCoordinate - 1][particleList[i].xCoordinate + 1];

		particleList[i].xInertia += tempInertiaDiag;
		particleList[i].yInertia -= tempInertiaDiag;

		//	o-o-x
		//	o-o-o
		//	x-o-o
		tempInertiaDiag = 
			cellArray[particleList[i].yCoordinate - 1][particleList[i].xCoordinate - 1] - 
			cellArray[particleList[i].yCoordinate + 1][particleList[i].xCoordinate + 1];

		particleList[i].xInertia += tempInertiaDiag;
		particleList[i].yInertia += tempInertiaDiag;

		//	Calculating the inertia directly above, below, and to the side of the particle
		//	o-o-o
		//	x-o-x
		//	o-o-o
		particleList[i].xInertia +=
			cellArray[particleList[i].yCoordinate][particleList[i].xCoordinate - 1] - 
			cellArray[particleList[i].yCoordinate][particleList[i].xCoordinate + 1];
		
		//	o-x-o
		//	o-o-o
		//	o-x-o
		particleList[i].yInertia += 
			cellArray[particleList[i].yCoordinate - 1][particleList[i].xCoordinate] - 
			cellArray[particleList[i].yCoordinate + 1][particleList[i].xCoordinate];

		particleList[i].xInertia = (3 * ((0xffe000 >> (particleList[i].xInertia + 10)) & 1))
			+ (particleList[i].xInertia * ((0x01f80 >> (particleList[i].xInertia + 10)) & 1))
			+ (-3 * ((0x0007f >> (particleList[i].xInertia + 10)) & 1));
		particleList[i].yInertia = (3 * ((0xffe000 >> (particleList[i].yInertia + 10)) & 1))
			+ (particleList[i].yInertia * ((0x01f80 >> (particleList[i].yInertia + 10)) & 1))
			+ (-3 * ((0x0007f >> (particleList[i].yInertia + 10)) & 1));

		//	Calculating the magnitude of the change in position due to inertia
		//	Will be used to determine if particle moves by 1 unit
		particleList[i].xPositionChange += particleList[i].xInertia;
		particleList[i].yPositionChange += particleList[i].yInertia;
	}

	int negativePart = 0;
	int positivePart = 0;
	int offset = 0;

	// Move the particle by removing from its old position and placing it at the new one
	// What if they are at the same position? Then try not to put particles in the same position
	for (size_t i = 0; i < DEFAULT_NUMBER_OF_PARTICLES; ++i)
	{
		RemoveParticle(particleList[i].yCoordinate, particleList[i].xCoordinate);

		//	Logic for moving the particle by 1 unit only if the magnitude of the change in position
		//	is large enough
		//	Range of the offset is from 3 to 9 to prevent having a negative offset for bit shifting
		//	1111 1110 0000 0000 & 0000 0000 0000 0001 = 1 if offset is 9 or more (move in positive
		//		direction by 1 unit
		//	0000 0000 0000 1111 & 0000 0000 0000 0001 = 1 if offset is 3 or less (move in negative
		//		direction by 1 unit
		offset = particleList[i].xPositionChange + 6;
		positivePart = (0xfe00 >> offset) & 1;		
		negativePart = (0x000f >> offset) & 1;		
		particleList[i].xCoordinate += positivePart - negativePart;
		particleList[i].xPositionChange += 
			(negativePart + positivePart) * -particleList[i].xPositionChange;

		offset = particleList[i].yPositionChange + 6;
		positivePart = (0xfe00 >> offset) & 1;
		negativePart = (0x000f >> offset) & 1;
		particleList[i].yCoordinate += positivePart - negativePart;
		particleList[i].yPositionChange += 
			(negativePart + positivePart) * -particleList[i].yPositionChange;

		AddParticle(particleList[i].yCoordinate, particleList[i].xCoordinate);
	}
}

//	Convert from index to coordinate
inline float Universe::xFieldIndexToCoordinate(int particleListNumber)
{
	return (particleList[particleListNumber].xCoordinate - ((float)DEFAULT_DIMENSION / 2.0f)) * 0.01f;
}

inline float Universe::yFieldIndexToCoordinate(int particleListNumber)
{
	return (particleList[particleListNumber].yCoordinate - ((float)DEFAULT_DIMENSION / 2.0f)) * 0.01f;
}

//	Convert from coordinate to index
inline size_t Universe::coordinateToFieldIndex(int coordinate)
{
	return size_t(coordinate) + (DEFAULT_DIMENSION / 2);
}