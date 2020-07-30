#include <Adafruit_NeoPixel.h>


//#define PIN        5
//#define NUMPIXELS 100
#define PIN         D2
#define NUMPIXELS 195


int FARBEROT = 50;
int FARBEBLAU = 250;
int FARBEGRUEN =50;
int Modus =40;
int Warte = 0;
int Vor = 2;
int Hinten = 0;
int Bassfilter = 2;
int Randomwert = 240;
short  nfarben_m6 =3;
bool Debugmodus = false;
bool submodus = true;
bool Startecounter = false;
int potenz = 0;
int num1 = 1;
String Taste = " ";







int Bass = 0;


short Zwischenspeicher[200];
double zwischenrot = 0;
double zwischenblau = 0;
double zwischengruen = 0;



int groessterwert = 0;


short einzelnrot[NUMPIXELS];
short einzelnblau[NUMPIXELS];
short einzelngruen[NUMPIXELS];
short arraygruen[200];
short arrayrot[200];
short arrayblau[200];
double GenauePosition[200];
short Position[200];
short Buffer[200];
double Geschwindigkeit[200];
short Ram1[10];
short Ram2[10];
int Signal = 0;
int Signallange = 0;
int Tastenmodus = 0;
int Wert = 0;
int Buchstabe = 0;
int Zeit = 0;
bool zweiterbuchstabe = false;
int Zweiterbuchstabe = 0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{

	Serial.begin(74880);
	Serial.println("Programm gestartet");
  pixels.begin();

	Position[0] = 0;
	Buffer[0] = 0;
	arraygruen[0] = 250;
	Position[1] = 74;
	Buffer[1] = 0;
	arrayblau[1] = 250;
	Einschlagberechnen();
	while (arraygruen[0] != 0)
	{
		Einschlagberechnen();
	}

}
void loop()
{


	if (Serial.available() != 0)
	{
		aktualisierewerte();
  }
	unsigned long time = 0;
	time = millis();
	//Serial.print("Time: ");

	switch (Modus)
	{
	case 0: Modus0(); break;
	case 1: Modus1(); break;
	case 2: Modus2(); break;
	case 3: Modus3(); break;
	case 4: Modus4(); break;
	case 5: Modus5(); break;
	case 6: Modus6(); break;
	case 7: Modus7(); break;
	case 8: Modus8(); break;
	case 9: Modus9(); break;
	case 10: Modus10(); break;
	case 11: Modus11(); break;
	case 12: Modus12(); break;
	case 13: Modus13(); break;
	case 14: Modus14(); break;

	case 15: Modus15(); break;
	case 16: Modus16(); break;
	case 18: Modus18(); break;
	case 19: Modus19(); break;
	case 20: Modus20(); break;
  case 21: Modus21(); break;
  case 22: Modus22(); break;
  case 23: Modus23(); break;
  case 24: Modus24(); break;
  case 25: Modus25(); break;
  case 26: Modus26(); break;
  case 27: Modus27(); break;
  case 28: Modus28(); break;
  case 29: Modus29(); break;
  case 30: Modus30(); break;
  case 31: Modus31(); break;
  case 32: Modus32(); break;
  case 40: Modus40(); break;
  case 100: Modus100(); break;
  case 101: Modus101(); break;
  case 102: Modus102(); break;
  case 103: Modus103(); break;
	case 200: Modus200(); break;
	case 201: LEDARRAYReset(); break;
	case 202: ZeigeZwischenwerte();
	default:
		Serial.println("Wartemodus");
		delay(1000);
		break;
	}
}
void Modus0()
{
  Lichtersofort(FARBEROT, FARBEBLAU, FARBEGRUEN);
}
void Modus1()
{
  Lichter(FARBEROT, FARBEBLAU, FARBEGRUEN, Warte,0,200);
}
void Modus2()
{
	Lichter(FARBEROT, FARBEBLAU, FARBEGRUEN, Warte, 0, 200);
	Lichter(0, 0, 0, Warte, 0, 200);
}
void Modus3()
{
  while (Modus == 3)
  {
    if (Serial.available() != 0)
    {
      aktualisierewerte();
    }
    Lichtersofort(FARBEROT, FARBEBLAU, FARBEGRUEN);
    delay(Warte);
    Lichtersofort(0, 0, 0);
    delay(Warte);
  }
}
void Modus4()
{
	Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 100);
	for (int i = 0; i < 100; i++)
	{
		Lichtersofort(zwischenrot*i, zwischenblau*i, zwischengruen*i);
		delay(Warte);
	}
	for (int i = 100; i != 1; i--)
	{
		Lichtersofort(zwischenrot*i, zwischenblau*i, zwischengruen*i);
		delay(Warte);
	}
}

