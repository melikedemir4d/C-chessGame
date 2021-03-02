/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void initializeTheBoard(char **, int, int);
void printScreen(char **, int, int);
void play(char **, int *);
int canMove(char **, int, int, int, int, int);
int pawnMove(char **, int, int, int, int, int);
int destinationCheck(char, int);
int isGameOver(char **, int, int);
int castleMove (char **, int, int, int,int);
int horseMove(char **,int ,int,int,int);
int elephantMove(char **,int, int, int, int);
int pawnToQueen  (char **, int, int , int, int);
int kingMove (char **, int , int , int ,int,int);

#define HEIGTH 8
#define WIDTH 8

int main()
{
    char **arr;
    int  i = 0, turn = 0, gameOver=0, sRow, eRow, sCol, eCol;
    char destPiece;
    

    //hafızadan alan al
    arr = malloc(sizeof(char *) * HEIGTH);
    for(; i<HEIGTH; i++)
    {
        arr[i] = malloc(sizeof(char) * WIDTH);
    }
    //tahtaya ilk halini ver
    //initializeTheBoard(arr, HEIGTH, WIDTH);
    initializeTheBoard(arr, HEIGTH, WIDTH);

    do
    {
        printScreen(arr, HEIGTH, WIDTH);
        play(arr, &turn);
    }while( (gameOver=isGameOver(arr, HEIGTH, WIDTH)) == 0);

    printf("%d player wins!", gameOver);
    //hafizayi geri bırak
    for(i=0;i<5;i++)
    {
        free(arr[i]);
    }
    free(arr);

    return 0;
}

//kullanıcıların ikisinin de sah tası mevcut mu
//eger oyleyse return 0
//eger 0. oyuncunun tasi yoksa 1 dondur
//eger 1. oyuncunun tasi yoksa 2 dondur
int isGameOver(char ** arr, int nRows, int nCols)
{       
     //char piece = arr[nRows][nCols];
    
    int tempS = 0, temps = 0;
    for (int i=0; i<=7;i++)
    {
        for(int j=0;j<=7;j++)
        {
            if(arr[i][j] == 'S')
            {
               tempS++;     
            }
            else if(arr[i][j] == 's')
            {
               temps++;     
            }
        }
    }
    if(tempS == 1 && temps == 1)
        return 0;
    else if (tempS == 0)
        return 2;
    else if(temps == 0)
        return 1;
}
//hareket edilecek hedef noktasindaki tas kimin
//eger siranin kendisindeki oyuncunun ise 0
//degilse 1 dondur
int destinationCheck(char destPiece, int turn)
{
    //turn 0 ise
    if ( (destPiece >= 'A' && destPiece <= 'Z') && turn == 0)
    {
        return 0;
    }
    //turn 1 ise
    if ( (destPiece >= 'a' && destPiece <= 'z') && turn == 1)
    {
        return 0;
    }
    return 1;
}
//piyon hareketi. hareket gecerliyse 1 degilse 0 dondurur
int pawnMove(char **arr, int sRow, int sCol, int eRow, int eCol, int direction)
{
    //hareket duz ise ilgili alan bos mu?
    if (eRow == sRow + direction && sCol == eCol)
    {
        if(arr[eRow][eCol] == ' ')
        {
            return 1;
        }
    }
    //hareket capraz ise hedef alan bos olmamalı
    else if (
              eRow == sRow + direction &&
              ( (sCol == eCol+1) || (sCol == eCol-1) )
             )
    {

        if (arr[eRow][eCol] != ' ')
        {
            return 1;
        }
    }
    //buraya ulastıysa yukaridaki returnlere ulasamamistir o yuzden 0 dondur
    return 0;
}

int horseMove ( char **arr , int sRow, int sCol, int eRow, int eCol)
{
    if (( (eRow == sRow +2 || eRow == sRow -2 ) && (eCol == sCol +1 || eCol == sCol -1 ) )
    || ( (eRow == sRow +1 || eRow == sRow -1 ) && (eCol == sCol +2 || eCol == sCol -2 ) ) )
    
        return 1;

else {
   return 0;
   }
}
 int castleMove ( char **arr, int sRow, int sCol, int eRow, int eCol)
{
  if(eRow==sRow)
   {
       if(eCol>sCol)
    {
        for(int i=sCol+1;i<eCol;i++)
            {
                if(arr[eRow][i]!= ' ') 
                return 0;

            } 
             return 1;
            }
    else if (eCol<sCol)
    {
        for(int i=eCol+1;i<sCol;i++)
        {
             if(arr[eRow][i]!= ' ')
                return 0;
                 }
       
                return 1;
    }
}
else if(eCol==sCol)
   {
       if(eRow>sRow)
           { for(int i=sRow+1;i<eRow;i++)
           {
               if(arr[i][eCol]!= ' ')
               return 0;

           }
           return 1;
           }
    else if(eRow<sRow)
           { for(int i=eRow+1;i<sRow;i++)
           {
               if(arr[i][eCol]!= ' ')
               return 0; 
           }
                return 1;

           }
            else 
                return 1;


   }
  return 0;     
}

