//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Image Management
//  @ File Name : IM_Image.h
//  @ Date : 20/04/2007
//  @ Author : Thibaut Aubrun http://aubrun.thibaut.free.fr
//
//


#if !defined(_IM_IMAGE_H)
#define _IM_IMAGE_H

#include <list>
#include <utility>
#include <iostream>
#include <fstream>

#include "export.h"
#include "definition.h"


#include "lignel.h"
#include "transform.h"
#include "logger-file.h"
#include "logger-debug.h"
#include "file.h"
#include "exceptions.h"
#include "image-memory.h"

namespace fogrimmi
{
  class IM_Transform;
  class IM_Lignel;
  class IM_ImageMemory;


  //==========================================================
  /// Classe mere des images
  //==========================================================
  class IM_EXPORT IM_Image
  {

  public:

    //----------------------------------------------------------
    /// Constructeur par defaut
    //----------------------------------------------------------
    IM_Image();

    //----------------------------------------------------------
    /// Constructeur par recopie
    //----------------------------------------------------------
    IM_Image(const IM_Image &imgSource);

    //----------------------------------------------------------
    /// Destructeur
    //----------------------------------------------------------
    virtual ~IM_Image();

    //----------------------------------------------------------
    /// Ouvre un fichier image en lecture et récupère ses caractéristiques \n peut lever une exception de type CLoadingFailed
    //----------------------------------------------------------
    virtual void          open          () = 0;
    //----------------------------------------------------------
    /// Ferme le fichier
    //----------------------------------------------------------
    virtual void          close         () = 0;

    //----------------------------------------------------------
    /// Lecture de l'image
    //----------------------------------------------------------
    virtual void          read          () = 0;
    //----------------------------------------------------------
    /// Lecture des pixels de l'image contenus dans la box
    //----------------------------------------------------------
    virtual void          read          (IM_Box box) = 0;


    virtual std::string getStrFullname() { return fileName.Fullname(); };

    //----------------------------------------------------------
    /// Affecte les valeurs RGB du pixel
    //----------------------------------------------------------
    virtual bool          getPixelValue (IM_Pixel &pix) = 0;

    virtual bool          setPixelValue (IM_Pixel &pix) = 0;


    //----------------------------------------------------------
    /// Ecris l'image chargee en mémoire dans le fichier specifie
    //----------------------------------------------------------
    virtual void          write         (const CFile& fileName) = 0;

    //----------------------------------------------------------
    /// Effectue un zoom sur l'image
    //----------------------------------------------------------
    virtual IM_ImageMemory     zoom(float ratioX, float ratioY, TYPE_ZOOM ZC=NN) = 0;

    //----------------------------------------------------------
    /// Recadre selon le ratio au centre du cadre de lecture puis effectue un zoom sur l'image(permet d'obtenir une image de meme taille que l'originale)
    //----------------------------------------------------------
    virtual IM_ImageMemory      cropAndZoom(float ratioX, float ratioY, TYPE_ZOOM TZ) = 0;
    //----------------------------------------------------------
    /// Effectue une rotation de l'image
    //----------------------------------------------------------
    virtual bool          rotate        (float angle) = 0;
    //----------------------------------------------------------
    /// Effectue une projection de l'image
    //----------------------------------------------------------
    virtual IM_Box        projection(IM_Box boxSrc, unsigned short int pageSrc, unsigned short int pageDest) = 0;

    //----------------------------------------------------------
    /// Effectue un redimenssionnement de l'image
    //----------------------------------------------------------
    virtual bool          rescale       (IM_Image* img, IM_Box sizeBox) = 0;

    //----------------------------------------------------------
    /// Effectue une extraction d'une partie de l'image
    //----------------------------------------------------------
    virtual bool          extract(IM_Box box, unsigned short int page, int flag, char* fileOut) = 0;

    //----------------------------------------------------------
    /// Retourne la largeur de l'image
    //----------------------------------------------------------
    unsigned int          getWidth      ();

    //----------------------------------------------------------
    /// Retourne la hauteur l'image
    //----------------------------------------------------------
    unsigned int          getHeight     ();

    //----------------------------------------------------------
    /// Retourne le mode de couleur
    //----------------------------------------------------------
    unsigned int          getColorMode  ();



    //----------------------------------------------------------
    /// Test si un pixel appartient à l'image
    //----------------------------------------------------------
    bool                  hold          ( unsigned int row, unsigned int col );



    //----------------------------------------------------------
    /// Ajoute un lignel
    //----------------------------------------------------------
    /* ajout du Lignel : lPixel est une list de pair IMPixel, int . int est la direction du deuxième pixel(auto calculé, mettre une valeur par défaut)
       attention aucun contôle d'ordre n'est fait*/
    void          addLignel         ( std::list<lignel> lPixel, unsigned short int iGroup );
    //----------------------------------------------------------
    /// Supprime un lignel
    //----------------------------------------------------------
    void          removeLignel      ( unsigned short int lIndex, unsigned short int iGroup = 0 );

    //----------------------------------------------------------
    /// Supprime tous les lignels du group iGroup
    //----------------------------------------------------------
    void          removeAllLignels( unsigned short int iGroup );

