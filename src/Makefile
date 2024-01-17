#
# Hello Robot C - Makefile des sources du projet.
#
# @author Matthias Brun
#

#
# Organisation des sources.
#

# Packages du projet (à compléter si besoin est).
PACKAGES = robot_app

# Un niveau de package est accessible.
SRC  = $(wildcard */*.c)
# Pour ajouter un second niveau :		
# SRC += $(wildcard */*/*.c)

OBJ = $(SRC:.c=.o)

# Point d'entrée du programme.
MAIN = main.c

# Gestion automatique des dépendances.
DEP = $(MAIN:.c=.d)

# Exécutable à générer.
EXEC = ../$(PROG)

# Inclusion depuis le niveau du package.
CCFLAGS += -I.

#
# Règles du Makefile.
#

.PHONY: all clean $(PACKAGES)

# Compilation.
all: $(PACKAGES)
	@$(MAKE) $(EXEC)

$(EXEC): $(OBJ) $(MAIN)
	$(CC) $(CCFLAGS) $(OBJ) $(MAIN) -MF $(DEP) -o $(EXEC) $(LDFLAGS)

# Nettoyage.
clean: $(PACKAGES)
	@rm -f $(DEP)

# Packages
$(PACKAGES):
	$(MAKE) $(MAKECMDGOALS) -C $@


-include $(DEP)
