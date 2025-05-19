# --------------------------------- Makefile Main ---------------------------------- #

MAIN		=	$(SRCDIR)pipex.c	\

SRC			=	$(SRCDIR)utils.c	\

BSRC		=	$(SRCDIR)pipex_bonus.c												-#

SRCDIR		=	src/
OBJDIR		=	obj/
INCDIR		=	-I ./include/				\
				-I ./libft/include/			\

MAKENM		=	libft

LIBFT		=	libft.a
LIBEXE		=	pipex.a

NAME		=	pipex
BONUS		=	#- The name of the bonus final program.								-#

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror $(INCDIR) -g 

INFILE		=	#- Text to be added on infile.txt. Ifndef, file starts with '\n'.

# --------------------------- Makefile Object Compilation -------------------------- #

OBJ			=	$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
MOBJ		=	$(MAIN:$(SRCDIR)%.c=$(OBJDIR)%.o)
BOBJ		=	$(BSRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

# ------------------------------- Makefile Cosmetics ------------------------------- #

CLIBFT			=	Libft
CNAME			=	Pipex
CBONUS			=	#-Name of the final bonus program with first letter in caps.	-#
COLOUR_GREEN	=	\033[0;32m
COLOUR_RED		=	\033[0;31m
COLOUR_CIAN		=	\033[0;35m
COLOUR_BLUE		=	\033[0;34m
COLOUR_END		=	\033[0m

# --------------------------------- Makefile Body ---------------------------------- #

.PHONY: all msg clear clean fclean re

all: inoutfile $(NAME)

inoutfile:
	@echo $(INFILE) > infile.txt
	@touch outfile.txt

#- Creates the libft.a library.														-#
$(LIBFT):
	@echo "$(COLOUR_GREEN)$(CNAME) - $(CLIBFT) compilation.\n$(COLOUR_END)"
	@echo "$(COLOUR_BLUE)#--------------------------------------------------#\n"
	@make -s -C $(MAKENM)
	@echo "$(COLOUR_BLUE)\n#--------------------------------------------------#\n"
	@echo "$(COLOUR_GREEN)$(CNAME) - $(CLIBFT) initialized.$(COLOUR_END)"

#- Creates the program library with all the objects minus the main object			-# 
$(LIBEXE): $(LIBFT) $(OBJDIR) $(OBJ) $(MOBJ)
	@echo -n "$(COLOUR_GREEN)"
	@cp $(MAKENM)/$(LIBFT) $(LIBEXE)
	@ar rcs $(LIBEXE) $(OBJ)

#- Creates a directory named $(OBJDIR).												-#
$(OBJDIR):
	@echo "\n$(COLOUR_GREEN)$(CNAME) - Object compilation:\n$(COLOUR_END)"
	@mkdir -p $@
#
#- Compiles each %(generic).c source into its respective %(generic).o				-#
$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(COLOUR_CIAN)\t-$@ created.$(COLOUR_END)"
#
#- Compiles the main object with the program library into the final executable.		-#
$(NAME): $(LIBEXE)
	@$(CC) $(CFLAGS) -o $(NAME) $(MOBJ) $(LIBEXE)
	@echo "\n$(COLOUR_GREEN)$(CNAME) - Program ready.$(COLOUR_END)"
#
msg:
	@echo "$(COLOUR_GREEN)\n$(CBONUS) - Bonus program compilation.\n$(COLOUR_END)"
	@echo "$(COLOUR_BLUE)#--------------------------------------------------#\n"
#
clear:
	@clear
#
#- Compiles the bonus objects and the program library into the bonus executable.	-#
bonus: $(NAME) msg $(BOBJ)
	@$(CC) $(CFLAGS) -o $(BONUS) $(BOBJ) $(LIBEXE)
	@echo "$(COLOUR_BLUE)\n#--------------------------------------------------#\n"
	@echo "$(COLOUR_GREEN)$(CBONUS) - Bonus program ready.$(COLOUR_END)"
#
#- Removes every object inside $(OBJDIR) and the directory itself.					-#
clean:
	@make clean -s -C $(MAKENM)
	@echo "$(COLOUR_RED)$(CNAME) - Object cleaning complete.\n$(COLOUR_END)"
#
#- Removes the final files made with this makefile, executing clean as well.		-#
fclean:
	@make fclean -s -C $(MAKENM)
	@rm -rf $(OBJDIR)
	@echo "$(COLOUR_RED)$(CNAME) - Object cleaning complete.\n$(COLOUR_END)"
	@rm -f $(NAME)
	@rm -f infile.txt
	@rm -f outfile.txt
	@rm -f $(BONUS)
	@rm -f $(LIBEXE)
	@echo "$(COLOUR_RED)$(CNAME) - Files removed.\n$(COLOUR_END)"
#
#- Restarts the Makefile. Erases everything to default, and executes again.			-#
re: clear fclean all