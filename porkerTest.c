#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUIT_MASK 0x30
#define VALUE_MASK 0x0F

// Function declarations
int isStraightFlush(char *hand);
int isFlush(char *hand);
int isStraight(char *hand);

// Function to convert card value from encoded byte to character (A, 2-9, T, J, Q, K)
char valueToChar(char encodedValue)
{
  switch (encodedValue & VALUE_MASK)
  { // Mask to get lower 4 bits for value
  case 0b0001:
    return 'A'; // Ace
  case 0b0010:
    return '2';
  case 0b0011:
    return '3';
  case 0b0100:
    return '4';
  case 0b0101:
    return '5';
  case 0b0110:
    return '6';
  case 0b0111:
    return '7';
  case 0b1000:
    return '8';
  case 0b1001:
    return '9';
  case 0b1010:
    return 'T'; // Ten
  case 0b1011:
    return 'J'; // Jack
  case 0b1100:
    return 'Q'; // Queen
  case 0b1101:
    return 'K'; // King
  default:
    return '?'; // Handle invalid cases
  }
}

// Function to convert card suit from encoded byte to suit (S, H, D, C)
char suitToChar(char encodedSuit)
{
  switch (encodedSuit & SUIT_MASK)
  { // Mask to get upper 2 bits for suit
  case 0b110000:
    return 'S'; // Spades
  case 0b100000:
    return 'H'; // Hearts
  case 0b010000:
    return 'D'; // Diamonds
  case 0b000000:
    return 'C'; // Clubs
  default:
    return '?'; // Handle invalid cases
  }
}

// Function to convert encoded card to readable card string
void convertToReadableCard(char encodedCard, char *output)
{
  output[0] = suitToChar(encodedCard);
  output[1] = valueToChar(encodedCard);
  output[2] = '\0'; // Null-terminate the string
}

// Function to determine the order of suits (S > H > D > C)
int suitOrder(char suit)
{
  switch (suit)
  {
  case 'S':
    return 1;
  case 'H':
    return 2;
  case 'D':
    return 3;
  case 'C':
    return 4;
  default:
    return 5; // Should not happen with valid suits
  }
}

// Function to determine the order of values (A > K > Q > J > T > 9 > ... > 2)
int valueOrder(char value)
{
  switch (value)
  {
  case 'A':
    return 1;
  case 'K':
    return 2;
  case 'Q':
    return 3;
  case 'J':
    return 4;
  case 'T':
    return 5;
  case '9':
    return 6;
  case '8':
    return 7;
  case '7':
    return 8;
  case '6':
    return 9;
  case '5':
    return 10;
  case '4':
    return 11;
  case '3':
    return 12;
  case '2':
    return 13;
  default:
    return 14; // Should not happen with valid values
  }
}

// Comparator function for qsort to sort cards based on suit and value
int compareCards(const void *a, const void *b)
{
  char cardA = *((char *)a);
  char cardB = *((char *)b);

  // Convert cards to readable format
  char readableCardA[3];
  char readableCardB[3];
  convertToReadableCard(cardA, readableCardA);
  convertToReadableCard(cardB, readableCardB);

  // Compare suits first in descending order (S > H > D > C)
  int suitOrderA = suitOrder(readableCardA[0]);
  int suitOrderB = suitOrder(readableCardB[0]);

  if (suitOrderA != suitOrderB)
  {
    return suitOrderA - suitOrderB; // Sort by suit in ascending order for easier reverse sorting
  }
  else
  {
    // If suits are equal, compare values in descending order (A > K > ... > 2)
    int valueOrderA = valueOrder(readableCardA[1]);
    int valueOrderB = valueOrder(readableCardB[1]);
    return valueOrderA - valueOrderB; // Sort by value in ascending order for easier reverse sorting
  }
}

// Function to check if two cards have the same suit
int isSameSuit(char card1, char card2)
{
  // printf("%d", (card1 & SUIT_MASK) == (card2 & SUIT_MASK));
  return (card1 & SUIT_MASK) == (card2 & SUIT_MASK);
}

// Function to check if two cards have the same value
int isSameValue(char card1, char card2)
{
  // printf("%d", (card1 & VALUE_MASK) == (card2 & VALUE_MASK));
  return valueToChar(card1 & VALUE_MASK) == valueToChar(card2 & VALUE_MASK);
}

