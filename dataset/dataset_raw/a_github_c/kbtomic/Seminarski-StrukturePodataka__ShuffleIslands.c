#include "ShuffleIslands.h"
#include "RandomGenerator.h"
#include "NumberOfIslands.h"
int Shuffle(islandPointer startIsland, int numberOfIslands)
{
    islandPointer islandToChange = startIsland->next;
    islandPointer start = startIsland;
    islandPointer prevOfIslandToChange = startIsland;
    while(islandToChange->next)
    {
        prevOfIslandToChange = startIsland;
        islandToChange = startIsland->next;
        int randomIndex = GenerateRandom(start->next->index, numberOfIslands);
        islandPointer changeWithMe = start;
        islandPointer prevOfChangeWithMe = changeWithMe;
        islandPointer nextOfChangeWithMe = changeWithMe->next;
        while (changeWithMe->index != randomIndex)
        {
            prevOfChangeWithMe = changeWithMe;
            changeWithMe = changeWithMe->next;
            nextOfChangeWithMe = changeWithMe->next;
        }
        if (islandToChange->index != randomIndex)
        {
            if (islandToChange->next == changeWithMe)
            {
                prevOfIslandToChange->next = changeWithMe;
                prevOfChangeWithMe->next = changeWithMe->next;
                changeWithMe->next = islandToChange;
                islandToChange->next = nextOfChangeWithMe;
            }
            else if (changeWithMe->next == islandToChange)
            {
                prevOfChangeWithMe->next = islandToChange;
                prevOfIslandToChange->next = islandToChange->next;
                changeWithMe->next = islandToChange->next;
                islandToChange->next = changeWithMe;
            }
            else 
            {
                prevOfIslandToChange->next = changeWithMe;
                prevOfChangeWithMe->next = islandToChange;
                changeWithMe->next = islandToChange->next;
                islandToChange->next = nextOfChangeWithMe;
            }
        }
        startIsland = startIsland->next;
        if (!startIsland->next)
            break;
    }
    return 0;
}