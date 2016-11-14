/*
 * musikplayer.cpp
 *
 *  Created on: 07.11.2016
 *      Author: Devin
 */

#include <vector>
#include <iostream>
#include <array>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;



double generiere_zufallszahl(){

				double z1= rand() %1000000+1;
				z1=z1/1000001;
				return z1;
 	}

int generiere_zufallszahl_bis_anzahl_der_Lieder(int anzahl_der_Lieder){

				int z1= rand() %anzahl_der_Lieder+1;
				return z1;
 	}


class Lied
{
	private:
	// Lied* pointer; // ?? Pointeraddresse fuer das Lied

	public:
	int index_Name;
	Lied(int i){
		index_Name = i;
	}



};




class Playlist
{
	private:
	int index_Anzahl;
	vector<Lied*> playlist; //Zeiger fuer Lied
	vector<int> wichtung;
	vector<int> reihenfolge;


	public:

	Playlist()
	{
		index_Anzahl=0;
	}








	void erstelle_Playlist(int platz)
	{
		playlist.reserve(platz);
		index_Anzahl=platz;
		for(int i=0; i<platz; i++){
			playlist[i] = new Lied(i);
			wichtung[i] = 0;
			reihenfolge[i] = i;
		}
	};

	void generiere_Playlist()
	{
		double zufallszahl[index_Anzahl];

		for(int i=0; i<index_Anzahl;i++)
		{
			zufallszahl[i]= generiere_zufallszahl()*(wichtung[i]+1);
		}
		double max_zufallszahl = 0;
		int max_index;
		for(int i=0; i<index_Anzahl;i++)
		{

			for(int j=0; j<index_Anzahl;j++)
					{
						if (zufallszahl[j]>max_zufallszahl) {
							max_index = j;
							max_zufallszahl = zufallszahl[j];
						}
					}
			reihenfolge[index_Anzahl-1-i] = max_index;
			zufallszahl[max_index] = 0;
			max_zufallszahl=0;
		}

	};

	void next(vector<double> rank){
		for(int i=0; i<sizeof(playlist)-1;i++)
		{
			//Anhand von einer Zufallszahl und der Wichtung wird errechnet, ob ein Lied uebersprungen wird
			if((rank[i]*generiere_zufallszahl_bis_anzahl_der_Lieder(sizeof(playlist)-1))<=0.5)
			{
				wichtung[i]++;
			}
		}


	}


	/*
	void add_lied(Playlist &List, Lied lied, int index) //index von 0 bis n
	{
		if(index<List.index_Anzahl)
		{
			if(List.playlist[index]==NULL)
			{

			List.playlist[index]=&lied;

			}
		}
		else
		{
			cout<< "Fehler beim einfuegen eines Wertes !"<< endl;
		}
	}
*/
};


class Musikspieler
{
	private:

	Playlist playlist;
	vector<double> like_Rank;


	public:

	Musikspieler()
	{
		like_Rank.reserve(10);
		for(int i=0;i<sizeof(like_Rank)-1;i++)
		{
			like_Rank[i]=0;
		}
	};

		void stop();

		void play()
		 {
			playlist.generiere_Playlist();
			for(int i=0;i<1000000;i++)
			{
				playlist.next(like_Rank);
				playlist.generiere_Playlist();
			}


		 };

		void get_Like_Rank(vector<double> Rank)
		{
			for(int i=0;i<sizeof(playlist)-1;i++)
			{
				//%Fehler% "Quit (expect signal SIGINT when the program is resumed)"

				like_Rank[i]=Rank[i];
			}
		}

};


class Benutzer
{
		public:

	Musikspieler M;
	int anzahl_der_Lieder;
	vector<double> like_Rank;




	public:


	Benutzer()
	{
		anzahl_der_Lieder=10; //Skalierung

		ifstream Benutzer_text;
		Benutzer_text.open("Ergebnisse_Benutzer.txt",ios_base::in | ios_base::out | ios_base::trunc);
		if (!Benutzer_text)
		{
			cerr<<"Fehler beim oeffnen von Ergebnisse_Benutzer";
		}

		like_Rank.reserve(anzahl_der_Lieder);
				for(int i=0;i<sizeof(like_Rank)-1;i++)
				{
					like_Rank[i]=1;
				};

	}

