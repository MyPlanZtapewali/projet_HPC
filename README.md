# projet_HPC


### Sujet du Projet : 

Génération aléatoire entre deux chaînes avec distance de Hamming fixe : étant données  

deux chaînes b1 et b2 de bits de la même longueur mais différentes, et un entier positif dist,  

générer une nouvelle chaîne aléatoire b telle que: 

    -   avant de commencer, vérifier (avec un assert) que la distance de Hamming entre b1 et b2 est inférieure ou égale à dist 

    -   les bits de b telle que leur correspondant en b1^b2 est 0 restent identiques à ceux de b1 et b2 

    -  tous les autres bits correspondent soit au bit en b1, soit au bit en b2 

    -   la distance de Hamming entre b et b1 doit être dist 

bits_t* bits_random_from(bits_t *b1,bits_t *b2,size_t dist); 

Sur GPU: après avoir affecté deux chaînes de bits différentes à tous les threads (les threads auront tous accès à la même copie des deux chaînes), utiliser cette méthode pour générer des nouvelles instances de bits_t sur chaque thread (en modifiant aussi la valeur de dist). Ensuite, vérifier, sur CPU, que la distance de Hamming entre b1 et toutes les nouvelles chaînes générées est bien égale à l'argument dist. 
