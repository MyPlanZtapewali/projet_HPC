
/* bits type
 *
 * These are strings of bits of variable length
 *
 * last update: September 29th, 2024
 *
 * AM
 */

#include "bits.h"
#include "assert.h"

// allocating memory for a bits_t instance
bits_t* bits_allocate(size_t nbits)
{
   bits_t *bits = NULL;
   bits = (bits_t*)malloc(sizeof(bits_t));
   if (bits == NULL)  return NULL;
   bits->nbytes = nbits/8;
   bits->ignore = (short) (8 - nbits%8);
   if (bits->ignore != 0)  bits->nbytes++;
   bits->byte = NULL;
   bits->byte = (char*)calloc(bits->nbytes,sizeof(char));
   if (bits->byte == NULL)
   {
      free(bits);
      return NULL;
   }
   return bits;
};

// counting the number of actually used bits
size_t bits_actual_length(bits_t *bits)
{
   return 8*bits->nbytes - bits->ignore;
};

// constructor for a bits_t instance with all bits set to 0
bits_t* bits_zeros(size_t nbits)
{
   bits_t *bits = bits_allocate(nbits);
   if (bits == NULL)  return NULL;
   for (size_t k = 0; k < bits->nbytes; k++)  bits->byte[k] = 0;
   return bits;
};

// constructor for a bits_t instance with all bits set to 1
bits_t* bits_ones(size_t nbits)
{
   bits_t *bits = bits_allocate(nbits);
   if (bits == NULL)  return NULL;
   for (size_t k = 0; k < bits->nbytes; k++)  bits->byte[k] = 255;
   return bits;
};

// constructor for a bits_t instance with random bits
bits_t* bits_random(size_t nbits)
{
   bits_t *bits = bits_allocate(nbits);
   if (bits == NULL)  return NULL;
   for (size_t k = 0; k < bits->nbytes; k++)  bits->byte[k] = rand()%255;
   return bits;
};

// constructor for two bits_t instance with random bits, the same size and a distance valeu
bits_t* bits_random_from(bits_t *b1, bits_t *b2, size_t dist) {
    // Je m'assure que la distance de Hamming entre b1 et b2 est inférieure ou égale à dist
    size_t hamming_b1_b2 = 0;
    size_t nbits = bits_actual_length(b1);
    
    // Je vérifie que b1 et b2 ont la même longueur
    assert(bits_actual_length(b1) == bits_actual_length(b2));

    // Je calcule la distance de Hamming entre b1 et b2
    for (size_t k = 0; k < b1->nbytes; k++) {
        char xor_byte = b1->byte[k] ^ b2->byte[k]; // XOR des octets correspondants
        hamming_b1_b2 += __builtin_popcount(xor_byte); // Compter les bits différents
    }

    // Vérifier que la distance de Hamming entre b1 et b2 est au moins égale à dist
    assert(hamming_b1_b2 >= dist);

    //printf("La distance de hamming est : %zu\n", );


    // Créer la nouvelle chaîne b
    bits_t *b = bits_allocate(nbits);
    if (b == NULL) return NULL;

    // Remplir les bits de b en fonction des conditions
    size_t hamming_b1_b = 0;
    for (size_t k = 0; k < b1->nbytes; k++) {
        char xor_byte = b1->byte[k] ^ b2->byte[k];
        for (short bit = 7; bit >= 0; bit--) {
            if (k == 0 && bit >= 8 - b1->ignore) continue; // Ignorer les bits non utilisés

            if ((xor_byte >> bit) & 1) {
                // Si les bits sont différents dans b1 et b2, choisir aléatoirement entre les deux
                if (rand() % 2 == 0) {
                    b->byte[k] |= (b1->byte[k] & (1 << bit));
                } else {
                    b->byte[k] |= (b2->byte[k] & (1 << bit));
                    hamming_b1_b++; // Incrémente la distance de Hamming si on prend un bit différent de b1
                }
            } else {
                // Si les bits sont identiques dans b1 et b2, copier le bit de b1
                b->byte[k] |= (b1->byte[k] & (1 << bit));
            }

            // Vérifier que la distance de Hamming entre b et b1 ne dépasse pas dist
            if (hamming_b1_b == dist) break;
        }
        if (hamming_b1_b == dist) break;  // Sortir si on a atteint la distance souhaitée
    }

    return b;
}



// constructor for a bits_t instance cloned from another
bits_t* bits_clone(bits_t *bits)
{
   size_t nbits = bits_actual_length(bits);
   bits_t *cloned = bits_allocate(nbits);
   if (bits == NULL)  return NULL;
   for (size_t k = 0; k < bits->nbytes; k++)  cloned->byte[k] = bits->byte[k];
   return cloned;
};

// counting the number of bits having a given value
size_t bits_count(bits_t *bits,bool bvalue)
{
   size_t count = 0;
   for (size_t k = 0; k < bits->nbytes; k++)
   {
      short b = 7;
      char byte = bits->byte[k];
      if (k == 0 && bits->ignore != 0)  b = b - bits->ignore;
      for (; b >= 0; b--)
      {
         if ((byte&1) == bvalue)  count++;
         byte = byte >> 1;
      };
   };
   return count;
};

// counting the number of zeros
size_t bits_nzeros(bits_t *bits)
{
   return bits_count(bits,0);
};

// counting the number of ones
size_t bits_nones(bits_t *bits)
{
   return bits_count(bits,1);
};

// verifying equality between two bits_t instances
bool bits_equals(bits_t *b1,bits_t *b2)
{
   if (b1->nbytes != b2->nbytes)  return false;
   if (b1->ignore != b2->ignore)  return false;
   if (b1->ignore != 0)
   {
      char byte1 = b1->byte[0] << b1->ignore;
      char byte2 = b2->byte[0] << b2->ignore;
      if (byte1 != byte2)  return false;
   };
   for (size_t k = 1; k < b1->nbytes; k++)
   {
      if (b1->byte[k] != b2->byte[k])  return false;
   };
   return true;
};

// printing a bits_t instance
void bits_print(bits_t *bits)
{
   // the list of bits
   printf("[");
   for (size_t k = 0; k < bits->nbytes; k++)
   {
      short b = 7;
      if (k == 0 && bits->ignore != 0)  b = b - bits->ignore;
      for (; b >= 0; b--)
      {
         printf("%1d",(bits->byte[k]>>b)&1);
      };
      if (k != bits->nbytes - 1)  printf("|");
   };
   printf("] ");

   // info about the bit string
   size_t actual_bits = bits_actual_length(bits);
   printf("(%lu;%lu)",actual_bits,bits->nbytes);
};

// printing a bits_t instance with new line
void bits_println(bits_t *bits)
{
   bits_print(bits);
   printf("\n");
};

// freeing the memory for a bits_t instance
void bits_free(bits_t *bits)
{
   free(bits->byte);
   free(bits);
};

