
/* bits type (testing)
 *
 * These are strings of bits of variable length
 *
 * last update: September 29th, 2024
 *
 * AM
 */

#include "bits.h"
#include "assert.h"

// Vos autres déclarations et structures ici...



// Fonction pour calculer la distance de Hamming entre deux chaînes binaires
size_t bits_hamming_distance(bits_t *b1, bits_t *b2) {
    size_t hamming_distance = 0;
    for (size_t k = 0; k < b1->nbytes; k++) {
        char xor_byte = b1->byte[k] ^ b2->byte[k]; // XOR des octets correspondants
        hamming_distance += __builtin_popcount(xor_byte); // Compter les bits différents
    }
    return hamming_distance;
}


int main()
{
   /*
   *  ###########################
   *     Création de b1 et b2 
   *     de même taille, et de
   *      bits différents 
   *  ###########################
   */ 

  // Créer deux chaînes de 16 bits, b1 et b2

   bits_t *b1 = bits_ones(15);  // Chaîne binaire de 40 bits remplie de zéros
   bits_t *b2 = bits_ones(15);   // Chaîne binaire de 40 bits remplie de uns
   size_t dist = 8;  // La distance de Hamming souhaitée
   bits_t *b = bits_random_from(b1, b2, dist);
   printf("b1 : ----> \n");
   bits_println(b1);

   printf("b2 : ----> \n");
   bits_println(b2);

   printf("b : ----> \n");
   bits_println(b);


   /*
   printf("bits_t type\n");
   bits_t *zero = bits_zeros(30);
   bits_println(zero);
   
   printf("Number of 0's : %lu\n",bits_nzeros(zero));
   bits_t *one = bits_ones(20);
   bits_println(one);
   printf("Number of 1's : %lu\n",bits_nones(one));
   printf("These two bit strings are identical : ");
   bool answer = bits_equals(one,one);
   if (answer) printf("YES!\n"); else printf("NO\n");
   bits_t *random = bits_random(40);
   bits_println(random);
   */


   /* ##############################
   *    La libération de la mémoire
   *  ##############################
   */

   /*
   printf("Les valeurs à partir de maintenant font reference au random \n");
   printf("Number of 0's : %lu\n",bits_nzeros(random));
   printf("Number of 1's : %lu\n",bits_nones(random));
   printf("Cloning ... ");
   bits_t *cloned = bits_clone(random);
   bits_println(cloned);
   printf("These two bit strings are identical : ");
   answer = bits_equals(cloned,random);
   if (answer) printf("YES!\n"); else printf("NO\n");
   */

   /* ##############################
   *    La libération de la mémoire
   *  ##############################
   */

   
   bits_free(b1);
   bits_free(b2);
   bits_free(b);
   
   
};

