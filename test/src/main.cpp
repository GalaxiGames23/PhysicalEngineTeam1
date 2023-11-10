#include "../../src/Input.h"
#include "../../src/Vector.h"
#include "../../src/Particule.h"
#include "TestVector.h"
#include "TestInput.h"
#include "TestRegistre.h"
#include "TestQuaternion.h"
#include "TestMatrix.h"
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

    printColoredText("\nTest sur le Registre :\n\n", "33");
    
    runTest("Addition au registre", testRegistreAdd);
    
    runTest("Retrait du registre", testRegistreRemove);
    
    runTest("Clear du registre", testRegistreClear);

    printColoredText("\nTest sur la classe Matrix:\n\n", "33");

    runTest("Addition de matrices", testMatrixAddition);

    runTest("Soustraction de matrices", testMatrixSub);

    runTest("Multiplication de matrices", testMatrixMult);

    runTest("Transposee de matrices", testMatrixTransposed);

    runTest("Determinant de matrices", testMatrixDeterminant);

    runTest("Adjacent de matrices", testMatrixAdjacent);

    runTest("Inverse de matrices", testMatrixInverse);

    printColoredText("\nTest sur la classe Quaternion:\n\n", "33");

    runTest("Addition de quaternions", testQuaternionAddition);

    runTest("Soustraction de quaternions", testQuaternionSub);

    runTest("Multiplication de quaternions", testQuaternionMult);

    runTest("Norme de quaternions", testQuaternionNorm);

    runTest("Negation de quaternions", testQuaternionNegation);

    runTest("Produit Scalaire de quaternions", testQuaternionScalarProd);

    runTest("Conjugue de quaternions", testQuaternionConjugate);

    runTest("Inverse de quaternions", testQuaternionInvers);
    
    runTest("Difference de quaternions", testQuaternionDiff);


    return 0;
}