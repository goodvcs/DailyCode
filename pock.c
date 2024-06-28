#include <stdio.h>
#include <stdbool.h>

// Function to convert card value from encoded byte to rank (A, K, Q, J, T, 9, ..., 2)
char valueToRank(char encodedValue)
{
  switch (encodedValue)
  {
  case '2':
    return 0b0010;
   case '3':
    return 0b0011;
  case '4':
    return 0b0100;
  case '5':
    return 0b0101;
  case '6':
    return 0b0110;
  case '7':
    return 0b0111;
  case '8':
    return 0b1000;
  case '9':
    return 0b1001;
  case 'T':
    return 0b1010;
  case 'J':
    return 0b1011;
  case 'Q':
    return 0b1100;
  case 'K':
    return 0b1101;
  case 'A':
    return 0b1110;

  }
}

// Function to convert card suit from encoded byte to suit (S, H, D, C)
char valueToSuit(char encodedSuit)
{
  switch (encodedSuit >> 6)
  { // Shift and mask to get upper 2 bits for suit
  case 'S':
    return 0b11; // Spades
  case 'H':
    return 0b10; // Hearts
  case 'D':
    return 0b01; // Diamonds
  case 'C':
    return 0b00; // Clubs
  }
}
int greaterValue(char card1, char card2)
{
  return ((unsigned char)(card1 & 0x0F) > (unsigned char)(card2 & 0x0F));
}

// Function to check if the hand is a Flush (all cards of the same suit)
int isFlush(char *hand)
{
  int count;
  char suit = hand[0] >> 6; // Get the suit of the first card
  for (int i = 1; i < 5; ++i)
  {

    if ((hand[i] >> 6) == suit)
    {
      count++;
    }
  }
  return count;
}

// Function to check if the hand is a Straight (consecutive values)
int isStraight(char *hand)
{
  // Sort the hand based on card values
  for (int i = 0; i < 4; ++i)
  {
    for (int j = i + 1; j < 5; ++j)
    {
      if (greaterValue(hand[j], hand[i]))
      {
        char temp = hand[i];
        hand[i] = hand[j];
        hand[j] = temp;
      }
    }
  }

  // Initialize a count for consecutive pairs
  int consecutiveCount = 0;

  // Check if the hand is a straight with Ace as the highest card
  for (int i = 0; i < 4; ++i)
  {
    unsigned char currentValue = hand[i] & 0x0F;
    unsigned char nextValue = hand[i + 1] & 0x0F;

    // Check if the values are consecutive
    if (currentValue == nextValue + 1)
    {
      consecutiveCount++;
    }
  }

  // Check if the hand is a straight with Ace as the lowest card (A, 2, 3, 4, 5)
  if ((hand[0] & 0x0F) == 13) // A (binary: 1101) as the lowest card (Ace's encoded value is assumed to be 13)
  {
    int lowAceStraight = 1; // Initialize to true
    // Check the sequence 5, 4, 3, 2, A (where A is considered as 1)
    for (int i = 1; i < 4; ++i)
    {
      unsigned char currentValue = hand[i] & 0x0F;
      unsigned char nextValue = hand[i + 1] & 0x0F;

      if (currentValue != nextValue + 1)
      {
        lowAceStraight = 0; // If not consecutive, set to false
        break;
      }
    }
    if ((hand[4] & 0x0F) == 1) // Check if the lowest card is Ace treated as 1
    {
      lowAceStraight = 1; // Confirm A, 2, 3, 4, 5 sequence
    }

    // If we found a low Ace straight, we increase the count to 5 to indicate a straight
    if (lowAceStraight)
    {
      consecutiveCount = 4; // This is actually 4 pairs, indicating a straight
    }
  }

  return consecutiveCount == 4; // A straight will have 4 consecutive pairs
}

// Function to determine and print the rank of the hand
void determineRank(char *hand, FILE *fout)
{

  // Check for Royal Flush (Rank 1)
  if (isFlush(hand) == 5 && isStraight(hand) == 5)
  {
    fprintf(fout, "Rank 1"); // Royal Flush
    return;
  }

  // Check for Straight Flush (Rank 2)
  if (isFlush(hand))
  {
    fprintf(fout, "Rank 2"); // Straight Flush
    return;
  }

  // Check for Four of a Kind (Rank 3)
  int valueCount[13] = {0}; // Array to count occurrences of each card value
  for (int i = 0; i < 5; ++i)
  {
    valueCount[hand[i] & 0x0F]++;
  }
  for (int i = 0; i < 13; ++i)
  {
    if (valueCount[i] == 4)
    {
      fprintf(fout, "Rank 3"); // Four of a kind
      return;
    }
  }

  // Check for Full House (Rank 4)
  int threeCount = 0, pairCount = 0;
  for (int i = 0; i < 13; ++i)
  {
    if (valueCount[i] == 3)
    {
      threeCount++;
    }
    else if (valueCount[i] == 2)
    {
      pairCount++;
    }
  }
  if (threeCount == 1 && pairCount == 1)
  {
    fprintf(fout, "Rank 4"); // Full House
    return;
  }

  // Check for Flush (Rank 5)
  if (isFlush(hand))
  {
    fprintf(fout, "Rank 5"); // Flush
    return;
  }

  // Check for Straight (Rank 6)
  if (isStraight(hand))
  {
    fprintf(fout, "Rank 6"); // Straight
    return;
  }

  // Check for Three of a Kind (Rank 7)
  if (threeCount == 1)
  {
    fprintf(fout, "Rank 7"); // Three of a kind
    return;
  }

  // Check for Two Pair (Rank 8)
  if (pairCount == 2)
  {
    fprintf(fout, "Rank 8"); // Two pair
    return;
  }

  // Check for One Pair (Rank 9)
  if (pairCount == 1)
  {
    fprintf(fout, "Rank 9"); // One pair
    return;
  }

  // Default to High Card (Rank 10)
  fprintf(fout, "Rank 10"); // High card
}

int main(int argc, char **argv)
{

  FILE *fin = fopen(argv[1], "r");
  FILE *fout = fopen(argv[2], "wb");

  if ((fin == NULL) || (fout == NULL))
  {
    return -1;
  }

  char hand[5];
  int cardIndex = 0;
  char card;

  while (fgets(hand, sizeof(hand), fin) != NULL)
  {
    if (hand[0] == 'E')
    {
      break;
    }

    printf("Read card: %s", hand); // 打印读取的卡牌信息，用于调试
    // fprintf(fout, "%s", hand);

    determineRank(hand, fout);
  }

  fclose(fin);
  fclose(fout);

  return 0;
}
