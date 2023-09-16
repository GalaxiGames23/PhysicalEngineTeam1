#include "../../src/Input.h"
#include "../../src/Vector.h"
#include "../../src/Particule.h"
#include "TestVector.h"
#include "TestInput.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>


// Fonction pour afficher du texte en couleur avec printf
void printColoredText(const char* text, const char* color) {
    printf("\033[%sm%s\033[0m", color, text);
}

// Fonction pour exécuter un test et afficher le résultat en couleur
template <typename TestFunction>
void runTest(const char* testName, TestFunction testFunction) {
    printf("  Test \"%s\": ", testName);
    if (testFunction()) {
        printColoredText("PASSED\n", "32");  // Vert pour le succès
    }
    else {
        printColoredText("FAILED\n", "31");  // Rouge pour l'échec
    }
    printf("\n");
}


int main() {
    printColoredText("Test sur la classe Vecteur :\n\n", "33");

    runTest("Addition:", testVectAddition);

    runTest("Multiplication:", testVectMult);

    runTest("Produit scalaire:", testVectScalarProd);

    runTest("Produit vectoriel:", testVectVectProd);

    runTest("Norme:", testVectNorm);

    runTest("Normalisation:", testVectNormalisation);

    printColoredText("\nTest sur la classe Input :\n\n", "33");

    runTest("Initialisation du vecteur:", testSetInput);

    runTest("Reinitialisation du vecteur",testReset );

    runTest("Augmenter la norme:", testIncreaseNorm);

    runTest("Decroitre la norme:", testDecreaseNorm);

    runTest("Augmenter l'angle:", testIncreaseAngle);

    runTest("Decroitre l'angle:", testDecreaseAngle);
    

    return 0;
}