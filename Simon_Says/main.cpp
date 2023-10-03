#include <cstdlib>
#include <iostream>
#include <string.h>
#include<windows.h>
void Simon_Says(uint32_t turn)
{
    uint32_t Generated_Array[turn];
    uint32_t Input_Array[turn];

    //printing and filling the array
    for (int i = 0; i < turn; i++)
    {  
        Generated_Array[i] = rand() % 10;
        printf("%1",Generated_Array[i]);
        Sleep(1000);
        system("clear");
    }
    
    //checking the array
    printf("type the numbers now in the correct order");
    for (int i = 0; i < turn; i++)
    {
        scanf("%i", Input_Array[i]);
        if (Input_Array[i] != Generated_Array[i])
        {
            break;
        }   
    }

    //we check if they won the round
    if (Input_Array[turn-1] == Generated_Array[turn-1])
    {
        system("clear");
        printf("You finished this round");
        turn++;
        Simon_Says(turn);
    }
    else
    {
        system("clear");
        printf("You failed");
    }
}
int main(void)
{
    Simon_Says(1);
}