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
}


void mettreAJourTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
    int indiceRemplacement = 0;
	int numeroPage = calculerNumeroDePage(req->adresseVirtuelle);
	int numeroCadre = calculerNumeroDePage(req->adressePhysique);
	unsigned long plusAncienneDate = mem->tlb->dateCreation[numeroPage];
	for (int i = 0; i < TAILLE_TLB; i++) {
		if(mem->tlb->entreeValide[i]){
			if (mem->tlb->dateCreation[i] < plusAncienneDate) {
				plusAncienneDate = mem->tlb->dateCreation[i];
				indiceRemplacement = i;
			}
		}
		else{
			indiceRemplacement = i;
			break;
		}
	}
    mem->tlb->numeroPage[indiceRemplacement] = numeroPage;
    mem->tlb->numeroCadre[indiceRemplacement] = numeroCadre;
    mem->tlb->entreeValide[indiceRemplacement] = 1;
    mem->tlb->dernierAcces[indiceRemplacement] = req->date;
    mem->tlb->dateCreation[indiceRemplacement] = req->date;
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
