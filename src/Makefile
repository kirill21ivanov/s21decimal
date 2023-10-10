CC=gcc
NAME=s21_decimal.a
CFLAGS=-Wall -Wextra -Werror -std=c11
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

OS=$(shell uname -s)
ROOT_DIR=$(shell dirname $(abspath $(MAKEFILE_LIST)))

SRCS=$(shell find $(ROOT_DIR) -name "s21_*.c" ! -name "s21_*_test.c")
SRC_OBJS=$(patsubst %.c,%.o,$(SRCS))
TEST_SRCS=$(shell find $(ROOT_DIR) -name "s21_*_test.c")

ifeq ($(OS),Darwin)
	LINUX_FLAGS=
	OPEN_CMD=open
	LCOV_INSTALL_CMD=brew install lcov
endif
ifeq ($(OS),Linux)
	OPEN_CMD=xdg-open
	LCOV_INSTALL_CMD=apt install lcov
	LINUX_FLAGS=-lsubunit -lrt -lpthread -lm
endif

.SILENT:
.PHONY: all
all: $(NAME) gcov_report

$(NAME): $(SRC_OBJS) $(ROOT_DIR)/s21_decimal.h
	ar -rcs $(ROOT_DIR)/$(NAME) $(SRC_OBJS)
	ranlib $(ROOT_DIR)/$(NAME)
	cp $(ROOT_DIR)/$(NAME) $(ROOT_DIR)/lib$(NAME)
	rm -rf $(ROOT_DIR)/*.o

.PHONY: help
help: ## Display this help screen
	awk 'BEGIN {FS = ":.*##"; printf "Usage:\n  make \033[36m<target>\033[0m\n"} /^[a-zA-Z0-9_-]+:.*?##/ { printf "  \033[36m%-14s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) }' $(MAKEFILE_LIST)

.PHONY: lint
lint: ## Lint
	clang-format -i $(ROOT_DIR)/*.c

.PHONY: lint-check
lint-check: ## Lint check
	cp ../materials/linters/.clang-format ./
	clang-format -n $(ROOT_DIR)/*.c

.PHONY: test
test: $(NAME) ## Test
	$(CC) $(CFLAGS) ${TEST_SRCS} $< -o $(ROOT_DIR)/test -lcheck $(LINUX_FLAGS)
	$(ROOT_DIR)/test && rm -rf $(ROOT_DIR)/test

.PHONY: gcov_report
gcov_report: $(NAME) install-lcov ## Gcov report
	$(CC) $(CFLAGS) $(GCOV_FLAGS) ${TEST_SRCS} ${SRCS} -o $(ROOT_DIR)/gcov_report -lcheck $(LINUX_FLAGS)
	$(ROOT_DIR)/gcov_report && rm -rf $(ROOT_DIR)/gcov_report
	lcov -t s21_decimal_test -o $(ROOT_DIR)/s21_decimal_test.info -c -d .
	genhtml -o $(ROOT_DIR)/report $(ROOT_DIR)/s21_decimal_test.info
	$(OPEN_CMD) $(ROOT_DIR)/report/index.html
	make clean-lcov

.PHONY: install-lcov
install-lcov: ## Install lcov
	$(LCOV_INSTALL_CMD)

.PHONY: clean-lcov
clean-lcov: ## Clean lcov
	rm -rf $(ROOT_DIR)/*.gcda \
		   $(ROOT_DIR)/*.gcno \
		   $(ROOT_DIR)/*.info

.PHONY: clean
clean: clean-lcov ## Clean
	rm -rf $(ROOT_DIR)/*.a \
		   $(ROOT_DIR)/*.o \
		   $(ROOT_DIR)/test \
		   $(ROOT_DIR)/report \
		   $(ROOT_DIR)/gcov_report