int elephantMove (char **arr, int sRow, int eRow, int sCol, int eCol)
{
    int j;
    
    if ( (abs(sRow - eRow)) == (abs (sCol - eCol)) )
    {

            if((sRow > eRow) && (sCol > eCol))//azalan azalan
            {for (int i=sRow+1,j=sCol+1; i<eRow && i<eCol; i--,j--)
                if(arr[i][j]!= ' ')
                return 0;
            }
            else
            return 1;


        if ((sRow > eRow) && (sCol < eCol))// azalan artan

            {for (int i=sRow +1 , j=sCol+1; i>eRow && j>eCol;i--,j++)
             if(arr[i][j]!=' ')
             return 0;
    }
             else
            return 1;
         
        if ((sRow < eRow) && (sCol < eCol))// artan artan
            {for (int i=sRow+1,j=sCol+1;i<eRow && j<eCol;i++,j++)
                if(arr[i][j] != ' ')
                return 0;
    }
                else
            return 1;
               

        if ((sRow < eRow ) && (sCol > eCol ))//artan azalan
        {for(int i=sRow+1, j=sCol+1; i<eRow && j<eCol; i++, j--)
            if(arr [i][j] != ' ')
            return 0; 
        }
            else
            return 1;
            
    } 
    return 0;
}

int kingMove (char **arr, int sRow, int eRow, int sCol,int eCol,int direction)
{ 
    if (sCol == eCol )
    {
        if(eRow = sRow + direction )
            if( (arr [eRow] [eCol]== ' ')|| (arr [eRow] [eCol]!= ' '))
        return 1;
        else
        return 0;
    }
    else if (eRow == sRow)
    {
        if(eRow = sRow + direction )
            if( (arr [eRow] [eCol]== ' ')|| (arr [eRow] [eCol]!= ' '))
        return 1;
        else
        return 0;
    }

        else if (eRow == sRow + 1 &&((sCol == eCol+1) || (sCol == eCol-1) ))
        {
            if((arr[eRow][eCol]==' ') ||(arr[eRow][eCol]!=' '))
            return 1;
            else 
            return 0;


        }
        else if (eRow == sRow -1  &&((sCol == eCol+1) || (sCol == eCol-1) ))
        {
            if((arr[eRow][eCol]==' ') ||(arr[eRow][eCol]!=' '))
            return 1;
            else 
            return 0;

        }
              
    return 0;

}
                
        
//tasın cinsine göre her tasi kontrol et fonksiyonlarını yaz
//destinationCheck fonksiyonu yukarıda yazılmıs ve hedef olarak gideceginiz
//noktadaki tasin kimin olduğuna bakar. Eğer sıranın kendindeki oyuncunun tası
//ise 0 dondurur. Değilse 1 dondurur. Boylece hem hareket fonksyionunda
//gelen deger 1 hem de destinationCheck fonksiyonundan donen deger 1 ise
//canMove fonksiyonu 1 dondurur. && ile bu durum kontrol edilebilir
int canMove(char **arr, int turn, int sRow, int sCol, int eRow, int eCol)
{
    char piece = arr[sRow][sCol];

    if (piece == 'P')
    {
       return pawnMove(arr, sRow, sCol, eRow, eCol, 1) && destinationCheck(arr[eRow][eCol], turn);
    }
    else if ( piece == 'p')
    {
       return pawnMove(arr, sRow, sCol, eRow, eCol, -1) && destinationCheck(arr[eRow][eCol], turn);
    }
    //buradan sonrası her tas icin fonksiyon yazacaksınız
    //fil hareketi icin yaz
    else if (piece == 'F' || piece == 'f')
    {
       return elephantMove(arr , sRow, eRow, sCol, eCol ) && destinationCheck(arr[eRow][eCol], turn);
    }
    //at hareketi icin yaz
    else if (piece == 'A' || piece == 'a')
    {
        return horseMove (arr, sRow, sCol, eRow , eCol ) && destinationCheck(arr[eRow][eCol], turn);
    }
    //kale icin yaz
    else if (piece == 'K' || piece == 'k')
    {
       return castleMove (arr, sRow,  sCol, eRow, eCol ) && destinationCheck (arr[eRow][eCol], turn);
    }
    //vezir icin yaz
    else if (piece == 'V' || piece == 'v')
    {
        return  ( castleMove (arr, sRow,  sCol, eRow, eCol ) || elephantMove(arr , sRow, eRow, sCol, eCol ) )
        && destinationCheck (arr[eRow][eCol], turn);
    }
    //sah icin yaz
    else if (piece == 'S') //veya else if (piece == 'S' || piece == 's') yazabilirsiniz
    {
        return ( kingMove (arr, sRow,eRow,sCol,eCol,+1) && destinationCheck (arr[eRow][eCol], turn) );
    }
    else if (piece == 's')
    {
        return ( kingMove (arr, sRow,eRow,sCol,eCol,-1) && destinationCheck (arr[eRow][eCol], turn) );
    }
    //yukarıdaki kodlar yazıldığında buraya ulasamaz ama su anki halinde warning almamak icin yazıldı.
    //Tum kodu yazınca silebilirsiniz.
    return 0;

}

