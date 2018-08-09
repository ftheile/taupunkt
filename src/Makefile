app = taupunkt
src = $(wildcard *.c)
obj = $(src:.c=.o)
dep = $(obj:.o=.d)  # one dependency file for each source

CFLAGS = -Wall -Wextra -Werror=implicit-function-declaration -g -grecord-gcc-switches -pipe -O2 -D_FORTIFY_SOURCE=2
LDFLAGS = -lm

.PHONY: all
all: $(app)

$(app): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

-include $(dep)   # include all dep files in the makefile

# rule to generate a dep file by using the C preprocessor
# (see man cpp for details on the -MM and -MT options)
%.d: %.c
	@$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(obj) $(app)

.PHONY: cleandep
cleandep:
	rm -f $(dep)
