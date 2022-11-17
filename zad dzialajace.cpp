/* 
  Prosz� dopisa� kod, doda� nowe pliki, tak aby program si� wykonywa�, a wynik jego dzia�ania by� taki sam, jak podany na ko�cu tego pliku.
 Zadanie opiera si� na znanej ju� Wam tre�ci (mo�na korzysta� ze �r�de� lab3), lecz tym razem mamy klasy, konstruktory, destruktory, klasy i funkcje zaprzyja�nione.
 Klasa MapPoint (pliki MapPoint.h, MapPoint.cpp) reprezentuje punkt na mapie sk�adaj�cy si� z nazwy (mo�e by� typu string), d�ugo�ci (longitude) i szeroko�ci (latitude) geograficznej. S� to prywatne sk�adowe klasy.
 
 Konstruktory i destruktory (dawne construct i clear) tworz� i usuwaj� punkt.
 Konstruktor posiada r�ne wersje.
  Pierwsza przyjmuje wsp�rz�dne w postaci dodatniej (unsigned) oraz strony �wiata w postaci char ('E', 'W' dla d�ugo�ci i 'N', 'S' dla szeroko�ci).
  Druga przyjmuje dodatnie i ujemne warto�ci wsp�rz�dnych i na ich podstawie wnioskujemy strony �wiata. Odpowiednio zgodnie z uk�adem wsp�rz�dnych dla d�ugo�ci ujemnych mamy W, a dla szeroko�ci ujemnych mamy S.
  UWAGA! Oznacze� znakowych p�kul nie przechowujemy, tak jak w zadaniu, kt�re ju� robili�my. Po prostu w okre�lonych przypadkach w pierwszym konstruktorze zmieniamy znak.
  Bezparametrowa ustawia punkt na (0,0) i nazw� na "Punkt".
 
 Funkcja sk�adowa movePoint zmienia wsp�rzedne punktu, przesuwaj�c go o warto�ci podane w argumentach funkcji. Prosz� pami�ta� o ew. zmianach stron �wiata po przesuni�ciu.
Funkcja skladowa closestFrom pobiera 3 argumenty. Pierwszy argument jest punktem referencyjnym. Z dw�ch kolejnych wybiera ten,kt�ry jest najbli�ej punktu referencyjnego. Funkcja wykorzystuje angularDistance.
 
Funkcja zaprzyja�niona inTheMiddle powinna tworzy� nowy punkt na mapie o zadanej nazwie i po�o�eniu, kt�re jest �redni� arytmetyczn� z po�o�e� podanych punkt�w czyli x = (x1 + x2)/2 itp. Prosz� uwa�a� w przypadku r�nych p�kul.
Klasa MapDist (pliki MapDist.h, MapDist.cpp) reprezentuje odleg�o�� pomi�dzy dwoma punktami. Odleg�o�� wzd�u� po�udnik�w lub r�wnole�nik�w nale�y obliczy� po prostu odejmuj�c od siebie wsp�rz�dne punkt�w ko�cowego i pocz�tkowego (konstruktor dzia�a podobnie jak funkcja distance).
Funkcja angularDistance oblicza pierwiastek z sumy kwadrat�w odleg�o�ci wzgl�dem po�udnik�w i r�wnole�nik�w, czyli sqrt(delta_x*delta_x + delta_y*delta_y).
Funkcja obliczaj�ca pierwiastek nazywa si�: sqrt(double) i znajduje si� w bibliotece "cmath".
Za brak prywatnych danych b�d� obni�ane punkty. Mo�na zaprzyja�ni� klasy.
Prosz� zadba� o dobre zarz�dzanie pami�ci�.
Pliku main.cpp, nie wolno modyfikowa�.
*/

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
  // Tu wywo�uj� si� destruktory
  delete nyc;
  delete porto;
}
/** Wynik dzia�ania programu:
./main
Wspolrzedne dla Krakow: 19.9383E, 50.0614N
Wspolrzedne dla Nowy Jork: 74.0059W, 40.7127N
Wspolrzedne dla Sydney: 151.102E, 33.454S
Wspolrzedne dla Porto: 41.1621E, 8.62195N
*** Po przesunieciu ***
Wspolrzedne dla Porto: 45.2855E, 17.365S
*** Po przesunieciu ***
Wspolrzedne dla Porto: 45.2855W, 17.365N
Odleglosci miedzy NYC i Sydney: 
Roznica dlugosci: 225.108
Roznica szerokosci: 74.1667
Odleglosc: 237.011
Blizej Krakowa jest Nowy Jork
Wspolrzedne dla Kenia: 38.5481E, 3.62935N
*** Czyszczenie ***
Usuwanie Nowy Jork
Usuwanie Porto
Usuwanie Kenia
Usuwanie Sydney
Usuwanie Krakow
*/
