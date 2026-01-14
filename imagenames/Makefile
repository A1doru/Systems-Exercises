CFLAGS=-Wall -g
.PHONY: all
SHELL=/bin/bash

PROGRAM=imagenames

TIMEOUT=8

TESTS_DIR=tests

TESTS_SH:=$(wildcard $(TESTS_DIR)/*.sh)
TESTS:=$(patsubst $(TESTS_DIR)/%.sh, %, $(TESTS_SH))

.PHONY: all
all: compile-program check

.PHONY: compile-program

compile-program: $(PROGRAM)

.PHONY: check
check: compile-program $(TESTS_SH)
	@exec 2> /dev/null; \
	for t in $(TESTS); do \
		echo -n "Running test $$t..." ; \
		/bin/sh "$(TESTS_DIR)/$$t.sh" $(dir $(PROGRAM))$(PROGRAM) > "$$t.out" 2>&1 & \
		prog_pid=$$!; \
		( sleep $(TIMEOUT); kill $$prog_pid > /dev/null 2>&1 ) & \
		killer_pid=$$!; \
		wait $$prog_pid; \
		res=$$?; \
		if test $$res -gt 128; \
		then \
			echo KILLED; \
			rm -f "$$t.out" ;\
		else \
			kill $$killer_pid > /dev/null 2>&1 ;\
			wait $$killer_pid; \
			if cmp -s "$$t.out" "$(TESTS_DIR)/$$t.expected"; \
			then \
				echo "PASSED" ;\
				rm -f "$$t.out" ;\
			else \
				echo "FAILED" ;\
				diff "$$t.out" "$(TESTS_DIR)/$$t.expected";\
			fi; \
		fi; \
	done

.PHONY: clean
clean:
	rm -f $(PROGRAM) tests/*.out
