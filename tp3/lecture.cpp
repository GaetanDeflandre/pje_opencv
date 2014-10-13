/* --------------------------------------------------------------------------
   Introduction à OpenCV, projet encadre IVI
   -------------------------------------------------------------------------- */



/* --------------------------------------------------------------------------
   Inclure les fichiers d'entete
   -------------------------------------------------------------------------- */
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <cv.h>
#include <highgui.h>



/* --------------------------------------------------------------------------
   Programme principal
   -------------------------------------------------------------------------- */
void usage(){
  printf("Usage:\n");
  printf("\t$./lecture 1\n");
  printf("\t$./lecture 2 image_path\n");
  printf("\t$./lecture 3 image_path\n");
}

int main (int argc, char* argv[]) {

  // Noms du fichier image et de la fenêtre d'affichage
  IplImage* image = NULL;
  std::string nomImage = "./img/gateaux1.png";
  std::string nomFenetre = "pjE3";

  int choix;

  if( argc<2 || (argv[1]!=NULL && strcmp(argv[1], "-h")==0) ){
    usage();
    exit(EXIT_SUCCESS);
  }

  choix = atoi(argv[1]);
  
  if(choix<0 || choix>3){
    usage();
    exit(EXIT_SUCCESS);
  }

  switch(choix){

  case 1:

    // QUESTION 1

    // Lire le fichier image
    image = cvLoadImage( nomImage.data(), CV_LOAD_IMAGE_UNCHANGED );
    if ( !image ) {
      printf( "Impossible de charger l'image %s\n", nomImage.data() );
      exit( EXIT_FAILURE );
    }

    // Créer une fenêtre et y afficher l'image
    cvNamedWindow( nomFenetre.data() );
    cvShowImage( nomFenetre.data(), image );

    // Afficher des propriétés de l'image sur la console
    printf( "Infos sur l'image %s\n", nomImage.data() );
    printf( "Definition \t: %dx%d pixels\n", image->width, image->height );
    printf( "Taille \t\t: %d octets\n", image->imageSize );
    printf( "Profondeur \t: %d\n", image->depth );
    printf( "Nb de canaux \t: %d\n", image->nChannels );
    printf( "Appuyer sur une touche pour terminer.\n" );

    // Sur appui d'une touche, fermer la fenêtre et libérer la mémoire image
    cvWaitKey( 0 );
    cvDestroyWindow( nomFenetre.data() );
    break;

  case 2:

    // QUESTION 2
    
    if(argv[2]==NULL){
      usage();
      exit(EXIT_SUCCESS);
    }

    nomImage = argv[2];
    
      // Lire le fichier image
      image = cvLoadImage( nomImage.data(), CV_LOAD_IMAGE_UNCHANGED );
      if ( !image ) {
	printf( "Impossible de charger l'image %s\n", nomImage.data() );
	exit( EXIT_FAILURE );
      }

      // Créer une fenêtre et y afficher l'image
      cvNamedWindow( nomFenetre.data() );
      cvShowImage( nomFenetre.data(), image );

      // Afficher des propriétés de l'image sur la console
      printf( "Infos sur l'image %s\n", nomImage.data() );
      printf( "Definition \t: %dx%d pixels\n", image->width, image->height );
      printf( "Taille \t\t: %d octets\n", image->imageSize );
      printf( "Profondeur \t: %d\n", image->depth );
      printf( "Nb de canaux \t: %d\n", image->nChannels );
      printf( "Appuyer sur une touche pour terminer.\n" );

      // Sur appui d'une touche, fermer la fenêtre et libérer la mémoire image
      cvWaitKey( 0 );
      cvDestroyWindow( nomFenetre.data() );
      break;

  case 3:

    // QUESTION 3
    
    if(argv[2]==NULL){
      usage();
      exit(EXIT_SUCCESS);
    }

    nomImage = argv[2];
    
      // Lire le fichier image
      image = cvLoadImage( nomImage.data(), CV_LOAD_IMAGE_GRAYSCALE );
      if ( !image ) {
	printf( "Impossible de charger l'image %s\n", nomImage.data() );
	exit( EXIT_FAILURE );
      }

      printf("\n -> Image ouvert en mode grayscale.\n\n");

      // Créer une fenêtre et y afficher l'image
      cvNamedWindow( nomFenetre.data() );
      cvShowImage( nomFenetre.data(), image );

      // Afficher des propriétés de l'image sur la console
      printf( "Infos sur l'image %s\n", nomImage.data() );
      printf( "Definition \t: %dx%d pixels\n", image->width, image->height );
      printf( "Taille \t\t: %d octets\n", image->imageSize );
      printf( "Profondeur \t: %d\n", image->depth );
      printf( "Nb de canaux \t: %d\n", image->nChannels );
      printf( "Appuyer sur une touche pour terminer.\n" );

      // Sur appui d'une touche, fermer la fenêtre et libérer la mémoire image
      cvWaitKey( 0 );
      cvDestroyWindow( nomFenetre.data() );
      break;
      
  }


  // Terminer
  cvDestroyAllWindows();
  cvReleaseImage( &image );
  exit(EXIT_SUCCESS);
}
