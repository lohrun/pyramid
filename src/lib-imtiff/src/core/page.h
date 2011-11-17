//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Image Management
//  @ File Name : IM_Page.h
//  @ Date : 20/04/2007
//  @ Author : Thibaut Aubrun http://aubrun.thibaut.free.fr
//
//


#ifndef _IM_PAGE_H
#define _IM_PAGE_H
#include <tiffio.h>
#include "image.hh"
#include <math.h>
#include "tile.h"
#include "strip.h"
#include <deque>
namespace fogrimmi
{
  //==========================================================
  /// Gestion en memoire d'une page d'une image TIFF
  //==========================================================
  class IM_Page
  {


  public:


    //----------------------------------------------------------
    /// Constructeur
    //----------------------------------------------------------
    IM_Page(unsigned short int _index = 0);


    IM_Page(TIFF_Properties _tiffP, uint8* _data, unsigned short int _index = 0);


    //----------------------------------------------------------
    /// Destructeur
    //----------------------------------------------------------
    ~IM_Page()
      {
	unLoad();
      };


    //----------------------------------------------------------
    /// Ouverture de la page - récuperation des informations
    //----------------------------------------------------------
    bool          open(TIFF& tif);
    bool          open32(TIFF& tif);

    //----------------------------------------------------------
    /// Non utilisee
    //----------------------------------------------------------
    float         getRatio();
    //----------------------------------------------------------
    /// Charge en memoire les pixels contenu dans box
    //----------------------------------------------------------
    bool          load(TIFF& tif, IM_Box box);

    //----------------------------------------------------------
    /// Charge en memoire les pixels contenu dans currentReadBox
    //----------------------------------------------------------
    bool          load(TIFF& tif);

    //----------------------------------------------------------
    /// Decharge la memoire - destruction des containers
    //----------------------------------------------------------
    void          unLoad();


    //----------------------------------------------------------
    /// Retourne la valeur du pixel
    //----------------------------------------------------------
    bool          getPixelValue(IM_Pixel &pix);

    //----------------------------------------------------------
    /// Ecris dans le fichier specifie
    //----------------------------------------------------------
    bool          write(const CFile& fileName, TIFF *tifDest = NULL);

    //----------------------------------------------------------
    /// Ecris un tiff suivant la compression choisie
    //----------------------------------------------------------
    bool          write(TIFF_Properties TiffP);


    //----------------------------------------------------------
    /// Ecris la page en entiere dans le fichier specifie
    //----------------------------------------------------------
    bool          writeAllIn(TIFF& tifSrc, TIFF_Properties _TiffP);



    //----------------------------------------------------------
    /// Ouvre en ecriture
    //----------------------------------------------------------
    TIFF*         openWrite(const CFile &fileName, TIFF_Properties _TiffP);


    //----------------------------------------------------------
    /// Retourne la boite englobant la page entiere
    //----------------------------------------------------------
    IM_Box        getBox();

    //----------------------------------------------------------
    /// Retourne la boite de lecture courante de la page
    //----------------------------------------------------------
    inline IM_Box        getCurrentReadBox(){ return currentReadBox; };

    //----------------------------------------------------------
    /// Definit la boite de lecture de la page
    //----------------------------------------------------------
    bool          setCurrentReadBox(IM_Box box);


    //----------------------------------------------------------
    /// Retourne vrai si la page est ouverte
    //----------------------------------------------------------
    inline bool          getIsOpen(){ return isOpen; };

    //----------------------------------------------------------
    /// Retourne vrai si l'image est organisee en tuile
    //----------------------------------------------------------
    inline bool          isTiled(){ if(tiffP.pixOrganisation==TILE) return true; else return false; };

    //----------------------------------------------------------
    /// Retourne la largeur totale
    //----------------------------------------------------------
    inline unsigned int  getWidth(){return tiffP.width;};

    //----------------------------------------------------------
    /// Retourne la hauteur totale
    //----------------------------------------------------------
    inline unsigned int  getHeight(){return tiffP.height;};

    //----------------------------------------------------------
    /// Affiche les tags de la page
    //----------------------------------------------------------
    void          printTags();

    //----------------------------------------------------------
    /// Renvoie le mode de couleur utilisé (RGB=3)
    //----------------------------------------------------------
    inline unsigned short int getColorMode(){ return tiffP.colorMode; };

