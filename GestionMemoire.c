#include "./libs/lib.h"
unsigned long TAILLE_PAGE = 1024;

unsigned int calculerNumeroDePage(unsigned long adresse) {
    return adresse / TAILLE_PAGE;
}

unsigned long calculerDeplacementDansLaPage(unsigned long adresse) {
     return adresse % TAILLE_PAGE;
}

unsigned long calculerAdresseComplete(unsigned int numeroDePage, unsigned long deplacementDansLaPage) {
     return (numeroDePage*TAILLE_PAGE) + deplacementDansLaPage;
}

void rechercherTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
}

void rechercherTableDesPages(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
}

void ajouterDansMemoire(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	//TODO
}

void mettreAJourTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
}

// NE PAS MODIFIER
int main() {
    evaluate(
		&calculerNumeroDePage, 
		&calculerDeplacementDansLaPage, 
		&calculerAdresseComplete, 
        &rechercherTLB, 
		&rechercherTableDesPages,
		&mettreAJourTLB,
		&ajouterDansMemoire
    );
    return 0;
}
