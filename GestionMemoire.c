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