void Modus5()
{
  Lichthinzufuegen(0, FARBEROT, FARBEBLAU, FARBEGRUEN);
 Streifen(true);
}
void Modus6()
{
	for (int a = 1; a < nfarben_m6 + 1; a++)
	{
		Position[a] = (NUMPIXELS / nfarben_m6) * a;
	}
	for (int i = 0; i < nfarben_m6; i++)
	{
		Zwischenspeicher[i] = random(NUMPIXELS);
	}
	for (int i = 0; i < nfarben_m6; i++)
	{
		einzelnrot[i] = random(Randomwert);
		einzelnblau[i] = random(Randomwert);
		einzelngruen[i] = random(Randomwert);
	}
	while (Modus == 6)
	{
		for (int i = 0; i < NUMPIXELS; i++)
		{
			for (int e = 0; e < nfarben_m6; e++)
			{
				if (Zwischenspeicher[e] == i)
				{
					Zwischenspeicher[e] = random(NUMPIXELS);
					for (int b = 0; b < nfarben_m6; b++)
					{
						einzelnrot[b] = random(Randomwert);
						einzelnblau[b] = random(Randomwert);
						einzelngruen[b] = random(Randomwert);
					}
				}
			}
			for (int a = 0; a != nfarben_m6; a++)
			{

				pixels.setPixelColor(Position[a], pixels.Color(einzelnrot[a], einzelnblau[a], einzelngruen[a]));
			}
			pixels.show();
			delay(Warte);
			for (int e = 0; e < nfarben_m6; e++)
			{
				Position[e]++;
				if (Position[e] == NUMPIXELS)
				{
					Position[e] = 0;
				}
			}
			if (Serial.available() != 0)
			{
				aktualisierewerte();
			}
		}
	}
}
void Modus7()
{
	while (Modus == 7)
	{
		Hinten = random(Randomwert);
		Vor = random(Randomwert);
		int a = random(NUMPIXELS);
		einzelnrot[a] = random(Randomwert);
		einzelnblau[a] = random(Randomwert);
		einzelngruen[a] = random(Randomwert);
		Streifen(true);
		if (Serial.available() != 0)
		{
			aktualisierewerte();
			if (Modus != 7)
			{
				break;
			}
		}


	}
}
void Modus8()
{
	while (Modus == 8)
	{
		for (int i = 0; i < Bassfilter; i++)
		{
			Bass = Lesenalogpin(0) ;
			if (Bass >= groessterwert)
			{
				groessterwert = Bass;
			}
		}	
		Bass = groessterwert;
		groessterwert = 0;
		if (Bass >= 255)
		{
			Lichtersofort(0, 0, 250);
		}
		if (Bass > 400)
		{
			Lichtersofort(250, 0, Bass);
		}
		if (Bass > 600)
		{
			Lichtersofort(0, 250, 0);
		}
		if (Bass < 250)
		{
			Lichtersofort(Bass, Bass, Bass);
		}
		if (Serial.available() != 0)
		{
			aktualisierewerte();
		}
		delay(0);
	}
}
void Modus9()
{
	Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 200);
	while (Modus == 9)
	{
		for (int i = 0; i < Bassfilter; i++)
		{
			Bass = Lesenalogpin(0);
			if (Bass >= groessterwert)
			{
				groessterwert = Bass;
			}
		}
		Bass = groessterwert;
		groessterwert = 0;
		Lichtersofort(Bass*zwischenrot, Bass*zwischenblau, Bass*zwischengruen);
		if (Serial.available() != 0)
		{
			aktualisierewerte();
			Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 200);
		}
		delay(0);
	}
}
void Modus10()
{
	while (Modus == 10)
	{
		for (int i = 0; i < NUMPIXELS; i++)
		{
			if (i < NUMPIXELS / 2)
			{
				pixels.setPixelColor(i, pixels.Color(250, 0, 0));
			}
			else
			{
				pixels.setPixelColor(i, pixels.Color(0, 250, 0));
			}
		}
		pixels.show();
		delay(Warte);
		for (int i = 0; i < NUMPIXELS; i++)
		{
			if (i < NUMPIXELS / 2)
				pixels.setPixelColor(i, pixels.Color(0, 250, 0));
			else
				pixels.setPixelColor(i, pixels.Color(250, 0, 0));
		}
		pixels.show();
		delay(Warte);
		if (Serial.available() != 0)
		{
			aktualisierewerte();

		}
	}
 
}
void Modus11()
{

	zwischenblau = 0; zwischengruen = 0; zwischenrot = 0;
	while (Modus == 11)
	{
		if (Serial.available() != 0)
		{
			aktualisierewerte();
		}
		Zwischenspeicher[0] = random(3);
		Zwischenspeicher[1] = random(255);
		Zwischenspeicher[2] = random(2);
		if (Zwischenspeicher[2] == 0)
		{
			for (int i = 0; i < Zwischenspeicher[1]; i++)
			{
				switch (Zwischenspeicher[0])
				{
				case 0: zwischenblau++; if (zwischenblau > 250) zwischenblau = 250; break;
				case 1: zwischenrot++; if (zwischenrot > 250) zwischenrot = 250; break;
				case 2: zwischengruen++; if (zwischengruen > 250) zwischengruen= 250; break;
				default:
					break;
				}
				delay(Warte);
				Lichthinzufuegen(1, zwischenrot, zwischenblau, zwischengruen);
				Streifen(false);
			
				
			}
		}
		else
		{
			for (int i = 0; i < Zwischenspeicher[1]; i++)
			{

				switch (Zwischenspeicher[0])
				{
				case 0: zwischenblau--; if (zwischenblau < 0) zwischenblau = 0; break;
				case 1: zwischenrot--; if (zwischenrot < 0) zwischenrot = 0; break;
				case 2: zwischengruen--; if (zwischengruen < 0) zwischengruen = 0; break;
				default:
					break;
				}
				delay(Warte);
				Lichthinzufuegen(1, zwischenrot, zwischenblau, zwischengruen);
				Streifen(false);

			}
		}


	}
}



void Modus12()
{
	while (Modus == 12)
	{
		for (int i = 0; i < Bassfilter; i++)
		{
			Bass = Lesenalogpin(0);
			if (Bass >= groessterwert)
			{
				groessterwert = Bass;
			}
		}
		Bass = groessterwert;
		groessterwert = 0;
		for (int a = 0; a != NUMPIXELS; a++)
		{
			if (Bass > a)
			{
				pixels.setPixelColor(a, pixels.Color(FARBEROT, FARBEBLAU, FARBEGRUEN));
			}
			else
			{
				pixels.setPixelColor(a, pixels.Color(0, 0, 0));
			}
		}
		if (Serial.available() != 0)
		{
			aktualisierewerte();
		}
		delay(0);
		pixels.show();
	}

}
void Modus13()
{
	while (Modus == 13)
	{
	
		for (int i = 0; i < Bassfilter; i++)
		{
			Bass = Lesenalogpin(0);
			if (Bass >= groessterwert)
			{
				groessterwert = Bass;
			}
		}
		Bass = groessterwert;
		groessterwert = 0;
		zwischengruen = 200;
		zwischenrot = 0;
		for (int a = 0; a != NUMPIXELS; a++)
		{
			if (Bass > a)
			{
				if (a < NUMPIXELS/2)
				{
					zwischenrot = zwischenrot + 2;
				}
				else
				{
					zwischengruen = zwischengruen - 2;
				}
				pixels.setPixelColor(a, pixels.Color(zwischenrot, 0, zwischengruen));
			}
			else
			{
				pixels.setPixelColor(a, pixels.Color(0, 0, 0));
			}
		}
		pixels.show();
		delay(0);
		if (Serial.available() != 0)
		{
			aktualisierewerte();
		}

	}

}
void Modus14()
{
	Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN,NUMPIXELS);
	for (int i = 0; i < NUMPIXELS; i++)
	{
		Lichthinzufuegen(i, zwischenrot*i, zwischenblau*i, zwischengruen*i);
	}
	while (Modus == 14)
	{
		Streifen(true);
		if (Serial.available() != 0)
		{
			aktualisierewerte();
			Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, NUMPIXELS);
			for (int i = 0; i < NUMPIXELS; i++)
			{
				Lichthinzufuegen(i, zwischenrot*i, zwischenblau*i, zwischengruen*i);
			}
			
		}
	}
}