int countSameSuit(char *hand)
{
  int suitCount[4] = {0}; // Counters for suits: 0 = Spades, 1 = Hearts, 2 = Diamonds, 3 = Clubs
  int maxCount = 0;

  for (int i = 0; i < 5; ++i)
  {
    char suit = suitToChar(hand[i]);

    switch (suit)
    {
    case 'S':
      suitCount[0]++;
      break;
    case 'H':
      suitCount[1]++;
      break;
    case 'D':
      suitCount[2]++;
      break;
    case 'C':
      suitCount[3]++;
      break;
    default:
      break; // Skip invalid cases
    }
  }

  // Find the maximum count among the suits
  for (int i = 0; i < 4; ++i)
  {
    if (suitCount[i] > maxCount)
      maxCount = suitCount[i];
  }

  return maxCount;
}

// Function to count the number of cards with the same value
int countSameValue(char *hand)
{
  int count = 0;
  for (int i = 0; i < 4; ++i)
  {
    for (int j = i + 1; j < 5; ++j)
    {
      if (isSameValue(hand[i], hand[j]))
        count++;
    }
  }
  return count;
}

int compare(const void *a, const void *b)
{
  return (*(int *)a - *(int *)b);
}

// Function to count consecutive values in a sorted hand
int countConsecutiveValues(char *hand)
{
  int values[5];
  int count = 1; // At least one card itself is consecutive

  // Decode and convert values
  for (int i = 0; i < 5; ++i)
  {
    values[i] = valueOrder(valueToChar(hand[i]));
  }

  // Sort the values in ascending order
  qsort(values, 5, sizeof(int), compare);

  // Check for consecutive values
  for (int i = 0; i < 4; ++i)
  {
    if (values[i] + 1 == values[i + 1])
    {
      count++;
    }
    else if (values[0] == 1 && values[4] == 14 && values[1] == 2 && values[2] == 3 && values[3] == 4)
    {
      // Special case for A-2-3-4-5 straight
      count = 5;
      break;
    }
    else
    {
      count = 1; // Reset count if not consecutive
    }
  }

  // Special case check for A-2-3-4-5
  if (values[0] == 1 && values[4] == 14 && values[1] == 2 && values[2] == 3 && values[3] == 4)
  {
    count = 5;
  }

  // printf("%d  \n", count);
  // printf("%s  \n", "_____________________");
  return count;
}

// Function to check if a hand is a Royal Flush
int isRoyalFlush(char *hand)
{
  // Sort the hand first

  // Check if it's a Straight Flush and starts with 10 and ends with A
  if (isStraightFlush(hand) && valueOrder(valueToChar(hand[0])) == 1) // Check if the first card is 'T' (10)
  {
    return 1;
  }
  return 0;
}

// Function to check if a hand is a Straight Flush
int isStraightFlush(char *hand)
{

  return countSameSuit(hand) == 5 && countConsecutiveValues(hand) == 5; // Straight Flush has all cards in sequence with the same suit
}

// Function to check if a hand is a Four of a Kind
int isFourOfAKind(char *hand)
{
  // Sort the hand first to handle different cases of Four of a Kind correctly

  // Check for Four of a Kind (AAAAx or xAAAA)
  if (isSameValue(hand[0], hand[1]) && isSameValue(hand[1], hand[2]) && isSameValue(hand[2], hand[3]))
    return 1; // First four cards are the same

  if (isSameValue(hand[1], hand[2]) && isSameValue(hand[2], hand[3]) && isSameValue(hand[3], hand[4]))
    return 1; // Last four cards are the same

  return 0; // Not Four of a Kind
}

// Function to check if a hand is a Full House
int isFullHouse(char *hand)
{

  int firstGroupCount = 0, secondGroupCount = 0;
  char firstGroupValue, secondGroupValue;

  // Find the first group of three cards with the same value
  for (int i = 0; i < 3; ++i)
  {
    if (isSameValue(hand[i], hand[i + 1]) && isSameValue(hand[i + 1], hand[i + 2]))
    {
      firstGroupValue = valueToChar(hand[i]);
      firstGroupCount = 3;
      break;
    }
  }

  // Find the second group of two cards with the same value (different from first group)
  for (int i = 0; i < 4; ++i)
  {
    if (valueToChar(hand[i]) != firstGroupValue && isSameValue(hand[i], hand[i + 1]))
    {
      secondGroupValue = valueToChar(hand[i]);
      secondGroupCount = 2;
      break;
    }
  }

  // Full House has one group of three cards and one group of two cards with different values
  return firstGroupCount == 3 && secondGroupCount == 2;
}

