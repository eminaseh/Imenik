#ifndef IMENIK_H
#define IMENIK_H

#include <iostream>
#include <string>
#include <vector>

/* Klasa Imenik predstavlja telefonski imenik. Svaki imenik ima atribut naziv.
   Klasa je implementirana kao dvostruko povezana lista, pri cemu cvorovi liste pored pokazivaca sadrze i atribut tipa Kontakt (struct),
   a to je struktura koja se sastoji od: naziva osobe/firme (tipa string), mobilni telefon (tipa string, u obliku "062123456") i fiksni telefon
   (tipa string, u obliku "033654321"). Moguce je da je u kontaktu upisan mobilni telefon, a fiksni nije (tj. fiksni je prazan string), ili obrnuto,
   ali je neophodno da je upisan bar jedan od njih, kao i naziv. Mobilni i fiksni telefon mogu sadrzavati samo cifre (u suprotnom se baca izuzetak).
   Elementi imenika se cuvaju u sortiranom poretku po nazivu osobe/firme.
   Omoguceno je dodavanje novog kontakta, brisanje postojeceg, promjena naziva osobe/firme kao i promjena broja(mobilnog ili fiksnog).
   Takodjer omogucena je pretraga po nazivu osobe/firme, pretraga po broju telefona kao i spajanje dva imenika u novi sortirani imenik.
*/


using namespace std;
class Imenik{

    struct Kontakt{
        string naziv;
        string mobilni;
        string fiksni;
        Kontakt(){}
        /*Funkcija jeLiBroj vraca true ukoliko je string broj ili prazan string jer je potrebno omoguciti da se moze unijeti samo mobitel ili samo fiksni telefon.*/
        bool jeLiBroj(const string &str) {
            return str.empty() || str.find_first_not_of("0123456789") == string::npos;
        }
        Kontakt(string naziv, string mobilni, string fiksni):
            naziv(naziv), mobilni(mobilni), fiksni(fiksni){
            if(naziv.empty())
                throw runtime_error("Kontakt mora imati naziv. ");

            if(mobilni.empty() && fiksni.empty())
                throw runtime_error("Kontakt mora imati kontakt telefon(mobilni, fiksni ili oba). ");

            if(!jeLiBroj(mobilni))
                throw runtime_error("Mobilni telefon sadrzi znakove koji nisu brojevi ");

            if(!jeLiBroj(fiksni))
                throw runtime_error("Fiksni telefon sadrzi znakove koji nisu brojevi ");

            }

    };

    struct Cvor{
    Kontakt kontakt;
    Cvor *prethodni;
    Cvor *sljedeci;
    Cvor(Kontakt kontakt = Kontakt(), Cvor *prethodni = nullptr, Cvor *sljedeci = nullptr):
        kontakt(kontakt), prethodni(prethodni), sljedeci(sljedeci) {}
    };


    string naziv_imenika;
    Cvor *head;
    Cvor *tail;

    void init();


    public:
    Imenik(){init();}
    Imenik(string naziv_imenika): naziv_imenika(naziv_imenika) { init();}
    Imenik(vector<Kontakt> kontakti,string naziv_imenika);

    void Sort();
    bool DaLiVecPostojiIme(string naziv_kontakta);
    void DodajKontakt(Kontakt kontakt);
    void Ispisi();
    void IzbrisiKontakt(string naziv_kontakta);
    void PromijeniNazivKontakta(string naziv_kontakta);
    void PromijeniTelefonKontakta(string naziv_kontakta);

    void PretraziPoNazivu(string naziv_kontakta);
    void PretraziPoBroju(string broj);

    string vratiNazivImenika() {return naziv_imenika;}

