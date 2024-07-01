#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUIT_MASK 0x30
#define VALUE_MASK 0x0F

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
  int suitOrderA = suitOrder(readableCardA[1]);
  int suitOrderB = suitOrder(readableCardB[1]);

  if (suitOrderA != suitOrderB)
  {
    return suitOrderA - suitOrderB; // Sort by suit in ascending order for easier reverse sorting
  }
  else
  {
    // If suits are equal, compare values in descending order (A > K > ... > 2)
    int valueOrderA = valueOrder(readableCardA[0]);
    int valueOrderB = valueOrder(readableCardB[0]);
    return valueOrderA - valueOrderB; // Sort by value in ascending order for easier reverse sorting
  }
}

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    printf("Usage: %s <input_file> <output_file>\n", argv[0]);
    return -1;
  }

  FILE *fin = fopen(argv[1], "r");
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
    // Sort the hand based on encoded card values using the compareCards function
    qsort(hand, 5, sizeof(char), compareCards);

    // Write the sorted hand in readable format to the output file
    for (int i = 0; i < 5; ++i)
    {
      // Convert sorted encoded cards to readable format and write
      char readableCard[3];
      convertToReadableCard(hand[i], readableCard);
      fprintf(fout, "%s\n", readableCard);
    }
  }

  fclose(fin);
  fclose(fout);

  return 0;
}
