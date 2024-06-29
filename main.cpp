#include<iostream>
#include<string>
#include "imenik.h"


using namespace std;

int main(){

    Imenik imenik("Prijatelji");
    string ime = "Emina";
    string mobilni = "061172890";
    string fiksni = "033999999";

    imenik.DodajKontakt({ime,mobilni,fiksni});
    imenik.DodajKontakt({"Emin","062228922","033267987"});
    imenik.DodajKontakt({"Zehra","062927822","033148267"});
    imenik.DodajKontakt({"Nejra","062222222","033234567"});

    imenik.Ispisi();
    cout<<endl<<endl;

    /*
    cout<<"Sortiran imenik"<<endl;
    imenik.Sort();
    imenik.Ispisi();
    cout<<endl<<endl;
    */

    cout<<endl<<endl;
    cout<<"Pretrazivaje po stringu - svi kontakti koji sadrze \"Em\" iz imenika Prijatelji"<<endl;
    imenik.PretraziPoNazivu("Em");

    cout<<"Pretrazivaje po broju mobitela ili fiksnog telefona - svi kontakti koji sadrze \"062\" iz imenika Prijatelji"<<endl;
    imenik.PretraziPoBroju("062");

    cout<<endl<<endl<<"Brisem kontakt Nejra iz imenika Prijatelji"<<endl;
    imenik.IzbrisiKontakt("Nejra");
    imenik.Ispisi();
    cout<<endl<<endl;
    cout<<endl<<endl<<"Brisem kontakt Amar koji ne postoji"<<endl;
    imenik.IzbrisiKontakt("Amar");
    imenik.Ispisi();
    cout<<endl<<endl;

    cout<<"Konstruktor koji prima niz kontakata"<<endl;
    Imenik imenik2({{"Emina","061111222","033999999"}, {"Muaz","063000777","033480000"}, {"Aida","063812377","033123890"}},"Porodica");
    imenik2.Ispisi();

    cout<<endl<<"Spojeni imenici prijatelji i porodica"<<endl;
    Imenik spojeni;
    spojeni = Spoji(imenik,imenik2);
    spojeni.Ispisi();

    cout<<endl<<"Promijeni telefon kontakta Emin"<<endl;
    imenik.PromijeniTelefonKontakta("Emin");
    cout<<endl<<endl;

}
