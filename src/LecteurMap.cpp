

#include <iostream>
#include <fstream>

using namespace std;

void loader()
{
        ifstream Carte("Carte.txt", ios::in);  // on ouvre

        char caractere;
        int i = 0;
        if(Carte)
        {
            while(getchar(Carte))
        {
                  // notre variable où sera stocké le caractère
                Carte.get(caractere);  // on lit un caractère et on le stocke dans caractere
                cout << caractere;  // on l'affiche

                if (caractere == 'b' )
                {
                    Draw(block(10*i,0,0));

                }
                i=i+1;

        }
        else
                cerr << "Impossible d'ouvrir le fichier !" << endl;
        }


}
