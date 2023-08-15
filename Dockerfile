FROM debian:latest

ENV CC="gcc" CFLAGS="-Wall -Wextra -Werror" READLINE_LINK="-lreadline "

RUN apt-get -y update \
&& \
	apt-get install \
	gcc \
	vim \
	make \
	git \
	lldb \
	valgrind \
	libcriterion-dev \
	libreadline-dev \
	strace \
	manpages \
	less \
	-y \
&& \
	apt-get clean \

#	start up docker application
#
#	to build image:
#	docker build ./ -f Dockerfile
#
#	to find image_ID:
#	docker image list
#
#	to run docker container:
#	docker run -it --rm -v $PWD:/pwd [image_tag/image_ID]
#
#	cd pwd
#	make fclean
#	make DEBUG=1 (executable = "minishell") [ RE Make your minishell with (-g) debug flags ]
#
#	to run valgrind:
#	valgrind --leak-check=full --show-leak-kinds=all --suppressions=[SUPPRESSIONFILE.supp] ./[EXE]
#	--trace-fds=yes
#   --trace-childs=yes
#	leaks shown at exit (or ctrl-D)
#