#include<stdio.h>
#include<stdlib.h>


// la structure de données Page qui définit une page web
typedef struct page {
    int numero;
    char *titre;
    char *contenu;
} Page;

// la structure de données ElementPage pour gérer la liste chainée des pages web
typedef struct elementPage {
    Page *page;
    struct elementPage *next;
} ElementPage;

// la structure de données qui définit un élément doublement chainée des pages web
typedef struct elementDCPage {
    Page *page;
    struct elementDCPage *precedent;
    struct elementDCPage *suivant;
} ElementDCPage;

// la structure de données qui définit l'adresse de début et l'adresse de fin de la liste doublement chainée
typedef struct listDC {
    ElementDCPage *first;
    ElementDCPage *last;
} ListDC;

//fonction qui crée une page
Page *createPage(int num, char *titre, char *contenu) {
    Page *nouvellePage;
    nouvellePage = (Page *) malloc(sizeof(Page));
    nouvellePage->numero = num;
    nouvellePage->titre = titre;
    nouvellePage->contenu = contenu;
    return nouvellePage;
}

//fonction qui créee un élément de la liste
ElementPage *createElementPage(Page *page) {
    ElementPage *elementPage;
    elementPage = (ElementPage *) malloc(sizeof(ElementPage));
    elementPage->page = page;
    elementPage->next = NULL;
    return elementPage;
}

//fonction retourne la derniére adresse d'une liste chainée
ElementPage *lastAdressEltPg(ElementPage *L) {
    ElementPage *elementPage;
    if (L == NULL) return NULL;
    for (elementPage = L; elementPage->next != NULL; elementPage = elementPage->next);
    return elementPage;
}

//la fonction permet d'ajouter une page web à la liste chainée
void addPage(Page *page, ElementPage **L) {
    ElementPage *elementPage = createElementPage(page);
    if (*L == NULL) {
        *L = elementPage;
        return;
    } else {
        lastAdressEltPg(*L)->next = elementPage;
    }
}

//le fonction qui permet d'afficher le détail d'une page WEB
void displayPage(Page *page) {
    printf("_______________________________________________________________________________________\n");
    printf(" Numero    |      TITRE         |   CONTENU                                            |\n");
    printf("___________|____________________|______________________________________________________|\n");
    printf("\n %d\t\t%s\t%s\n", page->numero, page->titre, page->contenu);
}

Page *getPage(int num, ElementPage *L) {
    ElementPage *temp = L;
    //Tant que on n'est pas au bout de la liste
    while (temp != NULL) {
        if (temp->page->numero == num) {
            //Si le produit a la valeur recherchÃˆe, on renvoie son adresse
            return temp->page;
        }
        temp = temp->next;
    }
    //s'il n'y a aucun produit avec ce code recherché on renvoie NULL
    return NULL;
}

//la fonction qui crée un élément de la liste chainée
ElementDCPage *createElementDCPage(Page *page) {
    ElementDCPage *newElem;
    newElem = (ElementDCPage *) malloc(sizeof(ElementDCPage));
    newElem->page = page;
    newElem->precedent = NULL;
    newElem->suivant = NULL;
    return newElem;
}

//la fonction qui crée une liste doublement chainée
ListDC *createListDC() {
    ListDC *L;
    L = (ListDC *) malloc(sizeof(ListDC));
    L->first = NULL;
    L->last = NULL;
    return L;
}

//la fonction qui permet d'ajouter une page web â€¡ la liste doublement chainÃˆe
void addPageDC(Page *page, ListDC *L) {
    ElementDCPage *elemDC;
    elemDC = createElementDCPage(page);
    if (L->first == NULL) {
        L->first = L->last = elemDC;
        return;
    }
    L->last->suivant = elemDC;
    elemDC->precedent = L->last;
    L->last = elemDC;
}

//qui permet d'afficher le contenu de la liste doublement chainée de pages
//web depuis le début de la liste
void displayFromFirst(ListDC *L) {
    ElementDCPage *eltDC;
    eltDC = L->first;
    while (eltDC) {
        displayPage(eltDC->page);
        eltDC = eltDC->suivant;
    }
}