void Modus15()
{
	LEDARRAYReset();
	Errechnezwischenwerte(250, 250, 250, 66);
	for (int i = 0; i < 66; i++)
	{
		einzelnrot[i] = i *zwischenrot;
	}
	for (int i = 66; i < 132; i++)
	{
		einzelnrot[i] = einzelnrot[i-1] -zwischenrot;
		if (einzelnrot[i] <= 0)
			einzelnrot[i] = 0;
	}

	for (int i = 66; i < 132; i++)
	{
		einzelnblau[i] = (i-66) *zwischenblau;
	}
	for (int i = 132; i < 200; i++)
	{
		einzelnblau[i] = einzelnblau[i - 1] - zwischenblau;
		if (einzelnblau[i] <= 0)
			einzelnblau[i] = 0;
	}
	for (int i = 132; i < 200; i++)
	{
		einzelngruen[i] = (i - 132) *zwischenblau;
	}
	einzelngruen[0] = 250;
	for (int i = 1; i < 66; i++)
	{
		einzelngruen[i] = einzelngruen[i - 1]- zwischengruen;
		if (einzelngruen[i] <= 0)
			einzelngruen[i] = 0;
	}


 
  while (Modus == 15)
  {
	  Streifen(true);
    if (Serial.available() != 0)
    {
      aktualisierewerte();

    }
  }
}
void Modus16()
{
	zwischenblau = 0; zwischengruen = 0; zwischenrot = 0;
	while (Modus == 16)
	{
		if (Serial.available() != 0)
		{
			aktualisierewerte();
		}
		Zwischenspeicher[0] = random(3);
		Zwischenspeicher[1] = random(Randomwert);
		Zwischenspeicher[2] = random(2);
		if (Zwischenspeicher[2] == 0)
		{
			for (int i = 0; i < Zwischenspeicher[1]; i++)
			{
				switch (Zwischenspeicher[0])
				{
				case 0: zwischenblau++; if (zwischenblau > FARBEBLAU)  zwischenblau = FARBEBLAU; break;
				case 1: zwischenrot++; if (zwischenrot > FARBEROT) zwischenrot = FARBEROT; break;
				case 2: zwischengruen++; if (zwischengruen > FARBEGRUEN) zwischengruen = FARBEGRUEN; break;
				default:
					break;
				}
				Lichthinzufuegen(1, zwischenrot, zwischenblau, zwischengruen);
				Streifen(false);
			}
		}
		else
		{
			for (int i = 0; i < Zwischenspeicher[1]; i++)
			{

				switch (Zwischenspeicher[0])
				{
				case 0: zwischenblau--; if (zwischenblau < 0) zwischenblau = 0; break;
				case 1: zwischenrot--; if (zwischenrot < 0) zwischenrot = 0; break;
				case 2: zwischengruen--; if (zwischengruen < 0) zwischengruen = 0; break;
				default:
					break;
				}
				delay(Warte);
				Lichthinzufuegen(1, zwischenrot, zwischenblau, zwischengruen);
				Streifen(false);

			}
		}
	}
}
void Einschlagberechnen()
{
  for (int a = 0; a != nfarben_m6; a++)
  {
    if (arrayrot[a] > 0)
    {
      if (NUMPIXELS > Position[a] + Buffer[a])
      {
        if (arrayrot[a] > einzelnrot[Position[a] + Buffer[a]])
        {
          einzelnrot[Position[a] + Buffer[a]] = arrayrot[a];
        }
      }
      if (0 < Position[a] - Buffer[a])
      {
        if (arrayrot[a] > einzelnrot[Position[a] - Buffer[a]])
        {
          einzelnrot[Position[a] - Buffer[a]] = arrayrot[a];
        }
      }
      arrayrot[a]--;
    }


    if (arraygruen[a] > 0)
    {
      if (NUMPIXELS > Position[a] + Buffer[a])
      {
        if (arraygruen[a] > einzelngruen[Position[a] + Buffer[a]])
        {
          einzelngruen[Position[a] + Buffer[a]] = arraygruen[a];
        }
      }
      if (0 < Position[a] - Buffer[a])
      {
        if (arraygruen[a] > einzelngruen[Position[a] - Buffer[a]])
        {
          einzelngruen[Position[a] - Buffer[a]] = arraygruen[a];
        }
      }

      arraygruen[a]--;
    }

    if (arrayblau[a] > 0)
    {
      if (NUMPIXELS > Position[a] + Buffer[a])
      {
        if (arrayblau[a] > einzelnblau[Position[a] + Buffer[a]])
        {
          einzelnblau[Position[a] + Buffer[a]] = arrayblau[a];
        }
      }
      if (0 < Position[a] - Buffer[a])
      {
        if (arrayblau[a] > einzelnblau[Position[a] - Buffer[a]])
        {
          einzelnblau[Position[a] - Buffer[a]] = arrayblau[a];
        }

      }

      arrayblau[a]--;
    }
   
	if (Modus == 40)
	{
		if (Geschwindigkeit[a] == 0) Buffer[a]++;
		if (arrayblau[a] == 0 && arrayrot[a] == 0 && arraygruen[a] == 0)
		{
			Buffer[a] = 0;
		}
	}
	else
	{
		Buffer[a]++; delay(Warte);
		if (Buffer[a] > 200)
		{
			Buffer[a] = 0; 
		}
	}
  }

  for (int a = 0; a != NUMPIXELS; a++)
  {
    if (einzelnrot[a] >= 1)
    {
      einzelnrot[a] = einzelnrot[a] - 1;
    }
    if (einzelnblau[a] >= 1)
    {
      einzelnblau[a] = einzelnblau[a] - 1;
    }
    if (einzelngruen[a] >= 1)
    {
      einzelngruen[a] = einzelngruen[a] - 1;
    }
  }
 
  Arraylicht();
}
void Einschlagberechneneinmalig( int Berrechnearray)
{
	int a = Berrechnearray;
		if (arrayrot[a] > 0)
		{
			if (NUMPIXELS > Position[a] + Buffer[a])
			{
				if (arrayrot[a] > einzelnrot[Position[a] + Buffer[a]])
				{
					einzelnrot[Position[a] + Buffer[a]] = arrayrot[a];
				}
			}
			if (0 < Position[a] - Buffer[a])
			{
				if (arrayrot[a] > einzelnrot[Position[a] - Buffer[a]])
				{
					einzelnrot[Position[a] - Buffer[a]] = arrayrot[a];
				}
			}
			arrayrot[a]--;
		}


		if (arraygruen[a] > 0)
		{
			if (NUMPIXELS > Position[a] + Buffer[a])
			{
				if (arraygruen[a] > einzelngruen[Position[a] + Buffer[a]])
				{
					einzelngruen[Position[a] + Buffer[a]] = arraygruen[a];
				}
			}
			if (0 < Position[a] - Buffer[a])
			{
				if (arraygruen[a] > einzelngruen[Position[a] - Buffer[a]])
				{
					einzelngruen[Position[a] - Buffer[a]] = arraygruen[a];
				}
			}

			arraygruen[a]--;
		}

		if (arrayblau[a] > 0)
		{
			if (NUMPIXELS > Position[a] + Buffer[a])
			{
				if (arrayblau[a] > einzelnblau[Position[a] + Buffer[a]])
				{
					einzelnblau[Position[a] + Buffer[a]] = arrayblau[a];
				}
			}
			if (0 < Position[a] - Buffer[a])
			{
				if (arrayblau[a] > einzelnblau[Position[a] - Buffer[a]])
				{
					einzelnblau[Position[a] - Buffer[a]] = arrayblau[a];
				}

			}

			arrayblau[a]--;
		}

		if (Modus == 40)
		{
			if (Geschwindigkeit[a] == 0) Buffer[a]++;
			if (arrayblau[a] == 0 && arrayrot[a] == 0 && arraygruen[a] == 0)
			{
				Buffer[a] = 0;
			}
		}
		else
		{
			Buffer[a]++; delay(Warte);
			if (Buffer[a] > 200)
			{
				Buffer[a] = 0;
			}
		}
	

	for (int a = 0; a != NUMPIXELS; a++)
	{
		if (einzelnrot[a] >= 1)
		{
			einzelnrot[a] = einzelnrot[a] - 1;
		}
		if (einzelnblau[a] >= 1)
		{
			einzelnblau[a] = einzelnblau[a] - 1;
		}
		if (einzelngruen[a] >= 1)
		{
			einzelngruen[a] = einzelngruen[a] - 1;
		}
	}

	
}
void Modus18()
{
	Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 250);
 Position[0] = 50;
  Buffer[0] = 0;
  arraygruen[0] = 250;

  Einschlagberechnen();

  for (int a = 0; a != nfarben_m6; a++)
  {
	  Position[a] = random(0, NUMPIXELS);
	  Buffer[a] = 0;
	  switch (random(0, 3))
	  {
	  case 0: arrayrot[a] = random(Randomwert)*zwischenrot; break;
	  case 1: arraygruen[a] = random(Randomwert)*zwischengruen; break;
	  case 2: arrayblau[a] = random(Randomwert)*zwischenblau; break;
	  default: break;
	  }
  }
  while (Modus == 18)
  {
    Einschlagberechnen();
   for (int a = 0; a != nfarben_m6; a++)
    {
      if (arrayblau[a] <= 0 && arraygruen[a] <= 0 && arrayrot[a] <= 0  )
      {
        Buffer[a] = 0;
        Position[a] = random(0, NUMPIXELS);
        switch (random(0, 3))
        {
          case 0: arrayrot[a] = random(Randomwert)*zwischenrot; break;
          case 1: arraygruen[a] = random(Randomwert)*zwischengruen; break;
          case 2: arrayblau[a] = random(Randomwert)*zwischenblau; break;
          default:; break;

        }
      }
    }
    if (Serial.available() != 0)
    {
      aktualisierewerte();
	  Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 250);
    }
  }
}
void Modus19()
{
	Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 250);

	while (Modus == 19)
	{
		Einschlagberechnen();
		for (int a = 0; a != nfarben_m6; a++)
		{
			if (arrayblau[a] <= 0 && arraygruen[a] <= 0 && arrayrot[a] <= 0)
			{
				Buffer[a] = 0;
				Position[a] = random(0, 200);
				switch (random(0, 3))
				{
				case 0: arrayrot[a] = random(0, Lesenalogpin(0))*zwischenrot; break;
				case 1: arraygruen[a] = random(0, Lesenalogpin(0))*zwischengruen; break;
				case 2: arrayblau[a] = random(0, Lesenalogpin(0))*zwischenblau; break;
				default:; break;
				}
			}
		}
		if (Serial.available() != 0)
		{
			aktualisierewerte();
			Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 250);
		}
	}
}
void Modus20()
{
	Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 200);
	short Randomwert2 = 0;
	for (int a = 0; a < NUMPIXELS; a++)
	{
		Randomwert2 = random(Randomwert);
		Lichthinzufuegen(a, zwischenrot*Randomwert2, zwischenblau*Randomwert2, zwischengruen*Randomwert2);
	}
	while (Modus == 20)
	{

		for (int a = 0; a < NUMPIXELS; a++)
		{
			if (einzelnrot[a] <= 1 && einzelngruen[a] <= 1 && einzelnblau[a] <= 1)
			{
				Randomwert2 = random(Randomwert);
				Lichthinzufuegen(a, zwischenrot*Randomwert2, zwischenblau*Randomwert2, zwischengruen*Randomwert2);
			}
		}
		LedKetteMinus();
		Arraylicht();
		if (Serial.available() != 0)
		{
			aktualisierewerte();
			Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 200);
		}
		delay(Warte);
	}
}
void Modus21()
{
 
  if(Vor == 0)
  {
  Lichthinzufuegen(NUMPIXELS-1, FARBEROT, FARBEBLAU, FARBEGRUEN);
  Streifen(false);
  Lichthinzufuegen(NUMPIXELS-1, 0, 0, 0);
  Streifen(false);
  }
  else
  {
  Lichthinzufuegen(0, FARBEROT, FARBEBLAU, FARBEGRUEN);
  Streifen(false);
  Lichthinzufuegen(0, 0, 0, 0);
  Streifen(false);
  }
}
void Modus22()
{
 
  short Bass = Lesenalogpin(0);
  Lichthinzufuegen(0, Bass, Bass, Bass);
  Streifen(false);
}
void Modus23()
{
   short Bass = Lesenalogpin(0);
  Lichthinzufuegen(0, Bass, Bass, Bass);
  for (int i = 0; i < Vor; i++)
  {
    LedKetteplusverkleinern(false);
    Arraylicht();
    delay(Warte);
  }

    
}
void Modus24()
{
  Errechnezwischenwerte(FARBEROT,FARBEBLAU,FARBEGRUEN,NUMPIXELS);
  short Bass = 0;
  while (Modus == 24)
  {
  Bass = Lesenalogpin(0);
  Lichthinzufuegen(0, Bass*zwischenrot, Bass*zwischenblau, Bass*zwischengruen);
  Streifen(false);
  if (Serial.available() != 0)
  {
	  aktualisierewerte();
	  Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, NUMPIXELS);
  }
  }
  
}
void Modus25()
{
	Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, NUMPIXELS);
	short Bass = 0;
	while (Modus == 25)
	{
		Bass = Lesenalogpin(0);
		Lichthinzufuegen(0, Bass*zwischenrot, Bass*zwischenblau, Bass*zwischengruen);
		LedKetteplusverkleinern(false);
		Arraylicht();
		delay(Warte);
		if (Serial.available() != 0)
		{
			aktualisierewerte();
			Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, NUMPIXELS);
		}
	}
}
void Modus26()
{
	Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 200);
	short Randomwert = 0;
	while (Modus == 26)
	{
		for (int a = 0; a < NUMPIXELS; a++)
		{
			if (einzelnrot[a] <= 1 && einzelngruen[a] <= 1 && einzelnblau[a] <= 1)
			{
				Randomwert = random(Lesenalogpin(0));
				Lichthinzufuegen(a, zwischenrot*Randomwert, zwischenblau*Randomwert, zwischengruen*Randomwert);
			}
		}
		LedKetteMinus();
		Arraylicht();
	if (Serial.available() != 0)
		{
			aktualisierewerte();
			Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 200);
		}
		delay(Warte);
	}
}
void Modus27()
{
	Position[0] = 0;
	short Randomwert = 0;
	short Abstaende = NUMPIXELS / nfarben_m6;

	Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 200);
	while (Modus == 27)
	{

		Randomwert = random(Lesenalogpin(0));

			for (int a = 0; a < nfarben_m6; a++)
			{
				if (zwischenblau*Randomwert > einzelnblau[0])
				{
					Lichthinzufuegen(Position[0], zwischenrot*Randomwert, zwischenblau*Randomwert, zwischengruen*Randomwert);
				}
				Position[0] = Position[0] + Abstaende;
				if (Position[0] >= NUMPIXELS)
				{
					Position[0] = Position[0] - NUMPIXELS;
				}
				if (Position[0] > 196) Position[0] = 0;

			}
			Position[0] = Position[0] + Vor;
	


		LedKetteplusverkleinern(true);
		Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 200);
		Arraylicht();

		delay(Warte);
		if (Serial.available() != 0)
		{
			aktualisierewerte();
			Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 200);
			Abstaende = NUMPIXELS / nfarben_m6;
			if (nfarben_m6 == 1) Abstaende = 0;
		}
	}
}

