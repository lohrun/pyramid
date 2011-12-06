//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Image Management
//  @ File Name : IM_Tiff.h
//  @ Date : 20/04/2007
//  @ Author : Thibaut Aubrun http://aubrun.thibaut.free.fr
//
//  @ Notes: Classe généralisant les images de type TIFF.
//         Permet de manipuler des images TIFF indépendamment de l'organisation interne de l'image (tuile, ligne, compression)


#if !defined(_IM_TIFF_H)
#define _IM_TIFF_H

#include "export.h"
#include "image.hh"
#include "page.h"
#include <tiffio.h>
#include <vector>
#include "projection.h"
#include "zoom.h"
#include "image-memory.h"


namespace fogrimmi
{

  //==========================================================
  /// Classe servant a manipuler les images de type tiff - specialisation de la classe Image
  //==========================================================

  class IM_EXPORT IM_Tiff : public IM_Image
  {

  public:

    //----------------------------------------------------------
    /// Constructeur
    //----------------------------------------------------------
    IM_Tiff(const CFile& _fileName);


    //----------------------------------------------------------
    /// Constructeur par recopie
    //----------------------------------------------------------
    IM_Tiff(const IM_Tiff& tifSource);

    //----------------------------------------------------------
    /// Constructeur a partir d'une image memoire - utile pour ecrire dan un tif une image memoire
    //----------------------------------------------------------
    IM_Tiff(IM_ImageMemory& imgMem, const CFile& _fileName);

    //----------------------------------------------------------
    /// Destructeur
    //----------------------------------------------------------
    ~IM_Tiff();


    //----------------------------------------------------------
    /// open: ouvre toutes les pages et recupere les infos puis ouvre le tiffdirectory sur 0
    //----------------------------------------------------------
    void          open();

    //----------------------------------------------------------
    /// open: ouvre toutes les pages et recupere les infos puis ouvre le tiffdirectory sur page
    //----------------------------------------------------------
    void          open(unsigned short int page);



    //----------------------------------------------------------
    /// close: fermeture des pages
    //----------------------------------------------------------
    void          close();


    //----------------------------------------------------------
    /// ouvre la prochaine page
    //----------------------------------------------------------
    void          nextPage();

    //----------------------------------------------------------
    /// ouvre la précédente page
    //----------------------------------------------------------
    void          previousPage();

    //----------------------------------------------------------
    /// lit la page courante de la boite courante
    //----------------------------------------------------------
    void          read();


    //----------------------------------------------------------
    /// lit les donnees contenu dans la boite box de la page courante
    //----------------------------------------------------------
    void          read(IM_Box box);

    //----------------------------------------------------------
    /// lit les donnees contenu dans la boite box de la page page
    //----------------------------------------------------------
    void          read(IM_Box box, unsigned short int page);

    //----------------------------------------------------------
    /// lit les donnees contenu dans la boite box de toutes les pages, \n les dimensions de la boite correspond à la page courante. Des projections successives sont effectuées
    //----------------------------------------------------------
    void          readProjectivePages(IM_Box box);


    //----------------------------------------------------------
    /// lit les valeurs d'un pixel de la page courante
    //----------------------------------------------------------
    bool          getPixelValue(IM_Pixel &pix);

    inline bool getPixelValue(IM_Pixel &pix, unsigned int APage)
    {
      return vPages[APage]->getPixelValue(pix);
    };


    //----------------------------------------------------------
    /// lit les valeurs d'un pixel de la page courante
    //----------------------------------------------------------
    bool          getForcedPixelValue(IM_Pixel &pix);

    //----------------------------------------------------------
    /// retourne les donnees bruts d'une tuile
    //----------------------------------------------------------
    uint8*        getData(unsigned int page, unsigned int row, unsigned int col);

    //----------------------------------------------------------
    /// retourne toutes les donnees bruts des composants sous forme de tableau a une entree \n - conversion composants en tableau - \n attention a la capacite memoire \n
    //----------------------------------------------------------
    void        getAllDataRGB32(unsigned int page, uint8* data);


    //----------------------------------------------------------
    /// inutilise pour l'instant
    //----------------------------------------------------------
    bool          setPixelValue(IM_Pixel &pix);


