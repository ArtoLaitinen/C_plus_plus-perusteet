/*
Arto Laitinen

Hotellihuoneen varausjärjestelmä:
-järjestelmässä on lisäominaisuutena mahdollisuus muokata varausta tai perua se kokonaan

*/


//otetaan kirjastot käyttöön
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;



//asetetaan huoneiden minimi ja maksimimäärä vakioiksi, oikeasti huoneita voi olla vain 300 mutta asetaan maksimiksi 301, jotta on helpompi pelata taulukoiden indeksien kanssa
const int Max_huoneet = 301;
const int Min_huoneet = 40;

//asetetaan myös huoneiden hinnat per yö vakioiksi
const int Hinta_1hh = 100;
const int Hinta_2hh = 150;

//alustetaan structi johon kaikki varauksen tiedot tallennetaan
struct Varaus {
	int huonetyyppi = 0;
	int oiden_maara = 0;
	int huoneen_numero = 0;
	int varausnumero = 0;
	int alennus = 0;
	int hinta = 0;
	string varaajan_nimi;
};
//tehdään kaikkien funktioiden prototyypit
int arvonta(int, int);
void menu();
int int_kysyminen(int, int);
bool huoneen_tarkistus(int, bool[]);
string nimen_kysyminen();
void varauksen_tiedot(int, Varaus[]);



