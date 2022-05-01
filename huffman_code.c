#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

// déclaration structure commune pour listes et arbres composé principalement
// du nombre d'occurences, de la lettre et du code binaire
typedef struct stru_all stru_all;


struct stru_all{
    char lettre;
    int nb_oc;
    int eq;
    char* code;
    int codesize;
    stru_all* suiv;
    stru_all* fg;
    stru_all* fd;
};

// structure pour affichage graphique
typedef struct TArbBin TArbBin;
struct TArbBin {
  int elmt;
  int equilibre;
  char lettre;
};



// fonction qui crée le premier élément de la liste
stru_all* creerListe(char lettre) {
    stru_all* liste;
    liste = malloc(sizeof(stru_all));
    liste->lettre = lettre;
    liste->nb_oc = 1;
    liste->suiv = NULL;
    liste->fg = NULL;
    liste->fd = NULL;
    liste->code = "===";
    return liste;
}

// fonction vérifiant l'arbre existe
int estVide(stru_all* racine){
  if(racine == NULL){
    return 1;
  }
  return 0 ;
}

// fonction qui vérifie si le noeud est une feuille
int estFeuille(stru_all* a) {
    return !(a->fg || a->fd);
}

// fonction qui permet d'insérer à la fin de liste un nouveau chainon
stru_all* Insertion_fin(char lettre, stru_all* tete_liste) {
    stru_all* liste = tete_liste;
    stru_all* chaine;
    chaine = malloc(sizeof(stru_all));
    chaine->lettre = lettre;
    chaine->nb_oc = 1;
    chaine->suiv = NULL;
    chaine->fg =NULL;
    chaine->fd = NULL;
    chaine->code = "===";
    while(liste->suiv != NULL){
        liste = liste->suiv;
    }
    liste->suiv = chaine;
    return tete_liste;
}

// fonction qui supprime le dernier élément de la liste
stru_all* supp_fin(stru_all* tete_liste){
    stru_all* liste = tete_liste;
    while(liste->suiv->suiv != NULL){
        liste = liste->suiv;
    }
    liste->suiv = NULL;
    return tete_liste;
}

// fonction qui permet de trier les contenus de la liste
stru_all* trie(stru_all* tete_liste ){
    stru_all* ptr1 = tete_liste;
    stru_all* ptr2;
    int tmp;
    char tmp2;
    if(tete_liste == NULL){
        printf("Pas de liste \n");
        exit(1);
    }
    if(tete_liste->suiv == NULL){
        return tete_liste;
    }
    while(ptr1->suiv != NULL){
        ptr2= ptr1->suiv;
            while ( ptr2 != NULL)
            {
                 if(ptr1->nb_oc > ptr2->nb_oc){
                   tmp = ptr1->nb_oc;
                   ptr1->nb_oc = ptr2->nb_oc;
                   ptr2->nb_oc = tmp;

                   tmp2 = ptr1->lettre;
                   ptr1->lettre = ptr2->lettre;
                   ptr2->lettre = tmp2;
                 }
                 ptr2 = ptr2->suiv;
            }

        ptr1 =ptr1->suiv;
    }       
       return tete_liste;     
       
}

// fonction qui mettre à jour l'histogramme
stru_all* listoc_update(stru_all* tete_liste,char lettre){
    stru_all* l = tete_liste;
    if(tete_liste == NULL){
        return creerListe(lettre);
    }
    else{
         while(l != NULL)
         {
             if(l->lettre == lettre){
                l->nb_oc = l->nb_oc + 1;
             return tete_liste;
            }
            else{
            l = l->suiv;
         }
             
         }
    }

    return Insertion_fin(lettre,tete_liste);

}

// procédure qui affiche la liste
void affiche_listoc(stru_all* liste ){
    while(liste != NULL){
        printf("____ \n");
        printf("| %c |\n", liste->lettre);
        printf("| %d |\n", liste->nb_oc);
        printf("____ \n");
        liste = liste->suiv;
    }
    
}