void play(char **arr, int *turn)
{
    char *sMove, *eMove;
    int sRow, sCol, eRow, eCol;
    sMove = malloc(sizeof(char) * 3);
    eMove = malloc(sizeof(char) * 3);
    do
    {
        printf("%d. player turn: ", *turn+1);
        scanf("%2s %2s", sMove, eMove);
        fflush(stdin);
        sRow = (int)(sMove[0] - 'A');
        sCol = (int)(sMove[1] - '1');
        eRow = (int)(eMove[0] - 'A');
        eCol = (int)(eMove[1] - '1');
        if(
            (sRow >= 0 && sRow <= 7) &&
            (sCol >= 0 && sCol <= 7) &&
            (eCol >= 0 && eCol <= 7) &&
            (eRow >= 0 && eRow <= 7)
           )
        {
            char piece = arr[sRow][sCol];
            //secilen tas sırası gelen kullanıcının mı
            if (
                 ( *turn == 0 && (piece >= 'A' && piece <= 'Z') )
                  ||
                 ( *turn == 1 && (piece >= 'a' && piece <= 'z') )
               )
            {
                //secilen tas hedef konuma gidebilir mi
                if( canMove(arr, *turn, sRow, sCol, eRow, eCol) == 1 )
                {
                   
                    arr[eRow][eCol] = piece;
                    arr[sRow][sCol] = ' ';
                    *turn = (*turn + 1) % 2;
                    if ( pawnToQueen(arr, sCol, eCol, sRow, eRow) )
                    {
                        arr[eRow][eCol] += 6;
                    }
                    break;
                }
                //eger gidemiyorsa illegal move
                else
                {
                    printf("Illegal move. Try again.\n");
                }

            }
            //secilen tas kullanıcının degil
            else
            {
                printf("It's your opponent's piece\n");
            }
        }
        //istenen konumlar aralıkta girilmemis
        else
        {
            printf("Your move is out of boundary\n");
        }
    }while(1);//dogru hareket yapılana kadar devam eder. Dogru hareket yapıldıysa
              //yukarıdaki break bu while kosulunu kırar ve cıkılır.
}
//dizi iceriklerini ekrana yaz.
//her bir tas bir karenin icine girsin diye
//bir kac duzenleme yapildi
void printScreen(char ** arr, int nRows, int nCols)
{

    //ekranı her seferinde silip tekrar yazmak isterseniz.
    //aşagıdaki komutu aciniz
    system("@cls||clear");

    int i, j;

    printf("%s", " |");
    for(j=0;j<nCols;)
    {
        printf("  %d  |", ++j);
    }

    printf("\n--");

    for(j=0;j<nCols;j++)
    {
        printf("%s", "------");
    }

    printf("\n");

    for(i=0;i<nRows;i++)
    {
        printf("%c|", 'A'+i);

        for(j=0;j<nCols;j++)
        {
            printf("  %c  |", arr[i][j]);
        }

        printf("\n--");

        for(j=0;j<nCols;j++)
        {
            printf("%s", "------");
        }
        printf("\n");
    }
}

/*void testTheBoard(char **arr, int nRows, int nCols)
{
    int i, j;
    for(i=0;i<nRows;i++)
    {
        for(j=0;j<nCols;j++)
            arr[i][j] = ' ';
    }
    for(j=0;j<nCols;j++)
    {
        arr[1][j] = 'p';
        arr[6][j] = 'P';
    }
}
*/

//arrayın içinde ki başlangıc degerlerini belirler.
//ekrana yazmaz.
void initializeTheBoard(char **arr, int nRows, int nCols)
{
    int i, j;
    for(i=0;i<nRows-2;i++)
    {
        for(j=0;j<nCols;j++)
        {
            if (i == 0)
            {
                if (j == 0 || j==nCols-1)
                {
                    arr[i][j] = 'K';
                }

                else if (j == 1 || j==nCols-2)
                {
                    arr[i][j] = 'A';
                }

                else if (j == 2 || j==nCols-3)
                {
                    arr[i][j] = 'F';
                }
                else if (j == 3 )
                {
                    arr[i][j] = 'V';
                }
                else
                {
                    arr[i][j] = 'S';
                }
            }
            else if (i == 1)
            {
                arr[i][j] = 'P';
            }
            else
            {
                arr[i][j] = ' ';
            }
        }
    }
    //last 2 rows for opponent
    for(i=nRows-2; i<nRows;i++)
    {
        for(j=0;j<nCols;j++)
        {
            //add 32 to lower the opponent's character
            arr[i][j] = arr[nRows-i-1][j] + 32;
        }
    }
}

    int pawnToQueen  (char **destPiece, int sCol, int eCol, int sRow, int eRow)
    {
        if  (destPiece[7][eCol] == 'P')
        {
            if( (sCol == eCol ) && (eRow == 7) )
            return 1;
        }
        else if (destPiece [0][eCol]== 'p')
        {
            if ( (sCol == eCol) && (eRow == 0) )
            return 1;
        }
        else return 0;

    } 