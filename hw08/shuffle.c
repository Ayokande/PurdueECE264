#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// You can add more functions to this file.

void _newFunction(CardDeck upper_deck, CardDeck lower_deck, CardDeck new_deck, int count_upper, int count_lower, int total);
void _helper(CardDeck upper_deck, CardDeck lower_deck, CardDeck new_deck, int count_upper, int count_lower, int total, int k);
void _interleaver(CardDeck upper_deck, CardDeck lower_deck, int k);


void divide(CardDeck orig_deck, CardDeck * upper_deck, CardDeck * lower_deck)
{
        
        int deck_size = orig_deck.size;
        int numWays = deck_size -1;
        
        for(int i=0; i < numWays; i++)
	{
        	 int q = 0;
                	for(int j = 0; j < i+1; j++)
			{
                		upper_deck[i].cards[j] = orig_deck.cards[j];
                	}       
                        		for(int k = i+1; k < deck_size; k++)
					{
                         			lower_deck[i].cards[q] = orig_deck.cards[k];
                        			q++;
                        		}
        	 lower_deck[i].size = numWays - i;
         	upper_deck[i].size = 1+i;
         }
}


void _newFunction(CardDeck upper_deck, CardDeck lower_deck, CardDeck new_deck, int count_upper, int count_lower, int total)
{
        if(count_lower == lower_deck.size && count_upper == upper_deck.size)
	{
                printDeck(new_deck);
                fprintf(stdout, "\n");
                return;
        }

        else if(count_upper == (upper_deck.size))
	{
               new_deck.cards[total] = lower_deck.cards[count_lower];
                _newFunction(upper_deck, lower_deck, new_deck, count_upper, (count_lower + 1), (total + 1));
                return;
        }

        else if(count_lower == (lower_deck.size))
	{
               new_deck.cards[total] = upper_deck.cards[count_upper];
               _newFunction(upper_deck, lower_deck, new_deck, (count_upper + 1), count_lower, (total + 1));
                return;
        }
        new_deck.cards[total] = lower_deck.cards[count_lower];
        _newFunction(upper_deck, lower_deck, new_deck, count_upper, (count_lower+1), (total + 1));
        new_deck.cards[total] = upper_deck.cards[count_upper];
        _newFunction(upper_deck, lower_deck, new_deck, (count_upper+1), count_lower, (total + 1));
        return;
}

void interleave(CardDeck upper_deck, CardDeck lower_deck)
{
        int count_upper = 0;
        int count_lower = 0;
        int total = 0;
        CardDeck new_deck = {
                .size = upper_deck.size + lower_deck.size,
                .cards = {0}
         };

        _newFunction(upper_deck, lower_deck, new_deck, count_upper, count_lower, total);
}

void shuffle(CardDeck orig_deck)
{
        int numpairs = orig_deck.size - 1;

        CardDeck* upper_deck = malloc(sizeof(*upper_deck) * orig_deck.size);
        CardDeck* lower_deck = malloc(sizeof(*lower_deck) * orig_deck.size);
	
	//allocate memory
        if (upper_deck == NULL)
        {
                return;
        }
        if (lower_deck == NULL)
        {
                return;
        }

	//call divideDeck to fill upper_deck and lower_deck
        divide(orig_deck, upper_deck, lower_deck);

        int index = 0;
        while (numpairs > 0)
        {
		//for each pairs call interleave
                interleave(upper_deck[index] , lower_deck[index]);
                numpairs--;
                index++;
        }
        free(upper_deck);
        free(lower_deck);
}


void _helper(CardDeck upper_deck, CardDeck lower_deck, CardDeck new_deck, int count_upper, int count_lower, int total, int k)
{       

	if(k ==0)
	{
		return;
	}

        if(count_lower == lower_deck.size && count_upper == upper_deck.size && k == 1)
        {       
                printDeck(new_deck);
                fprintf(stdout, "\n");
                return;
        }

        if(count_lower == lower_deck.size && count_upper == upper_deck.size && k != 1)
        {
		repeat_shuffle(new_deck, k-1);       	 
	        return;
        }

        
        else if(count_upper == (upper_deck.size))
        {  
		new_deck.cards[total] = lower_deck.cards[count_lower];
                _helper(upper_deck, lower_deck, new_deck, count_upper, (count_lower + 1), (total + 1), k);
                return;
        }
        
        else if(count_lower == (lower_deck.size))
        {      
               new_deck.cards[total] = upper_deck.cards[count_upper];
               _helper(upper_deck, lower_deck, new_deck, (count_upper + 1), count_lower, (total + 1), k);
               return;
        }
        new_deck.cards[total] = lower_deck.cards[count_lower];
        _helper(upper_deck, lower_deck, new_deck, count_upper, (count_lower+1), (total + 1), k);
        new_deck.cards[total] = upper_deck.cards[count_upper];
        _helper(upper_deck, lower_deck, new_deck, (count_upper+1), count_lower, (total + 1), k);
        return;
}

void _interleaver(CardDeck upper_deck, CardDeck lower_deck, int k)
{
        int count_upper = 0;
        int count_lower = 0;
        int total = 0;
        CardDeck new_deck = {
                .size = upper_deck.size + lower_deck.size,
                .cards = {0}
         };

        _helper(upper_deck, lower_deck, new_deck, count_upper, count_lower, total, k);
}


void repeat_shuffle(CardDeck orig_deck, int k)
{
        int numpairs = orig_deck.size - 1;

        CardDeck* upper_deck = malloc(sizeof(*upper_deck) * orig_deck.size);
        CardDeck* lower_deck = malloc(sizeof(*lower_deck) * orig_deck.size);

	//allocate memory
        if (upper_deck == NULL)
        {
                return;
        }
        if (lower_deck == NULL)
        {
                return;
        }

        divide(orig_deck, upper_deck, lower_deck);

        int index = 0;
        while (numpairs > 0)
        {
		//for each pair call _interleaver
                _interleaver(upper_deck[index] , lower_deck[index], k);
                numpairs--;
                index++;
        }
        free(upper_deck);
        free(lower_deck);


}
