CC = g++
CFLAGS = -Wall -Wextra -Iinclude -std=c++17 -O2
LDFLAGS = `sdl2-config --libs --cflags` -Ofast -lm 

BUILD_DIR = build
OBJS_DIR = $(BUILD_DIR)/objs
DEPS_DIR = $(BUILD_DIR)/deps

PRECOMPILE = mkdir -p $(dir $@)
POSTCOMPILE = sleep 0

ifndef NODEPS

PRECOMPILE += ;mkdir -p $(dir $(DEPS_DIR)/$*)
CFLAGS += -MT $@ -MMD -MP -MF $(DEPS_DIR)/$*.Td
POSTCOMPILE += ;mv -f $(DEPS_DIR)/$*.Td $(DEPS_DIR)/$*.d && touch $@

endif

include src.mk

OBJS = $(patsubst src/%.cpp, $(OBJS_DIR)/%.o, $(SRCS))

all: projet

$(OBJS_DIR)/%.o: src/%.cpp Makefile
	@$(PRECOMPILE)
	$(CC) $(CFLAGS) -c -o $@ $<
	@$(POSTCOMPILE)

projet: $(OBJS_GAME) $(OBJS)

projet:
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf build

fclean: clean
	rm -rf projet

re:
	$(MAKE) fclean
	$(MAKE) all

include $(wildcard $(DEPS_DIR)/**/*.d)

.PHONY: all clean fclean re test
