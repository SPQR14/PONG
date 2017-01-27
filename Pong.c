/*
*   Pico Lara Alberto Isaac 05/ Julio / 2015.
*   juego de pong.
*/

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define X 76
#define Y 22

int i, j;

void Campo(char campo [Y] [X], int pelX, int pelY, int inij, int finj, int inipc, int finpc);
void Frontera(char campo[Y][X]);
void RaquetaJ(char campo[Y][X], int inij, int finj);
void RaquetaPC(char campo[Y][X], int inipc, int finpc);
void Pelota(char campo[Y][X], int pelX, int pelY);
void Dibuja(char campo[Y][X]);
void Motor(char campo [Y] [X], int pelX, int pelY, int inij, int finj, int inipc, int finpc, int modX, int modY, int modpc);
void Dibuja1(char campo[Y][X]);
void Entrada(char campo [Y] [X], int *pelX, int *pelY, int *inij, int *finj, int *inipc, int *finpc, int *modX, int *modY, int *modpc, int *gol);

int main(void)
{
    system("title PONG");
    system("color f0");
    int pelX, pelY, inij, finj, inipc, finpc; // Posicion
    pelX = 38;
    pelY = 10;
    inij = 8;
    finj = 12;
    inipc = 8;
    finpc = 12;
    int modX, modY, modpc; // modificacion;
    modX = -1;
    modY = -1;
    modpc = -1;
    char campo[Y] [X];
    Campo(campo, pelX, pelY, inij, finj, inipc, finpc);
    Motor(campo, pelX, pelY, inij, finj, inipc, finpc, modX, modY, modpc);
    system( "pause" );
    return 0;
}

void Campo(char campo [Y] [X], int pelX, int pelY, int inij, int finj, int inipc, int finpc)
{
    Frontera(campo);
    RaquetaJ(campo, inij, finj);
    RaquetaPC(campo, inipc, finpc);
    Pelota(campo, pelX, pelY);
}

void Frontera(char campo[Y][X])
{
    for( i = 0; i < Y; i++ )
    {
        for( j = 0; j < X; j++ )
        {
            if( i == 0 || i == Y-1 )
            {
                campo[i][j] = '-';
            }else if( j == 0 || j == X-1 )
            {
                campo[i][j] = '|';
            }
            else
            {
                campo[i][j] = ' ';
            }
        }
    }
}

void RaquetaJ(char campo[Y][X], int inij, int finj)
{
    for( i = inij; i <= finj; i++ )
    {
        for( j = 2; j <= 3; j++ )
        {
            campo[i][j] = 'X';
        }
    }
}

void RaquetaPC(char campo[Y][X], int inipc, int finpc)
{
    for( i = inipc; i <= finpc; i++ )
    {
        for( j = X-4; j <= X-3; j++ )
        {
            campo[i][j] = 'X';
        }
    }
}

void Pelota(char campo[Y][X], int pelX, int pelY)
{
    campo[pelY][pelX] = 'O';
}

void Dibuja(char campo[Y][X])
{
    for(i = 0; i < Y; i++)
    {
        for(j = 0; j < X; j++)
        {
            printf("%c", campo[i][j]);
        }
        printf("\n");
    }
}

void Motor(char campo [Y] [X], int pelX, int pelY, int inij, int finj, int inipc, int finpc, int modX, int modY, int modpc)
{
    int gol = 0;
    do{
        Dibuja1(campo);
        Entrada(campo, &pelX, &pelY, &inij, &finj, &inipc, &finpc, &modX, &modY, &modpc, &gol);
        Campo(campo, pelX,  pelY, inij, finj, inipc, finpc);
        Sleep(20);
    }while(gol < 1);
}

void Dibuja1(char campo[Y][X])
{
    system("cls");
    Dibuja(campo);
}

void Entrada(char campo [Y] [X], int *pelX, int *pelY, int *inij, int *finj, int *inipc, int *finpc, int *modX, int *modY, int *modpc, int *gol)
{
    int motor = 0;
    char tecla;
    //Verficación
    if( *pelY == 1 || *pelY == Y - 2 )
    {
        *modY *= -1;
    }

    if( (*pelX) == 1 || (*pelX) == X - 2 )
    {
        *gol = 1;
    }

    if( *pelX == 4 )
    {
        for(motor = (*inij); motor <= (*finj); motor++)
        {
            if( motor == *pelY )
            {
                (*modX) *= -1;
            }
        }
    }

    if( *pelX == X - 5 )
    {
        for( motor == (*inipc); motor <= (*finpc); motor++)
        {
            if(motor == (*pelY))
            {
                (*modX) *= 1;
            }
        }
    }

    if( (*inipc) == 1 || (*finpc) == Y - 1 )
    {
        *modpc *= -1;
    }

    //Modificacioń
    if( *gol <= 4 )
    {
        //pelota
        *pelX += (*modX);
        *pelY += (*modY);
        //PC
        *inipc += (*modpc);
        *finpc += (*modpc);
        //jugador
        if( kbhit() == 1 )
        {
            tecla = getch();
            if( tecla == 'w')
            {
                if( *inij != 1)
                {
                    *inij -= 1;
                    *finj -= 1;
                }
            }
            if(tecla == 's' )
            {
                if( *finj != Y - 2 )
                {
                    *inij += 1;
                    *finj += 1;
                }
            }
        }
    }
}
