#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>



char c, GRILLE[20][15];
int temps;
int point, f, coordonnee, sens;
void initialisegrille();
void affichegrille();
void genererpieces();
void affichepiece();
void hauteurMax();
void ecrirepiece();
void clear();
void score();
char get_key();
void rotation();
void piece_1();
void piece_2();
void piece_3();
void piece_4();
void Color (int couleurduTexte, int couleurduFond);

typedef struct{
    int hauteur;
    int largeur;
    char forme[3][3];
}piece;
piece tabpiece[4];
void Color(int couleurduTexte, int couleurduFond)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurduFond*16+couleurduTexte);
}

int main()
{

    char choix, rejouer;
    int i, touche;
    mciSendString("open \"N:\\IUT\\Tetris_v2\\Tetris.mp3\" alias mp3", NULL, 0, 0);
    mciSendString("play mp3 repeat", NULL, 0, 0);

    puts("Tapez [ENTER] pour Continuer.");

    while(getchar() != '\n')
        Sleep(50);
    printf("========   ========   ========   ========   =   ========\n");
    printf("   ==      ==            ==      ==    ==   =   ==      \n");
    printf("   ==      ========      ==      =======    =   ========\n");
    printf("   ==      ==            ==      ==    ==   =         ==\n");
    printf("   ==      ========      ==      ==    ==   =   ========\n\n");

    printf("\t=    ===  ===  ==   =  =   =  ====     \n");
    printf("\t=    = =  ===  = =  =  = = =  = == \n");
    printf("\t===  ===  = =  ==   =  =   =  ====   \n");
    printf("\n\t");
     for(i=0;i<15;i++)
            {
                Sleep(300);
                printf("%c",220);
                Sleep(300);
                printf(" ");
            }
        if (i=15)
        {
            printf("\n\n\tInstructions:");
            printf("\n\tTouche utilisees: 5");
            printf("\n\t                 1 3");
            printf("\n\t\t 1: Deplacer la piece vers la gauche");
            printf("\n\t\t 3: Deplacer la piece vers la droite");
            printf("\n\t\t 5: Rotation de la piece");
            printf("\n\n\tChoisis le niveau de difficulte : 1 - 2 - 3");
            printf("\n\n\tNiveau: ");
            scanf("%d",&touche);
        }
        switch (touche)
        {
            case 1: {printf("\n\tPetit joueur"); temps=750;}break;
            case 2: {printf("\n\tNiveau moyen, tres bon choix");temps=350;}break;
            case 3: {printf("\n\tJ'espere que tu vas t'en sortir !!");temps=50;}break;
        }
    printf("\n\n\tEs tu pret a jouer ? !!!!! (y/n)");
    scanf("%c",&choix);
    scanf("%c",&choix);
    if(choix=='y')
    {
        do
        {
            f=0;
            initialisegrille();
            do
            {
                genererpieces();
                affichegrille();
                ecrirepiece();
                hauteurMax();
                clear();
                score();
            }while(f!=1);
            printf("\n\tTu as perdu ! Ton score est de %i",point);
            printf("\n\n\tLa partie etait trop dur pour toi j'imagine !!!");
            printf("\n\n\tRecommmences tu feras peut etre mieux !!!  (y/n) ");
            scanf("%c",&rejouer);
            scanf("%c",&rejouer);
            if (rejouer=='y')
            {
               printf("\n\n\tChoisis le niveau de difficulte : 1 - 2 - 3");
                printf("\n\n\tNiveau: ");
                scanf("%d",&touche);

                switch (touche)
                {
                    case 1: {printf("\n\tPetit joueur"); temps=750;}break;
                    case 2: {printf("\n\tNiveau moyen, tres bon choix");temps=350;}break;
                    case 3: {printf("\n\tJ'espere que tu vas t'en sortir !!");temps=50;}break;
                }
                printf("\n\n\tEs tu pret a jouer ? !!!!! (y/n)");
            }
        }while(rejouer=='y');
    }
    printf("\n\n\tDommage tu t'en sortais bien !!!\n\n");

    mciSendString("stop mp3", NULL, 0, 0);
    mciSendString("close mp3", NULL, 0, 0);
    return 0;
}

void initialisegrille()
{
    int i, hr=0, lr=0;

    for(i=0;i<(319);i++)
    {
        GRILLE[hr][lr]=' ';
        if(lr<15)
        {
            lr++;
        }else
        {
            hr++;
            lr=0;
        }
    }
}

