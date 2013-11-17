#!/bin/sh
#
# $Id: devpkg.sh 401 2007-09-14 15:07:54Z softadm $
#
# Author: Wolfgang Glas
#
# Build a debian package right from the svn source tree.
#
# All options are passed to dpkg-buildpackage, so you might
# use i.e.
#
# debian/devpkg.sh -tc -uc
#
# To cleanup the debian tree and to not sign the changelog file.
#

hpgs_major=`awk '/^#define HPGS_MAJOR_VERSION/ { print $3; }' src/hpgs.h`
hpgs_minor=`awk '/^#define HPGS_MINOR_VERSION/ { print $3; }' src/hpgs.h`
hpgs_patch=`awk '/^#define HPGS_PATCH_VERSION/ { print $3; }' src/hpgs.h`
VERSION=$hpgs_major.$hpgs_minor.$hpgs_patch
RELEASE=`svn info | sed 's/^Revision: //p;d'`

GPGKEY=$(gpg -K | sed 's/^uid *//p;d' | tail -1)
DATE=$(date -R)

echo "VERSION="$VERSION
echo "RELEASE="$RELEASE
echo "GPGKEY="$GPGKEY
echo "DATE="$DATE

cat > debian/changelog <<EOF
hpgs ($VERSION-$RELEASE) any; urgency=high

  * devpkg.sh: Created developer test release.
 
 -- $GPGKEY  $DATE

EOF
cat debian/changelog.in >> debian/changelog

debian_files="debian/control debian/hpgs.install"

for file in $debian_files
do
  rm -f $file
  test -f $file.in && sed -e "s/HPGS_MAJOR_VERSION/$hpgs_major/" -e "s/HPGS_MINOR_VERSION/$hpgs_minor/" -e "s/HPGS_PATCH_VERSION/$hpgs_patch/" -e "s/HPGS_EXTRA_VERSION/$hpgs_extra/" < $file.in > $file
done

dpkg-buildpackage -rfakeroot -nc $*

rm -f $debian_files debian/changelog
