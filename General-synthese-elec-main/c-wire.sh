#!/bin/bash

declare -A consomateur=(['comp']=0 ['indiv']=1 ['all']=2)
declare -A stations=(['hvb']=1 ['hva']=2 ['lv']=3)


function showhelp(){
	echo "[--------------------HELP--------------------]"
	echo "[Paramètres]"
	echo "[*]Chemin d'accès du fichier de données"
	echo "	*Obligatoire"
	echo "[*]Type de station"
	echo "	*Valeurs possibles : hvb hva lv"
	echo "		hvb : "
	echo "		hva : "
	echo "		lv : "
	echo "	*Obligatoire"
	echo "[*]Type de consomateur"
	echo "	*Valeurs possibles : comp indiv all"
	echo "	*Obligatoire"
	echo "		comp : "
	echo "		indiv : "
	echo "		all : "
	echo "[*]Identifiant de la centrale"
	echo "	*Facultatif"
	echo "[*]Option aide -h"
	echo "	*Obligatoire"
}

for arg in "$@"; do

    if [[ "$arg" = "-h" ]]; then
        showhelp
		exit 1
    fi
done

if [ "$#" -lt 3 ]; then
    echo "Erreur : le nombre d'arguments est trop petit. (Attendu : 3, Reçu : $#)"
	showhelp
    exit 1
fi

if [ ! -f "$1" ]; then
    echo "Erreur : le fichier donné n'est pas valide ou n'existe pas."
	showhelp
    exit 1
fi

if [ ! "$2"  = "hvb" ] && [ ! "$2" = "hva" ] && [ ! "$2" = "lv" ]; then
    echo "Erreur : le format de station est incorrect."
	showhelp
    exit 1
fi

if [ ! "$3"  = "comp" ] && [ ! "$3" = "indiv" ] && [ ! "$3" = "all" ]; then
    echo "Erreur : le format de consomateur est incorrect."
	showhelp
    exit 1
fi

if [[ ("$2" = "hvb" || "$2" = "hva") && ("$3" = "indiv" || "$3" = "all") ]]; then
    echo "Erreur : la combinaison de $2 et $3 est impossible."
	showhelp
    exit 1
fi

if [ ! -f "codeC/cwire.out" ]; then
	make -C codeC/
	if [ ! $? -eq 0 ]; then
		echo "Erreur de compilation."
		exit 1
	fi
fi

if [ ! -d "graphs" ]; then
	mkdir -p "graphs"
fi

if [ ! -d "tmp" ]; then
	mkdir -p "tmp"
else
	rm -rf "tmp"/*
fi

time valgrind codeC/cwire "$1" "${stations["$2"]}" "${consomateur["$3"]}" "$4"