void Modus28()
{
	short Random = 0;
	Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 200);
	short Abstand = NUMPIXELS / nfarben_m6;
	while (Modus == 28)
	{


		for (int i = 0; i < nfarben_m6; i++)
		{
			Random = random(Lesenalogpin(0));
			if (Random != 0)
			{
				Lichthinzufuegen(Abstand*i, zwischenrot*Random, zwischenblau*Random, zwischengruen*Random);
			}
		}
		LedKetteplusverkleinern(false);
		Arraylicht();
		delay(Warte);

		if (Serial.available() != 0)
		{
			aktualisierewerte();
			Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 200);
			Abstand = NUMPIXELS / nfarben_m6;
			
		}
	}
}
void Modus29()
{
	int bass;
	for (int i = 0; i < nfarben_m6; i++)
	{
		GenauePosition[i] = random(NUMPIXELS);
		Geschwindigkeit[i] = random(-3, 3);
		if (Geschwindigkeit[i] == 0)
		{
			if (random(0, 2) == 1)Geschwindigkeit[i] = 1;
			else Geschwindigkeit[i] = -1;
		}
		arrayrot[i] = random(250);
		arraygruen[i] = random(250);
		arrayblau[i] = random(250);

	}
	arrayrot[0] = 250;
	arraygruen[0] = 0;
	arrayblau[0] = 0;
	arrayrot[1] = 0;
	arraygruen[1] = 250;
	arrayblau[1] = 0;
	arrayrot[2] = 0;
	arraygruen[2] = 0;
	arrayblau[2] = 250;
	while (Modus == 29)
	{
		Programm(5000);
		for (int i = 0; i < nfarben_m6; i++)
		{
			einzelnblau[Position[i]] = 0;
			einzelngruen[Position[i]] = 0;
			einzelnrot[Position[i]] = 0;
		}
		bass = Lesenalogpin(0);
		for (int i = 0; i < nfarben_m6; i++)
		{
			Position[i] = (int)GenauePosition[i];

			GenauePosition[i] = ErrechneGenaueFarbposition(GenauePosition[i], Geschwindigkeit[i]);
			if (bass == 0)
			{
				Geschwindigkeit[i] = Geschwindigkeit[i] * 0.98;
			}
			else
			{
				if (Geschwindigkeit[i] < 0)
				{
					if (-(Geschwindigkeit[i]) < bass*0.003)
						Geschwindigkeit[i] = -((random(80, 120) / 50)*(bass*0.003));
				}
				else
				{
					if (Geschwindigkeit[i] < bass*0.003)
						Geschwindigkeit[i] = (random(80, 120) / 50) * (bass*0.003);
				}
			}


			Position[i] = (int)GenauePosition[i];
			if (einzelnblau[Position[i]] <= arrayblau[i])
			{
				einzelnblau[Position[i]] = arrayblau[i];
			}
			if (einzelngruen[Position[i]] <= arraygruen[i])
			{
				einzelngruen[Position[i]] = arraygruen[i];
			}
			if (einzelnrot[Position[i]] <= arrayrot[i])
			{
				einzelnrot[Position[i]] = arrayrot[i];
			}

			if (Position[i] == NUMPIXELS)
			{
				Position[i] = NUMPIXELS - 1; Geschwindigkeit[i] = -(Geschwindigkeit[i]);
			}

			if (Position[i] == 0)
			{
				Position[i] = 1; Geschwindigkeit[i] = -(Geschwindigkeit[i]);
			}
		}
		delay(Warte);
		Arraylicht();

		if (Serial.available() != 0)
		{
			aktualisierewerte();
			for (int i = 0; i < nfarben_m6; i++)
			{
				GenauePosition[i] = random(NUMPIXELS);
				Geschwindigkeit[i] = random(-3, 3);
				if (Geschwindigkeit[i] == 0)
				{
					if (random(0, 2) == 1)Geschwindigkeit[i] = 1;
					else Geschwindigkeit[i] = -1;
				}
				arrayrot[i] = random(250);
				arraygruen[i] = random(250);
				arrayblau[i] = random(250);

			}
		}

	}
	Serial.println("Modus beeendet");

}
void Modus30()
{
	int bass;
for (int i = 0; i < nfarben_m6; i++)
	{
		GenauePosition[i] = random(NUMPIXELS);
		Geschwindigkeit[i] = random(-3, 3);
		if (Geschwindigkeit[i] == 0)
		{
			if (random(0, 2) == 1)Geschwindigkeit[i] = 1;
			else Geschwindigkeit[i] = -1;
		}
		arrayrot[i] = random(250);
		arraygruen[i] = random(250);
		arrayblau[i] = random(250);
		while (Modus == 30)
		{
			//Programm(5000);
			LedKetteMinus();
			bass = Lesenalogpin(0);
			for (int i = 0; i < nfarben_m6; i++)
			{
				Position[i] = (int)GenauePosition[i];

				GenauePosition[i] = ErrechneGenaueFarbposition(GenauePosition[i], Geschwindigkeit[i]);
				if (bass == 0)
				{
					Geschwindigkeit[i] = Geschwindigkeit[i] * 0.98;
				}
				else
				{
					if (Geschwindigkeit[i] < 0)
					{
						if (-(Geschwindigkeit[i]) < bass*0.003)
						{
							Geschwindigkeit[i] = -((random(80, 120) / 50)*(bass*0.003));
							if (Geschwindigkeit[i] > 1) Geschwindigkeit[i] = 1;
						}
					}
					else
					{
						if (Geschwindigkeit[i] < bass*0.003)
						{
							Geschwindigkeit[i] = (random(80, 120) / 50) * (bass*0.003);
							if (Geschwindigkeit[i] < -1) Geschwindigkeit[i] = -1;
						}

					}
				}
				if (arraygruen[i] == 0 && arrayrot[i] == 0 && arrayblau[i] == 0 && bass >= 5)
				{
					switch (random(3))
					{
					case 0: arrayrot[i] = random(250); break;
					case 1: arraygruen[i] = random(250);	break;
					case 2: arrayblau[i] = random(250); break;


					default:
						break;
					}

					
					GenauePosition[i] = random(NUMPIXELS);
				}
				ArrayFarbeMinus(i);
				Position[i] = (int)GenauePosition[i];
				if (einzelnblau[Position[i]] == 0)
				{
					einzelnblau[Position[i]] = arrayblau[i];
				}
				else if(einzelnblau[Position[i]] < 2000)
				{
					einzelnblau[Position[i]] = (arrayblau[i] + einzelnblau[Position[i]]) ;
				}
				if (einzelngruen[Position[i]] == 0)
				{
					einzelngruen[Position[i]] = arraygruen[i];
				}
				else if(einzelngruen[Position[i]] < 2000)
				{
					einzelngruen[Position[i]] = (arraygruen[i] + einzelngruen[Position[i]]);
				}
				if (einzelnrot[Position[i]] == 0)
				{
					einzelnrot[Position[i]] = arrayrot[i];
				}
				else if(einzelnrot[Position[i]] < 2000)
				{
					einzelnrot[Position[i]] = (arrayrot[i] + einzelnrot[Position[i]]);
				}
				if (Position[i] == NUMPIXELS)
				{
					Position[i] = NUMPIXELS - 1; Geschwindigkeit[i] = -(Geschwindigkeit[i]);
				}

				if (Position[i] == 0)
				{
					Position[i] = 1; Geschwindigkeit[i] = -(Geschwindigkeit[i]);
				}
			}
			delay(Warte);
			Arraylicht();
			if (Serial.available() != 0)
			{
				aktualisierewerte();
			}
		}
	}
}
void Modus31()
{
	int bass;
	for (int i = 0; i < nfarben_m6; i++)
	{
		GenauePosition[i] = random(NUMPIXELS);
		Geschwindigkeit[i] = random(-3, 3);
		if (Geschwindigkeit[i] == 0)
		{
			if (random(0, 2) == 1)Geschwindigkeit[i] = 1;
			else Geschwindigkeit[i] = -1;
		}
		arrayrot[i] = random(250);
		arraygruen[i] = random(250);
		arrayblau[i] = random(250);
		while (Modus == 31)
		{
			//Programm(5000);
			LedKetteMinus();
			bass = Lesenalogpin(0);
			for (int i = 0; i < nfarben_m6; i++)
			{
				Position[i] = (int)GenauePosition[i];

				GenauePosition[i] = ErrechneGenaueFarbposition(GenauePosition[i], Geschwindigkeit[i]);
				if (bass == 0)
				{
					Geschwindigkeit[i] = Geschwindigkeit[i] * 0.98;
				}
				else
				{
					if (Geschwindigkeit[i] < 0)
					{
						if (-(Geschwindigkeit[i]) < bass*0.003)
							Geschwindigkeit[i] = -((random(80, 120) / 50)*(bass*0.003));
					}
					else
					{
						if (Geschwindigkeit[i] < bass*0.003)
							Geschwindigkeit[i] = (random(80, 120) / 50) * (bass*0.003);
					}
				}
				if (arraygruen[i] == 0 && arrayrot[i] == 0 && arrayblau[i] == 0 && bass >= 5)
				{
					switch (random(3))
					{
					case 0: arrayrot[i] = random(250); break;
					case 1: arraygruen[i] = random(250);	break;
					case 2: arrayblau[i] = random(250); break;


					default:
						break;
					}

					ArrayFarbeMinus(i);
					GenauePosition[i] = random(NUMPIXELS);
				}
				Position[i] = (int)GenauePosition[i];
				if (einzelnblau[Position[i]] == 0)
				{
					einzelnblau[Position[i]] = arrayblau[i];
				}
				else if (einzelnblau[Position[i]] < 250)
				{
					einzelnblau[Position[i]] = (arrayblau[i] + einzelnblau[Position[i]]);
				}
				if (einzelngruen[Position[i]] == 0)
				{
					einzelngruen[Position[i]] = arraygruen[i];
				}
				else if (einzelngruen[Position[i]] < 250)
				{
					einzelngruen[Position[i]] = (arraygruen[i] + einzelngruen[Position[i]]);
				}
				if (einzelnrot[Position[i]] == 0)
				{
					einzelnrot[Position[i]] = arrayrot[i];
				}
				else if (einzelnrot[Position[i]] < 250)
				{
					einzelnrot[Position[i]] = (arrayrot[i] + einzelnrot[Position[i]]);
				}
				if (Position[i] == NUMPIXELS)
				{
					Position[i] = NUMPIXELS - 1; Geschwindigkeit[i] = -(Geschwindigkeit[i]);
				}

				if (Position[i] == 0)
				{
					Position[i] = 1; Geschwindigkeit[i] = -(Geschwindigkeit[i]);
				}
			}
			delay(Warte);
			Arraylicht();
			if (Serial.available() != 0)
			{
				aktualisierewerte();
			}
		}
	}
}
void Modus32()
{
	ARRAYFARBENResest();
	Position[0] = 0;
	short Randomwert = 0;
	short Abstaende = NUMPIXELS / nfarben_m6;
	for (int i = 0; i < nfarben_m6; i++)
	{
		switch (random(3))
		{
		case 0: arrayrot[i] = 1; break;
		case 1: arraygruen[i] = 1; break;
		case 2: arrayblau[i] = 1; break;
		default:
			break;
		}
	}
	while (Modus == 32)
	{

		Randomwert = random(Lesenalogpin(0));

		for (int a = 0; a < nfarben_m6; a++)
		{
			Lichthinzufuegen(Position[0], (arrayrot[a]*Randomwert),arrayblau[a]*Randomwert, arraygruen[a]*Randomwert);
			Position[0] = Position[0] + Abstaende;
			if (Position[0] >= NUMPIXELS)
			{
				Position[0] = Position[0] - NUMPIXELS;
			}
			if (Position[0] > 196) Position[0] = 0;

		}
		Position[0] = Position[0] + Vor;



		LedKetteplusverkleinern(true);
		Arraylicht();

		delay(Warte);
		if (Serial.available() != 0)
		{
			aktualisierewerte();
			Abstaende = NUMPIXELS / nfarben_m6;
			if (nfarben_m6 == 1) Abstaende = 0;
		}
	}
}
void Modus40()
{
	Buffer[0] = 0;
	ARRAYFARBENResest();
	while (Modus == 40)
	{
		for (int i = 0; i < 5; i++)
		{
			arraygruen[i] = random(240);
			arrayrot[i] = random(240);
			arrayblau[i] = random(240);
			Geschwindigkeit[i] = random(1, 4);
			Position[i] = 0;
		}
		while (true)
		{

			for (int i = 0; i < nfarben_m6; i++)
			{

				GenauePosition[i] = ErrechneGenaueFarbposition(GenauePosition[i], Geschwindigkeit[i]);
				Position[i] = (int)GenauePosition[i];

				Arraylicht();
				
				for (int a = 0; a < nfarben_m6; a++)
				{
					if(Geschwindigkeit[a] != 0)
					pixels.setPixelColor(Position[a], arrayrot[a], arrayblau[a], arraygruen[a]);
				}
			

				Geschwindigkeit[i] = Geschwindigkeit[i] * 0.98;
				/*	Serial.print("Buffer");
					Serial.print(i);
					Serial.print(" ");
					Serial.print(Buffer[i]);
					Serial.print(" ");
					Serial.print("Geschwindigkeit");
					Serial.print(i);
					Serial.print(" ");

					Serial.println(Geschwindigkeit[i]);
					*/
					
				if (Geschwindigkeit[i] == 0)
				{
					Einschlagberechneneinmalig(i);
					if (Buffer[i] == 0)
					{
						Position[i] = 0;
						Geschwindigkeit[i] = Geschwindigkeit[i] = (random(10, 240) / 50);
						arraygruen[i] = random(240);
						arrayrot[i] = random(240);
						arrayblau[i] = random(240);
						GenauePosition[i] = 0;

					}
				}
				if (Geschwindigkeit[i] <= 0.05 && Buffer[i] == 0)
				{
					Buffer[i] = 1;
					Geschwindigkeit[i] = 0;
				}

			}
			pixels.show();
			if (Serial.available() != 0)
			{
				aktualisierewerte();
				break;
			}
	
			delay(Warte);
		}


	}
}
void ArrayFarbeMinus(int i)
{
	if (arraygruen[i] != 0) arraygruen[i]--;
	if (arrayrot[i] != 0) arrayrot[i]--;
	if (arrayblau[i] != 0) arrayblau[i]--;
}
void Modus100()
{
  Arraylicht();
}
void Modus101()
{
	for (int i = NUMPIXELS - 1; i != 0; i--)
	{
		einzelnrot[i] = einzelnrot[i ] - 1;
		einzelnblau[i] = einzelnblau[i] - 1;
		einzelngruen[i] = einzelngruen[i] - 1;
		if (einzelnrot[i] < 0) einzelnrot[i] = 0;
		if (einzelngruen[i] < 0) einzelngruen[i] = 0;
		if (einzelnblau[i] < 0) einzelnblau[i] = 0;
	}
	Arraylicht();
}
void Modus102()
{
	LedKetteVor(true);
	Modus = 100;
}
void Modus103()
{
	LedKetteHinten(true);
	Modus= 100;
}
void Modus200()
{
  for (int a = 0; a != NUMPIXELS; a++)
  {
    Serial.print("Aktueller Platz: ");
    Serial.println(a);
    Serial.print("Rot: ");
    Serial.println(einzelnrot[a]);
    Serial.print("Gruen: ");
    Serial.println(einzelngruen[a]);
    Serial.print("Blau: ");
    Serial.println(einzelnblau[a]);
	delay(0);
  }
  Modus = 100;
}
void ARRAYFARBENResest()
{
	for (int i= 0; i < NUMPIXELS; i++)
	{
		arrayblau[i] = 0;
		arrayrot[i] = 0;
		arraygruen[i] = 0;
	}
}
void LEDARRAYReset()
{
	for (int i = 0; i < NUMPIXELS; i++)
	{
		einzelnrot[i] = 0;
		einzelnblau[i] = 0;
		einzelngruen[i] = 0;
	}
}
void ZeigeZwischenwerte()
{
	for (int a = 0; a != NUMPIXELS; a++)
	{
		if(arrayrot[a] != 0 || arrayblau[a] != 0 ||arraygruen[a] != 0)
		{ 
		Serial.print("Aktueller Platz: ");
		Serial.println(a);
		Serial.print("Rot: ");
		Serial.println(arrayrot[a]);
		Serial.print("Gruen: ");
		Serial.println(arraygruen[a]);
		Serial.print("Blau: ");
		Serial.println(arrayblau[a]);
		delay(0);
		}
	}
	Modus = 100;
}
/*void Programm(int neuanfang)
{
	if (analogRead(0) >= 10)
	{
		if (Startecounter == false)
		{
			Zwischenspeicher[0] = 0;
			Startecounter = true;
		}
	}
	if (Startecounter)
	{

		if (millis() > Zeit + neuanfang)
		{
			Zeit = millis();
			switch (Zwischenspeicher[0])
			{
			case 0: FARBEBLAU--; if (FARBEBLAU <= 0) Zwischenspeicher[0] = 1; break;
			case 1: FARBEROT++; if (FARBEROT >= 250) Zwischenspeicher[0] = 2; break;
			case 2: FARBEGRUEN--; if (FARBEGRUEN <= 0) Zwischenspeicher[0] = 3; break;
			case 3: FARBEBLAU++; if (FARBEBLAU >= 250) Zwischenspeicher[0] = 4; break;
			case 4: FARBEROT--; if (FARBEROT <= 0) Zwischenspeicher[0] = 5; break;
			case 5: FARBEGRUEN++; if (FARBEGRUEN >= 250) Zwischenspeicher[0] = 0; break;
			default:
				break;
			}
		}
		Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 200);
	}
}*/
void Programm(int neuanfang)
{
	if (analogRead(0) >= 10)
	{
		if (Startecounter == false)
		{

			Startecounter = true;

		}
	}
	if (Startecounter)
	{
		
		if (millis() > Zeit + neuanfang)
		{
			Zeit = millis();
			if(nfarben_m6 < 199)
				nfarben_m6++;
			GenauePosition[nfarben_m6] = random(200);
			Geschwindigkeit[nfarben_m6] = random(-1, 1);
			if (Geschwindigkeit[nfarben_m6] == 0)
			{
				if (random(0, 2) == 1)Geschwindigkeit[nfarben_m6] = 1;
				else Geschwindigkeit[nfarben_m6] = -1;
			}
			arrayrot[nfarben_m6] = random(250);
			arraygruen[nfarben_m6] = random(250);
			arrayblau[nfarben_m6] = random(250);

		}
		//Errechnezwischenwerte(FARBEROT, FARBEBLAU, FARBEGRUEN, 200);
	}
}
void aktualisierewerte()
{
	if (submodus)
	{
		lesewertsub();
	}
	else
	{
		while (Serial.available() != 0)
		{
			if (zweiterbuchstabe)
			{
				Signalzuordnen();
				break;
			}
			Lesewert();
			if (Signal >= 58)
			{
				Signalzuordnen();
				break;
			}
			else
			{
				break;
			}
		}
	}
}
int Lesenalogpin(int ANALOGPIN)
{
	int wert = analogRead(ANALOGPIN)-5;
	if (wert <= 5) wert = 0;
   return wert;
}
void Lesewert()
{
  while (true)
  {

    Signal = Serial.read();
    if (Signal >= 58)
    {
      break;
    }
    else
    {
      Buffer[Signallange] = Signal;
      Signallange++;
    }
    if (Serial.available() == 0)
    {
      break;
    }
  }
}

