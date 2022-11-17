
#include <iostream>
#include <cstring>
#include <cmath>

class MapPoint;
class point;
class MapDist;

class MapPoint
{
	private:
		char *name;
		double longtitude;
		double latitude;
		
	public:
	MapPoint();
    MapPoint(const char *name, double longitude, double latitude);
    MapPoint(const char *name, double longtitude, char longtitudeDirection, double latitude, char latitudeDirection);

    friend MapPoint inTheMiddle(MapPoint *p1, MapPoint *p2, const char *name);

    char *getName() const;
    double getLongtitude() const;
    double getLatitude() const;
    void print() const;
    void movePoint(double longitudeShift, double latitudeShift);
    MapPoint &closestFrom(MapPoint *p1, MapPoint *p2) const;

    ~MapPoint();
			
};

MapPoint inTheMiddle(MapPoint *p1, MapPoint *p2, const char *name);



class MapDist
{
private:
    double longtitudeDistance;
    double latitudeDistance;

public:
    MapDist(const MapPoint &p1, const MapPoint &p2);
    double getlongitude() const;
    double getlatitude() const;
    double angularDistance() const;

    friend bool operator<(const MapDist &ld, const MapDist &lr);
    friend bool operator>(const MapDist &ld, const MapDist &lr);
};

MapDist distance(const MapPoint &p1, const MapPoint &p2);


MapPoint::MapPoint(const char *name, double longtitude, double latitude)
    : longtitude(longtitude), latitude(latitude)
{
    int len = strlen(name);
    this->name = new char[len + 1]();
    strcpy(this->name, name);
};

MapPoint::MapPoint() : MapPoint("Punkt", 0, 0) {};

MapPoint::MapPoint(const char *name, double longtitude, char longtitudeDirection, double latitude, char latitudeDirection)
:MapPoint(name, longtitude, latitude)
{
	if (longtitudeDirection == 'W')
        this->longtitude *= -1;

    if (latitudeDirection == 'S')
        this->latitude *= -1;
};

double MapPoint::getLongtitude() const
{
    return this->longtitude;
};

double MapPoint::getLatitude() const
{
    return this->latitude;
};

char *MapPoint::getName() const
{
    return this->name;
};

void MapPoint::print() const
{
    char longtitudeDirection = this->longtitude > 0 ? 'E' : 'W';
    char latitudeDirection = this->latitude > 0 ? 'N' : 'S';

    std::cout << "Wspolrzedne dla " << this->name << ": "
              << fabs(this->longtitude) << longtitudeDirection << ", "
              << fabs(this->latitude) << latitudeDirection << std::endl;
};

void MapPoint::movePoint(double zmianadlugosci, double zmianaszerokosci)
{
    this->longtitude += zmianadlugosci;
    this->latitude += zmianaszerokosci;
};

MapPoint &MapPoint::closestFrom(MapPoint *p1, MapPoint *p2) const
{
    MapDist dist1 = distance(*this, *p1);
    MapDist dist2 = distance(*this, *p2);

    return dist1 < dist2 ? *p1 : *p2;
};

MapPoint::~MapPoint()
{
    if (this->name != NULL)
    {
        std::cout << "Usuwanie " << this->name << std::endl;
        delete[] this->name;
    }
};

MapPoint inTheMiddle(MapPoint *punkt1, MapPoint *punkt2, const char *name)
{
    return MapPoint(name, (punkt1->longtitude + punkt2->longtitude) / 2, (punkt1->latitude + punkt2->latitude) / 2);
};


///////////////////////////////////////////////////////////////////////////////


MapDist::MapDist(const MapPoint &p1, const MapPoint &p2)
{
    longtitudeDistance = fabs(p1.getLongtitude() - p2.getLongtitude());
    latitudeDistance = fabs(p1.getLatitude() - p2.getLatitude());
};

MapDist distance(const MapPoint &p1, const MapPoint &p2)
{
    MapDist result(p1, p2);
    return result;
};

double MapDist::getlongitude() const
{
    return this->longtitudeDistance;
};

double MapDist::getlatitude() const
{
    return this->latitudeDistance;
};

double MapDist::angularDistance() const
{
    return sqrt(pow(longtitudeDistance, 2) + pow(latitudeDistance, 2));
};

bool operator<(const MapDist &ld, const MapDist &rd)
{
    return ld.angularDistance() < rd.angularDistance();
};

bool operator>(const MapDist &ld, const MapDist &lr)
{
    return !(operator<(ld, lr));
};












int main()
{
  const double longitude = 19.938333;
  const double latitude = 50.061389;
  MapPoint krakow("Krakow", longitude, latitude); //kierunki E N
  krakow.print();
  MapPoint *nyc = new MapPoint("Nowy Jork", 74.0059, 'W', 40.7127, 'N');
  nyc->print();
  MapPoint sydney("Sydney", 151.102, -33.454); // kierunki E i S jak ujemna to S
  sydney.print();
  MapPoint *porto = new MapPoint("Porto", 41.162142, 8.621953); // kierunki E i N
  const MapPoint &portugalCity = *porto;
  portugalCity.print();

  const double longitudeShift = 4.1234;
  const double latitudeShift = -25.987;
  std::cout << "*** Po przesunieciu ***\n";
  porto->movePoint(longitudeShift, latitudeShift);
  portugalCity.print();
  std::cout << "*** Po przesunieciu ***\n";
  porto->movePoint(-90.5710, 34.7300);
  portugalCity.print();

  const MapDist d = distance(*nyc, sydney);
  const MapDist d1(*nyc, sydney); //to samo co distance
  std::cout << "Odleglosci miedzy NYC i Sydney: \nRoznica dlugosci: " << d1.getlongitude() << "\nRoznica szerokosci: " << d1.getlatitude() << "\nOdleglosc: " << d.angularDistance() << std::endl;

  const MapPoint &cl = krakow.closestFrom(nyc, &sydney);
  std::cout << "Blizej Krakowa jest " << cl.getName() << std::endl;

  MapPoint mp = inTheMiddle(nyc, &sydney, "Kenia");
  mp.print();

  std::cout << "*** Czyszczenie ***\n";
  // Tu wywo³uj¹ siê destruktory
  delete nyc;
  delete porto;
}