void genererpieces()
{
    int aleatoire;
    srand(time(NULL));
    aleatoire=rand()%4;
    switch (aleatoire)
    {
    case 0:
        {
            piece_1();
        }break;
    case 1:
        {
            piece_2();
        }break;
    case 2:
        {
            piece_3();
        }break;
    case 3:
        {
            piece_4();
        }break;
    }
    affichepiece();
}
void musique()
{
    PlaySound(TEXT("Tetris.wav"),NULL,SND_SYNC);
}
void affichepiece()
{
    int i;
    coordonnee=6;

    for(i=0;i<coordonnee+2;i++)
    {
        printf(" ");
    }
    for(i=0;i<3;i++)
    {
        if(tabpiece[sens].forme[2][i]=='@')
        {
            printf("%c",219);
        }else
        {
            printf(" ");
        }
    }
    printf("\n");
    for(i=0;i<coordonnee+2;i++)
    {
        printf(" ");
    }
    for(i=0;i<3;i++)
    {
        if(tabpiece[sens].forme[1][i]=='@')
        {
            printf("%c",219);
        }else
        {
            printf(" ");
        }
    }
    printf("\n");
    for(i=0;i<coordonnee+2;i++)
    {
        printf(" ");
    }
    for(i=0;i<3;i++)
    {
        if(tabpiece[sens].forme[0][i]=='@')
        {
            printf("%c",219);
        }else
        {
            printf(" ");
        }
    }
    printf("\n");
}

void affichegrille()
{
    int i, ha, la;

    for(ha=0;ha<20;ha++)
    {
        printf("%c%c",204,185);
        for(la=0;la<15;la++)
        {
            printf("%c",GRILLE[ha][la]);
        }
        printf("%c%c",204,185);
        printf("\n");
    }

    for(i=0;i<9;i++)
    {
        printf("%c%c",204,185);
    }
    printf("%c",185);
}


void hauteurMax()
{
    int i;
    for(i=1;i<15;i++)
    {
        if(GRILLE[0][i]!=' ')
        {
            f=1;
        }
    }
}

void ecrirepiece()
{
    int l=2, i;
    int fin=0;
    sens=0;

    do
    {
        for(i=0;i<3;i++)
        {
            if(tabpiece[sens].forme[0][i]=='@')
            {
                GRILLE[l-1][coordonnee+i]=' ';
            }
            if(tabpiece[sens].forme[1][i]=='@')
            {
                GRILLE[l-2][coordonnee+i]=' ';
            }
            if(tabpiece[sens].forme[2][i]=='@')
            {
               GRILLE[l-3][coordonnee+i]=' ';
            }
        }
        get_key();
        for(i=0;i<3;i++)
        {
            if (GRILLE[l][coordonnee+i]!=' ')
            {
                if(tabpiece[sens].forme[0][i]=='@')
                {
                    i--;
                    l--;
                    fin=1;
                }else if(tabpiece[sens].forme[1][i]=='@')
                {
                    fin=1;
                }else if(tabpiece[sens].forme[2][i]=='@')
                {
                    fin=1;
                }
            }
        }
        for(i=0;i<3;i++)
        {
            if(tabpiece[sens].forme[0][i]=='@')
            {
                GRILLE[l][coordonnee+i]=219;
            }
            if(tabpiece[sens].forme[1][i]=='@')
            {
                GRILLE[l-1][coordonnee+i]=219;
            }
            if(tabpiece[sens].forme[2][i]=='@')
            {
                GRILLE[l-2][coordonnee+i]=219;
            }
        }
        l++;
        Sleep(temps);
        clear();
        printf("\n\n\n");
        affichegrille();
    }while((fin==0)&&(l !=21));
    point=point+10;
}


void score()
{
    int i, j, k, l, ligne=0;

    for(j=0;j<15;j++)
    {
        if(GRILLE[i][j]!=' ')
        {
            ligne++;
        }
    }
    if(ligne==15)
    {
        for(j=0;j<15;j++)
        {
        GRILLE[i][j]=' ';
        }
        point++;
    }
    ligne=0;
    for(i=1;i<20;i++)
    {
        for(j=0;j<15;j++)
        {
            if(GRILLE[i][j]!=' ')
            {
                ligne++;
            }
        }
        if(ligne==15)
        {
            for(j=0;j<15;j++)
            {
                for(k=i;k>0;k--)
                {
                    GRILLE[k][j]=GRILLE[k-1][j];
                }
            }

            point=point+100;
        }
        ligne=0;
    }
}