void lesewertsub()
{
  //delay(2);
  Signal = Serial.read() - 48;
  //delay(4);
  Serial.print("ankommende zeichen:");
  Serial.println(Serial.available());
  Serial.print("gelesende zahl:");
  Serial.println(Signal);
  if (Signal == Serial.available())
  {
    Buchstabe = Serial.read();
	LeseZahlen();
    Signalzuordnen();
  }
  else
  {
  while (Serial.available() != 0)
    {
 Serial.println(Serial.read());
	  
    }
    delay(2);
    Serial.print("~");
    delay(2);
    }
}

void Bufferreset()
{
  if(Debugmodus)
  {
  Serial.println("Buffer:");
  }
  for (int i = 0; i < 10; i++)
  { 
    if(Debugmodus)
    {
    Serial.println(Buffer[i]);
    }
    Buffer[i] = 0;
  }
  
}
int Errechnewert()
{
  if(Debugmodus)
  {
  Serial.print("Signallaenge:");
  Serial.println(Signallange);
  }
  Wert = 0;
  int multi = 1;
  while (Signallange != 0)
  {
    if ((Buffer[Signallange - 1] - 48) != 0)
    {
      Wert += (Buffer[Signallange - 1] - 48) * multi;
    }
    Signallange--;
    multi = multi * 10;
  }
  if (Debugmodus == true)
  {
	  Serial.print("Buchstabe:");
	  Serial.println(Buchstabe);
    Serial.print("Wert:");
  Serial.println(Wert);
  }
  Bufferreset();
  return Wert;
}
void Signalzuordnen()
{
  if (submodus == false)
  {
    if (zweiterbuchstabe)
    {
      Buchstabe = Zweiterbuchstabe;
      zweiterbuchstabe = false;
      Signal = 0;
    }
    else
    {
      Buchstabe = Signal;
    }
    Lesewert();
    if (Signal >= 58)
    {
      zweiterbuchstabe = true;
      Zweiterbuchstabe = Signal;
    }
    Serial.print("Buchstabe wird zugeordnet:");
    Serial.println(Buchstabe);
  }
  Wertezuordnen(Buchstabe, Errechnewert());
}
void Wertezuordnen(int Buchstabe, int Wert)
{
	switch (Buchstabe)
	{
	case 83 : Synchron(); break;
	case 98: FARBEBLAU = Wert; break;
	case 99: CreativMode(Wert); break;
	case 102: Bassfilter = Wert; break;
	case 104: Hinten = Wert; break;
	case 103: FARBEGRUEN = Wert; break;
	case 109: Modus = Wert; break;
	case 110: nfarben_m6 = Wert; break;
	case 112: Randomwert = Wert; break;
	case 114: FARBEROT = Wert; break;
	case 118: Vor = Wert; break;
	case 119: Warte = Wert; break;
	default:
		break;
	}
}

