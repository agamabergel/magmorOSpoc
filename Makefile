BIN_DIR = ./bin

MYFS_HEADERS = blkdev.h myfs.h
MYFS_SRC_FILES = blkdev.cpp myfs.cpp

MYFS_MAIN_SRC = $(MYFS_SRC_FILES) magmorOS.cpp

all: ${BIN_DIR}/magmorOS

${BIN_DIR}/magmorOS: $(MYFS_MAIN_SRC) $(MYFS_HEADERS) ${BIN_DIR}/.exist
	g++ ${MYFS_MAIN_SRC} -o ${BIN_DIR}/magmorOS -g -Wall

${BIN_DIR}/.exist:
	mkdir ${BIN_DIR}
	touch ${BIN_DIR}/.exist

clean:
	rm -f ${BIN_DIR}/magmorOS
