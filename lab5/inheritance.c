// Simulate genetic inheritance of blood type // Simula a herança genética do tipo sanguíneo

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles // Cada pessoa tem dois pais e dois alelos
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

// Prototypes // Protótipos
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();


int main(void)
{
    // Seed random number generator // Gerador de números aleatórios de sementes
    srand(time(0));

    // Create a new family with three generations // Crie uma nova família com três gerações
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types // Imprimir árvore genealógica de tipos sanguíneos
    print_family(p, 0);

    // Free memory // Liberar memory
    free_family(p);
}

// Create a new individual with `generations` // Crie um novo indivíduo com `gerações`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person // Alocar memoria para uma nova pessoa
    person *c = malloc(sizeof(person));

    // TODO: Handle base case // Lidar com a caixa de base
    if (c == NULL)
    {
        return NULL;
    }

    // Generation with parent data // Geração com dados dos pais
    if (generations > 1)
    {
        // TODO: Recursively create blood type histories for parents // Criar recursivamente históricos de tipo sanguíneo para os pais
        for (int index_c = 0; index_c < 2; index_c++)
        {
            c->parents[index_c] = create_family(generations - 1);
        }

        // TODO: Randomly assign child alleles based on parents // Atribuir alelos dos filhos aleatoriamente com base nos pais
        for (int index_a = 0; index_a < 2; index_a++)
        {
            c->alleles[index_a] = c->parents[index_a]->alleles[rand() % 2];
        }
    }

    // Generation without parent data // Geração sem dados pai
    else
    {
        // TODO: Set parent pointers to NULL // Definir ponteiros pai para NULL
        for (int index_c = 0; index_c < 2; index_c++)
        {
            c->parents[index_c] = NULL;
        }

        // TODO: Randomly assign alleles // Atribuir alelos aleatoriamente
        for (int index_r = 0; index_r < 2; index_r++)
        {
            c->alleles[index_r] = random_allele();
        }
    }

    // TODO: Return newly created person // Retornar pessoa recém-criada
    return c;
}

// Free `p` and all ancestors of `p`. // Livre `p` e todos os ancestrais de` p`.
void free_family(person *p)
{
    // TODO: Handle base case // Lidar com a caixa de base
    if (p == NULL)
    {
        return ;
    }
    // TODO: Free parents // Liberar Pais
    for (int index_p = 0; index_p < 2; index_p++)
    {
        free_family(p->parents[index_p]);
    }
    // TODO: Free child // Liberar Filho
    free(p);
}

// Print each family member and their alleles. // Imprima cada membro da família e seus alelos.
void print_family(person *p, int generation)
{
    // Handle base case // Lidar com a caixa de base
    if (p == NULL)
    {
        return;
    }

    // Print indentation // Imprimir recuo
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person // Imprimir pessoa
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele. // Escolhe aleatoriamente um alelo de tipo sanguíneo.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
