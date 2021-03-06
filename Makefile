EXENAME = alum1
ODIR = ./obj

FLAGS = -Wall -Wextra -Werror

# COLORS

BLACK = '\033[0;30m'
RED = '\033[0;31m'
GREEN = '\033[0;32m'
BROWN = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
LGRAY = '\033[0;37m'
DGRAY = '\033[1;30m'
LRED = '\033[1;31m'
LGREEN = '\033[1;32m'
YELLOW = '\033[1;33m'
LBLUE = '\033[1;34m'
PINK = '\033[1;35m'
LCYAN = '\033[1;36m'
WHITE = '\033[1;37m'
NC = '\033[0m'


# Libft

LIBFT_DIR = libft
LIBFT_NAME = libft.a
LIBFT_SRCDIR = $(LIBFT_DIR)/srcs
LIBFT_INCDIR = $(LIBFT_DIR)/includes

LIBFT_HEADNAMES =	libft

LIBFT_HEADERS = $(patsubst %, $(LIBFT_INCDIR)/%.h, $(LIBFT_HEADNAMES))

LIBFT_FILENAMES = ft_atoi ft_bzero ft_isalnum ft_isalpha ft_isascii ft_isdigit \
 	ft_isprint ft_isspace ft_iswhitespace ft_itoa ft_lstadd ft_lstaddb ft_lstdel \
	ft_lstdelnode ft_lstdelone ft_lstiter ft_lstmap ft_lstnew ft_lstpushb ft_lstpushf \
	ft_lsttostr ft_memalloc ft_memccpy ft_memchr ft_memcmp ft_memcpy ft_memdel \
	ft_memdup ft_memmove ft_memset ft_putchar ft_putchar_fd ft_putendl ft_putendl_fd \
	ft_putnbr ft_putnbr_fd ft_putstr ft_putstr_fd ft_realloc ft_strcat ft_strchr \
	ft_strclr ft_strcmp ft_strcpy ft_strdel ft_strdup ft_strequ ft_striter ft_striteri \
	ft_strjoin ft_strlcat ft_strlen ft_strmap ft_strmapi ft_strncat ft_strncmp \
	ft_strncpy ft_strnequ ft_strnew ft_strnstr ft_strrchr ft_strsplit ft_strsrch \
	ft_strstr ft_strsub ft_strtrim ft_tolower ft_toupper get_next_line

LIBFT_CFILES = $(patsubst %, $(LIBFT_SRCDIR)/%.c, $(LIBFT_FILENAMES))
LIBFT_OFILES = $(patsubst %, $(ODIR)/$(LIBFT_DIR)/%.o, $(LIBFT_FILENAMES))

# Alum1

ALUM_SRCDIR = ./srcs
ALUM_INCDIR = ./includes

ALUM_HEADNAMES = alcu
ALUM_HEADERS = $(patsubst %, $(ALUM_INCDIR)/%.h, $(ALUM_HEADNAMES))

ALUM_FILENAMES = main game
ALUM_CFILES = $(patsubst %, $(ALUM_SRCDIR)/%.c, $(ALUM_FILENAMES))
ALUM_OFILES = $(patsubst %, $(ODIR)/%.o, $(ALUM_FILENAMES))

all: $(ODIR) $(LIBFT_NAME) $(EXENAME)

$(LIBFT_NAME): $(ODIR) $(LIBFT_OFILES)
	@echo ${CYAN}"Compiling $(LIBFT_NAME)"${NC}
	@ar rc $(LIBFT_NAME) $(LIBFT_OFILES)
	@ranlib $(LIBFT_NAME)
	@echo ${GREEN}"[$(LIBFT_NAME) is up to date.]"${NC}

$(EXENAME): $(ODIR) $(LIBFT_NAME) $(ALUM_OFILES) $(ALUM_HEADERS)
	@echo ${CYAN}[Compiling $(EXENAME)]${NC}
	@gcc $(FLAGS) -o $(EXENAME) -I$(LIBFT_INCDIR) -L. -lft $(ALUM_OFILES) -O3
	@echo ${GREEN}"[--------| $(EXENAME) is up to date. |---------]"${NC}

$(ODIR)/%.o: $(ALUM_SRCDIR)/%.c $(ALUM_HEADERS)
	@gcc $(FLAGS) -o $@ -c $< -I$(ALUM_INCDIR) -I$(LIBFT_INCDIR)

$(ODIR)/$(LIBFT_DIR)/%.o: $(LIBFT_SRCDIR)/%.c $(LIBFT_HEADERS)
	@gcc $(FLAGS) -o $@ -c $< -I$(LIBFT_INCDIR)

$(ODIR):
	@mkdir -p $(ODIR)
	@mkdir -p $(ODIR)/$(LIBFT_DIR)

clean:
	@echo ${RED}"[Removing *.o files]"${NC}
	@/bin/rm -rf $(ODIR)

fclean: clean
	@echo ${RED}"[Removing $(LIBFT_NAME)]"${NC}
	@/bin/rm -f $(LIBFT_NAME)
	@echo ${RED}"[Removing $(EXENAME)]"${NC}
	@/bin/rm -f $(EXENAME)

re: fclean all
