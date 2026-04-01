# ============================================================================
# Makefile pour pipex - Automatise la compilation et la gestion des targets
# ============================================================================

# Variables (pour éviter de répéter les chemins et drapeaux)
CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
INCLUDES = -I includes
TARGET   = raw

# Fichiers source
SRCS     = raw.c utils/utils.c utils/eyes_utils.c

# Fichiers objets (générés automatiquement à partir des sources)
OBJS     = $(SRCS:.c=.o)

# ============================================================================
# TARGETS (cibles du Makefile)
# ============================================================================

# Target par défaut : compile le binaire
all: $(TARGET)

# Règle générique : compile un .o à partir d'un .c
%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Lie les .o en un exécutable
$(TARGET): $(OBJS)
	@echo "Linking $@..."
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
	@echo "✓ Build successful: $(TARGET)"

# Nettoie les fichiers objets (.o)
clean:
	@echo "Cleaning object files..."
	rm -f $(OBJS)
	@echo "✓ Cleaned"

# Nettoie tout (objets + exécutable)
fclean: clean
	@echo "Removing executable..."
	rm -f $(TARGET)
	@echo "✓ Full clean done"

# Recompile tout (clean + all)
re: fclean all

# Affiche les variables (debug)
info:
	@echo "CC=$(CC)"
	@echo "SRCS=$(SRCS)"
	@echo "OBJS=$(OBJS)"
	@echo "TARGET=$(TARGET)"

# Declare phony targets (cibles qui ne sont pas des fichiers réels)
.PHONY: all clean fclean re info
