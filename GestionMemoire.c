#include "./libs/lib.h"
#include <stdio.h>

unsigned long TAILLE_PAGE = 1024;

unsigned int calculerNumeroDePage(unsigned long adresse)
{
	return adresse / TAILLE_PAGE;
}

unsigned long calculerDeplacementDansLaPage(unsigned long adresse)
{
	return adresse % TAILLE_PAGE;
}

unsigned long calculerAdresseComplete(unsigned int numeroDePage, unsigned long deplacementDansLaPage)
{
	return (numeroDePage * TAILLE_PAGE) + deplacementDansLaPage;
}

void rechercherTLB(struct RequeteMemoire *req, struct SystemeMemoire *mem)
{
	unsigned int numPage = calculerNumeroDePage(req->adresseVirtuelle);
	unsigned long depPage = calculerDeplacementDansLaPage(req->adresseVirtuelle);
	for (int i = 0; i < TAILLE_TLB; i++)
	{
		if (mem->tlb->numeroPage[i] == numPage && mem->tlb->entreeValide[i])
		{
			unsigned int numCadre = mem->tlb->numeroCadre[i];
			req->adressePhysique = calculerAdresseComplete(numCadre, depPage);
			req->estDansTLB = 1;
			mem->tlb->dernierAcces[i] = req->date;

			return;
		}
	}
	req->adressePhysique = 0;
	req->estDansTLB = 0;
}

<<<<<<< HEAD
void rechercherTableDesPages(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	unsigned int numeroDePage = calculerNumeroDePage(req->adresseVirtuelle);
	unsigned long offsetAdresse = calculerDeplacementDansLaPage(req->adresseVirtuelle);
	if(mem->tp->entreeValide[numeroDePage]){
		int numeroDeCadre = mem->tp->numeroCadre[numeroDePage];
		req->adressePhysique = calculerAdresseComplete(numeroDeCadre, offsetAdresse);
	}
	else{
		req->adressePhysique = 0;
	}
}

void ajouterDansMemoire(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	int page = calculerNumeroDePage(req->adresseVirtuelle);

    // Trouver le premier cadre disponible
    int premierCadreDisponible = 0;
	 for (int i = 0; i < TAILLE_MEMOIRE; i++) {
        if (!mem->memoire->utilisee[i]) {
            premierCadreDisponible = i;
        }
    }

    // Ajouter la page dans la mémoire
    mem->memoire->utilisee[premierCadreDisponible] = 1;
    mem->memoire->numeroPage[premierCadreDisponible] = page;
    mem->memoire->dateCreation[premierCadreDisponible] = req->date;
    mem->memoire->dernierAcces[premierCadreDisponible] = req->date;

    // Mise à jour de la table des pages
    mem->tp->entreeValide[page] = 1;
    mem->tp->numeroCadre[page] = premierCadreDisponible;
}


void mettreAJourTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	//Trouver l'indice plus ancien
    int indiceRemplacement = 0;
	unsigned long plusAncienneDate = mem->tlb->dateCreation[0];

    for (int i = 1; i < TAILLE_TLB; i++) {
        if (mem->tlb->dateCreation[i] < plusAncienneDate) {
            plusAncienneDate = mem->tlb->dateCreation[i];
            indiceRemplacement = i;
        }
    }

    // Remplacer les informations dans l'entrée du TLB
    mem->tlb->numeroPage[indiceRemplacement] = calculerNumeroDePage(req->adresseVirtuelle);
    mem->tlb->numeroCadre[indiceRemplacement] = mem->tp->numeroCadre[calculerNumeroDePage(req->adresseVirtuelle)];
    mem->tlb->entreeValide[indiceRemplacement] = 1;
    mem->tlb->dernierAcces[indiceRemplacement] = req->date;
    mem->tlb->dateCreation[indiceRemplacement] = req->date;
=======
void rechercherTableDesPages(struct RequeteMemoire *req, struct SystemeMemoire *mem)
{
	// TODO
}

void ajouterDansMemoire(struct RequeteMemoire *req, struct SystemeMemoire *mem)
{
	// TODO
}

void mettreAJourTLB(struct RequeteMemoire *req, struct SystemeMemoire *mem)
{
	// TODO
>>>>>>> 704e2e99ea4426d659338e3dba4f78b10748370f
}

// NE PAS MODIFIER
int main()
{
	evaluate(
		&calculerNumeroDePage,
		&calculerDeplacementDansLaPage,
		&calculerAdresseComplete,
		&rechercherTLB,
		&rechercherTableDesPages,
		&mettreAJourTLB,
		&ajouterDansMemoire);
	return 0;
}
