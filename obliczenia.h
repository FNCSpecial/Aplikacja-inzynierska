#pragma on 
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <sstream>



using std::endl;
using std::cout;

class Obliczenia
{
    
public:

    //stale oraz zmienne potrzebne w obliczeniach 

    #define M_PI 3.14159265358979323846
     double a, b, c, eps;

     double tablica1[1001], tablica2[1001], tablica3[101], tablica4[101];

     double zmienna1, zmienna2;

    int licznik2, licznik, numer_m_z;

     double Lmin, Lmax, betaA, betaB, betaC, eps1, eps2, AH, CH1, CH2, mi0, eps0, omega, x, deltaX;
     double L, deltaL, n1, n2;
     double k, beta, betamin, betamax, deltabeta, kappa, gamma1, N, HX1, EY1, H01, E01;
     double HX2, EY2, H02, E02, CH;
     double E01_TAB[1002], H01_TAB[1002], E02_TAB[1002], H02_TAB[1002];
     double E01max, H01max;
     double lambda;
   
    int LicznikPom1 = 1;
    int LicznikPom2 = 1;

    long double TablicaPom1[1000];
    long double TablicaPom2[1000];
    long double TablicaPom3[1000];

    double xcord[2001], ycord[2001];

    //Konstruktor w którym inicuje potrzebne zmienne oraz przy wywo³aniu klasu pobiram zmienne z okna aplikacji wprowadzone przez uzytkownika 

    Obliczenia(int N, double L,int  dom1, int dom2) {
     
        lambda = L*0.000001;
        

        numer_m_z = N;

        AH = 1;

       // L = 1.3e-6;
      //  n1 = n_GeO2_3_1(L);
      //  n2 = n_SiO2(L);

        if (dom1 == 1) {
            n1 = n_GeO2_3_1(lambda);
        }
        if (dom1 == 2) {
            n1 = n_SiO2(lambda);

        }


     
        if (dom2 == 1) {
            n2 = n_SiO2(lambda);

        }
        if (dom2 == 2) {
            n2 = n_F_1(lambda);
        }

       


        a = 70e-6;
        k = 2 * M_PI / lambda;
        betamin = k * n2;
        betamax = k * n1;
        deltabeta = (betamax - betamin) / 1000;
        beta = betamin;
        N = beta / k;
        kappa = sqrt(pow(n1 * k, 2) - pow(beta, 2));
        gamma1 = sqrt(pow(beta, 2) - pow(k * n2, 2));


        CH1 = AH * cos(kappa * a);
        CH2 = (-AH * (gamma1 / kappa)) * sin(kappa * a);
        c = 2.997925e8;
        mi0 = 4 * M_PI * 1.e-7;
        eps0 = 1 / (pow(c, 2) * mi0);
        omega = k * c;

        deltaX = a / 1000;
        x = 0;
    }

    double n_GeO2_3_1(double L)
    {
        double a1, a2, a3;
        double b1, b2, b3;
        double p1, p2, p3;
        a1 = 0.7028554;
        a2 = 0.4146307;
        a3 = 0.8974540;
        b1 = 0.0727723e-6;
        b2 = 0.1143085e-6;
        b3 = 9.896161e-6;
        p1 = (a1 * pow(L, 2)) / (pow(L, 2) - pow(b1, 2));
        p2 = (a2 * pow(L, 2)) / (pow(L, 2) - pow(b2, 2));
        p3 = (a3 * pow(L, 2)) / (pow(L, 2) - pow(b3, 2));
        return sqrt(1 + p1 + p2 + p3);
    }

    double n_SiO2(double L)
    {
        double a1, a2, a3;
        double b1, b2, b3;
        double p1, p2, p3;
        a1 = 0.6961663;
        a2 = 0.4079426;
        a3 = 0.8974994;
        b1 = 0.0684043e-6;
        b2 = 0.1162414e-6;
        b3 = 9.896161e-6;
        p1 = (a1 * pow(L, 2)) / (pow(L, 2) - pow(b1, 2));
        p2 = (a2 * pow(L, 2)) / (pow(L, 2) - pow(b2, 2));
        p3 = (a3 * pow(L, 2)) / (pow(L, 2) - pow(b3, 2));
        return sqrt(1 + p1 + p2 + p3);
    }

