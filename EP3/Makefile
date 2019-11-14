CC = cc
CFLAGS = -w

test: change_policy \
	make_holes \
	tester \
	#

change_policy: change_policy.c
	$(CC) $(CFLAGS) -o $@ $?

make_holes: make_holes.c
	$(CC) $(CFLAGS) -o $@ $?

tester: tester.c
	$(CC) $(CFLAGS) -o $@ $?

clean:
	rm change_policy \
	rm make_holes \
	rm tester \
	#