    //----------------------------------------------------------
    /// ecrit les donnees contenu dans la boite courante de la page page vers un fichier
    //----------------------------------------------------------
    void          write(const CFile& fileName, unsigned short int page);


    //----------------------------------------------------------
    /// ecrit les donnees contenu dans la boite courante de la page courante selon les proprietes tiff
    //----------------------------------------------------------
    void          write(unsigned short int page, TIFF_Properties TiffP);

    //----------------------------------------------------------
    /// ecrit les donnees contenu dans la boite courante de la page courante vers un fichier
    //----------------------------------------------------------
    void          write(const CFile& fileName);


    //----------------------------------------------------------
    /// ecrit les donnees contenu dans la boite courante de la page courante selon les proprietes tiff
    //----------------------------------------------------------
    void          write(TIFF_Properties TiffP);




    //----------------------------------------------------------
    /// Zoom
    //----------------------------------------------------------
    IM_ImageMemory     zoom(float ratioX, float ratioY, TYPE_ZOOM TZ=NN);

    //----------------------------------------------------------
    /// crop and Zoom
    //----------------------------------------------------------
    IM_ImageMemory      cropAndZoom(float ratioX, float ratioY, TYPE_ZOOM TZ);


    //----------------------------------------------------------
    /// Rotation
    //----------------------------------------------------------
    bool          rotate(float angle);


    //----------------------------------------------------------
    /// Projection
    //----------------------------------------------------------
    IM_Box        projection(IM_Box boxSrc, unsigned short int pageSrc, unsigned short int pageDest);

    //----------------------------------------------------------
    /// Redimmensionnement
    //----------------------------------------------------------
    bool          rescale(IM_Image* img, IM_Box sizeBox);


    //----------------------------------------------------------
    /// Surcharge de l'operateur () - rends accessible les pixels par (col, row, page)
    //----------------------------------------------------------
    IM_Pixel      operator()(unsigned int col, unsigned int row, unsigned short int page);

    //----------------------------------------------------------
    /// extraction des donnees selon une boite
    //----------------------------------------------------------
    bool          extract(IM_Box box, unsigned short int page, int flag, char* fileOut);


    //----------------------------------------------------------
    /// chargement des donnees selon un lignel
    //----------------------------------------------------------
    void          loadFromLignel(unsigned short int lIndex, unsigned short int iGroup = 0);

    //----------------------------------------------------------
    /// extraction des donnees selon un lignel
    //----------------------------------------------------------
    void          extractFromLignel(unsigned short int lIndex, unsigned short int iGroup = 0, const CFile& fileOut="lignelOut.tif");




    //----------------------------------------------------------
    /// Ajoute un tif a une page dans le tif courant - attention limitee par la RAM
    //----------------------------------------------------------
    void          append(char *file, int index, unsigned int mode=0);


    //----------------------------------------------------------
    /// Insertion d'un tif a une page dans le tif courant, efface la page en insertion - attention limitee par la RAM
    //----------------------------------------------------------
    void          insert(char *file, int index);

    //----------------------------------------------------------
    /// Suppression d'une page - attention limitee par la RAM
    //----------------------------------------------------------
    void					remove(int index);



    //----------------------------------------------------------
    /// Recuperer les proprietes d'une page
    //----------------------------------------------------------
    TIFF_Properties	getProperties(int index = 0);



    //----------------------------------------------------------
    /// non implemente
    //----------------------------------------------------------
    void          setPage(unsigned short int index);

    //----------------------------------------------------------
    /// Retourne l'index de la page actuellement en lecture
    //----------------------------------------------------------
    inline unsigned short int  getCurrentPage() { return currentPage; };



    //----------------------------------------------------------
    /// Retourne la largeur de la page specifie
    //----------------------------------------------------------
    unsigned int  getPageWidth(unsigned short int page);
    //----------------------------------------------------------
    /// Retourne la hauteur de la page specifie
    //----------------------------------------------------------
    unsigned int  getPageHeight(unsigned short int page);


    //----------------------------------------------------------
    /// Retourne vrai si les coordonnees specifie appartiennent aux dimensions de la page
    //----------------------------------------------------------
    bool          holdPage(unsigned int row, unsigned int col, unsigned short int page);

