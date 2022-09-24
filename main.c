#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

typedef struct player {
    char name[100];
    int is_IA;
    int level;
} Player;

typedef struct boardgame {
    int nb_allumettes;
    int nb_allumettes_max;
    int nb_allumettes_min;
    int nb_joueurs;
    Player joueur1;
    Player joueur2;
} BoardGame;

//check if the input is a number
int isNumber(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (!isdigit(str[i])) {
            return 0;
        }
        i++;
    }
    return 1;
}

void secure_scanf(char *format, void *value) {
    scanf("%*c");
    scanf(format, value);
}

/**
 * @brief Show th game menu
 * 
 * @return [int] the choice of the user
 */

int menu(){
    int choice;
    printf("1. Jouer\n");
    printf("2. Voir les regles du jeu\n");
    printf("3. Voir les credits\n");
    printf("4. Quitter\n");
    do
    {
        printf("Votre choix : ");
        fflush( stdin );
        choice = getchar() - 48;        
    }
    while(choice<1 || choice>4);
    return choice;
}

int menu_Rules(){
    int choice;
        printf("1. Jouer\n");
        printf("2. Voir les credits\n");
        printf("3. Quitter\n");
        do{   
            fflush( stdin );
            choice = getchar() - 48;  
        } while(choice<1 || choice>3);
    return choice;
}

int menu_Credit(){
    int choice;
    printf("1. Jouer\n");
    printf("2. Voir les regles du jeu\n");
    printf("3. Quitter\n");
    do{
        fflush( stdin );
        choice = getchar() - 48;  
  
    }
    while(choice<1 || choice>3);
    return choice;
}

int menu_IA(){
    int choice;
    printf("1. Niveau naif\n");
    printf("2. Niveau expert \n");
    do{
        fflush( stdin );
        choice = getchar() - 48;  
    }
    while(choice<1 || choice>2);
    return choice;
}



int show_Result(char *player){
    printf("%s a gagne\n", player);
    return 0;
}

int gameIntroduction(){
    printf("                            **********************\n");
    printf("                            * Jeu des allumettes *\n");
    printf("                            **********************\n\n\n\n");


    printf("               Bonjour et bienvenue dans le jeu des allumettes\n\n");
    
    printf("Vous allez avoir 3 menus.\n");
    printf("Vous choisirez d abord si vous voulez voir les regles du jeu ou non, puis le \nnombre d allumettes a utiliser, et enfin le nombre de joueur.\n");
    
    printf("       Que faire ?\n");
    return 0;   
}

int showCredits(){
    printf("Jeu des allumettes realise par Timotei GERANTE (timotei.gerante@efrei.net) et Alexis Bozel (alexis.bozel@efrei.net) \n");
}

/**
 * @brief Show game rules
 * 
 */
int showRules() 
{
    printf("Le but du jeu est simple: \n");
    printf("Ce jeu se joue a deux. Vous avez un nombre n d'allumettes.\n");
    printf("A tour de role, chacun des deux joueurs enleve entre 1 et 3 allumettes selon ce qui'il souhate. le perdant est celui qui doit\n");
    printf("Enlever la derniere allumette. \n");
    printf("\n");
    printf("Attention, il existe 3 niveaux de dificulte en version humain vs ORDI.\n");
    printf("Le premier est plutot simple a battre, donc pour les débutans. Mais le dernier ....\n");
    printf("Contactez-moi si vous avez reussi (screenshot evidemment ^^ ), mon e-mail est dans les credits !\n");
    return 0;
}

int showAllumettes(int nb_allumettes_restantes){
    int i;      

    for(i=0; i < nb_allumettes_restantes; i++){
        printf("| ");
    }
    printf("        Il reste %d allumettes\n\n", nb_allumettes_restantes);
    return 0;
}

//initialize the game 
int initGame(BoardGame *game, int nb_allumettes, int nb_allumettes_max, int nb_allumettes_min,int nb_joueurs){
    game->nb_allumettes = nb_allumettes;
    game->nb_allumettes_max = nb_allumettes_max;
    game->nb_allumettes_min = nb_allumettes_min;
    game->nb_joueurs = nb_joueurs;
    showAllumettes(game -> nb_allumettes);
    return 0;
}