char get_key()
{


        c = '0';
        while (_kbhit())
        {
            c = _getch();
        }
        switch (c)
        {
            case '1':
                {
                    coordonnee--;
                    if (coordonnee==-1)
                    {
                        coordonnee=12;
                    }
                }break;
            case '3':
                {
                    coordonnee++;
                    if (coordonnee==13)
                    {
                        coordonnee=0;
                    }
                }break;
            case '5':
                {
                    rotation();
                }break;
        }
}

void rotation()
{
    if (sens<3)
    {
        sens++;
    }else
    {
        sens=0;
    }
}

void piece_1()
{
    int i=0;

    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]=' ';
    tabpiece[i].forme[2][1]=' ';
    tabpiece[i].forme[2][2]=' ';
    tabpiece[i].forme[1][0]=' ';
    tabpiece[i].forme[1][1]='@';
    tabpiece[i].forme[1][2]=' ';
    tabpiece[i].forme[0][0]='@';
    tabpiece[i].forme[0][1]='@';
    tabpiece[i].forme[0][2]='@';
    i++;
    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]='@';
    tabpiece[i].forme[2][1]=' ';
    tabpiece[i].forme[2][2]=' ';
    tabpiece[i].forme[1][0]='@';
    tabpiece[i].forme[1][1]='@';
    tabpiece[i].forme[1][2]=' ';
    tabpiece[i].forme[0][0]='@';
    tabpiece[i].forme[0][1]=' ';
    tabpiece[i].forme[0][2]=' ';
    i++;
    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]=' ';
    tabpiece[i].forme[2][1]=' ';
    tabpiece[i].forme[2][2]=' ';
    tabpiece[i].forme[1][0]='@';
    tabpiece[i].forme[1][1]='@';
    tabpiece[i].forme[1][2]='@';
    tabpiece[i].forme[0][0]=' ';
    tabpiece[i].forme[0][1]='@';
    tabpiece[i].forme[0][2]=' ';
    i++;
    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]=' ';
    tabpiece[i].forme[2][1]=' ';
    tabpiece[i].forme[2][2]='@';
    tabpiece[i].forme[1][0]=' ';
    tabpiece[i].forme[1][1]='@';
    tabpiece[i].forme[1][2]='@';
    tabpiece[i].forme[0][0]=' ';
    tabpiece[i].forme[0][1]=' ';
    tabpiece[i].forme[0][2]='@';
    Color(12,0);
}

void piece_2()
{
    int i=0;

    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]=' ';
    tabpiece[i].forme[2][1]=' ';
    tabpiece[i].forme[2][2]=' ';
    tabpiece[i].forme[1][0]=' ';
    tabpiece[i].forme[1][1]=' ';
    tabpiece[i].forme[1][2]='@';
    tabpiece[i].forme[0][0]='@';
    tabpiece[i].forme[0][1]='@';
    tabpiece[i].forme[0][2]='@';
    i++;
    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]='@';
    tabpiece[i].forme[2][1]=' ';
    tabpiece[i].forme[2][2]=' ';
    tabpiece[i].forme[1][0]='@';
    tabpiece[i].forme[1][1]=' ';
    tabpiece[i].forme[1][2]=' ';
    tabpiece[i].forme[0][0]='@';
    tabpiece[i].forme[0][1]='@';
    tabpiece[i].forme[0][2]=' ';
    i++;
    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]=' ';
    tabpiece[i].forme[2][1]=' ';
    tabpiece[i].forme[2][2]=' ';
    tabpiece[i].forme[1][0]='@';
    tabpiece[i].forme[1][1]='@';
    tabpiece[i].forme[1][2]='@';
    tabpiece[i].forme[0][0]='@';
    tabpiece[i].forme[0][1]=' ';
    tabpiece[i].forme[0][2]=' ';
    i++;
    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]=' ';
    tabpiece[i].forme[2][1]='@';
    tabpiece[i].forme[2][2]='@';
    tabpiece[i].forme[1][0]=' ';
    tabpiece[i].forme[1][1]=' ';
    tabpiece[i].forme[1][2]='@';
    tabpiece[i].forme[0][0]=' ';
    tabpiece[i].forme[0][1]=' ';
    tabpiece[i].forme[0][2]='@';
    Color(14,0);
}

