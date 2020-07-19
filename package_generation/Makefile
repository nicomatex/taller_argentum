CLIENT_SOURCE_DIR := ../client

ASSETS_DIR := $(CLIENT_SOURCE_DIR)/assets
IND_DIR := $(CLIENT_SOURCE_DIR)/ind
BIN_FILE := $(CLIENT_SOURCE_DIR)/build/aoclient

PACKAGE_NAME := argentum
VERSION := 1.0
REVISION := 1

PACKAGE_DIR := ./$(PACKAGE_NAME)_$(VERSION)-$(REVISION)
PACKAGE_FILENAME := $(PACKAGE_DIR).deb

define DEBFILE_BODY
Package: $(PACKAGE_NAME)
Version: $(VERSION)-$(REVISION)
Section: base
Priority: optional
Architecture: i386
Maintainer: Grupo 4 - Taller 75.42
Description: Argentum Online
 Remake del clasico juego Argentum Online!
endef
export DEBFILE_BODY

generate_package: copy_files create_control_file
	dpkg-deb --build $(PACKAGE_DIR)
	rm -rf $(PACKAGE_DIR)

create_package_dir: clean
	mkdir $(PACKAGE_DIR)
	mkdir $(PACKAGE_DIR)/usr
	mkdir $(PACKAGE_DIR)/usr/local
	mkdir $(PACKAGE_DIR)/usr/local/bin
	mkdir $(PACKAGE_DIR)/usr/local/share
	mkdir $(PACKAGE_DIR)/usr/local/share/argentum
	mkdir $(PACKAGE_DIR)/DEBIAN

create_control_file: clean create_package_dir
	echo "$$DEBFILE_BODY" > $(PACKAGE_DIR)/DEBIAN/control

copy_files: clean create_package_dir
	cp -rf $(ASSETS_DIR) $(PACKAGE_DIR)/usr/local/share/argentum
	cp -rf $(IND_DIR) $(PACKAGE_DIR)/usr/local/share/argentum
	cp -f $(BIN_FILE) $(PACKAGE_DIR)/usr/local/bin

clean: 
	rm -rf $(PACKAGE_DIR) $(PACKAGE_FILENAME)