// fonction qui insère un chainon de façon croissante dans la liste
stru_all* insertion_croissant(stru_all* tete_liste, stru_all* noeud){
    stru_all* liste = tete_liste;
    if(tete_liste == NULL){
        return noeud;
    }
    if(noeud->nb_oc < tete_liste->nb_oc){
        noeud->suiv = liste;
           
        return noeud;
    }
    else{
        while(liste->suiv != NULL && liste->suiv->nb_oc < noeud->nb_oc ){
            liste = liste->suiv;
        }
        if(liste->suiv != NULL){
            noeud->suiv = liste->suiv; 
        }
        liste->suiv = noeud;
    }
    
    return tete_liste;
}

// fonction qui crée le nouveau noeud utile à l'arbre Huffman
stru_all* creenoeud(stru_all* ptr1, stru_all* ptr2){
    stru_all* noeud;
    noeud = malloc(sizeof(stru_all));
    noeud->nb_oc = ptr1->nb_oc + ptr2->nb_oc;
    noeud->suiv = NULL;
    noeud->lettre = '-';
    noeud->fg = ptr1;
    noeud->fd = ptr2;
    noeud->code = "===";
    return noeud;
}

// parcours préfixe
void prefix(stru_all* arbre){
    if(arbre != NULL){

        printf("%d ", arbre->nb_oc);
        printf("%c\n", arbre->lettre);
        prefix(arbre->fg);
        prefix(arbre->fd);
        
    }  
}

// fonction qui affiche le code binaire de chaque caractère dans le terminal
void affiche_feuille_terminal(stru_all* arbre){
    if(arbre != NULL){
        if(estFeuille(arbre)){
                printf("%c ", arbre->lettre);
                printf("%s\n", arbre->code);
                    
        }

        affiche_feuille_terminal(arbre->fg);
        affiche_feuille_terminal(arbre->fd);
        
    }
    
}

// fonction qui affiche le nouveau code binaire Huffman dans le fichier compressé 
void affiche_code_fichier(stru_all* arbre, char c, FILE* fichier2){
    if(arbre != NULL){
        if(estFeuille(arbre)){
            if(c == arbre->lettre)    
                fprintf(fichier2, "%s", arbre->code); 


        }
        affiche_code_fichier(arbre->fg, c, fichier2);
        affiche_code_fichier(arbre->fd, c, fichier2);        
    }    
}

// fonction qui affiche le code binaire de chaque caractère dans le fichier compressé
void affiche_feuille_fichier(stru_all* arbre,FILE* fichier){
    if(arbre != NULL){
        if(estFeuille(arbre)){
                    fprintf(fichier,"%c :      ", arbre->lettre);
                    fprintf(fichier,"%d                   ", arbre->nb_oc);
                    fprintf(fichier,"%s\n", arbre->code);                   
        }

        affiche_feuille_fichier(arbre->fg, fichier);
        affiche_feuille_fichier(arbre->fd, fichier);
        
    }
    
}

// fonction permettant la création de l'arbre Huffman
stru_all* arbre_huff(stru_all* tete_liste){
    stru_all* ptr1 = tete_liste;
    stru_all* ptr2 = ptr1->suiv;
    if(ptr2 == NULL){
            return ptr1;
    }
    stru_all* ptr3 = ptr2->suiv;
    stru_all* noeud = NULL;
    while (ptr2 !=NULL)
    {
        noeud = creenoeud(ptr1, ptr2);
       
        ptr1 = insertion_croissant(ptr3, noeud);
         
        ptr2 = ptr1->suiv;
        
        if(ptr2 == NULL){
            ptr3 == NULL;
        }else{
                ptr3 = ptr2->suiv; 
        }

    
       
    }
      
    
    return ptr1;
   
}

// fonction qui calcule le max pour l'affichage graphique
int max(int x1, int x2){
  if(x1>x2){
    return x1;
  }
  else{
    return x2;
  }
}


