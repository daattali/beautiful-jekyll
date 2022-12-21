# tested with pandoc 2.9.2.1 and sed 4.7 (debian)
.PHONY: all

all:
	sed 's/Answer: .*//'  mds_self_test.md \
		| sed '/Answer:/,/end answer/d' \
		| pandoc -o mds_self_test.pdf
	pandoc mds_self_test.md -o mds_self_test_answers.pdf