int main() {
	//otetaan ääkköset käyttöön
	setlocale(LC_ALL, "Finnish");

	//"aloitetaan" random numero generaattori
	srand(time(0));

	//luodaan varaukset niminen taulukko johon kaikki varaustiedot tallennetaan
	Varaus varaukset[Max_huoneet];

	//luodaan taulukko, jonka avulla pidetään kirjaa onko huone varattu vai ei
	bool onko_varattu[Max_huoneet] = {};

	//esitellään ja alustetaan muuttujat
	int toiminto=0, valinta=0;
	int huoneiden_lkm=0, lkm_1hh=0, lkm_2hh=0, vapaana_1hh=0, vapaana_2hh=0;
	bool lippu = true, ok = true;
	int tehdyt_varaukset = 0;
	int min_int=0, max_int=0;
	string merkki;
	string muokkaus_nimi;
	int muokkaus_varaus=0, muokkaus_numero=0;

	//käydään ensin arpomassa huoneiden määrä arvonta funktiossa, jonka jälkeen tarkistetaan onko luku parillinen ja jos ei ole niin käydään arpomassa uusi luku
		do {
			huoneiden_lkm = arvonta(Min_huoneet, Max_huoneet);
		} while (huoneiden_lkm % 2 != 0);

	//asetetaan sitten yhden ja kahden hengen huoneiden määrä ja samalla se kuinka monta kumpaakin huonetyyppiä on vapaana
		lkm_1hh = huoneiden_lkm / 2;
		lkm_2hh = lkm_1hh;
		vapaana_1hh = lkm_1hh;
		vapaana_2hh = lkm_2hh;

		do {
			//tulostetaan menu
			menu();

			//asetetaan minimin arvoksi 1 ja maksimiksi 3, koska käyttäjän syöttämän luvun täytyy olla tältä väliltä
			min_int = 1, max_int = 3;

			//kysytään sitten käyttäjältä mitä tämä haluaa tehdä
			toiminto = int_kysyminen(min_int, max_int);
		

			//tehdään se toiminto, jonka käyttäjä syöttää
			switch (toiminto) {
			case 1:
				//tarkistetaan onko huoneita vapaana
				if (vapaana_1hh + vapaana_2hh == 0) {
					cout << endl << "Kaikki huoneet on varattu!" << endl<<endl<<endl;
					break;
				}

				//lisätään tehtyihin varauksiin 1
				tehdyt_varaukset++;

				cout << endl << endl << endl << endl;
				cout << "Yhden hengen huoneita on vapaana " << vapaana_1hh << " ja kahden hengen huoneita " << vapaana_2hh << endl<<endl;
				
				cout << "Yhden hengen huone maksaa "<<Hinta_1hh<<" euroa/yö ja kahden hengen huone " <<Hinta_2hh<< " euroa/yö" << endl << endl;
				
				
				cout << "Monenko hengen huoneen haluat varata?(Syötä numero 1-2)" << endl;
				
				//asetetaan minimi ja maksimi arvot
				min_int = 1, max_int = 2;

				cin.ignore(80, '\n');
				//pyydetään sitten käyttäjää syöttämään huonetyyppi
				varaukset[tehdyt_varaukset].huonetyyppi = int_kysyminen(min_int, max_int);

				//tarkistetaan onko käyttäjän valitsemaa huonetyyppiä vapaana
				if (vapaana_1hh == 0 && varaukset[tehdyt_varaukset].huonetyyppi == 1 ) {
					cout << endl << "Kaikki 1hh on varattu!" << endl << endl << endl;
					tehdyt_varaukset--;
					break;
				}

				if (vapaana_2hh == 0 && varaukset[tehdyt_varaukset].huonetyyppi == 2) {
					cout << endl << "Kaikki 2hh on varattu!" << endl << endl << endl;
					tehdyt_varaukset--;
					break;
				}

				
				cout <<endl<< "Kuinka moneksi yöksi haluat varata huoneen(max 365 yötä)? " << endl;

				//asetetaan minimi ja maksimi arvot
				min_int = 1, max_int = 365;

				cin.ignore(80, '\n');
                //kysytään käyttäjältä öiden määrä
				varaukset[tehdyt_varaukset].oiden_maara= int_kysyminen(min_int, max_int);

				//jos valitun huonetyypin huoneista on vapaana vain alle puolet arvotaan numero. muussa tapauksessa kysytään käyttäjältä haluaako tämä valita sen itse
				if (varaukset[tehdyt_varaukset].huonetyyppi == 1 && vapaana_1hh >lkm_1hh/2 || varaukset[tehdyt_varaukset].huonetyyppi == 2 && vapaana_2hh > lkm_2hh/2) {
					cout << endl << "Haluatko valita huoneen numeron itse(1=kyllä, 0=en)?" << endl;

					//asetataan minimi ja maksimi
					min_int = 0, max_int = 1;

					cin.ignore(80, '\n');
					//kysytään toiminto
					valinta = int_kysyminen(min_int, max_int);

					//jos käyttäjä haluaa itse valita numeron kysytään sitä häneltä
					if (valinta == 1) {
						cout << endl << "Valitse huoneen numero väliltä ";
						if (varaukset[tehdyt_varaukset].huonetyyppi == 1) {  //kerrotaan käyttäjälle väli jolla 1hh on jos tämä on varaamassa sellaisen ja asetetaan samalla minimi ja maksimi
							cout << "1-" << lkm_1hh << endl;
							min_int = 1, max_int = lkm_1hh;
						}

						else {
							cout << lkm_1hh + 1 << "-" << huoneiden_lkm << endl;  //kerrotaan sama jos on valinnut 2hh ja asetetaan minimi ja maksimi
							min_int = lkm_1hh + 1, max_int = huoneiden_lkm;
						}


						//kysytään huoneen numeroa niin kauan kunnes käyttäjä syöttää huoneen jota ei ole varattu
						do {
							cin.ignore(80, '\n');
							lippu = false;
							varaukset[tehdyt_varaukset].huoneen_numero = int_kysyminen(min_int, max_int);

							ok = huoneen_tarkistus(varaukset[tehdyt_varaukset].huoneen_numero, onko_varattu); //käydään tarkistamassa onko huone vapaana

							if (ok == true) {
								lippu = true;
								cout << endl << "Valitsemasi huone on jo varattu! Syötä jokin toinen huoneen numero!" << endl;
							}
						} while (lippu);

					}
				}

				/*käydään arpomassa käyttäjälle huone jos hän ei halunnut sitä itse valita.
				 asetetaan minimi ja maksimi sen mukaan minkä tyyppinen huone on kyseessä ja samalla vähennetään yksi sen tyypin vapaana olevista huoneista*/
				if (valinta == 0 || varaukset[tehdyt_varaukset].huonetyyppi == 1 && vapaana_1hh <= lkm_1hh/2 || varaukset[tehdyt_varaukset].huonetyyppi == 2 && vapaana_2hh <= lkm_2hh/2) {
					if (varaukset[tehdyt_varaukset].huonetyyppi == 1) {  
						min_int = 1, max_int = lkm_1hh;
					}

					else {  
						min_int = lkm_1hh + 1, max_int = huoneiden_lkm; 
					}

					//arvotaan sitten huoneen numero niin monta kertaa kunnes tulee vapaana oleva huone
					do {
						lippu = false;
						varaukset[tehdyt_varaukset].huoneen_numero = arvonta(min_int, max_int);

						ok = huoneen_tarkistus(varaukset[tehdyt_varaukset].huoneen_numero, onko_varattu); //käydään tarkistamassa onko huone vapaana

						if (ok == true) {
							lippu = true;
						}

					} while (lippu);
				}
				
				//vähennetään valitun huonetyypin vapaista huoneista 1
				if (varaukset[tehdyt_varaukset].huonetyyppi == 1) {
					vapaana_1hh--;
				}
				else vapaana_2hh--;


				//arvotaan sitten käyttäjälle varausnumero ja asetetaan sitä varten minimi ja maksimi
				min_int = 10000, max_int = 99999;

				do {
					lippu = false;
					varaukset[tehdyt_varaukset].varausnumero = arvonta(min_int, max_int);

					//tarkistetaan sitten onko varausnumero jo käytössä
					for (int i = 1; i < tehdyt_varaukset; i++) {
						if (varaukset[tehdyt_varaukset].varausnumero == varaukset[i].varausnumero)
							lippu = true;
					}
				
				} while (lippu);

				//kysytään varaajan nimi
				cout << endl << "Anna varaajan nimi:" << endl;
				varaukset[tehdyt_varaukset].varaajan_nimi = nimen_kysyminen();

				//arvotaan alennus
				min_int = 0, max_int = 2;
				varaukset[tehdyt_varaukset].alennus = arvonta(min_int, max_int);
				
				//tulostetaan lasku
				cout << endl<<endl<<endl<<endl<<"Varauksesi tiedot:"<<endl;
				varauksen_tiedot(tehdyt_varaukset, varaukset);

				cout << endl << "Syötä jokin merkki ja paina sen jälkeen enter, kun olet valmis" << endl;
				cin >> merkki;
				
				cout << endl << endl << endl << endl<<endl<<endl;

				break;

			case 2:
				if (tehdyt_varaukset == 0) {
					cout << endl << "Yhtään varausta ei ole tehty!"<<endl<<endl << endl << endl;
					break;
				}
					cout << endl << endl << endl << endl;

			    //etsitään ne varukset joissa on käyttäjän syöttämä vaarajan nimi
						lippu = false;
						cout << "Anna nimi, jolla varaus on tehty:" << endl;
						muokkaus_nimi = nimen_kysyminen();

						for (int i = 1; i <= tehdyt_varaukset; i++) {
							if (muokkaus_nimi == varaukset[i].varaajan_nimi) {
								lippu = true;
								cout << endl << "Varausnumero " << varaukset[i].varausnumero << ": " << varaukset[i].huonetyyppi << "hh varattu " << varaukset[i].oiden_maara << " yöksi"<<endl<<endl;
							}
						}
						if (lippu == false) {
							cout << endl << "Syöttämällänne nimellä ei löytynyt varauksia!" << endl<<endl<<endl;
							break;
						}
					
					//kysytään käyttäjältä mitä hänen varauksistaan tämä haluaa muokata
					cout << "Syötä se varauksen varausnumero jota haluat muokata tai tarkastella:" << endl;
					do {
						lippu = false;
						ok = false;

						min_int = 10000, max_int = 99999;
						muokkaus_numero = int_kysyminen(min_int, max_int);

						for (int i = 1; i <= tehdyt_varaukset; i++) {
							if (muokkaus_nimi == varaukset[i].varaajan_nimi && muokkaus_numero==varaukset[i].varausnumero) {
								ok = true;
								muokkaus_varaus = i;
							}
						}
						if (ok == false) {
							lippu = true;
							cout << endl << "Syötä jokin varausnumeroistasi!" << endl;
						}
					} while (lippu);

					cout << endl << "Varauksesi:" << endl;
					varauksen_tiedot(muokkaus_varaus, varaukset);
					
					//kysytään käyttäjältä mitä hän haluaa tehdä varauksensa kanssa
					min_int = 1, max_int = 4;

					cin.ignore(80, '\n');
					cout << endl << "Mitä haluat tehdä(1=peruuttaa varauksen  2=muuttaa öiden määrää  3=muuttaa varaajan nimeä  4=halusin vain tarkastella varausta)?" << endl;
					valinta = int_kysyminen(min_int, max_int);

					//perutaan varaus
					if (valinta == 1) {
						//muutetaan vapaana olevien huoneiden määrää
						if (varaukset[muokkaus_varaus].huonetyyppi == 1) {
							vapaana_1hh++;
						}
						else {
							vapaana_2hh++;
						}

						//laitetaan varattu huone vapaaksi
						onko_varattu[varaukset[muokkaus_varaus].huoneen_numero] = false;

						//siirretään kaikki varauksia ja vähennetään tehdyistä varauksista 1
						for (int i = muokkaus_varaus+1; i <= tehdyt_varaukset; i++) {
							varaukset[i-1] = varaukset[i];
						}

						tehdyt_varaukset--;
						cout << endl << "Varauksesi on nyt peruttu!" << endl << endl << endl;
						cin.ignore(80, '\n');
					}
					//vaihdetaan öiden määrä
					if (valinta == 2) {
						cout << endl << "Anna uusi öiden määrä (max 365 yötä)? " << endl;

						//asetetaan minimi ja maksimi arvot
						min_int = 1, max_int = 365;

						cin.ignore(80, '\n');
						//kysytään käyttäjältä öiden määrä
						varaukset[muokkaus_varaus].oiden_maara = int_kysyminen(min_int, max_int);

						cout << endl << "Uusi varauksesi:" << endl;
						varauksen_tiedot(muokkaus_varaus, varaukset);
						cout << endl << "Syötä jokin merkki ja paina sen jälkeen enter, kun olet valmis" << endl;
						cin >> merkki;
						cout << endl << endl << endl;
					}
					//vaihdetaan varaajan nimi
					if (valinta == 3) {
						cout << endl << "Anna uusi varaajan nimi:" << endl;
						varaukset[muokkaus_varaus].varaajan_nimi = nimen_kysyminen();
						
						cout << endl << "Uusi varauksesi:" << endl;
						varauksen_tiedot(muokkaus_varaus, varaukset);
						cout << endl << "Syötä jokin merkki ja paina sen jälkeen enter, kun olet valmis" << endl;
						cin >> merkki;
						cout << endl << endl << endl;
					}

					else cout << endl << endl << endl << endl;

				break;

			}


		} while (toiminto != 3);

	return 0;
}



