#pragma once
constexpr auto DEFAULT_DIMENSION = 256;
constexpr auto DEFAULT_NUMBER_OF_WIREPOINTS = 6;

class Field
{
	int (*field)[DEFAULT_DIMENSION];

	struct WirePoint
	{
		int xCoordinate;
		int yCoordinate;
	};

	WirePoint* wirePointList;

public:
	Field();
	~Field();

	void AddWirePoint(int, int);
	void RemoveWirePoint(int, int);
	void UpdateWirePointState();
	float xFieldIndexToCoordinate(int);
	float yFieldIndexToCoordinate(int);
	size_t coordinateToFieldIndex(int);
};

Field::Field()
{
	// Create field array and wirePoints
	field = new int[DEFAULT_DIMENSION][DEFAULT_DIMENSION]();
	wirePointList = new WirePoint[DEFAULT_NUMBER_OF_WIREPOINTS]();
	
	// Add wirePoints
	wirePointList[0].yCoordinate = coordinateToFieldIndex(0), 
		wirePointList[0].xCoordinate = coordinateToFieldIndex(-2);
	wirePointList[1].yCoordinate = coordinateToFieldIndex(0), 
		wirePointList[1].xCoordinate = coordinateToFieldIndex(0);
	wirePointList[2].yCoordinate = coordinateToFieldIndex(0), 
		wirePointList[2].xCoordinate = coordinateToFieldIndex(2);
	wirePointList[3].yCoordinate = coordinateToFieldIndex(2),
		wirePointList[3].xCoordinate = coordinateToFieldIndex(-2);
	wirePointList[4].yCoordinate = coordinateToFieldIndex(2),
		wirePointList[4].xCoordinate = coordinateToFieldIndex(0);
	wirePointList[5].yCoordinate = coordinateToFieldIndex(2),
		wirePointList[5].xCoordinate = coordinateToFieldIndex(2);
}

Field::~Field()
{
	delete[] field;
	delete[] wirePointList;
}

inline void Field::AddWirePoint(int yCoordinate, int xCoordinate)
{
	//convert coordinate value to index value
}

inline void Field::RemoveWirePoint(int yCoordinate, int xCoordinate)
{
}

inline void Field::UpdateWirePointState()
{
	for (size_t i = 0; i < DEFAULT_NUMBER_OF_WIREPOINTS; ++i)
	{

	}
}

//	Convert from index to coordinate
inline float Field::xFieldIndexToCoordinate(int wirePointListNumber)
{
	return (wirePointList[wirePointListNumber].xCoordinate - ((float)DEFAULT_DIMENSION / 2.0f)) * 0.01f;
}

inline float Field::yFieldIndexToCoordinate(int wirePointListNumber)
{
	return (wirePointList[wirePointListNumber].yCoordinate - ((float)DEFAULT_DIMENSION / 2.0f)) * 0.01f;
}

//	Convert from coordinate to index
inline size_t Field::coordinateToFieldIndex(int coordinate)
{
	return size_t(coordinate) + (DEFAULT_DIMENSION / 2);
}