// qui permet d'afficher le contenu de la liste doublement chainée de pages
//web depuis le début de la liste
void displayFromLast(ListDC *L) {
    ElementDCPage *eltDC;
    eltDC = L->last;
    while (eltDC) {
        displayPage(eltDC->page);
        eltDC = eltDC->precedent;
    }
}

int main() {
    ElementDCPage *pageActuelle = NULL;
    char caractere;
    int numPg;
    //________________décalaration et initialisation des pages______________
    Page *page1, *page2, *page3, *page4, *page5, *page6, *page7, *page8, *pageCherche;
    page1 = createPage(1, "khaoula elmajni", "blog de khaoula elmajni");
    page2 = createPage(2, "wikipedia", "definition du langage C");
    page3 = createPage(3, "hespress", "nouvelles du monde");
    page4 = createPage(4, "wordpress", "content management system");
    page5 = createPage(5, "blogspot", "blogger\'s website");
    page6 = createPage(6, "facebook", "connectez-vous ou creer un compte");
    page7 = createPage(7, "stuckoverflow", "site web de changement d\'idee a propos des codes");
    page8 = createPage(8, "w3schools", "certifiez-vous en connectant et continuant les tutos");

    //____________traitement de la liste simplement chainée________________
    ElementPage *listPage;
    listPage = NULL;

    addPage(page1, &listPage);
    addPage(page2, &listPage);
    addPage(page3, &listPage);
    addPage(page4, &listPage);
    addPage(page5, &listPage);
    addPage(page6, &listPage);
    addPage(page7, &listPage);
    addPage(page8, &listPage);

    //_________________traitement de la liste doublement chainée_________________
    ListDC *LDC;
    LDC = createListDC();

    //_________________traitement d'affichage_____________________________________
    printf("_______________________Bonjour tout le monde_______________________\n");
    printf("Indication : \n\tTaper un 'W' || 'w' pour naviguer\n\tTaper un 'P' || 'p' pour retourner a la page precedente\n\tTaper un 'N' || 'n' pour aller a la page suivante\n\n");
    do {
        printf("Taper un caractere : ");
        scanf(" %c", &caractere);

        if (caractere == 'W' || caractere == 'w') {
            printf("\nVeuillez saisir le numero de la page souhaitee : ");
            scanf("%d", &numPg);
            pageCherche = getPage(numPg, listPage);
            if (pageCherche == NULL)
                printf("\n\n\aLe numero de la page que vous avez entre n\'existe pas!!! ressayez un autre numero!\n\n");
            else
                displayPage(pageCherche);
            addPageDC(pageCherche, LDC);
            pageActuelle = LDC->last;

        }
        if (caractere == 'P' || caractere == 'p') {
            if (LDC->last != NULL) {
                if (LDC->last->precedent != NULL) {
                    pageActuelle = pageActuelle->precedent;
                    if (pageActuelle != NULL) {
                        displayPage(pageActuelle->page);
                    } else {
                        printf("C'est la premiere page, pas de precedent !\n");
                        pageActuelle = LDC->first;
                    }
                } else
                    printf("\nVous n\'avez pas encore naviguer entre des page web ou c\'est votre 1ere page!\n");
            }else{
                printf("La liste est vide, pas de suivant ou precedent !\n");
            }
        }
        if (caractere == 'N' || caractere == 'n') {
            if (LDC->last != NULL) {
                if (LDC->last->precedent != NULL) {
                    pageActuelle = pageActuelle->suivant;
                    if (pageActuelle != NULL) {
                        displayPage(pageActuelle->page);
                    } else {
                        printf("C'est la derniere page, pas de suivant !\n");
                        pageActuelle = LDC->last;
                    }
                } else
                    printf("\nVous n\'avez pas encore naviguer entre des page web ou c\'est votre 1ere page!\n");
            }else{
                printf("La liste est vide, pas de suivant ou precedent !\n");
            }
        }

    } while (caractere != 'E' && caractere != 'e');

    printf("\n\n________________________AFIICHAGE DE LISTE DOUBLEMENT CHAINEE DU DEBUT________________________\n\n");
    displayFromFirst(LDC);
    printf("\n\n________________________AFIICHAGE DE LISTE DOUBLEMENT CHAINEE DE LA FIN________________________\n\n");
    displayFromLast(LDC);
}