int arvonta(int min, int max) {
	//alustetaan muuttuja
	int num = 0;
	
	//arvotaan luku minimin ja maksimin väliltä
	num = rand() % (max - min + 1) + min;

	//palautetaan arvottu luku
	return num;
}

void menu() {
	cout << "Tervetuloa!" << endl << endl;
	cout << "Mitä haluaisit tehdä? (Syötä numero 1-3)" << endl;
	cout << "1: Tee varaus" << endl;
	cout << "2: Muokkaa tai tarkastele varausta" << endl;
	cout << "3: Lopeta" << endl << endl;
}



int int_kysyminen(int min, int max) {
	int luku=0;
	bool virhe = false;

	//tarkistetaan ettei käyttäjä syötä jotakin muuta kuin numeroa
	do {
		virhe = false;
		cin >> luku;

		if (cin.fail()|| luku > max || luku < min) {
			cout << "Virhe! Syötä luku, joka on väliltä "<<min<<"-"<<max<<"!"<< endl;
			virhe = true;
			cin.clear();
			cin.ignore(80, '\n');

		}
	} while (virhe);

	return luku;
}


bool huoneen_tarkistus(int numero, bool tila[]) {
	bool varattu = false;

	// tarkistetaan onko huone vapaana
	varattu = tila[numero];

	//jos huone ei ole varattu, asetetaan se varatuksi
	if (varattu == false)
		tila[numero] = true;

	return varattu;
}

