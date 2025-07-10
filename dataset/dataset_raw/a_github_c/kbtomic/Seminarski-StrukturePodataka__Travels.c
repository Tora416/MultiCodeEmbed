#include "Travels.h"
#include "CoinCalculator.h"
#include "Respawn.h"
#include "Stack.h"
#include "IslandType.h"
islandPointer TravelToLeftIsland(int* currentAmountOfCoins, int* numberOfFoundClues, islandPointer start, islandPointer currentIsland, stackPointer stackHead, int* flagForGameOver)
{
    islandPointer parentIsland = currentIsland;
    if (HaveEnoughCoins(*currentAmountOfCoins, currentIsland->leftNext->coins))
    {
        *currentAmountOfCoins = SpendCoins(*currentAmountOfCoins, currentIsland->leftNext->coins);
        currentIsland = currentIsland->leftNext;
        PushStack(currentIsland, stackHead);
        printf("%s\n", currentIsland->description);
        if (isClueIsland(currentIsland))
        {
            printf("Trag je: %c\n", currentIsland->clue);
            *numberOfFoundClues += 1;
        }
        else if (isDeathlyIsland(currentIsland, start))
        {
            if (HaveEnoughCoins(*currentAmountOfCoins, COINS_AMOUNT_FOR_RESPAWN_OR_MAIN_PRIZE))
            {
                char choice = RespawnPrint(*currentAmountOfCoins);
                system("cls");
                if (tolower(choice) == 'd')
                {
                    *currentAmountOfCoins = SpendCoins(*currentAmountOfCoins, COINS_AMOUNT_FOR_RESPAWN_OR_MAIN_PRIZE);
                    PrintCurrentPath(currentIsland, stackHead);
                    printf("Status coina: %d\n", *currentAmountOfCoins);
                    printf("Uskrsnuo si!\n");
                    currentIsland = TravelToPrevIsland(parentIsland, currentIsland, stackHead);
                }
                else
                {
                    currentIsland = TravelToStartIsland(start, currentIsland, stackHead);
                    *flagForGameOver = 1;
                }
            }
            else
            {
                currentIsland = TravelToStartIsland(start, currentIsland, stackHead);
                *flagForGameOver = 1;
            }
        }
        else
        {
            PrintCurrentPath(currentIsland, stackHead);
            currentIsland = TravelToPrevIsland(parentIsland, currentIsland, stackHead);
        }
    }
    else 
    {
        printf("Nazalost presiromasan si za daljnja putovanja :(!\n");
        *flagForGameOver = 1;
    }
    return currentIsland;
}
islandPointer TravelToRightIsland(int* currentAmountOfCoins, int* numberOfFoundClues, islandPointer start, islandPointer currentIsland, stackPointer stackHead, int* flagForGameOver)
{
    islandPointer parentIsland = currentIsland;
    if (HaveEnoughCoins(*currentAmountOfCoins, currentIsland->rightNext->coins))
    {
        *currentAmountOfCoins = SpendCoins(*currentAmountOfCoins, currentIsland->rightNext->coins);
        currentIsland = currentIsland->rightNext;
        PushStack(currentIsland, stackHead);
        printf("%s\n", currentIsland->description);
        if (isClueIsland(currentIsland))
        {
            printf("Trag je: %c\n", currentIsland->clue);
            *numberOfFoundClues += 1;
        }
        else if (isDeathlyIsland(currentIsland, start))
        {
            if (HaveEnoughCoins(*currentAmountOfCoins, COINS_AMOUNT_FOR_RESPAWN_OR_MAIN_PRIZE))
            {
                char choice = RespawnPrint(*currentAmountOfCoins);
                system("cls");
                if (tolower(choice) == 'd')
                {
                    *currentAmountOfCoins = SpendCoins(*currentAmountOfCoins, COINS_AMOUNT_FOR_RESPAWN_OR_MAIN_PRIZE);
                    PrintCurrentPath(currentIsland, stackHead);
                    printf("Status coina: %d\n", *currentAmountOfCoins);
                    printf("Uskrsnuo si!\n");
                    currentIsland = TravelToPrevIsland(parentIsland, currentIsland, stackHead);
                }
                else
                {
                    currentIsland = TravelToStartIsland(start, currentIsland, stackHead);
                    *flagForGameOver = 1;
                }
            }
            else
            {
                currentIsland = TravelToStartIsland(start, currentIsland, stackHead);
                *flagForGameOver = 1;
            }
        }
        else
        {
            PrintCurrentPath(currentIsland, stackHead);
            currentIsland = TravelToPrevIsland(parentIsland, currentIsland, stackHead);
        }
    }
    else 
    {
        printf("Nazalost presiromasan si za daljnja putovanja :(!\n");
        *flagForGameOver = 1;
    }
    return currentIsland;
}
islandPointer TravelToPrevIsland(islandPointer parentIsland, islandPointer currentIsland, stackPointer stackHead)
{
    printf("Vracamo se na prethodni otok: %s kako bi nastavio svoje putovanje u drugom smjeru\n", parentIsland->islandName);
    PopStack(stackHead);
    currentIsland = parentIsland;
    return currentIsland;
}
islandPointer TravelToStartIsland(islandPointer start, islandPointer currentIsland, stackPointer stackHead)
{
    currentIsland = start;
    CleanStack(stackHead);
    return currentIsland;
}