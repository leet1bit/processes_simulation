#include <stdio.h>

#define NB_MAT 4
#define MAX_ETU 50

typedef struct {
    float note;
    int coefficient;
} Matiere;

typedef struct {
    char nom[30];
    char prenom[30];
    Matiere matieres[NB_MAT];
} Etudiant;

void saisirEtudiants(Etudiant etu[], int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        printf("\nEtudiant %d\n", i + 1);

        printf("Nom : ");
        scanf("%s", etu[i].nom);

        printf("Prenom : ");
        scanf("%s", etu[i].prenom);

        for (j = 0; j < NB_MAT; j++) {
            do {
                printf("Note matiere %d : ", j + 1);
                scanf("%f", &etu[i].matieres[j].note);
            } while (etu[i].matieres[j].note < 0 || etu[i].matieres[j].note > 20);

            printf("Coefficient matiere %d : ", j + 1);
            scanf("%d", &etu[i].matieres[j].coefficient);
        }
    }
}

float moyenneEtudiant(Etudiant e) {
    int i;
    float somme = 0;
    int sommeCoef = 0;

    for (i = 0; i < NB_MAT; i++) {
        somme += e.matieres[i].note * e.matieres[i].coefficient;
        sommeCoef += e.matieres[i].coefficient;
    }

    return somme / sommeCoef;
}

void afficherMoyennes(Etudiant etu[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        printf("\n%s %s - Moyenne : %.2f",
               etu[i].nom,
               etu[i].prenom,
               moyenneEtudiant(etu[i]));
    }
}

void modifierNote(Etudiant *e, int indiceMatiere, float nouvelleNote) {
    if (indiceMatiere >= 0 && indiceMatiere < NB_MAT &&
        nouvelleNote >= 0 && nouvelleNote <= 20) {
        e->matieres[indiceMatiere].note = nouvelleNote;
    }
}

int main() {
    Etudiant classe[MAX_ETU];
    int n;
    int choixEtudiant, choixMatiere;
    float nouvelleNote;

    printf("Nombre d'etudiants : ");
    scanf("%d", &n);

    if (n > MAX_ETU || n <= 0) {
        printf("Nombre d'etudiants invalide.\n");
        return 0;
    }

    saisirEtudiants(classe, n);
    afficherMoyennes(classe, n);

    printf("\n\nModifier une note");
    printf("\nChoisir l'etudiant (1 a %d) : ", n);
    scanf("%d", &choixEtudiant);

    printf("Choisir la matiere (1 a %d) : ", NB_MAT);
    scanf("%d", &choixMatiere);

    printf("Nouvelle note : ");
    scanf("%f", &nouvelleNote);

    if (choixEtudiant >= 1 && choixEtudiant <= n) {
        modifierNote(&classe[choixEtudiant - 1],
                     choixMatiere - 1,
                     nouvelleNote);
    }

    printf("\nApres modification :");
    afficherMoyennes(classe, n);

    return 0;
}