//random number generator between  1 - 3
int random_number(int min_num, int max_num){
    int result=0,low_num=0,hi_num=0;
    if(min_num<max_num){
        low_num=min_num;
        hi_num=max_num+1; // this is done to include max_num in output.
    }else{
        low_num=max_num+1;// this is done to include max_num in output.
        hi_num=min_num;
    }
    srand(time(NULL));
    result = (rand()%(hi_num-low_num))+low_num;
    return result;
}

int jouer(BoardGame *game,Player player){
   int nb_allumettes;
    // int playerReponse;
    do{
        nb_allumettes = 0;
        //print is IA or not
        if(player.is_IA == 1){
            printf("C'est au tour de l'IA de jouer\n");
        }else{
            printf("C'est au tour de %s de jouer\n", player.name);
        }

        if(player.is_IA){
            if(player.level == 1){
    
                nb_allumettes = random_number(1,game->nb_allumettes < 3 ? game->nb_allumettes: 3);
            }else{
                int rand = game->nb_allumettes % 4;
                nb_allumettes = rand == 0 ? 1: rand;
            }
            printf("L'ordinateur a pris %d allumettes\n", nb_allumettes);
        }else{
            printf("%s, combien d'allumettes voulez-vous prendre ? (entre %d et %d) : ", player.name, game->nb_allumettes_min, game->nb_allumettes_max); 
            fflush( stdin );
            nb_allumettes = getchar() - 48;
            printf("Vous avez pris %d allumettes\n", nb_allumettes);
        }  
    }while( nb_allumettes < game->nb_allumettes_min || nb_allumettes > game->nb_allumettes_max);
    game->nb_allumettes -= nb_allumettes;
    if(game->nb_allumettes <= 0){
       show_Result(player.name);
        return 0;
    }showAllumettes(game->nb_allumettes);
    return 1;
}




int initializePlayers(BoardGame* game){
    // ask if the game is with IA
    int is_IA = 0;
    printf("Voulez-vous jouer contre l'ordinateur ? (1 = oui, 0 = non) ");
    fflush(stdin);
    is_IA = getchar() - 48;
    Player *joueur1 = (Player *) malloc(sizeof(Player)), *joueur2 = (Player *) malloc(sizeof(Player));

    if(is_IA){
        joueur1->is_IA = 0;
        printf("Quel est votre nom ? ");  
        scanf("%s", joueur1->name);
        joueur2->is_IA = 1;
        joueur2->level = menu_IA();
        strcpy(joueur2->name, "Ordinateur");
    }else{
        joueur1->is_IA = 0;
        printf("Quel est le nom du joueur 1 ? ");
        scanf("%s", joueur1->name);
        joueur2->is_IA = 0;
        printf("Quel est le nom du joueur 2 ? ");
        scanf("%s", joueur2->name);
    }
    game->joueur1 = *joueur1;
    game->joueur2 = *joueur2;
    //print names 
    printf("Joueur 1 : %s\n", game->joueur1.name);
    printf("Joueur 2 : %s\n", game->joueur2.name);
    initGame(game, 10, 3, 1, 2);
}
int main(){
   
    gameIntroduction(); //show the introduction
    int choice = -1;
    do {
        choice = menu(); //show the menu    
    switch(choice){
        case 1:
            printf("Vous avez choisi de jouer\n");
            BoardGame *game = (BoardGame *) malloc (sizeof(BoardGame)); //create a game
            initializePlayers(game); //initialize the players
            while(jouer(game,game->joueur1) && jouer(game, game->joueur2));
            break;
        case 2:
            printf("Vous avez choisi de voir les regles du jeu\n");
            showRules();
            break;
        case 3:
            printf("Vous avez choisi de voir les credits\n");
            showCredits();
            break;
        case 4:
            printf("Vous avez choisi de quitter\n");
            break;
        default:
            printf("Erreur\n");
            break;
    }
    }while(choice!=4);
    
    return 0;
}
