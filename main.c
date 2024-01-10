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
        printf("\05 2. Rechercher un client par numéro \05\n");
        SetConsoleTextAttribute(hConsole, 12);
        printf("\03 3. Enregistrer un nouveau compte \03\n");
        SetConsoleTextAttribute(hConsole, 8);
        printf("\05 4. Débloquer un compte \05\n");
        SetConsoleTextAttribute(hConsole, 12);
        printf("\03 5. Modifier les informations d'un client \03\n");
        SetConsoleTextAttribute(hConsole, 8);
        printf("\05 6. Solliciter un emprunt \05\n");
        SetConsoleTextAttribute(hConsole, 12);
        printf("\03 7. Afficher les emprunts \03\n");
        SetConsoleTextAttribute(hConsole, 8);
        printf("\05 8. Effectuer un remboursement \05\n");
        SetConsoleTextAttribute(hConsole, 12);
        printf("\03 9. Afficher les remboursements \03\n");
        SetConsoleTextAttribute(hConsole, 8);
        printf("\05 0. Quitter \05\n");

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

            SetConsoleTextAttribute(hConsole, 6);
            printf("\03 Enregistrer un nouveau client \03\n\n");

            SetConsoleTextAttribute(hConsole, 15);

            printf("Entrez le numéro du client : ");
            scanf("%ld", &nouveauClient.numero);

            printf("Entrez le nom du client : ");
            scanf("%s", nouveauClient.nom);

            printf("Entrez le prénom du client : ");
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
            printf("Client enregistré avec succès.\n\n");
            break;
        }


        case 2:
            SetConsoleTextAttribute(hConsole, 6);
            printf("\05 Rechercher un client par numéro \05\n\n");

            SetConsoleTextAttribute(hConsole, 15);
            printf("Entrez le numéro du client à rechercher : ");
            scanf("%ld", &numeroRecherche);
            Client *clientTrouve = rechercher_client(&listeClients, numeroRecherche);
            if (clientTrouve != NULL)
            {
                printf("Client trouvé :\n");
                printf("Numéro : %ld, Nom : %s, Prénom : %s\n", clientTrouve->numero, clientTrouve->nom, clientTrouve->prenom);
            }
            else
            {
                system("cls");
                SetConsoleTextAttribute(hConsole, 15);
                ENTETE;
                printf("Aucun client trouvé avec le numéro %ld\n", numeroRecherche);
            }
            break;
            system("cls");
            SetConsoleTextAttribute(hConsole, 15);
            ENTETE;
        case 3:
        {
            Compte nouveauCompte;
            SetConsoleTextAttribute(hConsole, 6);
            printf("\03 Enregistrer un nouveau compte \03\n\n");

            SetConsoleTextAttribute(hConsole, 15);
            printf("Entrez le numéro du compte : ");
            scanf("%ld", &nouveauCompte.numero);

            printf("Entrez le type du compte (0 pour EPARGNE, 1 pour COURANT) : ");
            scanf("%d", (int*)&nouveauCompte.type);

            printf("Entrez le numéro du client associé au compte : ");
            scanf("%ld", &nouveauCompte.numero_client);

            printf("Entrez le solde initial du compte : ");
            scanf("%lf", &nouveauCompte.solde);

            printf("Entrez l'état du compte (0 pour LIBRE, 1 pour BLOQUE) : ");
            scanf("%d", (int*)&nouveauCompte.etat);

            enregistrer_compte(&listeComptes, &nouveauCompte);
            system("cls");
            SetConsoleTextAttribute(hConsole, 15);
            ENTETE;
            printf("Compte enregistré avec succès.\n");

            break;
        }

        case 4:
        {
            SetConsoleTextAttribute(hConsole, 6);
            printf("\05 Débloquer un compte \05\n\n");

            SetConsoleTextAttribute(hConsole, 15);
            long numeroDeblocage;
            printf("Entrez le numéro du compte à débloquer/bloquer : ");
            scanf("%ld", &numeroDeblocage);

            debloquer_compte(&listeComptes, numeroDeblocage);
            system("cls");
            ENTETE;
            printf("Opération effectuée avec succès.\n");
            break;
        }
        case 5:
            SetConsoleTextAttribute(hConsole, 6);
            printf("\03 Modifier les informations d'un client \03\n\n");

            SetConsoleTextAttribute(hConsole, 15);
            printf("Entrez le numéro du client à modifier : ");
            scanf("%ld", &numeroModification);
            modifier_client(&listeClients, numeroModification);
            system("cls");
            SetConsoleTextAttribute(hConsole, 15);
            ENTETE;
            break;
        case 6:
        {
            SetConsoleTextAttribute(hConsole, 6);
            printf("\05 Solliciter un emprunt \05\n\n");

            SetConsoleTextAttribute(hConsole, 15);
            printf("Entrez le numéro du client : ");
            scanf("%ld", &numeroClient);

            Client *clientEmprunt = rechercher_client(&listeClients, numeroClient);

            if (clientEmprunt != NULL)
            {
                Emprunt nouvelEmprunt;
                nouvelEmprunt.numero_client = clientEmprunt->numero;

                printf("Type d'emprunt (0: Prêt scolaire, 1: Prêt investissement, 2: Prêt immobilier) : ");
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
                printf("Emprunt sollicité avec succès.\n");
            }
            else
            {
                system("cls");
                SetConsoleTextAttribute(hConsole, 15);
                ENTETE;
                printf("Aucun client trouvé avec le numéro %ld\n", numeroClient);
            }
            break;
        }


        case 7:
        {
            SetConsoleTextAttribute(hConsole, 6);
            printf("\03 Afficher les emprunts \03\n\n");

            SetConsoleTextAttribute(hConsole, 15);
            printf("Entrez le numéro du client : ");
            scanf("%ld", &numeroClient);

            Client *clientEmprunt = rechercher_client(&listeClients, numeroClient);

            if (clientEmprunt != NULL)
            {
                Emprunt nouvelEmprunt;
                nouvelEmprunt.numero_client = clientEmprunt->numero;

                printf("Type d'emprunt (1: Prêt scolaire, 2: Prêt investissement, 3: Prêt immobilier) : ");
                scanf("%d", &typeEmprunt);


                printf("Raison de l'emprunt : ");
                scanf("%s", nouvelEmprunt.raison);


                solliciter_emprunt(&listeEmprunts, &nouvelEmprunt);
                system("cls");
                SetConsoleTextAttribute(hConsole, 15);
                ENTETE;
                printf("Emprunt sollicité avec succès.\n");
            }
            else
            {
                system("cls");
                SetConsoleTextAttribute(hConsole, 15);
                ENTETE;
                printf("Aucun client trouvé avec le numéro %ld\n", numeroClient);

            }
            break;

        }



        case 8:
            SetConsoleTextAttribute(hConsole, 6);
            printf("\05 Effectuer un remboursement \05\n\n");

            SetConsoleTextAttribute(hConsole, 15);
            printf("Entrez le numéro de l'emprunt à rembourser : ");
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
                printf("Aucun emprunt trouvé avec le numéro %ld\n", numeroEmprunt);
            }
            break;


        case 9:
            SetConsoleTextAttribute(hConsole, 6);
            printf("\03 Afficher les remboursements \03\n\n");

            SetConsoleTextAttribute(hConsole, 15);
            afficher_remboursements(&listeRemboursements);
            break;

    case 0:
        {
            SetConsoleTextAttribute(hConsole, 3);
            printf("Programme terminé.\02\n");
            SetConsoleTextAttribute(hConsole, 15);
            }
            break;
}

    }
    while (choix != 0);

    return 0;

}
