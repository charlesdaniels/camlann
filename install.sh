#!/bin/sh

# .SCRIPTDOC
#
# This script installs ``camlann`` into a NIOSII SDK project.
#
# .SYNTAX
#
# $1 . . . Path to the top-level directory of the Eclipse project in which the
#          C code to wrap is stored.
#
# .ENDOC

set -e
set -u

if [ $# -ne 1 ] ; then
	echo "FATAL: incorrect usage."
	echo "$0 [install path]"
	exit 1
fi

INSTALL_PATH="$1"
SOURCE_PATH="$(dirname "$0")"

if [ ! -d "$INSTALL_PATH" ] ; then
	echo "FATAL: '$INSTALL_PATH' does not exist or not a directory."
	exit 1
fi

CAMLANN_DIR="$INSTALL_PATH/camlann"
CAMLANN_MK="$INSTALL_PATH/camlann.mk"

PROMPT_CHOICE_FLAG="NO"
if [ -e "$CAMLANN_DIR" ] ; then
	echo "WARNING: '$CAMLANN_DIR' exists already, it will be overwritten."
	PROMPT_CHOICE_FLAG="YES"
fi

if [ -e "$CAMLANN_MK" ] ; then
	echo "WARNING: '$CAMLANN_MK' exists already, it will be overwritten."
	PROMPT_CHOICE_FLAG="YES"
fi

echo "Camlann will be installed from '$SOURCE_PATH'"

if [ "$PROMPT_CHOICE_FLAG" != "NO" ] ; then
	read -p "Are you sure you wish to proceed (y/n)? " choice
	case "$choice" in
		[Yy]* ) echo "Proceeding with installation... "; break ;;
		[Nn]* ) echo "Installation canceled." ; exit 1 ;;
		* ) echo "Invalid choice. Aborting installation"; exit 2 ;;
	esac
fi

echo "Removing existing Camlann installation (if any)... "
if [ -e "$CAMLANN_MK" ] ; then
	rm "$CAMLANN_MK"
fi
if [ -e "$CAMLANN_DIR" ] ; then
	rm -r "$CAMLANN_DIR"
fi

echo "Installing Camlann files... "
cp -r "$SOURCE_PATH/camlann/" "$CAMLANN_DIR"
cp "$SOURCE_PATH/camlann.mk" "$CAMLANN_MK"

echo "Generating objects list... "
OBJECT_LIST="$(ls "$INSTALL_PATH"/*.c | while read -r cfile ; do basename "$cfile" | sed 's/.c$/.o/g' ; done | tr '\n' ' ')"
echo "Generated objects list '$OBJECT_LIST'"

echo "Installing objects list... "
sed -i 's/##NIOS2OBJECTS##/'"$OBJECT_LIST"'/g' "$CAMLANN_MK"

echo "Installation completed."