    double n_F_1(double L)
    {
        double a1, a2, a3;
        double b1, b2, b3;
        double p1, p2, p3;
        a1 = 0.69325;
        a2 = 0.39720;
        a3 = 0.86008;
        b1 = 0.06724e-6;
        b2 = 0.11714e-6;
        b3 = 9.7761e-6;
        p1 = (a1 * pow(L, 2)) / (pow(L, 2) - pow(b1, 2));
        p2 = (a2 * pow(L, 2)) / (pow(L, 2) - pow(b2, 2));
        p3 = (a3 * pow(L, 2)) / (pow(L, 2) - pow(b3, 2));
        return sqrt(1 + p1 + p2 + p3);
    }

    double HD(double beta)
    {
      
        kappa = sqrt(pow(n1 * k, 2) - pow(beta, 2));
        gamma1 = sqrt(pow(beta, 2) - pow(k * n2, 2));
        return sin(kappa * a) / cos(kappa * a) + kappa / gamma1;
    }
    
    void Tablice() {

        for (licznik = 1; licznik <= 1000; licznik++) {

            beta = beta + deltabeta;
            tablica1[licznik] = beta;
            tablica2[licznik] = HD(beta);

        }

       // Tablice1_2();

        licznik2 = 0;


        for (licznik = 2; licznik <= 1000; licznik++)
        {
            eps1 = 1;
            zmienna1 = tablica2[licznik - 1];
            zmienna2 = tablica2[licznik];

            if (zmienna1 * zmienna2 < 0)
                if (fabs(fabs(zmienna1) - fabs(zmienna2)) < eps1)
                {
                    licznik2 = licznik2 + 1;
                    tablica3[licznik2] = tablica1[licznik - 1];
                }
        }

        for (licznik = 1; licznik <= licznik2; licznik++)
        {
            betaA = tablica3[licznik];
            betaB = tablica3[licznik] + deltabeta;
            eps2 = 1.e-10;
            do
            {
                betaC = (betaA + betaB) / 2;
                if ((HD(betaA) * HD(betaC)) < 0)
                    betaB = betaC;
                else betaA = betaC;
                //  plik << betaC << " " << HD(betaC) << endl;
            } while (!(fabs(HD(betaC)) < eps2));
            // plik << "miejsce zerowe: betaC=" << betaC << "HD(betaC)=" << HD(betaC) << endl;
            // plik << " " << endl;
            tablica4[licznik] = betaC;
        }

        for (licznik = 1; licznik <= licznik2; licznik++)
        {
            tablica3[licznik2 - licznik + 1] = tablica4[licznik];
        }

    }

    void Tablice_2() {

        Tablice();

        beta = tablica3[numer_m_z];
        kappa = sqrt(pow(n1 * k, 2) - pow(beta, 2));
        gamma1 = sqrt(pow(beta, 2) - pow(k * n2, 2));
        CH1 = AH * cos(kappa * a);

       

        for (licznik = 0; licznik < 1001; licznik++)
        {

            x = x + deltaX;

            HX1 = (AH * beta * sin(x * kappa)) / kappa;
            EY1 = (AH * omega * mi0 * sin(x * kappa)) / kappa;
            H01 = fabs(HX1);
            E01 = fabs(EY1);

            H01_TAB[licznik] = H01;
            E01_TAB[licznik] = E01;

        }

        E01max = E01_TAB[0];
        H01max = H01_TAB[0];

        for (licznik = 1; licznik < 1001; licznik++)
        {
            if (E01max < E01_TAB[licznik])
                E01max = E01_TAB[licznik];
            if (H01max < H01_TAB[licznik])
                H01max = H01_TAB[licznik];
        }

        deltaX = a / 1000;
        x = a;

        for (licznik = 0; licznik < 1001; licznik++)
        {

            


            HX2 = (CH1 * beta * exp(-gamma1 * (fabs(x) - a))) / gamma1;
            EY2 = (CH1 * omega * mi0 * exp(-gamma1 * (fabs(x) - a))) / gamma1;
            H02 = fabs(HX2);
            E02 = fabs(EY2);
            H02_TAB[licznik] = H02;
            E02_TAB[licznik] = E02;
            x = x + deltaX;
        }



        for (licznik = 0; licznik < 1001; licznik++)
        {
            E01_TAB[licznik] = E01_TAB[licznik] / E01max;
            E02_TAB[licznik] = E02_TAB[licznik] / E01max;
            H01_TAB[licznik] = H01_TAB[licznik] / H01max;
            H02_TAB[licznik] = H02_TAB[licznik] / H01max;
        }




        
    }
  