// Procédure appartenant au parcours de l'arbre permettant de concatener les caracters afin
// d'avoir une chaine de caractere pour chaque feuille representant le nouveau code de nos occurences
void AfficherTableauFichier(char** tableau, int n, stru_all* arbre)
{
    for (int i = 0 ; i < n ; i++){
                   arbre->code = strcat(arbre->code ,tableau[i] );        
           
    }
 
}

// procédure récursive permettant de récupérer le parcours de chaque caractère/feuille
// pour leur associer leur nouveau code
void ParcoursOcc( stru_all* arbre, char** tableauOcc,int emplacement)
{
  

    arbre->code = malloc(10 *sizeof(char*));
    arbre->code = calloc(10, sizeof(char*));
    // Affecte 0 au fils gauche de la racine du noeud
    if (arbre->fg) {
        tableauOcc[emplacement] = "0";
        ParcoursOcc(arbre->fg, tableauOcc, emplacement + 1);
    }
  
    // Affecte 1 au fils droit de la racine du noeud
    if (arbre->fd) {
        tableauOcc[emplacement] = "1";
        ParcoursOcc(arbre->fd, tableauOcc, emplacement + 1);
    }
  

    if (estFeuille(arbre)) {
        AfficherTableauFichier(tableauOcc, emplacement, arbre);//case actuelle ici égale à la taille du tableau
    }

    //Remarque : on note ici "arbre" ce qui relève plus d'un noeud donné de l'arbre
    //Il s'agit de la racine de l'arbre local 
}



//-------------------------------------------------------------------------------------------------------------------------------------------

// fonctions pour l'affichage graphique
stru_all* filsGauche(stru_all* a) {
    return a->fg;
}
stru_all* filsDroit(stru_all* a) {
    return a->fd;
}

int hauteur(stru_all* a) {
    if (estVide(a)) return -1;
    if (estFeuille(a)) return 0;
    return 1 + max(hauteur(filsGauche(a)), hauteur(filsDroit(a))); 
}

void ABVersTabRec(stru_all* a, int pos, TArbBin *T) {
  if (! estVide(a)) {
    T[pos].elmt = a->nb_oc;
    T[pos].equilibre = a->eq;
    T[pos].lettre = a->lettre;
    ABVersTabRec(a->fg, 2 * pos + 1, T);
    ABVersTabRec(a->fd, 2 * pos + 2, T);
}
}

TArbBin* ABVersTab(stru_all* a) {
  TArbBin *T;
  if (estVide(a)) return NULL;
  if ((T = (TArbBin *) calloc((int) pow(2, hauteur(a) + 1) - 1, sizeof(TArbBin))) == NULL) {
    puts("Erreur allocation Arbre vers Tableau");
    exit(1);
}
  ABVersTabRec(a, 0, T);
  return T;
}

void affArbreGraphique(stru_all* a) {
  TArbBin *Tarb;
  int iTarb;
  int tailleAff = 7; // noeud=" xx,xx "
  int largeur; // largeur d'affichage maximum
  int h;
  int nbNoeuds;
  int p, i, j;
  int ecart;
  puts("");
  if (estVide(a)) {
    puts("Arbre vide");
  return;
  }
  h = hauteur(a);
  largeur = tailleAff * ((int) pow(2, h)); 
  Tarb = ABVersTab(a);
  iTarb = 0;
  for (p = 0, nbNoeuds = 1; p <= h; p++, nbNoeuds *= 2) { ecart = (largeur / (nbNoeuds * 2));
    for (j = 1; j <= nbNoeuds; j++) {
      for (i = 0; i < ecart - 3; i++) putchar(' '); 
       if (Tarb[iTarb].elmt == 0)
         printf(" ..... ");
       else
          printf(" %2d,%c ", Tarb[iTarb].elmt, Tarb[iTarb].lettre);
       iTarb++;
        if (j < nbNoeuds && p < h) // entre 2 noeuds sauf au dernier niveau
        for (i = 0; i < ecart - 4; i++) putchar(' '); 
   }
  puts("");
}
free(Tarb);
puts("");
}