    //----------------------------------------------------------
    /// Supprime tous les lignels
    //----------------------------------------------------------
    void          removeAllLignels  ( );

    //----------------------------------------------------------
    /// Charge une partie de l'image en fonction d'un lignel
    //----------------------------------------------------------
    virtual void  loadFromLignel ( unsigned short int lIndex, unsigned short int iGroup = 0){};

    //----------------------------------------------------------
    /// Extrait une partie de l'image en fonction d'un lignel
    //----------------------------------------------------------
    virtual void  extractFromLignel ( unsigned short int lIndex, unsigned short int iGroup = 0, const CFile& fileOut = "default.tif") = 0;

    //----------------------------------------------------------
    /// Retourne le lignel lIndex
    //----------------------------------------------------------
    IM_Lignel*    getLignel         ( unsigned short int lIndex, unsigned short int iGroup = 0 ){ return groupLignels[iGroup][lIndex]; };

    //----------------------------------------------------------
    /// Sauvegarde les lignels dans un fichier binaire
    //----------------------------------------------------------
    bool          saveBinLignel     ( const std::string &fileBin = "defaultBinLignel.txt");

    //----------------------------------------------------------
    /// Sauvegarde le lignel lIndex dans un fichier binaire
    //----------------------------------------------------------
    bool          saveBinLignel     ( unsigned short int lIndex, unsigned short int iGroup = 0, const std::string &fileBin = "defaultBinLignel.txt" );

    //----------------------------------------------------------
    /// Sauvegarde les lignels dans un fichier texte
    //----------------------------------------------------------
    bool          saveTextLignel     ( const std::string &fileBin = "defaultTextLignel.txt");

    //----------------------------------------------------------
    /// Sauvegarde le lignel lIndex dans un fichier texte
    //----------------------------------------------------------
    bool saveTextLignel     ( unsigned short int lIndex, unsigned short int iGroup, const std::string &fileBin );

    //----------------------------------------------------------
    /// Sauvegarde les lignels dans un fichier xml
    //----------------------------------------------------------
    bool          saveXMLLignel     ( const std::string &fileXML = "defaultXMLLignel.xml" );

    //----------------------------------------------------------
    /// Sauvegarde le lignel lIndex dans un fichier xml
    //----------------------------------------------------------
    bool          saveXMLLignel     ( unsigned short int lIndex, unsigned short int iGroup = 0, const std::string &fileXML = "defaultXMLLignel.xml" );

    //----------------------------------------------------------
    /// Importe les lignels d'un fichier binaire
    //----------------------------------------------------------
    bool          importBinLignel   (  const CFile &fileBin = "defaultBinLignel.txt", unsigned short int iGroup = 0 );

    //----------------------------------------------------------
    /// Importe les lignels d'un fichier binaire
    //----------------------------------------------------------
    bool          importTextLignel   (  const CFile &fileBin = "defaultTextLignel.txt", unsigned short int iGroup = 0 );


    //----------------------------------------------------------
    /// Importe les lignels d'un fichier xml
    //----------------------------------------------------------
    bool          importXMLLignel   ( const CFile &fileXML = "defaultXMLLignel.xml", unsigned short int iGroup = 0 );


    //----------------------------------------------------------
    /// Recompose une image à partir des lignels,
    //----------------------------------------------------------
    virtual void  cloneFromLignel   ( float width, float height, unsigned int maxSize, unsigned short int group = 0, char* fileOut = "cloneFromLignel.tif" ) {  };


    //----------------------------------------------------------
    /// Retourne le cadre englobant le lignel
    //----------------------------------------------------------
    IM_Box getBoundingBoxFromLignel(unsigned short int lIndex, unsigned short int iGroup = 0);



  public:


    //----------------------------------------------------------
    // Donnees membres
    //----------------------------------------------------------
    /// taille de l'image et type
    unsigned int            cols, rows, type;


    /// Nom du fichier image lu
    CFile                   fileName;
    /// Instance permettant d'appliquer des transformation - idealement unique par instance de IM_Image
    IM_Transform*           applyTransform;

    /// Vecteur de lignels
    typedef std::vector<IM_Lignel*>  vLignels;

    /// Groupe de vecteurs de lignels
    std::vector<vLignels>   groupLignels;

    /// Fonctions permettant la constitution de l'image mosaique \n Recherche du meilleur objet (Critere de surface)
    int           bestBox( unsigned int maxSize, IM_Box imgOut, std::vector<IM_Box> &boxIn, std::vector<IM_Box> &boxOut);

    /// Fonction recursive de recherche de formes \n sur une ligne contraint sur la taille d'une colonne
    int           espx( unsigned int maxSize, IM_Box imgOut, std::vector<IM_Box> &boxIn, std::vector<IM_Box> &boxOut);

    /// Fonction de recherche iterative de formes sur les colonnes
    void          espxy( unsigned int maxeSize, IM_Box imgOut, std::vector<IM_Box> &boxIn, std::vector<IM_Box> &boxOut);

    /// True si l'on a ouvert l'image
    bool isOpen;



  };

  inline
    unsigned int IM_Image::getWidth()
  {
    return cols;

  }

  inline
    unsigned int IM_Image::getHeight()
  {
    return rows;

  }

}//namespace fogrimmi
#endif  //_IM_IMAGE_H