	virtual void rang_bestimmen()
	{

	};

	void stop()
	{
		M.stop();
	};

	void start()
	{
		M.get_Like_Rank(like_Rank);
		M.play();
		//Weiter ab hier
	};



};

class Rang_Benutzer:Benutzer
{
public:

	Rang_Benutzer()
	{
		ifstream  Rang_Benutzer_text;
				Rang_Benutzer_text.open("Ergebnisse_Rang_Benutzer.txt",ios_base::in | ios_base::out | ios_base::trunc);
				if (!Rang_Benutzer_text)
				{
					cerr<<"Fehler beim oeffnen von Rang_Ergebnisse_Benutzer";
				}
				like_Rank.reserve(anzahl_der_Lieder);
								for(int i=0;i<sizeof(like_Rank)-1;i++)
								{
									like_Rank[i]=0;
								};
	}

	void rang_bestimmen()
	{
		// erstelle like_Rank fuer die praeferierung der Lieder fuer den Benutzer
						int  zufallszahl=-1;;
						for(double i=1/anzahl_der_Lieder;i<=anzahl_der_Lieder;i+=1/anzahl_der_Lieder)
						{

							while(zufallszahl!=0)
							{
								zufallszahl=like_Rank[generiere_zufallszahl_bis_anzahl_der_Lieder(anzahl_der_Lieder)];
							}

							like_Rank[zufallszahl]=i;
						};
	}
	void start()
				{
					M.get_Like_Rank(like_Rank);
					M.play();
					//Weiter ab hier
				}
};

class AllvsOne_Benutzer:Benutzer
{
public:

	AllvsOne_Benutzer()
		{
			ifstream  AllvsOne_Benutzer_text;
			AllvsOne_Benutzer_text.open("Ergebnisse_Rang_Benutzer.txt",ios_base::in | ios_base::out | ios_base::trunc);
					if (!AllvsOne_Benutzer_text)
					{
						cerr<<"Fehler beim oeffnen von Rang_Ergebnisse_Benutzer";
					}
					like_Rank.reserve(anzahl_der_Lieder);
									for(int i=0;i<sizeof(like_Rank)-1;i++)
									{
										like_Rank[i]=0;
									};
		}
	void rang_bestimmen()
	{
		//Lied Nr.4 wird nie uebersprungen,Rest wird immer
		like_Rank[3]=1;
	}

	void start()
				{
					M.get_Like_Rank(like_Rank);
					M.play();
					//Weiter ab hier
				}
};

class Gleichwarscheinlich_Benutzer:Benutzer
{
public:
	Gleichwarscheinlich_Benutzer()
{
	ifstream  Gleichwarscheinlich_Benutzer_text;
	Gleichwarscheinlich_Benutzer_text.open("Ergebnisse_Gleichwarscheinlich_Benutzer.txt",ios_base::in | ios_base::out | ios_base::trunc);
			if (!Gleichwarscheinlich_Benutzer_text)
			{
				cerr<<"Fehler beim oeffnen von Gleichwarscheinlich_Ergebnisse_Benutzer";
			}

			like_Rank.reserve(anzahl_der_Lieder);
							for(int i=0;i<sizeof(like_Rank)-1;i++)
							{
								like_Rank[i]=0;
							};
}


	void rang_bestimmen()
	{
		for(int i=0;i<sizeof(like_Rank)-1;i++)
		{
			like_Rank[i]=0.1;
		};
	}
	void start()
				{
					M.get_Like_Rank(like_Rank);
					M.play();
					//Weiter ab hier
				}
	};

int main(){
	srand(time(NULL));




	Benutzer b1;
	b1.start();
	//--------
	Rang_Benutzer b2;
	b2.start();
	//---------
	AllvsOne_Benutzer b3;
	b3.start();
	//--------------
	Gleichwarscheinlich_Benutzer b4;
	b4.start();
	//---------



}



