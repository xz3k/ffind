CC = gcc
CFLAGS = -march=native -O3 -Wall -Wextra -flto -mtune=native -pipe
SRC := ffind.c
OUT := ffind
SYSBIN := /usr/bin
DB_LOC := /usr/share/ffind
DB_F := $(DB_LOC)/ffind.db
FFUPDATE := ffupdate

all: $(OUT)

$(OUT): $(SRC)
	@printf 'CC  %-40s => %s\n' "$<" "$@"
	@$(CC) $(CFLAGS) $< -o $@

install: ffind
	@mkdir -p "$(SYSBIN)" "$(DB_LOC)"
	@touch "$(DB_F)"
	@printf 'COPY  %-40s => %s\n' "$(OUT)" "$(SYSBIN)/$(OUT)"
	@install -m 755 $(OUT) /usr/bin/$(OUT)
	@printf 'COPY  %-40s => %s\n' "$(FFUPDATE)" "$(SYSBIN)/$(FFUPDATE)"
	@install -m 755 $(FFUPDATE) /usr/bin/$(FFUPDATE)

clean:
	@printf 'DEL  %-40s\n' "$(OUT)"
	-@rm -f $(OUT)

rebuild: clean $(OUT)

.PHONY: clean install