    //----------------------------------------------------------
    /// Retourne vrai si les coordonnes specifie appartiennent au cadre de lecture de la page
    //----------------------------------------------------------
    bool          holdBoxPage(unsigned int row, unsigned int col, unsigned short int page);


    //----------------------------------------------------------
    /// Affiche les tags de la page
    //----------------------------------------------------------
    void          printTagsPage(unsigned short int page);


    //----------------------------------------------------------
    /// Recompose une image à partir des lignels,
    //----------------------------------------------------------
    void          cloneFromLignel   ( float width, float height, unsigned int maxSize, unsigned short int page = 0, std::string fileOut = "cloneFromLignel.tif" );


    //----------------------------------------------------------
    /// Renvoie le cadre referent de la page de destination d'un pixel d'une page source
    //----------------------------------------------------------
    IM_Box        getPixelReferent   ( unsigned x, unsigned y, unsigned short int pageSrc, unsigned short int pageDest );


    //----------------------------------------------------------
    /// Decharge les donnees de la page. Faire appel a read avant reutilisation.
    //----------------------------------------------------------
    void          unLoad(unsigned short int page);


    //----------------------------------------------------------
    /// Projection de lignel d'une page a une autre
    //----------------------------------------------------------
    void          projectionLignel(unsigned short int lIndex, unsigned short int iGroupSrc, unsigned short int iGroupDest);


    //----------------------------------------------------------
    /// Retourne la boite de lecture courante de la page
    //----------------------------------------------------------
    inline IM_Box        getCurrentReadBox(unsigned int page){ return vPages[page]->getCurrentReadBox(); };

    //----------------------------------------------------------
    /// Definit la boite de lecture de la page
    //----------------------------------------------------------
    inline bool          setCurrentReadBox(IM_Box box, unsigned int page){ vPages[page]->setCurrentReadBox(box); return true;};


    //----------------------------------------------------------
    /// Si une page est une macro image ou un label alors renvoie faux
    //----------------------------------------------------------
    bool isPage(unsigned short int page);

    //----------------------------------------------------------
    /// Retourne le nombres de pages
    //----------------------------------------------------------
    inline unsigned short int getNbPages(){ return nbPages; };

    //----------------------------------------------------------
    /// Retourne true si la page est deja lue
    //----------------------------------------------------------
    inline bool isLoaded(unsigned short int page)
    {
      return vPages[page]->isLoaded();
    };

    //----------------------------------------------------------
    /// Permet de reserver une plage memoire - utile en cas d'accès temps réel ou rapide
    //----------------------------------------------------------
    void reserve(unsigned short int page, int width, int height);

    //----------------------------------------------------------
    /// Arret de tout traitement sur un tiff
    //----------------------------------------------------------
    void abort();

    //----------------------------------------------------------
    /// Retourne vrai si l'image est organisee en tuile
    //----------------------------------------------------------
    bool isTiled(unsigned int page);

  private:

    /// Pointeur sur le TIFF en lecture de la librairie libtiff
    TIFF*                 tif;

    /// Vecteur de pages
    std::vector<IM_Page*> vPages;

    /// Compteur de pages
    unsigned short int    nbPages;

    /// Indice la page actuellement en lecture
    unsigned short int    currentPage;


    //----------------------------------------------------------
    /// deprecated - Copy une page d'image dans un fichier
    //----------------------------------------------------------
    void          copyPageToFile(TIFF_Properties _TiffP, unsigned short int page);











  };

  inline
    IM_Pixel IM_Tiff::operator()(unsigned int col, unsigned int row, unsigned short int page)
    {
      //if(page >= nbPages || page < 0)

      IM_Pixel pix;
      pix.x = col;
      pix.y = row;

      if(!vPages[page]->getPixelValue(pix))
	{
	  getForcedPixelValue(pix);
	}

      return pix;

    }



  inline
    unsigned int IM_Tiff::getPageWidth(unsigned short int page)
  {

    return vPages[page]->getWidth();

  }

  inline
    unsigned int IM_Tiff::getPageHeight(unsigned short int page)
  {
    return vPages[page]->getHeight();

  }
}//namespace Im

#endif  //_IM_TIFF_H