    //----------------------------------------------------------
    /// Renvoie la largeur d'une tuile/ligne selon l'organisation de l'image
    //----------------------------------------------------------
    inline unsigned int  getSizeWidth(){ return tiffP.componentWidth; };

    //----------------------------------------------------------
    /// Renvoie la hauteur d'une tuile/ligne selon l'organisation de l'image
    //----------------------------------------------------------
    inline unsigned int  getSizeHeight(){ return tiffP.componentHeight; };

    //----------------------------------------------------------
    /// Renvoie la largeur du cadre de lecture courant
    //----------------------------------------------------------
    inline float getCurrentReadBoxWidth(){ return currentReadBox.XBtm - currentReadBox.XTop;};

    //----------------------------------------------------------
    /// Renvoie la hauteur du cadre de lecture courant
    //----------------------------------------------------------
    inline float getCurrentReadBoxHeight(){ return currentReadBox.YBtm - currentReadBox.YTop;};

    //----------------------------------------------------------
    /// retourne les donnees bruts d'un composant
    //----------------------------------------------------------
    uint8* getData(unsigned int row, unsigned int col);

    //----------------------------------------------------------
    /// retourne toutes les donnees bruts des composants sous forme de tableau a une entree \n - conversion composants en tableau - \n attention a la capacite memoire \n
    //----------------------------------------------------------
    void getAllData(uint8 *allData);

    //----------------------------------------------------------
    /// retourne toutes les donnees bruts des composants sous forme de tableau a une entree \n - conversion composants en tableau - \n attention a la capacite memoire \n
    //----------------------------------------------------------
    void getAllDataRGB32(uint8 *allData);

    //----------------------------------------------------------
    /// modifie la valeur d'un pixel (non implementee)
    //----------------------------------------------------------
    bool setPixelValue(const IM_Pixel &pix);

    //----------------------------------------------------------
    /// convertie un tableau a une entree en component stockee dans un conteneur a 2 entrees
    //----------------------------------------------------------
    void convertData(uint8* _data);

    //----------------------------------------------------------
    /// Si la page a deja ete chargee alors true
    //----------------------------------------------------------
    inline bool isLoaded(){ return isLoad; };




    //----------------------------------------------------------
    /// Retourne les proprietes du tiff de la page courante
    //----------------------------------------------------------
    inline TIFF_Properties getProperties(){ return tiffP; };

    //----------------------------------------------------------
    /// Si une page est une macro image ou un label alors renvoie faux
    //----------------------------------------------------------
    bool isPage();

    //----------------------------------------------------------
    /// Permet de reserver une plage memoire - utile en cas d'accès temps réel ou rapide
    //----------------------------------------------------------
    void reserve(TIFF &tif, int width, int height);

    //----------------------------------------------------------
    /// Arret de tout traitement sur un tiff
    //----------------------------------------------------------
    void abort(bool _aborted);




  private:


    //----------------------------------------------------------
    // Donnees membres
    //----------------------------------------------------------

    /// Proprietes de la page
    TIFF_Properties tiffP;

    /// index de la page
    unsigned short int      index;

    /// If true page is previously loaded
    bool isLoad;

    /// If true alors arret des traitement en cours
    bool aborted;


    /// Ratio par rapport a la premiere page (inutilisee)
    float                   ratio;

    /// Type vecteur
    typedef std::vector<IM_Component*> component;

    /// Containeur des differentes parties de la page (tile ou strip)
    std::vector<component>         container;

    /// Cadre de lecture
    IM_Box                  currentReadBox;

    /// Retourne la Max
    unsigned short int      Max(unsigned short int alpha, unsigned short int beta);
    /// Retourne le Min
    unsigned short int      Min(unsigned short int alpha, unsigned short int beta);

    /// Vrai si page ouverte
    bool isOpen;


    // IM_Pixel& operator()(unsigned short int row, unsigned short int col);

  };

  /*
    inline
    IM_Pixel& IM_Page::operator()(unsigned short int row, unsigned short int col)
    {
    IM_Pixel pix;
    pix.x = col;
    pix.y = row;

    getPixelValue(pix);

    return pix;


    }
  */


  inline
    unsigned short int IM_Page::Max(unsigned short int alpha, unsigned short int beta)
  {
    if(alpha > beta)
      return alpha;

    return beta;
  }


  inline
    unsigned short int IM_Page::Min(unsigned short int alpha, unsigned short int beta)
  {
    if(alpha < beta)
      return alpha;

    return beta;
  }
}//namespace fogrimmi

#endif  //_IM_PAGE_H
