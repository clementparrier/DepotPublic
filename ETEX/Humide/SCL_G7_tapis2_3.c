!
(****************************)
(* Nom : G7 tapis 2/3       *)
(*                          *)
(* Le 18/01/2024            *)
(* Par IMAP3S               *)
(****************************)

!
(* Synthèse ligne *)
Synthtapis3pret:=FALSE;
Synthl2prete:=F2s6_ligne2_ok AND NOT F2s6_fin_prise_plaque2 AND NOT Mem_plaque_mauv_tapis2 AND NOT Mem_plaque_avant_mauv_tapis2 AND NOT Mem_plaque_entière_tapis2 AND Arret_tapis2_t1_vers_t2.T>=2 AND Arret_tapis2_t1_vers_t2;

!
(* Gestion de la tempo d'étape *)
Fm_seconde:=Seconde AND NOT Memo_fm_seconde;
Memo_fm_seconde:=Seconde;

IF Fm_seconde AND G7_tapis23_t1s<32000 THEN
	G7_tapis23_t1s:=G7_tapis23_t1s+1;
END_IF;

!
(* RAZ Séquence *)
IF NOT Essai_newg7_tapis23(*OR Init_macro2_tapis2*) THEN
	G7_tapis23_numetape:=0;
END_IF;

!
(* Etape 0 : Initialisation : Autorisation de démarrer la "macro" *)
IF G7_tapis23_numetape=0 AND Essai_newg7_tapis23 AND NOT Sel_marche_force AND NOT Tps_plus_marche_forcee.R AND Cond_marche_tapis2 THEN

	(* Compteur de plaque *)
	G7_tapis23_cptplaqueatraiter:=2;
	
	(* Transition *)
	G7_tapis23_numetape:=10;
	G7_tapis23_t1s:=0;
	JUMP %L99;
END_IF;

!
(* Etape 10 : Arrêt tapis 2 *)
IF G7_tapis23_numetape=10 THEN

	(* Transition *)
	IF Cond_marche_tapis2 AND NOT Sel_pont_montée AND(Pont_1_bas OR Pont_t1t2_bas OR Sel_pont_descente)AND Coupe_ct1 AND(Fin_coupe_ct1 OR(Mem_plaque_mauv_cylindre AND Sel_pont_descente))THEN
		G7_tapis23_numetape:=20;
		G7_tapis23_t1s:=0;
		JUMP %L99;
	END_IF;
END_IF;

!
(* Etape 20 : Marche tapis 2 GV *)
IF G7_tapis23_numetape=20 THEN

	(* Transition *)
	(* Valeur_v0_courante_mm : Position TAPIS 1 *)
	(* Valeur_v1_courante_mm : Position TAPIS 2 *)
	IF(Valeur_v0_courante_mm>=Valeur_v0_seuil1_mm AND G7_tapis23_cptplaqueatraiter=1)OR (* Si 1 seule plaque, ralentissement sur le côte TAPIS 1 *)
	(Valeur_v1_courante_mm>=0 AND G7_tapis23_cptplaqueatraiter=2)THEN (* Si 2 plaques, anticipation, ralentissement sur la côte TAPIS 2 *)
		G7_tapis23_numetape:=20;
		G7_tapis23_t1s:=0;
		JUMP %L99;
	END_IF;
END_IF;

!
(* Etape 100 : Marche tapis 2 PV *)
IF G7_tapis23_numetape=100 THEN

	(* Transition : Plaque passé sous E3 *)
	IF Mem_font_montant_e3 AND NOT %I8.7 THEN
		G7_tapis23_numetape:=110;
		G7_tapis23_t1s:=0;
		JUMP %L99;
	END_IF;
END_IF;

!
(* Etape 110 : Arrêt tapis (SI plaque=1) et compteur plaque-1 *)
IF G7_tapis23_numetape=110 THEN


	(* Transition : Nbr de plaque à traiter=1 et L2 prête *)
	IF G7_tapis23_cptplaqueatraiter=1 AND Synthl2prete THEN
		(* Compteur de plaque - Sur FRONT MONTANT *)
		G7_tapis23_cptplaqueatraiter:=G7_tapis23_cptplaqueatraiter-1;
		
		G7_tapis23_numetape:=210;
		G7_tapis23_t1s:=0;
		JUMP %L99;
	END_IF;
	(* Transition : Nbr de plaque à traiter=1 ET PAS L2 prete ET Tapis 3 tourne *)
	IF G7_tapis23_cptplaqueatraiter=1 AND NOT Synthl2prete THEN
		(* Compteur de plaque - Sur FRONT MONTANT *)
		G7_tapis23_cptplaqueatraiter:=G7_tapis23_cptplaqueatraiter-1;
		
		G7_tapis23_numetape:=20;
		G7_tapis23_t1s:=0;
		JUMP %L99;
	END_IF;
	(* Transition : Nbr de plaque à traiter = 0 *)
	IF G7_tapis23_cptplaqueatraiter=0 THEN
		(* Compteur de plaque - Sur FRONT MONTANT *)
		G7_tapis23_cptplaqueatraiter:=G7_tapis23_cptplaqueatraiter-1;
		
		G7_tapis23_numetape:=0;
		G7_tapis23_t1s:=0;
		JUMP %L99;
	END_IF;
END_IF;

!
(* Etape 200 : Marche tapis 2 PV *)
IF G7_tapis23_numetape=200 THEN

	(* Transition : Plaque passé sous E3 *)
	IF Mem_font_montant_e3 AND NOT %I8.7 THEN
		G7_tapis23_numetape:=210;
		G7_tapis23_t1s:=0;
		JUMP %L99;
	END_IF;
END_IF;

!
(* Etape 210 : Marche tapis 2 PV *)
IF G7_tapis23_numetape=210 THEN

	(* Transition : Ligne 2 prête *)
	IF NOT Synthtapis3pret AND Synthl2prete AND Valeur_v1_courante_mm>=180 THEN
		G7_tapis23_numetape:=220;
		G7_tapis23_t1s:=0;
		JUMP %L99;
	END_IF;
	(* Transition : Ligne 1 prête *)
	IF Synthtapis3pret AND Valeur_v1_courante_mm>=180 THEN
		G7_tapis23_numetape:=20;
		G7_tapis23_t1s:=0;
		JUMP %L99;
	END_IF;
END_IF;

!
(* Etape 220 : Arrêt taous 2 & Nbr plaque à traiter -1 *)
IF G7_tapis23_numetape=220 THEN

	(* Transition : Contrôle pas de prise en cours *)
	IF NOT F2s6_fin_prise_plaque2 THEN
		(* Compteur de plaque - Sur FRONT MONTANT *)
		G7_tapis23_cptplaqueatraiter:=G7_tapis23_cptplaqueatraiter-1;
		
		G7_tapis23_numetape:=230;
		G7_tapis23_t1s:=0;
		JUMP %L99;
	END_IF;
END_IF;

!
(* Etape 230 : Arrêt tapis 2 - Prise serviteur *)
IF G7_tapis23_numetape=230 THEN

	(* Transition : Fin de prise ET Nbr de plaque a traiter = 0*)
	IF F2s6_fin_prise_plaque2 AND G7_tapis23_cptplaqueatraiter=0 THEN
		G7_tapis23_numetape:=0;
		G7_tapis23_t1s:=0;
		JUMP %L99;
	END_IF;
	(* Transition : Fin de prise ET Nbr de plaque a traiter > 0 *)
	IF F2s6_fin_prise_plaque2 AND G7_tapis23_cptplaqueatraiter=1 THEN
		G7_tapis23_numetape:=20;
		G7_tapis23_t1s:=0;
		JUMP %L99;
	END_IF;
END_IF;

!
(* Fin *)
%L99:

!
(* Bit de commande G7 *)
Cmdtapis2_pv:=G7_tapis23_numetape=100 OR G7_tapis23_numetape=200 OR G7_tapis23_numetape=210;
Cmdtapis2_gv:=G7_tapis23_numetape=20;
Cmdpriseserv:=G7_tapis23_numetape=230;