    void Wykres1() {
        // wynik 1 to beta / betamin oraz HD(beta)
        
       
        for (licznik = 0; licznik < 1000; licznik++)
        {
           // plik << beta / betamin << "   " << HD(beta) << endl;

            beta = beta + deltabeta;

            xcord[licznik] = beta / betamin;
            ycord[licznik] = HD(beta);

        }
}

    void Wykres2()
    {
        
        Tablice();
        beta = tablica3[numer_m_z];
        kappa = sqrt(pow(n1 * k, 2) - pow(beta, 2));

        for (licznik = 0; licznik < 1000; licznik++)
        {
            x = x + deltaX;
            HX1 = (AH * beta * sin(x * kappa)) / kappa;
            H01 = fabs(HX1);
            H01_TAB[licznik] = H01;
           // plik << std::setprecision(18) << x / a << "   " << H01 << endl;

            xcord[licznik] = x / a;
            ycord[licznik] = H01;

           

           
            
        }
    }
    
    void Wykres3()
    {
        Tablice();
        beta = tablica3[numer_m_z];
        kappa = sqrt(pow(n1 * k, 2) - pow(beta, 2));

        for (licznik = 0; licznik < 1000; licznik++) {
            x = x + deltaX;
            EY1 = (AH * omega * mi0 * sin(x * kappa)) / kappa;
            E01 = fabs(EY1);

            // plik2 << std::setprecision(18) << x / a << "   " << E01 << endl;

            xcord[licznik] = x / a;
            ycord[licznik] = E01;

            

        }
    }

    void Wykres4() {

        Tablice();
        x = a;
        beta = tablica3[numer_m_z];

        kappa = sqrt(pow(n1 * k, 2) - pow(beta, 2));
        gamma1 = sqrt(pow(beta, 2) - pow(k * n2, 2));
        CH1 = AH * cos(kappa * a);
        
        
        

        for (licznik = 0; licznik < 1000; licznik++)
        {
            x = x + deltaX;

            HX2 = (CH1 * beta * exp(-gamma1 * (fabs(x) - a))) / gamma1;
            H02 = fabs(HX2);
            xcord[licznik] = x / a;
            ycord[licznik] = H02;

           
           // plik << std::setprecision(18) << x / a << "   " << H02 << endl;
           
        }

    }

    void Wykres5() {

        Tablice();
        x = a;
        beta = tablica3[numer_m_z];
        kappa = sqrt(pow(n1 * k, 2) - pow(beta, 2));
        gamma1 = sqrt(pow(beta, 2) - pow(k * n2, 2));
        CH1 = AH * cos(kappa * a);
        

        for (licznik = 0; licznik < 1000; licznik++)
        {
            x = x + deltaX;
 
            EY2 = (CH1 * omega * mi0 * exp(-gamma1 * (fabs(x) - a))) / gamma1;

            E02 = fabs(EY2);

            xcord[licznik] = x / a;
            ycord[licznik] = E02;

            
       //     plik2 << std::setprecision(18) << x / a << "   " << E02 << endl;
           
        }

    }