    /*Funkcija prima dva imenika. Imenici su vec sortirani. Zatim spaja imenike u novi sortirani imenik koji se sastoji od kontakata iz imenika a i b.
    Koristi pomocne pokazivace na cvorove, jedan za imenik a, drugi za imenik b kako bi prolazili kroz oba imenika i uporedjivali nazive kontakata.
    U novi imenik dodajemo kontakte poredane po alfabetskom poretku.
    Ako dva kontakta imaju isti naziv, isti mobilni i isti fiksni, u novi imenik dodajemo samo jedan od njih.
    Ako dva kontakta imaju isti naziv, a razlicite mobilne u imenik dodajemo oba kontakta pri cemu mijenjamo njihove nazive tako sto na kraj imena dodajemo
    i naziv imenika u kojem se nalaze.
    Ako dva kontakta imaju isti naziv, a razlicite fiksne telefone u imenik dodajemo oba kontakta pri cemu mijenjamo njihove nazive tako sto na kraj imena
    dodajemo i naziv imenika u kojem se nalaze.
    Ako dva kontakta imaju isti naziv, iste mobilne ali prvi ima fiksni a drugi nema u imenik dodajemo dodajemo prvi tj. onaj koji ima fiksni.
    Ako dva kontakta imaju isti naziv, iste mobilne ali drugi ima fiksni a prvi nema u imenik dodajemo dodajemo drugi tj. onaj koji ima fiksni.
    Ako dva kontakta imaju isti naziv, iste fiksne ali prvi ima mobilni a drugi nema u imenik dodajemo dodajemo prvi tj. onaj koji ima mobilni.
    Ako dva kontakta imaju isti naziv, iste fiksne ali drugi ima mobilni a prvi nema u imenik dodajemo dodajemo drugi tj. onaj koji ima mobilni.*/
    friend Imenik Spoji(Imenik& a, Imenik& b){

    string crtica = " - ";
    Cvor *cvor1 = a.head->sljedeci;
    Cvor *cvor2 = b.head->sljedeci;
    Imenik novi_imenik;

    while (cvor1 != a.tail || cvor2 != b.tail){
        if (cvor1 == a.tail){
            novi_imenik.DodajKontakt(cvor2->kontakt);
            cvor2 = cvor2->sljedeci;
        }
        else if (cvor2 == b.tail){
            novi_imenik.DodajKontakt(cvor1->kontakt);
            cvor1 = cvor1->sljedeci;
        }
        else{
            if (cvor2->kontakt.naziv < cvor1->kontakt.naziv){
                novi_imenik.DodajKontakt(cvor2->kontakt);
                cvor2 = cvor2->sljedeci;
            }
            else if(cvor1->kontakt.naziv < cvor2->kontakt.naziv){
                novi_imenik.DodajKontakt(cvor1->kontakt);
                cvor1 = cvor1->sljedeci;
            }

            else if(cvor2->kontakt.naziv == cvor1->kontakt.naziv) {
                    //kontakti identicni
                    if(cvor2->kontakt.mobilni == cvor1->kontakt.mobilni
                       && cvor2->kontakt.fiksni == cvor1->kontakt.fiksni){
                            novi_imenik.DodajKontakt(cvor1->kontakt);
                            cvor1 = cvor1->sljedeci;
                            cvor2 = cvor2->sljedeci;
                       }
                       //isto ime ali razlicit mobilni
                       else if(!(cvor2->kontakt.mobilni).empty() && !(cvor1->kontakt.mobilni).empty()
                               && cvor2->kontakt.mobilni != cvor1->kontakt.mobilni ){
                                cvor1->kontakt.naziv = cvor1->kontakt.naziv + crtica + a.naziv_imenika;
                                cvor2->kontakt.naziv = cvor2->kontakt.naziv + crtica + b.naziv_imenika;
                                novi_imenik.DodajKontakt(cvor1->kontakt);
                                novi_imenik.DodajKontakt(cvor2->kontakt);
                                cvor1 = cvor1->sljedeci;
                                cvor2 = cvor2->sljedeci;
                        }

                        //isto ime ali razliciti fiksni
                        else if(!(cvor2->kontakt.fiksni).empty() && !(cvor1->kontakt.fiksni).empty()
                               && cvor2->kontakt.fiksni != cvor1->kontakt.fiksni ){
                                cvor1->kontakt.naziv = cvor1->kontakt.naziv + crtica + a.naziv_imenika;
                                cvor2->kontakt.naziv = cvor2->kontakt.naziv + crtica + b.naziv_imenika;
                                novi_imenik.DodajKontakt(cvor1->kontakt);
                                novi_imenik.DodajKontakt(cvor2->kontakt);
                                cvor1 = cvor1->sljedeci;
                                cvor2 = cvor2->sljedeci;
                        }
                        //isti naziv, isti mobilni ali prvi ima fiksni a drugi nema
                        else if(!(cvor2->kontakt.mobilni).empty() && !(cvor1->kontakt.mobilni).empty()
                               && cvor2->kontakt.mobilni == cvor1->kontakt.mobilni
                               && !(cvor1->kontakt.fiksni).empty() && (cvor2->kontakt.fiksni).empty() ){
                                novi_imenik.DodajKontakt(cvor1->kontakt);
                                cvor1 = cvor1->sljedeci;
                                cvor2 = cvor2->sljedeci;
                        }
                        //isti naziv, isti mobilni ali prvi nema fiksni a drugi ima
                        else if(!(cvor2->kontakt.mobilni).empty() && !(cvor1->kontakt.mobilni).empty()
                               && cvor2->kontakt.mobilni == cvor1->kontakt.mobilni
                               && !(cvor2->kontakt.fiksni).empty() && (cvor1->kontakt.fiksni).empty() ){
                                novi_imenik.DodajKontakt(cvor2->kontakt);
                                cvor1 = cvor1->sljedeci;
                                cvor2 = cvor2->sljedeci;
                        }
                        //isti naziv, isti fiksni ali prvi ima mobilni a drugi nema
                        else if(!(cvor2->kontakt.fiksni).empty() && !(cvor1->kontakt.fiksni).empty()
                               && cvor2->kontakt.fiksni == cvor1->kontakt.fiksni
                               && !(cvor1->kontakt.mobilni).empty() && (cvor2->kontakt.mobilni).empty() ){
                                novi_imenik.DodajKontakt(cvor1->kontakt);
                                cvor1 = cvor1->sljedeci;
                                cvor2 = cvor2->sljedeci;
                        }
                        //isti naziv, isti fiksni ali prvi nema mobilni a drugi ima
                        else if(!(cvor2->kontakt.fiksni).empty() && !(cvor1->kontakt.fiksni).empty()
                               && cvor2->kontakt.fiksni == cvor1->kontakt.fiksni
                               && !(cvor2->kontakt.mobilni).empty() && (cvor1->kontakt.mobilni).empty()){
                                novi_imenik.DodajKontakt(cvor2->kontakt);
                                cvor1 = cvor1->sljedeci;
                                cvor2 = cvor2->sljedeci;
                        }

            }


        }
    }
      return novi_imenik;
  }

};



#endif // IMENIK_H
