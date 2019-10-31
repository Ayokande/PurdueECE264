#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// You may add more functions in this file.

void newFunction(CardDeck upper_deck, CardDeck lower_deck, CardDeck new_deck, int count_upper, int count_lower, int total);

void divide(CardDeck orig_deck, CardDeck * upper_deck, CardDeck * lower_deck) 
{
    
	int deck_size = orig_deck.size;
	int numWays = deck_size -1;
  
  	for(int i=0; i < numWays; i++){
   	 int q = 0;
    		for(int j = 0; j < i+1; j++){
      		upper_deck[i].cards[j] = orig_deck.cards[j];
    		}
    			for(int k = i+1; k < deck_size; k++){
     			 lower_deck[i].cards[q] = orig_deck.cards[k];
      			q++;
    			}
    	 lower_deck[i].size = numWays - i;
  	 upper_deck[i].size = 1+i;
 	 }



/*	for (int index = 0; index < deck_size; index++){
		upper_deck[index].size = 0;
		lower_deck[index].size = 0;
		int temp = 0;
		for (){
  			upper_deck[].cards[] = orig_deck.cards[]			
		}
	

 	int temp_array[MAX_SIZE];
	int temp_array2[MAX_SIZE];
	int temp2count;
        for (int level = 0; level<deck_size-1;level++){
           int iteration = 1;
           for (int j = 0; j < iteration; j++){
              temp_array[j] = orig_deck.cards[j];
            }
	   temp2count = 0;
	   for (int l = iteration; l<deck_size; l++){
	      temp_array2[temp2count] = orig_deck.cards[l];
              temp2count++;	
	    }
           memcpy(&upper_deck->cards[level], temp_array, MAX_SIZE);
	   memcpy(&lower_deck->cards[level], temp_array2, MAX_SIZE);
           iteration++;		
         }  */    

}


void newFunction(CardDeck upper_deck, CardDeck lower_deck, CardDeck new_deck, int count_upper, int count_lower, int total){
        if(count_lower == lower_deck.size && count_upper == upper_deck.size){
                print_deck(new_deck);
                fprintf(stdout, "\n");
                return;
        }
        
 	else if(count_upper == (upper_deck.size)){
           new_deck.cards[total] = lower_deck.cards[count_lower];
                newFunction(upper_deck, lower_deck, new_deck, count_upper, (count_lower + 1), (total + 1));
                return;
        }

        else if(count_lower == (lower_deck.size)){
               new_deck.cards[total] = upper_deck.cards[count_upper];
               newFunction(upper_deck, lower_deck, new_deck, (count_upper + 1), count_lower, (total + 1));
                return;
        }
        new_deck.cards[total] = lower_deck.cards[count_lower];
        newFunction(upper_deck, lower_deck, new_deck, count_upper, (count_lower+1), (total + 1));
        new_deck.cards[total] = upper_deck.cards[count_upper];
        newFunction(upper_deck, lower_deck, new_deck, (count_upper+1), count_lower, (total + 1));
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
	
	newFunction(upper_deck, lower_deck, new_deck, count_upper, count_lower, total);
}

void shuffle(CardDeck orig_deck) 
{
	int numpairs = orig_deck.size - 1;

	CardDeck* upper_deck = malloc(sizeof(*upper_deck) * orig_deck.size);
	CardDeck* lower_deck = malloc(sizeof(*lower_deck) * orig_deck.size);

	// allocate memory
	if (upper_deck == NULL) 
	{
		return;
	}
	if (lower_deck == NULL) 
	{
        	return;
	}

	// call divideDeck to fill upper_deck and lower_deck 
	divide(orig_deck, upper_deck, lower_deck);

	int index = 0;
	while (numpairs > 0) 
	{
		// for each pairs call interleave
		interleave(upper_deck[index] , lower_deck[index]);
		numpairs--;
		index++;	
	}
	free(upper_deck);
	free(lower_deck);
} 
