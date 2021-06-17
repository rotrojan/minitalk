# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rotrojan <rotrojan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/18 14:51:42 by rotrojan          #+#    #+#              #
#    Updated: 2021/06/17 01:04:26 by bigo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = $(CLIENT) $(SERVER)

CLIENT = client
SERVER = server

SRCS_CLIENT =	main_client.c
SRCS_SERVER =	main_server.c
SRCS = $(SRCS_CLIENT) $(SRCS_SERVER)
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPENDENCIES = $(OBJS:%.o=%.d)

SRCS_DIR = srcs
OBJS_DIR = .objs
INCLUDES_DIR = includes $(LIBS:%=lib%/includes)

LIBS = gc ft

MAKE = make
CC = clang
RM = rm -f
MKDIR = mkdir -p
DEBUG = off

CFLAGS = -MMD -Wall -Wextra $(INCLUDES_DIR:%=-I %) #-Werror
ifeq ($(DEBUG), on)
	CFLAGS += -g3 -fsanitize=address
endif
LDFLAGS = $(LIBS:%=-L lib%) $(LIBS:%=-l%) -lncurses

vpath %.c	$(addprefix $(SRCS_DIR), /. /client /server)

all:
	$(foreach LIB, ${LIBS}, ${MAKE} -C lib${LIB} ;)
	$(MAKE) $(NAME)

$(NAME): $(CLIENT) $(SERVER)

$(CLIENT): $(OBJS) | $(LIBS:%=lib%.a)
	$(CC) $^ -o $(CLIENT) $(LDFLAGS)

$(SERVER): $(OBJS) | $(LIBS:%=lib%.a)
	$(CC) $^ -o $(SERVER) $(LDFLAGS)

-include $(DEPENDENCIES)
$(OBJS_DIR)/%.o: %.c $(OBJS_DIR)/debug$(DEBUG) | $(OBJS_DIR) 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	$(MKDIR) $(OBJS_DIR)

lib%.a:
	$(MAKE) -C $(@:%.a=%)

$(OBJS_DIR)/debug$(DEBUG): | $(OBJS_DIR)
	$(RM) $(OBJS_DIR)/debug*
	touch $@

clean:
	$(foreach LIB, $(LIBS), $(MAKE) $@ -C lib$(LIB);)
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME) $(foreach LIB, $(LIBS), lib$(LIB)/lib$(LIB).a)

re: fclean all

.PHONY: all clean fclean re
