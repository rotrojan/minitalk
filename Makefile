# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rotrojan <rotrojan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/18 14:51:42 by rotrojan          #+#    #+#              #
#    Updated: 2021/06/18 02:37:49 by bigo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

CLIENT_NAME = client
SERVER_NAME = server

CLIENT_SRCS = client.c
CLIENT_OBJS = $(CLIENT_SRCS:%.c=$(OBJS_DIR)/%.o)

SERVER_SRCS = server.c
SERVER_OBJS = $(SERVER_SRCS:%.c=$(OBJS_DIR)/%.o)

UTILS_SRCS = ft_atoi.c ft_isdigit.c ft_putnbr_fd.c ft_putstr_fd.c \
			ft_strlen.c ft_putchar_fd.c
UTILS_OBJS = $(UTILS_SRCS:%.c=$(OBJS_DIR)/%.o)

SRCS_DIR = srcs
OBJS_DIR = .objs

DEP = $(CLIENT_OBJS:%.o=%.d) $(SERVER_OBJS:%.o=%.d) $(UTILS_OBJS:%.o=%.d)

CC = clang
RM = rm -f
MKDIR = mkdir -p

CFLAGS = -Wall -Wextra -Werror -MMD -I includes/

vpath %.c srcs/utils srcs

all: $(NAME)

$(NAME):
	$(MAKE) $(SERVER_NAME)
	$(MAKE) $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER_OBJS) $(UTILS_OBJS)
	$(CC) $^ -o $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJS) $(UTILS_OBJS)
	$(CC) $^ -o $(CLIENT_NAME)

-include $(DEP)
$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	$(MKDIR) $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(SERVER_NAME) $(CLIENT_NAME)

re: fclean all

.PHONY: $(NAME) all clean fclean re