//-------------------------------------------------------------------------------------------------------------------------------------------



int main(void){
    // déclaration des variables
    int taille_tab = 100;
    int emplacement = 0;
    char** tableauOcc = malloc(taille_tab *sizeof(char*));
    int i;
    stru_all* arbre = NULL;
    stru_all* liste = NULL;
    FILE * fichier;
    FILE* fichier2 = NULL;
    FILE* fichier_bis = NULL;
    char x; 
    char c;



    char file_name[50];
    printf("Quelle fichier voulez vous compresser ? (ne pas oublier le .txt) \n");
    scanf("%s",file_name );

    // ouverture du fichier que l'on veut compresser
    fichier = fopen(file_name,"r");

    if(fichier == NULL){
        printf("Pas de fichier ! \n");
        exit(1);
    }
   
    // parcours caractère par caractère du fichier
    while (c != EOF){
       
        c = fgetc(fichier);
        i++;
        liste = listoc_update( liste, c );   
    }
    

    printf("voici le nombre de lettre ! \n");
    printf("%d\n", i-1);

    // suppression du dernier chainon de la liste afin d'enlever
    // le caractère de fin parasite
    liste = supp_fin(liste);
    printf("\n");

    //Si besoin d'imprimer la liste non triée
    //affiche_listoc(liste);

    // permet de trier le contenu des listes (exécuter une seule fois)
    liste = trie(liste);

    // Si besoin d'imprimer la liste triée
    //affiche_listoc(liste);

    // création de l'arbre grâce à la liste
    arbre = arbre_huff(liste);
    printf("voici la valeur de la racine ! \n");
    printf("%d\n", arbre->nb_oc);
    printf("\n");
    printf("\n");

    printf("voici le parcours prefix ! \n");

    prefix(arbre);
    printf("\n");
    printf("\n");

    // ATTENTION NE PAS UTILISER LES 2 LIGNES SUIVANTES SI LE FICHIER
    // A COMPRESSER EST LOURD (EX : harry_potter.txt)
    //printf("voici l'arbre huffman ! \n");
    //affArbreGraphique(arbre);   

    printf("\n");
    printf("\n");
    
    // procédure permettant de trouver les nouveaux codes de caractère
    ParcoursOcc(arbre, tableauOcc, emplacement );
    printf("Voici les lettres et leurs nouvelle valeur de bits\n");
    affiche_feuille_terminal(arbre);
   
    // fermeture de fichier original
    fclose(fichier); 

    // ouverture du nouveau fichier qui comportera le contenu compressé
    // réouverture du fichier original
    fichier2 = fopen("compresse.txt", "w");
    fichier_bis = fopen(file_name, "r");
  
 //----------------------------------------------------------------------------------------
    // mise en page de l'en-tête
    fprintf( fichier2,"\tHuffman code\n");
    fprintf(fichier2, "\n" );
    fprintf(fichier2,"Voici le nombre de caracteres du fichier : %d\n", i-1);
    fprintf(fichier2, "\n" );    
    fprintf(fichier2,"Lettre| ");
    fprintf(fichier2,"Nombre d'occurence | ");
    fprintf(fichier2,"code\n");
    fprintf(fichier2, "\n" );  
    
    affiche_feuille_fichier(arbre,fichier2);

  // "----------------------------------------------------------------------------------------------------------------------------\n" );

    fprintf(fichier2,"Voici le code binaire du fichier compresse :\n");
    fprintf(fichier2, "\n" );
  //----------------------------------------------------------------------------------------
    
    // boucle imprimant le nouveau code compressé en binaire
    while (x != EOF){       
        x = fgetc(fichier_bis);

        affiche_code_fichier(arbre, x, fichier2); 


    }      

    // fermeture du nouveau fichier et du fichier original
    fclose(fichier_bis);
    fclose(fichier2);
    
    // libération des malloc
    free(tableauOcc);
    free(liste);
    free(arbre);
    return 0;
}