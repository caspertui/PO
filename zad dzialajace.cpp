/* 
  Proszê dopisaæ kod, dodaæ nowe pliki, tak aby program siê wykonywa³, a wynik jego dzia³ania by³ taki sam, jak podany na koñcu tego pliku.
 Zadanie opiera siê na znanej ju¿ Wam treœci (mo¿na korzystaæ ze Ÿróde³ lab3), lecz tym razem mamy klasy, konstruktory, destruktory, klasy i funkcje zaprzyjaŸnione.
 Klasa MapPoint (pliki MapPoint.h, MapPoint.cpp) reprezentuje punkt na mapie sk³adaj¹cy siê z nazwy (mo¿e byæ typu string), d³ugoœci (longitude) i szerokoœci (latitude) geograficznej. S¹ to prywatne sk³adowe klasy.
 
 Konstruktory i destruktory (dawne construct i clear) tworz¹ i usuwaj¹ punkt.
 Konstruktor posiada ró¿ne wersje.
  Pierwsza przyjmuje wspó³rzêdne w postaci dodatniej (unsigned) oraz strony œwiata w postaci char ('E', 'W' dla d³ugoœci i 'N', 'S' dla szerokoœci).
  Druga przyjmuje dodatnie i ujemne wartoœci wspórzêdnych i na ich podstawie wnioskujemy strony œwiata. Odpowiednio zgodnie z uk³adem wspó³rzêdnych dla d³ugoœci ujemnych mamy W, a dla szerokoœci ujemnych mamy S.
  UWAGA! Oznaczeñ znakowych pó³kul nie przechowujemy, tak jak w zadaniu, które ju¿ robiliœmy. Po prostu w okreœlonych przypadkach w pierwszym konstruktorze zmieniamy znak.
  Bezparametrowa ustawia punkt na (0,0) i nazwê na "Punkt".
 
 Funkcja sk³adowa movePoint zmienia wspó³rzedne punktu, przesuwaj¹c go o wartoœci podane w argumentach funkcji. Proszê pamiêtaæ o ew. zmianach stron œwiata po przesuniêciu.
Funkcja skladowa closestFrom pobiera 3 argumenty. Pierwszy argument jest punktem referencyjnym. Z dwóch kolejnych wybiera ten,który jest najbli¿ej punktu referencyjnego. Funkcja wykorzystuje angularDistance.
 
Funkcja zaprzyjaŸniona inTheMiddle powinna tworzyæ nowy punkt na mapie o zadanej nazwie i po³o¿eniu, które jest œredni¹ arytmetyczn¹ z po³o¿eñ podanych punktów czyli x = (x1 + x2)/2 itp. Proszê uwa¿aæ w przypadku ró¿nych pó³kul.
Klasa MapDist (pliki MapDist.h, MapDist.cpp) reprezentuje odleg³oœæ pomiêdzy dwoma punktami. Odleg³oœæ wzd³u¿ po³udników lub równole¿ników nale¿y obliczyæ po prostu odejmuj¹c od siebie wspó³rzêdne punktów koñcowego i pocz¹tkowego (konstruktor dzia³a podobnie jak funkcja distance).
Funkcja angularDistance oblicza pierwiastek z sumy kwadratów odleg³oœci wzglêdem po³udników i równole¿ników, czyli sqrt(delta_x*delta_x + delta_y*delta_y).
Funkcja obliczaj¹ca pierwiastek nazywa siê: sqrt(double) i znajduje siê w bibliotece "cmath".
Za brak prywatnych danych bêd¹ obni¿ane punkty. Mo¿na zaprzyjaŸniæ klasy.
Proszê zadbaæ o dobre zarz¹dzanie pamiêci¹.
Pliku main.cpp, nie wolno modyfikowaæ.
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
  // Tu wywo³uj¹ siê destruktory
  delete nyc;
  delete porto;
}
/** Wynik dzia³ania programu:
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
