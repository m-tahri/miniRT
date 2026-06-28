NAME        = miniRT

SRCS_DIR    = srcs
OBJS_DIR    = objs
MLX_DIR     = mlx

# Fichiers sources (Tu ajoutes juste ton nouveau fichier ici)
SRCS        = $(SRCS_DIR)/main.c $(SRCS_DIR)/maths.c $(SRCS_DIR)/ray.c

# Transformation des .c en .o placés dans le dossier objs/
OBJS        = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Compilateur et Flags
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -Iincludes -I$(MLX_DIR)

# Flags de liaison pour Linux (Graphisme + Mathématiques)
MLX_LNK     = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compilation de la MiniLibX..."
	make -C $(MLX_DIR)
	@echo "Compilation de miniRT..."
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LNK) -o $(NAME)
	@echo "✅ miniRT est prêt !"

# Règle pour compiler les fichiers .c en .o
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Nettoyage des fichiers objets..."
	rm -rf $(OBJS_DIR)
	@make clean -C $(MLX_DIR) > /dev/null

fclean: clean
	@echo "Nettoyage complet..."
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re