    void Wykres6() {

        Tablice_2();
       
        x = 0;

        for (licznik = 0; licznik < 1000; licznik++)
        {
            x = x + deltaX;
            xcord[licznik] = x / a;
            
            ycord[licznik] = E01_TAB[licznik];
            //plik << x / a << "   " << E01_TAB[licznik] << endl;
           
           
        }

        x = a;

        for (licznik = 0; licznik < 1000; licznik++)
        {
           
            xcord[1000 + licznik] = x / a;

            ycord[1000 + licznik] = E02_TAB[licznik];
            x = x + deltaX;
           // plik << x / a << "   " << E02_TAB[licznik] << endl;
           
           
        }

    }

    void Wykres7() {

        Tablice_2();
        x = 0;

        for (licznik = 0; licznik < 1000; licznik++)
        {
            x = x + deltaX;
            xcord[licznik] = x / a;
            ycord[licznik] = H01_TAB[licznik];
           
            //plik2 << x / a << "   " << H01_TAB[licznik] << endl;

        }

        x = a;

        for (licznik = 0; licznik < 1000; licznik++)
        {
           
            xcord[1000+licznik] = x / a;
            ycord[1000+licznik] = H02_TAB[licznik];
            x = x + deltaX;
            // plik2 << x / a << "   " << H02_TAB[licznik] << endl;

        }



    }

    void wynik2() {
            //wynik 2 to 
           // plik << "argumenty poprzedzajace wystapienie miejsca zerowego" << endl;
           // plik << "liczba miejsc zerowych jest rowna wartosci zmiennej licznik2" << endl;
            
            Tablice();

            licznik2 = 0;

            for (licznik = 2; licznik <= 1000; licznik++)
            {
                eps1 = 1;
                zmienna1 = tablica2[licznik - 1];
                zmienna2 = tablica2[licznik];
                if (zmienna1 * zmienna2 < 0)
                    if (fabs(fabs(zmienna1) - fabs(zmienna2)) < eps1)
                    {
                        licznik2 = licznik2 + 1;
                        tablica3[licznik2] = tablica1[licznik - 1];
                        
                    }
                
        }
            for (licznik = 1; licznik <= licznik2; licznik++)
            {
              //  plik << tablica3[licznik] << endl;
            }

           
    }

    void wynik3() {

            wynik2();

            


            //wynik 3 to betaC oraz HD(betaC)
            for (licznik = 1; licznik <= licznik2; licznik++)
            {
                betaA = tablica3[licznik];
                betaB = tablica3[licznik] + deltabeta;
                eps2 = 1.e-10;
                do
                {
                    betaC = (betaA + betaB) / 2;
                    if ((HD(betaA) * HD(betaC)) < 0)
                        betaB = betaC;
                    else betaA = betaC;
                    
                //    plik << betaC << " " << HD(betaC) << endl;

                    TablicaPom1[LicznikPom1] = betaC;
                    TablicaPom2[LicznikPom1] = HD(betaC);
                    LicznikPom1++;

                } while (!(fabs(HD(betaC)) < eps2));
           //     plik << "miejsce zerowe: betaC=" << betaC << "HD(betaC)=" << HD(betaC) << endl;
            //    plik << " " << endl;
                tablica4[licznik] = betaC;
                TablicaPom3[LicznikPom2] = HD(betaC);
                LicznikPom2++;
            }

        }

    void wynik4() {

        wynik3();

        for (licznik = 1; licznik <= licznik2; licznik++)
        {
            tablica3[licznik2 - licznik + 1] = tablica4[licznik];
        }


    }

    void wynik5() {

        wynik4();

        beta = tablica3[numer_m_z];

        kappa = sqrt(pow(n1 * k, 2) - pow(beta, 2));
        gamma1 = sqrt(pow(beta, 2) - pow(k * n2, 2));
        CH1 = AH * cos(kappa * a);
        CH2 = (-AH * (gamma1 / kappa)) * sin(kappa * a);
        
    }
    
    void wynik6_7() {

        Tablice_2();
       

    }
};


