///Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa    
    
typedef struct Graph
{
    int v;  ///nr de noduri (restaurante)
    int *vis; ///vector care marcheaza nodurile vizitate
    struct Node **alst; ///lista de adiacenta pt fiecare nod
} GPH;

typedef struct Stack
{
    int t; ///varful stivei
    int scap; ///capacitatea stivei
    int *arr; ///vector pt stocarea elementelor stivei
} STK;

NODE *create_node(int v)
{
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g,int src,int dest)
{
    NODE *nn = create_node(dest); ///creeaza nod pt destinatie
    nn->next = g->alst[src]; /// leaga nodul la lista de adiacenta
    g->alst[src] = nn; ///actualizeaza lista

    ///adauga si muchia inversa, fiind un graf neorientat
    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_graph(int v)  ///creeaza graf cu un nr dat de noduri
{
    int i;
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(sizeof(NODE *) * v);
    g->vis = malloc(sizeof(int) *v);

    for (int i=0; i<v; i++)
    {
        g->alst[i] = NULL;
        g->vis[i]  = 0;
    }   
    return g; ///returneaza graful creat
}

STK *create_stack(int scap) ///creeaza stiva cu capacitatea data
{
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;

    return s; ///returneaza stiva creata
}

void push(int pshd,STK *s) ///adauga element in varful stivei
{
    s->t = s->t + 1; ///creste varful
    s->arr[s->t] = pshd; ///adauga element in stiva
}

void DFS(GPH *g,STK *s,int v_nr) ///functie de cautare in adancime pt parcurgere grafic
{
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;
    g->vis[v_nr] = 1; /// marcheaza nodul ca vizitat
    printf("%d ",v_nr);
    push(v_nr, s);

    while (aux != NULL) ///parcurge lista vecini
    {
        int con_ver = aux->data; ///vecin
        if (g->vis[con_ver] == 0) ///daca vecinul nu a fost vizitat
        {
            DFS(g, s, con_ver); ///apel recursiv pt vecin
        }
        aux = aux->next; ///trece la urm vecin
    }
}

void insert_edges(GPH *g,int edg_nr) ///functie pt introducere muchii in graf
{
    int src, dest, i;
    printf("adauga %d munchii (de la 1 la %d)\n",edg_nr, g->v);
    for (i=0; i<edg_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(g, src-1, dest-1); ///adauga muchia in graf ajustat pt indexare 0
    }
}

void wipe(GPH *g)
{
    for (int i=0;i < g->v; i++)
    {
        g->vis[i] = 0; ///marcheaza nodurile ca nevizitate
    }
}  

void canbe(GPH *g, int nrv, STK *s1, STK *s2)// 0 sau 1 daca poate fi sau nu ajuns
{
    int ans = 0;
    for (int i = 0; i < nrv; i++) // aici i tine loc de numar adica de restaurant{for (int j = 0; j < 5; j++)
        {
            DFS(g, s1, i);
            wipe(g);

            DFS(g, s2, i);

            for (int j = 0; j < nrv && !ans; j++)
            {
                for (int k = 0; i < nrv && !ans; k++)
                {
                    if ((s1->arr[j] == k) && (s2->arr[j] == j))
                    {
                        ans = 1; ///daca exista drum direct
                    }
                }
            }
        }
            if(ans)
            {
                printf("Exista un drum direct intre restaurante.\n");
            }
            else
            {
                printf("Nu exista un drum direct intre restaurante.\n");
            }
}


int main()
{

    int nrv;
    int edg_nr;

    printf("Cate noduri(restaurante) are graful?");
    scanf("%d", &nrv);

    printf("Cate muchii(conexiuni) are graful?");
    scanf("%d", &edg_nr);

    GPH *g = create_graph(nrv);

    STK *s1 = create_stack(2 * nrv);
    STK *s2 = create_stack(2 * nrv);

    insert_edges(g, edg_nr);

    canbe(g, nrv, s1, s2);
    return 0;
}