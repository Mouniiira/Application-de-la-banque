#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "client.h"
#include "compte.h"
#include "client.c"
#include "compte.c"
#include "emprunter.c"
#include "emprunter.h"
#include "rembourser.h"
#include "rembourser.c"
#define ENTETE printf("\t\t\t\t\03  \06  \04  \05  \03  \06  \04  \05  \03  \06  \04  \05  \03  \06  \04\n\t\t\t\t\05   APPLICATION  DE GESTION  DES  BANQUE  \05\n\t\t\t\t\03  \06  \04  \05  \03  \06  \04  \05  \03  \06  \04  \05  \03  \06  \04\n\n\n")

int main()
{

    ListeClients listeClients;
    initialiserListeClients(&listeClients);

    ListeComptes listeComptes;
    initialiserListeComptes(&listeComptes);

    ListeEmprunts listeEmprunts;
    initialiserListeEmprunts(&listeEmprunts);

    ListeRemboursements listeRemboursements;
    initialiserListeRemboursements(&listeRemboursements);

    int choix;
    long numeroRecherche;
    long numeroModification;
    long numeroEmprunt;
    double montantRemboursement;
    long numeroClient;
    long typeEmprunt;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    ENTETE;

    do
    {
        SetConsoleTextAttribute(hConsole, 6);
        printf("\04 Menu principal \04\n");
        SetConsoleTextAttribute(hConsole, 12);
        printf("\03 1. Enregistrer un nouveau client \03\n");
        SetConsoleTextAttribute(hConsole, 8);
        printf("2. Rechercher un client par num�ro\n");
        SetConsoleTextAttribute(hConsole, 12);
        printf("3. Enregistrer un nouveau compte\n");
        SetConsoleTextAttribute(hConsole, 8);
        printf("4. D�bloquer un compte\n");
        SetConsoleTextAttribute(hConsole, 12);
        printf("5. Modifier les informations d'un client\n");
        SetConsoleTextAttribute(hConsole, 8);
        printf("6. Solliciter un emprunt\n");
        SetConsoleTextAttribute(hConsole, 12);
        printf("7. Afficher les emprunts\n");
        SetConsoleTextAttribute(hConsole, 8);
        printf("8. Effectuer un remboursement\n");
        SetConsoleTextAttribute(hConsole, 12);
        printf("9. Afficher les remboursements\n");
        SetConsoleTextAttribute(hConsole, 8);
        printf("0. Quitter\n");

        printf("Choix : ");
        scanf("%d", &choix);

        system("cls");
        SetConsoleTextAttribute(hConsole, 15);
        ENTETE;
        switch (choix)
        {
        case 1:
        {
            Client nouveauClient;

            printf("Entrez le num�ro du client : ");
            scanf("%ld", &nouveauClient.numero);

            printf("Entrez le nom du client : ");
            scanf("%s", nouveauClient.nom);

            printf("Entrez le pr�nom du client : ");
            scanf("%s", nouveauClient.prenom);

            printf("Entrez le genre du client (M/F) : ");
            scanf(" %c", &nouveauClient.genre);

            printf("Entrez la date de naissance du client (JJ/MM/AAAA) : ");
            scanf("%s", nouveauClient.date_naissance);

            printf("Entrez le lieu de naissance du client : ");
            scanf("%s", nouveauClient.lieu_naissance);

            printf("Entrez la profession du client : ");
            scanf("%s", nouveauClient.profession);

            enregistrer_client(&listeClients, &nouveauClient);

            system("cls");
            SetConsoleTextAttribute(hConsole, 15);
            ENTETE;
            printf("Client enregistr� avec succ�s.\n");
            break;
        }


        case 2:
            printf("Entrez le num�ro du client � rechercher : ");
            scanf("%ld", &numeroRecherche);
            Client *clientTrouve = rechercher_client(&listeClients, numeroRecherche);
            if (clientTrouve != NULL)
            {
                printf("Client trouv� :\n");
                printf("Num�ro : %ld, Nom : %s, Pr�nom : %s\n", clientTrouve->numero, clientTrouve->nom, clientTrouve->prenom);
            }
            else
            {
                system("cls");
                SetConsoleTextAttribute(hConsole, 15);
                ENTETE;
                printf("Aucun client trouv� avec le num�ro %ld\n", numeroRecherche);
            }
            break;
            system("cls");
            SetConsoleTextAttribute(hConsole, 15);
            ENTETE;
        case 3:
        {
            Compte nouveauCompte;
            printf("Entrez le num�ro du compte : ");
            scanf("%ld", &nouveauCompte.numero);

            printf("Entrez le type du compte (0 pour EPARGNE, 1 pour COURANT) : ");
            scanf("%d", (int*)&nouveauCompte.type);

            printf("Entrez le num�ro du client associ� au compte : ");
            scanf("%ld", &nouveauCompte.numero_client);

            printf("Entrez le solde initial du compte : ");
            scanf("%lf", &nouveauCompte.solde);

            printf("Entrez l'�tat du compte (0 pour LIBRE, 1 pour BLOQUE) : ");
            scanf("%d", (int*)&nouveauCompte.etat);

            enregistrer_compte(&listeComptes, &nouveauCompte);
            system("cls");
            SetConsoleTextAttribute(hConsole, 15);
            ENTETE;
            printf("Compte enregistr� avec succ�s.\n");

            break;
        }

        case 4:
        {
            long numeroDeblocage;
            printf("Entrez le num�ro du compte � d�bloquer/bloquer : ");
            scanf("%ld", &numeroDeblocage);

            debloquer_compte(&listeComptes, numeroDeblocage);
            system("cls");
            ENTETE;
            printf("Op�ration effectu�e avec succ�s.\n");
            break;
        }
        case 5:
            printf("Entrez le num�ro du client � modifier : ");
            scanf("%ld", &numeroModification);
            modifier_client(&listeClients, numeroModification);
            system("cls");
            SetConsoleTextAttribute(hConsole, 15);
            ENTETE;
            break;
        case 6:
        {
            printf("Entrez le num�ro du client : ");
            scanf("%ld", &numeroClient);

            Client *clientEmprunt = rechercher_client(&listeClients, numeroClient);

            if (clientEmprunt != NULL)
            {
                Emprunt nouvelEmprunt;
                nouvelEmprunt.numero_client = clientEmprunt->numero;

                printf("Type d'emprunt (0: Pr�t scolaire, 1: Pr�t investissement, 2: Pr�t immobilier) : ");
                scanf("%ld", &nouvelEmprunt.type);

                printf("Raison de l'emprunt : ");
                scanf("%s", nouvelEmprunt.raison);

                printf("Montant de l'emprunt : ");
                scanf("%lf", &nouvelEmprunt.montant);

                printf("Date limite de remboursement (JJ/MM/AAAA) : ");
                scanf("%s", nouvelEmprunt.date_limite);

                printf("Date du premier remboursement (JJ/MM/AAAA) : ");
                scanf("%s", nouvelEmprunt.date_premier_remboursement);
                system("cls");
                SetConsoleTextAttribute(hConsole, 15);
                ENTETE;
                solliciter_emprunt(&listeEmprunts, &nouvelEmprunt);
                printf("Emprunt sollicit� avec succ�s.\n");
            }
            else
            {
                system("cls");
                SetConsoleTextAttribute(hConsole, 15);
                ENTETE;
                printf("Aucun client trouv� avec le num�ro %ld\n", numeroClient);
            }
            break;
        }


        case 7:
        {
            printf("Entrez le num�ro du client : ");
            scanf("%ld", &numeroClient);

            Client *clientEmprunt = rechercher_client(&listeClients, numeroClient);

            if (clientEmprunt != NULL)
            {
                Emprunt nouvelEmprunt;
                nouvelEmprunt.numero_client = clientEmprunt->numero;

                printf("Type d'emprunt (1: Pr�t scolaire, 2: Pr�t investissement, 3: Pr�t immobilier) : ");
                scanf("%d", &typeEmprunt);


                printf("Raison de l'emprunt : ");
                scanf("%s", nouvelEmprunt.raison);


                solliciter_emprunt(&listeEmprunts, &nouvelEmprunt);
                system("cls");
                SetConsoleTextAttribute(hConsole, 15);
                ENTETE;
                printf("Emprunt sollicit� avec succ�s.\n");
            }
            else
            {
                system("cls");
                SetConsoleTextAttribute(hConsole, 15);
                ENTETE;
                printf("Aucun client trouv� avec le num�ro %ld\n", numeroClient);

            }
            break;

        }



        case 8:
            printf("Entrez le num�ro de l'emprunt � rembourser : ");
            scanf("%ld", &numeroEmprunt);

            Emprunt *empruntARembourser = rechercher_emprunt(&listeEmprunts, numeroEmprunt);

            if (empruntARembourser != NULL)
            {
                if (empruntARembourser->statut == EN_COURS)
                {
                    system("cls");
                    SetConsoleTextAttribute(hConsole, 15);
                    ENTETE;
                    printf("Entrez le montant du remboursement : ");
                    scanf("%lf", &montantRemboursement);

                    effectuer_remboursement(&listeRemboursements, &empruntARembourser, &montantRemboursement);
                }
                else
                {
                    printf("Cet emprunt n'est plus en cours.\n");
                }
            }
            else
            {
                system("cls");
                SetConsoleTextAttribute(hConsole, 15);
                ENTETE;
                printf("Aucun emprunt trouv� avec le num�ro %ld\n", numeroEmprunt);
            }
            break;


        case 9:
            afficher_remboursements(&listeRemboursements);
            break;

    case 0:
        {
            printf("Programme termin�.\n");
            }
            break;
}

    }
    while (choix != 0);

    return 0;

}