void Synchron()
{
	Serial.print("BLAU"); Serial.print(FARBEBLAU);
	Serial.print("G"); Serial.print(FARBEGRUEN);
	Serial.print("R"); Serial.print(FARBEROT);
	Serial.print("M"); Serial.print(Modus);
	Serial.print("W"); Serial.print(Warte);
	Serial.print("V"); Serial.print(Vor);
	Serial.print("H"); Serial.print(Hinten);
	Serial.print("A"); Serial.print(nfarben_m6);
	Serial.print("F"); Serial.print(Bassfilter);

}
void Lichter(int Rot, int Blau, int Gruen, int Wartev, int Start, int Stop)
{
	for (int i = Start; i < Stop; i++)
	{
		pixels.setPixelColor(i, pixels.Color(Rot, Blau, Gruen));
		delay(Wartev);
		pixels.show();
		if (Serial.available() != 0)
		{

			int Temp_Modus = Modus;
			aktualisierewerte();

			Blau = FARBEBLAU;
			Gruen = FARBEGRUEN;
			Rot = FARBEROT;
			if (Temp_Modus != Modus)
			{
				break;
			}

		}

	}

}
void Lichtersofort(int Rot, int Blau, int Gruen)
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(Rot, Blau, Gruen));
  }
  pixels.show();
}
void Arraylicht()
{
	
	for (int i = 0; i < NUMPIXELS - 1; i++)
	{
		
			pixels.setPixelColor(i, einzelnrot[i], einzelnblau[i], einzelngruen[i]);
		
	}
	pixels.show();
	
}
void Lichthinzufuegen(int Position, int Rot, int Blau, int Gruen)
{
  einzelnrot[Position] = Rot;
  einzelnblau[Position] = Blau;
  einzelngruen[Position] = Gruen;
}
void LedKetteHinten(bool Schleife)
{
  zwischenrot = einzelnrot[0];
  zwischenblau = einzelnblau[0];
  zwischengruen = einzelngruen[0];
  for (int i = 1; i < NUMPIXELS; i++)
  {
    einzelnrot[i - 1] = einzelnrot[i];
    einzelnblau[i - 1] = einzelnblau[i];
    einzelngruen[i - 1] = einzelngruen[i];
  }
  if(Schleife)
  {
  einzelnrot[NUMPIXELS - 1] = zwischenrot;
  einzelnblau[NUMPIXELS - 1] = zwischenblau;
  einzelngruen[NUMPIXELS - 1] = zwischengruen;
  }
}
void LedKetteVor(bool Schleife)
{
  if(Schleife)
  {
  zwischenrot = einzelnrot[NUMPIXELS-1];
  zwischenblau = einzelnblau[NUMPIXELS - 1];
  zwischengruen = einzelngruen[NUMPIXELS - 1];
  }
  for (int i = NUMPIXELS - 1; i != 0 ; i--)
  {
    einzelnrot[i] = einzelnrot[i - 1];
    einzelnblau[i] = einzelnblau[i - 1];
    einzelngruen[i] = einzelngruen[i - 1];
  }
  if(Schleife)
  {
  einzelnrot[0] = zwischenrot;
  einzelnblau[0] = zwischenblau;
  einzelngruen[0] = zwischengruen;
  }
}
void LedKetteMinus()
{
	for (int i =0; i != NUMPIXELS; i++)
	{
		einzelnrot[i] = einzelnrot[i] - 1;
		einzelnblau[i] = einzelnblau[i] - 1;
		einzelngruen[i] = einzelngruen[i] - 1;
		if (einzelnrot[i] < 0) einzelnrot[i] = 0;
		if (einzelngruen[i] < 0) einzelngruen[i] = 0;
		if (einzelnblau[i] < 0) einzelnblau[i] = 0;
	}
}
void LedKetteplusverkleinern(bool Schleife)
{
	if (Schleife)
	{
		zwischenrot = einzelnrot[NUMPIXELS - 1];
		zwischenblau = einzelnblau[NUMPIXELS - 1];
		zwischengruen = einzelngruen[NUMPIXELS - 1];
	}
	for (int i = NUMPIXELS - 1; i != 0; i--)
	{
		einzelnrot[i] = einzelnrot[i - 1] - 1;
		einzelnblau[i] = einzelnblau[i - 1] - 1;
		einzelngruen[i] = einzelngruen[i - 1] - 1;
		if (einzelnrot[i] < 0) einzelnrot[i] = 0;
		if (einzelngruen[i] < 0) einzelngruen[i] = 0;
		if (einzelnblau[i] < 0) einzelnblau[i] = 0;
	}
	if (Schleife)
	{
		einzelnrot[0] = zwischenrot;
		einzelnblau[0] = zwischenblau;
		einzelngruen[0] = zwischengruen;
	}

}
void Streifen(bool Schleife)
{
	for (int i = 0; i < Vor; i++)
	{
		LedKetteVor(Schleife);
		Arraylicht();
	
		delay(Warte);
		if (Serial.available() != 0)
		{
			aktualisierewerte();
		}

	}
	for (int i = 0; i < Hinten; i++)
	{
		if (Serial.available() != 0)
		{
			aktualisierewerte();
		}
		LedKetteHinten(Schleife);
		Arraylicht();
		delay(Warte);
	}
}
int ErrechneFarbpositionen(int Position,int Geschwindigkeit)
{
	Position = Position + Geschwindigkeit;
	if (Position > NUMPIXELS) Position = NUMPIXELS;
	if (Position < 0) Position = 0;
	return Position;
}
double ErrechneGenaueFarbposition(double Position, double Geschwindigkeit)
{
	Position = Position + Geschwindigkeit;
	if (Position > NUMPIXELS) Position = NUMPIXELS;
	if (Position < 0) Position = 0;
	return Position;
}
double ErrechneGeschwindigkeit(double Geschwindigkeit, double Beschleunigung, int i)
{
	return Geschwindigkeit * Beschleunigung;
	
}
void Errechnezwischenwerte(double Rot,double Blau,double Gruen,double Schritte)
{  
  zwischenrot = Rot/Schritte;
   zwischenblau = Blau/Schritte;
   zwischengruen = Gruen/Schritte;
}
void CreativMode(int Wert)
{

	switch (Wert)
	{
	case 0: 
		delay(200);
		Serial.print("p");
		WarteaufSignal(); LeseZahlen(); Position[0] = Errechnewert(); 
		Serial.print("r");
		WarteaufSignal(); LeseZahlen(); zwischenrot = Errechnewert();
		Serial.print("b");
		WarteaufSignal(); LeseZahlen(); zwischenblau = Errechnewert();
		Serial.print("g");
		WarteaufSignal(); LeseZahlen(); zwischengruen = Errechnewert();
		Lichthinzufuegen(Position[0], zwischenrot, zwischenblau, zwischengruen);
	default:
		break;
	}
}
void WarteaufSignal()
{
	while (Serial.available() == 0)
	{
		delay(1);
	}
	delay(4);
}
void LeseZahlen()
{
	while (Serial.available() != 0)
	{
		Signal = Serial.read();
		Buffer[Signallange] = Signal;
		Signallange++;
	}
}
void werteveraendern(int Neuezahl)
{
	switch (Tastenmodus)
	{
	case 1: if (Neuezahl < 250) FARBEBLAU = Neuezahl; else FARBEBLAU = 250; break;
	case 2: if (Neuezahl < 250) FARBEGRUEN = Neuezahl; else FARBEGRUEN = 250; break;
	case 3: if (Neuezahl < 250)  FARBEROT = Neuezahl; else FARBEROT = 250; break;
	case 4: Modus = Neuezahl; break;
	case 5: if (Neuezahl > 2) Warte = Neuezahl; else Warte = 2; break;
	case 6: Vor = Neuezahl; break;
	case 7: Hinten = Neuezahl; break;
	case 8: if (Neuezahl < 40) nfarben_m6 = Neuezahl; else nfarben_m6 = 40; break;
	case 9: Randomwert = Neuezahl; break;
	default:
break;
	}
}
int ZahlenString(String Taste, int Zahl)
{

	int Wert = 0;
	String Zahlenstring;
	Zahlenstring = String(Zahl);
	if (Taste == "1" || Taste == "2" || Taste == "3" || Taste == "4" || Taste == "5" || Taste == "6" || Taste == "7" || Taste == "8" || Taste == "9" || Taste == "0")
	{
		Zahlenstring = Zahlenstring + Taste;
	}
	if (Taste == "loeschen")
	{
		if (Zahlenstring.length() != 0)
		{
			Serial.println("löschen");
			int num1 = Zahlenstring.length();
			Serial.println(num1);
			Zahlenstring.remove(num1 - 1);
			Serial.println(Zahlenstring);
		}
		else
		{
			Zahlenstring = "0";
		}
	}
	Wert = Zahlenstring.toInt();
	return Wert;
}
