#ifndef IMENIK_CPP
#define IMENIK_CPP
#include"imenik.h"
#include <string>
#include<algorithm>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*Funkcija koja pravi praznu listu koja se sastoji samo od glave i repa.*/

void Imenik::init() {
    head = new Cvor;
    tail = new Cvor(Kontakt(),head);
    head->sljedeci = tail;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Konstruktor koji prima vektor kontakata i pravi imenik od tih kontakata. Poziva funkciju init(),
  nakon toga prolazi kroz vektor i dodaje elemente vektora u imenik pomocu funkcije DodajKontakt. Zatim sortira imenik.*/

Imenik::Imenik(vector<Kontakt> kontakti,string naziv_imenika):naziv_imenika(naziv_imenika){
    init();
    for(int i = 0; i < kontakti.size(); i++){
        DodajKontakt(kontakti[i]);
    }
    Sort();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Funkcija koja sortira imenik.*/

void Imenik::Sort(){
    Cvor *prvi = nullptr, *drugi = nullptr;
    Kontakt trenutna;
    prvi = head->sljedeci;
    while(prvi->sljedeci != tail){
        drugi = prvi->sljedeci;
        while(drugi != tail){
            if(prvi->kontakt.naziv > drugi->kontakt.naziv){
                trenutna = prvi->kontakt;
                prvi->kontakt = drugi->kontakt;
                drugi->kontakt = trenutna;
            }
            drugi = drugi->sljedeci;
        }
        prvi = prvi->sljedeci;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Prolazi kroz listu i ukoliko pronadje kontakt sa nazivom koji korisnik trazi vraca true a inace vraca false.*/

bool Imenik::DaLiVecPostojiIme(string naziv_kontakta){
    Cvor *trenutni = head->sljedeci;
    while(trenutni != tail){

        if(trenutni->kontakt.naziv == naziv_kontakta){
            return true;
        }
        trenutni = trenutni->sljedeci;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Provjerava da li naziv kontakta koji korisnik zeli da doda u listu vec postoji u imeniku.
  Ukoliko ne postoji onda dodaje kontakt na kraj liste a nakon toga sortira imenik.*/

void Imenik::DodajKontakt(Kontakt kontakt){

    if(DaLiVecPostojiIme(kontakt.naziv)) throw runtime_error("Kontakt sa datim imenom vec postoji. ");

    if(head->sljedeci == tail){
        Cvor *novi = new Cvor(kontakt, head, head->sljedeci);
        head->sljedeci = head->sljedeci->prethodni = novi;
    }
    else{
        Cvor *novi = new Cvor(kontakt, tail->prethodni, tail);
        tail->prethodni = tail->prethodni->sljedeci = novi;
    }
    Sort();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Funkcija koja ispisuje imenik*/

void Imenik::Ispisi(){

    cout<<"Kontakti iz imenika \""<<naziv_imenika<<"\": "<<endl;

    Cvor *trenutni = head->sljedeci;
    while(trenutni != tail){
        cout<<endl;
        cout<<"Ime: \t\t "<<trenutni->kontakt.naziv<<endl;
        cout<<"Mobilni telefon: "<<trenutni->kontakt.mobilni<<endl;
        cout<<"Fiksni telefon:  "<<trenutni->kontakt.fiksni<<endl;
        trenutni = trenutni->sljedeci;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Funkcija koja brise kontakt.*/

void Imenik::IzbrisiKontakt(string naziv_kontakta){

    if(head->sljedeci == tail) return;

    Cvor *trenutni = head->sljedeci;
    while(trenutni != tail){

        if(trenutni->kontakt.naziv == naziv_kontakta){
            trenutni->prethodni->sljedeci = trenutni->sljedeci;
            trenutni->sljedeci->prethodni = trenutni->prethodni;
            delete trenutni;
        }

        trenutni = trenutni->sljedeci;
    }
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Prolazi kroz listu i ukoliko nadje kontakt ciji naziv korisnik zeli da promijeni, trazi od korisnika da unese novi naziv kontakta.
 Naziv kontakta postaje novi naziv ukoliko korisnik nije unio prazan string i lista se sortira.*/

void Imenik::PromijeniNazivKontakta(string naziv_kontakta){
    string novi_naziv;
    Cvor *trenutni = head->sljedeci;
    while(trenutni != tail){

        if(trenutni->kontakt.naziv == naziv_kontakta){
            cout<<"Unesi novi naziv kontakta "<<trenutni->kontakt.naziv<<endl;
            cin>>novi_naziv;
            if(novi_naziv != "")
            trenutni->kontakt.naziv = novi_naziv;
            cout<<"Novi naziv je: "<<trenutni->kontakt.naziv<<endl<<endl;
            Sort();
        }

        trenutni = trenutni->sljedeci;
    }
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Funkcija koja prolazi kroz listu i ukoliko pronadje kontakt ciji telefon korisnik zeli promijeniti, nudi dvije opcije.
 Ako korisnik izabere prvu opciju unosenjem broja 1 onda moze da mijenja mobilni telefon.
 Ako korisnik izabere drugu opciju unosenjem broja 2 onda moze da unese novi fiksni telefon. Novi telefon mora sadrzavati samo brojeve.*/

void Imenik::PromijeniTelefonKontakta(string naziv_kontakta){

    string novi_mobilni;
    string novi_fiksni;
    int slucaj;

    Cvor *trenutni = head->sljedeci;
    while(trenutni != tail){

        if(trenutni->kontakt.naziv == naziv_kontakta){
            cout<<"Ukoliko zelite da promjenite mobilni telefon kontakta pritisnite 1. "<<endl<<
                  "Ukoliko zelite da promijenite fiksni telefon kontakta pritisnite 2. "<<endl;

            cin>>slucaj;
            switch(slucaj){
            case 1:
                cout<<"Unesite novi mobilni telefon."<<endl;
                cin>>novi_mobilni;
                trenutni->kontakt.mobilni = novi_mobilni;
                if(!trenutni->kontakt.jeLiBroj(trenutni->kontakt.mobilni))
                throw runtime_error("Novi mobilni telefon sadrzi znakove koji nisu brojevi ");
                cout<<"Novi mobilni telefon kontakta "<<trenutni->kontakt.naziv<<" je "<<novi_mobilni<<endl<<endl;
                Sort();
                break;

             case 2:
                cout<<"Unesite novi fiksni telefon."<<endl;
                cin>>novi_fiksni;
                trenutni->kontakt.fiksni = novi_fiksni;
                if(!trenutni->kontakt.jeLiBroj(trenutni->kontakt.fiksni))
                throw runtime_error("Novi fiksni telefon sadrzi znakove koji nisu brojevi ");
                cout<<"Novi fiksni telefon kontakta "<<trenutni->kontakt.naziv<<" je "<<novi_fiksni<<endl<<endl;
                Sort();
                break;

            default:
            cout<<"Opcija ne postoji";

        }

        }
        trenutni = trenutni->sljedeci;

    }

    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Vrsi pretrazivanje imenika po nazivu.
 Korisnik ne mora da unese puni naziv vec moze unijeti dio naziva nakon cega se izlistavaju svi kotakti koji sadrze u svom nazivu string koji se trazi.*/

void Imenik::PretraziPoNazivu(string naziv_kontakta){
    Cvor *trenutni = head->sljedeci;
    while(trenutni != tail){

        if(trenutni->kontakt.naziv.find(naziv_kontakta)!= string::npos){

        cout<<"Ime: \t\t "<<trenutni->kontakt.naziv<<endl;
        cout<<"Mobilni telefon: "<<trenutni->kontakt.mobilni<<endl;
        cout<<"Fiksni telefon:  "<<trenutni->kontakt.fiksni<<endl<<endl;

        }

        trenutni = trenutni->sljedeci;
    }
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Vrsi pretrazivanje imenika po broju. Korisnik ne mora da unese cijeli broj, moze unijeti dio broja.
Pretrazuju se i mobilni i fiksni telefoni te se izlistavaju svi kontakti koji sadrze dati broj.*/

void Imenik::PretraziPoBroju(string broj){
    Cvor *trenutni = head->sljedeci;
    while(trenutni != tail){

        if(trenutni->kontakt.mobilni.find(broj)!= string::npos
           || trenutni->kontakt.fiksni.find(broj) != string::npos){

        cout<<"Ime: \t\t "<<trenutni->kontakt.naziv<<endl;
        cout<<"Mobilni telefon: "<<trenutni->kontakt.mobilni<<endl;
        cout<<"Fiksni telefon:  "<<trenutni->kontakt.fiksni<<endl<<endl;

        }

        trenutni = trenutni->sljedeci;
    }
    return;
}

#endif // IMENIK_CPP
