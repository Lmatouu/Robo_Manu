#
# Robot (MRPiZ C) - Makefile principal.
# Version simplifiée pour simulateur Intox par Jérôme Delatour
#
# @author Matthias Brun (matthias.brun@eseo.fr)
# @author Jerome Delatour (jerome.delatour@eseo.fr)


# Répertoire d'installation de la librairie MRPiZ simulant le robot
#LIB_MRPIZ = /absolute/path/to/lib_mrpiz-v0.3/
LIB_MRPIZ = $(realpath  ../lib_mrpiz-v0.3/)
# Avec la ligne précédente, on suppose que la lib a été mise "au-dessus" du répertoire du projet
# Attention : pour que realpath marche : ne pas avoir mis des espaces ou des caractères accentués dans les noms des répertoires
# Mettre des espaces ou des caractéres "exotiques" (autre que ASCII) dans vos chemins (nom des répertoires et fichiers) = mauvaise pratique
#
# Organisation des sources.
#
export SRCDIR = src
export BINDIR = bin
SUBDIRS = $(SRCDIR)

#
# Définitions des outils.
#

# Compilateur.
export CC = gcc

export CCFLAGS  = -DINTOX -DINTOX_ADDRESS=127.0.0.1 -DINTOX_PORT=12345
export CCFLAGS += -I$(LIB_MRPIZ)/include/mrpiz/

# gestion automatique des dépendances
export CCFLAGS += -MMD -MP
export CCFLAGS += -D_BSD_SOURCE -D_XOPEN_SOURCE_EXTENDED -D_XOPEN_SOURCE -D_DEFAULT_SOURCE -D_GNU_SOURCE
export CCFLAGS += -std=gnu11 -Wall -pedantic

export LDFLAGS  = -L$(LIB_MRPIZ)/lib/ -lintoxmrpiz -lintox
export LDFLAGS += -lm -lrt -lpthread

# Debug
# Décommentez la ligne qui correspond a votre intention
# Sans debuggage :
# export CCFLAGS += -O3 -DNDEBUG
# Avec debuggage :
export CCFLAGS += -Og -g -DDEBUG


#
# Définitions des binaires à générer.
#
export PROG_NAME = go
export PROG = $(BINDIR)/$(PROG_NAME)

#
# Règles du Makefile.
#
.PHONY: all clean $(SUBDIRS)

# Compilation.
all: $(SUBDIRS)

# Nettoyage.
clean: $(SUBDIRS)
	@rm -f $(PROG) core* $(BINDIR)/core*

# Sous-répertoires.
$(SUBDIRS):
	$(MAKE) $(MAKECMDGOALS) -C $@