void piece_3()
{
    int i=0;

    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]=' ';
    tabpiece[i].forme[2][1]=' ';
    tabpiece[i].forme[2][2]=' ';
    tabpiece[i].forme[1][0]='@';
    tabpiece[i].forme[1][1]='@';
    tabpiece[i].forme[1][2]=' ';
    tabpiece[i].forme[0][0]=' ';
    tabpiece[i].forme[0][1]='@';
    tabpiece[i].forme[0][2]='@';
    i++;
    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]=' ';
    tabpiece[i].forme[2][1]='@';
    tabpiece[i].forme[2][2]=' ';
    tabpiece[i].forme[1][0]='@';
    tabpiece[i].forme[1][1]='@';
    tabpiece[i].forme[1][2]=' ';
    tabpiece[i].forme[0][0]='@';
    tabpiece[i].forme[0][1]=' ';
    tabpiece[i].forme[0][2]=' ';
    i++;
    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]='@';
    tabpiece[i].forme[2][1]='@';
    tabpiece[i].forme[2][2]=' ';
    tabpiece[i].forme[1][0]=' ';
    tabpiece[i].forme[1][1]='@';
    tabpiece[i].forme[1][2]='@';
    tabpiece[i].forme[0][0]=' ';
    tabpiece[i].forme[0][1]=' ';
    tabpiece[i].forme[0][2]=' ';
    i++;
    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]=' ';
    tabpiece[i].forme[2][1]=' ';
    tabpiece[i].forme[2][2]='@';
    tabpiece[i].forme[1][0]=' ';
    tabpiece[i].forme[1][1]='@';
    tabpiece[i].forme[1][2]='@';
    tabpiece[i].forme[0][0]=' ';
    tabpiece[i].forme[0][1]='@';
    tabpiece[i].forme[0][2]=' ';
    Color(9,0);
}

void piece_4()
{
    int i=0;
    Color(10,0);
    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]='@';
    tabpiece[i].forme[2][1]=' ';
    tabpiece[i].forme[2][2]=' ';
    tabpiece[i].forme[1][0]='@';
    tabpiece[i].forme[1][1]=' ';
    tabpiece[i].forme[1][2]=' ';
    tabpiece[i].forme[0][0]='@';
    tabpiece[i].forme[0][1]=' ';
    tabpiece[i].forme[0][2]=' ';
    i++;
    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]=' ';
    tabpiece[i].forme[2][1]=' ';
    tabpiece[i].forme[2][2]=' ';
    tabpiece[i].forme[1][0]='@';
    tabpiece[i].forme[1][1]='@';
    tabpiece[i].forme[1][2]='@';
    tabpiece[i].forme[0][0]=' ';
    tabpiece[i].forme[0][1]=' ';
    tabpiece[i].forme[0][2]=' ';
    i++;
    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]=' ';
    tabpiece[i].forme[2][1]=' ';
    tabpiece[i].forme[2][2]='@';
    tabpiece[i].forme[1][0]=' ';
    tabpiece[i].forme[1][1]=' ';
    tabpiece[i].forme[1][2]='@';
    tabpiece[i].forme[0][0]=' ';
    tabpiece[i].forme[0][1]=' ';
    tabpiece[i].forme[0][2]='@';
    i++;
    tabpiece[i].hauteur = 3;
    tabpiece[i].largeur = 3;
    tabpiece[i].forme[2][0]=' ';
    tabpiece[i].forme[2][1]=' ';
    tabpiece[i].forme[2][2]=' ';
    tabpiece[i].forme[1][0]='@';
    tabpiece[i].forme[1][1]='@';
    tabpiece[i].forme[1][2]='@';
    tabpiece[i].forme[0][0]=' ';
    tabpiece[i].forme[0][1]=' ';
    tabpiece[i].forme[0][2]=' ';
}

void clear()
{
    HANDLE handle;
    COORD coord= { 0, 0 };
    DWORD nbcar;
    CONSOLE_SCREEN_BUFFER_INFO info;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle,&info);
    FillConsoleOutputCharacter(handle, (TCHAR) ' ',info.dwSize.X *
                               info.dwSize.Y,coord,&nbcar);
    SetConsoleCursorPosition(handle,coord);
}
