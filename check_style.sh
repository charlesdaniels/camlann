#!/bin/sh

# Check code style using checkpatch

set -u

CHECKPATCH_URL='https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/plain/scripts/checkpatch.pl'

if [ ! -x "$(which checkpatch.pl)" ] ; then
	CHECKPATCH="/tmp/checkpatch.pl"
	wget -O "$CHECKPATCH" "$CHECKPATCH_URL"
	chmod +x "$CHECKAPTCH"
else
	CHECKPATCH="$(which checkpatch.pl)"
fi

CAMLANN_SRC="$(dirname "$0")/camlann"

EXIT=0
for f in "$CAMLANN_SRC"/*.h "$CAMLANN_SRC"/*.c ; do
	"$CHECKPATCH" -no-tree -file "$f"
	EC=$?
	if [ $EC -gt $EXIT ] ; then
		EXIT=$EC
	fi
done

exit $EXIT