string nimen_kysyminen() {
	string nimi;
	int pituus=0;

	cin.ignore(80, '\n');
	cin.clear();
	//käyttäjä syöttää nimen
	getline(cin, nimi);

	//vaihdetaan kaikki nimen kirjaimet pieniksi tallentamista varten
	pituus = nimi.length();
	for (int i = 0; i <= pituus; i++) {
		nimi[i] = tolower(nimi[i]);
	}

	return nimi;
}

string nimi_oikeaksi(string nimi) {
	int pituus = nimi.length();
	
	//muutetaan nimi oikeaksi eli ensimmäinen kirjain isoksi jne.
	for (int i = 0; i <= pituus; i++) {
		nimi[0] = toupper(nimi[0]);
		if (nimi[i] == ' ') {
			nimi[i + 1] = toupper(nimi[i + 1]);
		}
		if (nimi[i] == '-') {
			nimi[i + 1] = toupper(nimi[i + 1]);
		}
	}
	return nimi;
}

void varauksen_tiedot(int varauksen_numero, Varaus tiedot[]) {
	string temp_nimi;

	//käydään ensin muuttamassa nimi oikeaksi
	temp_nimi = nimi_oikeaksi(tiedot[varauksen_numero].varaajan_nimi);

	cout << endl << "Varaajan nimi: " << temp_nimi << endl;
	cout << "Varausnumero: " << tiedot[varauksen_numero].varausnumero << endl;
	cout << "Huoneen numero: " << tiedot[varauksen_numero].huoneen_numero << endl;
	cout << "Huonetyyppi: " << tiedot[varauksen_numero].huonetyyppi <<"hh"<< endl;
	cout << "Öiden lukumäärä: " << tiedot[varauksen_numero].oiden_maara << endl;
	cout << "Saamasi alennus: " << tiedot[varauksen_numero].alennus *10 <<"%"<< endl;
	
	//lasketaan huoneen hinta
	if (tiedot[varauksen_numero].huonetyyppi == 1) {
		tiedot[varauksen_numero].hinta = tiedot[varauksen_numero].oiden_maara * Hinta_1hh - tiedot[varauksen_numero].oiden_maara * Hinta_1hh * (0.1 * tiedot[varauksen_numero].alennus);
	}
	else tiedot[varauksen_numero].hinta = tiedot[varauksen_numero].oiden_maara * Hinta_2hh - tiedot[varauksen_numero].oiden_maara * Hinta_2hh * (0.1 * tiedot[varauksen_numero].alennus);

	cout << "Hinta: " << tiedot[varauksen_numero].hinta << " euroa" << endl;
}

