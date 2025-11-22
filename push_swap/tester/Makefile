ROOT		= ..
PUSH_SWAP	= $(ROOT)/push_swap

all: $(PUSH_SWAP)
	@bash run_tests.sh

$(PUSH_SWAP):
	@$(MAKE) -C $(ROOT)

clean:
	@rm -rf logs

re: clean all

.PHONY: all clean re
