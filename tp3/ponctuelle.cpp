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
  printf("\t$./ponctuelle numero\n");
  printf("\t -> numero: 2 .. 5\n");
}

int main (int argc, char* argv[]) {

  // Noms du fichier image et de la fenêtre d'affichage
  IplImage* image = NULL;
  IplImage* bin_image = NULL;
  IplImage* image_cmp = NULL;
  IplImage* bin_gimp1 = NULL;
  IplImage* bin_gimp2 = NULL;

  std::string nomFen = "binarization";
  std::string nomImage = "./img/gateaux1.png";

  int choix;

  // le meilleur threshold est de 30 pour gateaux1
  double t = 30;
  int max = 255;

  if( argc<2 || (argv[1]!=NULL && strcmp(argv[1], "-h")==0) ){
    usage();
    exit(EXIT_SUCCESS);
  }

  choix = atoi(argv[1]);
  
  if(choix<2 || choix>5){
    usage();
    exit(EXIT_SUCCESS);
  }

  switch(choix){

  case 2:

    // QUESTION 2

    double minVal, maxVal;
    CvPoint minLoc, maxLoc;

    // Lire le fichier image
    image = cvLoadImage( nomImage.data(), CV_LOAD_IMAGE_UNCHANGED );
    if ( !image ) {
      printf( "Impossible de charger l'image %s\n", nomImage.data() );
      exit( EXIT_FAILURE );
    }

    cvMinMaxLoc(image, &minVal, &maxVal, &minLoc, &maxLoc);

    printf("Info sur l'histogramme de %s:\n", nomImage.data() );
    printf("\t- valeur la plus somble: %lf\n", minVal);
    printf("\t- valeur la plus clair : %lf\n", maxVal);
    printf("\t- position du pixel le plus somble:\n");
    printf("\t\t- x: %d\n", minLoc.x);
    printf("\t\t- y: %d\n", minLoc.y);
    printf("\t- position du pixel le plus clair:\n");
    printf("\t\t- x: %d\n", maxLoc.x);
    printf("\t\t- y: %d\n", maxLoc.y);


    break;

  case 3:
    
    // QUESTION 3

    image = cvLoadImage( nomImage.data(), CV_LOAD_IMAGE_UNCHANGED );
    if ( !image ) {
      printf( "Impossible de charger l'image %s\n", nomImage.data() );
      exit( EXIT_FAILURE );
    }

    bin_image = cvCreateImage(cvGetSize(image), image->depth, image->nChannels);


    // Seuil binaire
    // les pixels > t seront initialisé a max
    // sinon zero
    // voir doc
    cvThreshold(image, bin_image, t, max, cv::THRESH_BINARY);

    cvNamedWindow(nomFen.data());
    cvShowImage(nomFen.data(), bin_image);
    cvWaitKey(0);
    cvDestroyWindow(nomFen.data());

    break;

  case 4:
    
    // QUESTION 4

    image = cvLoadImage( nomImage.data(), CV_LOAD_IMAGE_UNCHANGED );
    if ( !image ) {
      printf( "Impossible de charger l'image %s\n", nomImage.data() );
      exit( EXIT_FAILURE );
    }

    bin_image = cvCreateImage(cvGetSize(image), image->depth, image->nChannels);
    image_cmp = cvCreateImage(cvGetSize(image), image->depth, image->nChannels);

    // Seuil binaire
    // les pixels > t seront initialisé a max
    // sinon zero
    // voir doc
    cvThreshold(image, bin_image, t, max, cv::THRESH_BINARY);

    image = cvLoadImage( "./img/gateaux1_bin.png", CV_LOAD_IMAGE_UNCHANGED );
    if ( !image ) {
      printf( "Impossible de charger l'image %s\n", nomImage.data() );
      exit( EXIT_FAILURE );
    }

    cvCmp(bin_image, image, image_cmp, cv::CMP_NE);

    cvNamedWindow("T'=T");
    cvShowImage("T'=T", image_cmp);
    cvWaitKey(0);
    cvDestroyWindow("T'=T");

    printf("La distance des image avec les seuils T'=T: %d\n", cvCountNonZero(image_cmp));

    // Avec le meme seuil on remarque un legere different (quelques pixels près)
    // entre le seuil d'OpenCV et se lui de Gimp



    image = cvLoadImage( "./img/gateaux1_bin2.png", CV_LOAD_IMAGE_UNCHANGED );
    if ( !image ) {
      printf( "Impossible de charger l'image %s\n", nomImage.data() );
      exit( EXIT_FAILURE );
    }

    cvCmp(bin_image, image, image_cmp, cv::CMP_NE);

    cvNamedWindow("T'=2T");
    cvShowImage("T'=2T", image_cmp);
    cvWaitKey(0);
    cvDestroyWindow("T'=2T");

    printf("La distance des image avec les seuils T'=2T: %d\n", cvCountNonZero(image_cmp));
    
    // Avec un seuil à 60 sur gimp et à 30 sur OpenCV
    // la difference est visible sur les bords des gateaux

    break;

  case 5:
    
    // QUESTION 4

    image = cvLoadImage( nomImage.data(), CV_LOAD_IMAGE_UNCHANGED );
    if ( !image ) {
      printf( "Impossible de charger l'image %s\n", nomImage.data() );
      exit( EXIT_FAILURE );
    }

    bin_gimp1 = cvLoadImage( "./img/gateaux1_bin.png", CV_LOAD_IMAGE_UNCHANGED );
    if ( !bin_gimp1 ) {
      printf( "Impossible de charger l'image %s\n", nomImage.data() );
      exit( EXIT_FAILURE );
    }

    bin_gimp2 = cvLoadImage( "./img/gateaux1_bin2.png", CV_LOAD_IMAGE_UNCHANGED );
    if ( !bin_gimp2 ) {
      printf( "Impossible de charger l'image %s\n", nomImage.data() );
      exit( EXIT_FAILURE );
    }

    bin_image = cvCreateImage(cvGetSize(image), image->depth, image->nChannels);
    image_cmp = cvCreateImage(cvGetSize(image), image->depth, image->nChannels);

    printf("THRESH_BINARY:\n");
    cvThreshold(image, bin_image, t, max, cv::THRESH_BINARY);

    cvNamedWindow("THRESH_BINARY");
    cvShowImage("THRESH_BINARY", bin_image);
    cvWaitKey(0);
    cvDestroyWindow("THRESH_BINARY");

    cvCmp(bin_image, bin_gimp1, image_cmp, cv::CMP_NE);
    printf("\t distance avec T'=T: %d\n", cvCountNonZero(image_cmp));

    cvCmp(bin_image, bin_gimp2, image_cmp, cv::CMP_NE);
    printf("\t- distance avec T'=2T = %d\n", cvCountNonZero(image_cmp));

    printf("\n");


    printf("THRESH_TRUNC:\n");
    cvThreshold(image, bin_image, t, max, cv::THRESH_TRUNC);

    cvNamedWindow("THRESH_TRUNC");
    cvShowImage("THRESH_TRUNC", bin_image);
    cvWaitKey(0);
    cvDestroyWindow("THRESH_TRUNC");

    cvCmp(bin_image, bin_gimp1, image_cmp, cv::CMP_NE);
    printf("\t distance avec T'=T: %d\n", cvCountNonZero(image_cmp));

    cvCmp(bin_image, bin_gimp2, image_cmp, cv::CMP_NE);
    printf("\t- distance avec T'=2T = %d\n", cvCountNonZero(image_cmp));

    printf("\n");
    
    
    printf("THRESH_OTSU:\n");

    cvThreshold(image, bin_image, t, max, cv::THRESH_OTSU);

    cvNamedWindow("THRESH_OTSU");
    cvShowImage("THRESH_OTSU", bin_image);
    cvWaitKey(0);
    cvDestroyWindow("THRESH_OTSU");

    cvCmp(bin_image, bin_gimp1, image_cmp, cv::CMP_NE);
    printf("\t distance avec T'=T: %d\n", cvCountNonZero(image_cmp));

    cvCmp(bin_image, bin_gimp2, image_cmp, cv::CMP_NE);
    printf("\t- distance avec T'=2T = %d\n", cvCountNonZero(image_cmp));

    printf("\n");
    

    break;
  }


  // Terminer
  cvDestroyAllWindows();
  cvReleaseImage( &image );
  exit(EXIT_SUCCESS);
}
