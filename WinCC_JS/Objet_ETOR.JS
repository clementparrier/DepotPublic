export function Animation_ProcessValue_OnPropertyChanged(item, value) {

  // Source du mot d'animation
  let tagAnimationValue = item.ProcessValue;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  //~~~~~~~~~~~~~~~~~~~ Décomposition du mot d'animation ~~~~~~~~~~~~~~~~~~~ //
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

  //      #IHM.Out_Animation.%X0 := #Out_Entree;
  //      #IHM.Out_Animation.%X1 := #In_CtrlMont;
  //      #IHM.Out_Animation.%X2 := #In_CtrlRetomb;
  //      #IHM.Out_Animation.%X3 := #_bIHM_ModeManu;
  //      #IHM.Out_Animation.%X4 := #_bIHM_InhibCtrlMont;
  //      #IHM.Out_Animation.%X5 := #_bIHM_InhibCtrlRetomb;
  //      #IHM.Out_Animation.%X6 := FALSE;
  //      #IHM.Out_Animation.%X7 := FALSE;
        
  //      #IHM.Out_Animation.%X8 := #In_Entree;
  //      #IHM.Out_Animation.%X9 := FALSE;
  //      #IHM.Out_Animation.%X10 := FALSE;
  //      #IHM.Out_Animation.%X11 := FALSE;
  //      #IHM.Out_Animation.%X12 := FALSE;
  //      #IHM.Out_Animation.%X13 := FALSE;
  //      #IHM.Out_Animation.%X14 := FALSE;
  //      #IHM.Out_Animation.%X15 := FALSE;
        
  //      #IHM.Out_Animation.%X16 := #_bDefNonMont;
  //      #IHM.Out_Animation.%X17 := #_bDefNonRetomb;
  //      #IHM.Out_Animation.%X18 := FALSE;
  //      #IHM.Out_Animation.%X19 := FALSE;
  //      #IHM.Out_Animation.%X20 := FALSE;
  //      #IHM.Out_Animation.%X21 := FALSE;
  //      #IHM.Out_Animation.%X22 := FALSE;
  //      #IHM.Out_Animation.%X23 := FALSE;
        
  //      #IHM.Out_Animation.%X24 := FALSE;
  //      #IHM.Out_Animation.%X25 := FALSE;
  //      #IHM.Out_Animation.%X26 := FALSE;
  //      #IHM.Out_Animation.%X27 := FALSE;
  //      #IHM.Out_Animation.%X28 := FALSE;
  //      #IHM.Out_Animation.%X29 := FALSE;
  //      #IHM.Out_Animation.%X30 := FALSE;
  //      #IHM.Out_Animation.%X31 := FALSE;

  // Récupération des bits de mots
  let _Out_Entree           = (tagAnimationValue & (1 << 0))  === 0 ? 0 : 1; // Bit 0
  let _bIHM_ModeManu        = (tagAnimationValue & (1 << 1))  === 0 ? 0 : 1; // Bit 1
  let _bIHM_InhibCtrlMont   = (tagAnimationValue & (1 << 2))  === 0 ? 0 : 1; // Bit 2
  let _bIHM_InhibCtrlRetomb = (tagAnimationValue & (1 << 3))  === 0 ? 0 : 1; // Bit 3

  let _bDefNonMont          = (tagAnimationValue & (1 << 16))  === 0 ? 0 : 1; // Bit 16
  let _bDefNonRetomb        = (tagAnimationValue & (1 << 17))  === 0 ? 0 : 1; // Bit 17

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  //~~~~~~~~~~~~~~~~~~~~~~ Liste des couleurs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  let _colorTmp;
  let _colorRed   = 0xff0000;  // Rouge
  let _colorGreen = 0x00FF00;  // Vert   
  let _colorGris  = 0x808080;  // Gris
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  //~~~~~~~~~~~~~~~~~~~ Animation de l'état (rond)       ~~~~~~~~~~~~~~~~~~~ //
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  if (_bDefNonMont || _bDefNonRetomb) {
    _colorTmp = _colorRed;    // Rouge
  } else if (_Out_Entree) {
    _colorTmp = _colorGreen;  // Vert   
  } else {
    _colorTmp = _colorGris;   // Gris
  }
  
  // Ecrtiure de la couleur de l'objet graphique "pEtat"
  Faceplate.Items("gEtat").BackColor = _colorTmp; 
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  //~~~~~~~~~~~~~~~~~~~             Nom de l'objet       ~~~~~~~~~~~~~~~~~~~ //
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  // Ecriture du TagName (interface) dans l'objet graphique "TagName"
  Faceplate.Items("gTagName").Name = Faceplate.Properties.TagName;
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
  //~~~~~~~~~~~~~~~~~~~ Animation de l'inhibition (carré)  ~~~~~~~~~~~~~~~~~ //
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~// 
  let _VisibleTmp = false;//(_bIHM_InhibCtrlMont || _bIHM_InhibCtrlRetomb);

  // Ecrtiure de la visibilité de l'objet graphique "pInhib"
  Faceplate.Items("gInhib").Visible = _VisibleTmp;

}