// Function to check if a hand is a Flush
int isFlush(char *hand)
{
  return countSameSuit(hand) == 5; // Flush has all cards with the same suit
}

// Function to check if a hand is a Straight
int isStraight(char *hand)
{
  return countConsecutiveValues(hand) == 5; // Straight has all cards in sequence
}

// Function to check if a hand is Three of a Kind
int isThreeOfAKind(char *hand)
{
  for (int i = 0; i < 3; ++i)
  {
    if (isSameValue(hand[i], hand[i + 1]) && isSameValue(hand[i + 1], hand[i + 2]))
      return 1; // Found three of a kind
  }
  return 0; // No three of a kind found
}

// Function to check if a hand is Two Pair
int isTwoPair(char *hand)
{
  int pairCount = 0;

  // Count pairs in the hand
  for (int i = 0; i < 4; ++i)
  {
    for (int j = i + 1; j < 5; ++j)
    {
      if (isSameValue(hand[i], hand[j]))
        pairCount++;
    }
  }

  // Two Pair has exactly two pairs of cards with the same value
  return pairCount == 2;
}

// Function to check if a hand is a Pair
int isPair(char *hand)
{
  for (int i = 0; i < 4; ++i)
  {
    for (int j = i + 1; j < 5; ++j)
    {
      if (isSameValue(hand[i], hand[j]))
        return 1; // Found a pair
    }
  }
  return 0; // No pair found
}

// Function to determine the rank of the hand and write it to fout
void determineRank(char *hand, FILE *fout)
{
  if (isRoyalFlush(hand))
  {
    fprintf(fout, "Rank 1"); // Royal Flush
    return;
  }
  else if (isStraightFlush(hand))
  {
    fprintf(fout, "Rank 2"); // Straight Flush
    return;
  }
  else if (isFourOfAKind(hand))
  {
    fprintf(fout, "Rank 3"); // Four of a Kind
    return;
  }
  else if (isFullHouse(hand))
  {
    fprintf(fout, "Rank 4"); // Full House
    return;
  }
  else if (isFlush(hand))
  {
    fprintf(fout, "Rank 5"); // Flush
    return;
  }
  else if (isStraight(hand))
  {
    fprintf(fout, "Rank 6"); // Straight
    return;
  }
  else if (isThreeOfAKind(hand))
  {
    fprintf(fout, "Rank 7"); // Three of a Kind
    return;
  }
  else if (isTwoPair(hand))
  {
    fprintf(fout, "Rank 8"); // Two Pair
    return;
  }
  else if (isPair(hand))
  {
    fprintf(fout, "Rank 9"); // Pair
    return;
  }
  else
  {
    fprintf(fout, "Rank 10"); // High Card
    return;
  }
}

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    printf("Usage: %s <input_file> <output_file>\n", argv[0]);
    return -1;
  }

  FILE *fin = fopen(argv[1], "rb");
  FILE *fout = fopen(argv[2], "wb");

  if (fin == NULL || fout == NULL)
  {
    perror("Error opening file");
    return -1;
  }

  char hand[5]; // Array to store each hand (encoded bytes)
  size_t bytesRead;

  while ((bytesRead = fread(hand, sizeof(char), sizeof(hand), fin)) == sizeof(hand))
  {
    // Print the binary contents of the hand array
    // printf("Hand contents (binary representation): ");
    // for (int i = 0; i < 5; i++)
    // {
    //   for (int j = 7; j >= 0; j--)
    //   {
    //     printf("%d", (hand[i] & (1 << j)) ? 1 : 0);
    //   }
    //   printf(" ");
    // }
    // printf("\n");

    // Sort the hand based on encoded card values using the compareCards function
    qsort(hand, 5, sizeof(char), compareCards);

    // Print sorted hand for debugging
    // printf("Sorted hand: ");
    // for (int i = 0; i < 5; ++i)
    // {
    //   char readableCard[3];
    //   convertToReadableCard(hand[i], readableCard);
    //   printf("%s ", readableCard);
    // }
    // printf("\n");

    // Write the sorted hand in readable format to the output file
    for (int i = 0; i < 5; ++i)
    {
      char readableCard[3];
      convertToReadableCard(hand[i], readableCard);
      fprintf(fout, "%s\n", readableCard);
    }

    // Determine and print the rank of the hand
    determineRank(hand, fout);
  }

  fclose(fin);
  fclose(fout);

  return 0;
}
