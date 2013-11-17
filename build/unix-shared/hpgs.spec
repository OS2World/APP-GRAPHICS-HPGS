Summary: HPGl Script - A HPGL interpreter/renderer.
Name: hpgs
Version: HPGS_MAJOR_VERSION.HPGS_MINOR_VERSION.HPGS_PATCH_VERSION
Release: HPGS_EXTRA_VERSION
License: LGPL
Group: Applications/Graphics
Source: http://prdownload.berlios.de/hpgs/hpgs-%{version}.tar.gz
BuildRoot: /var/tmp/%{name}-buildroot
Requires: libpng zlib glibc
BuildRequires: libpng-devel glibc-devel gettext

%description
HPGS is an HPGL/2 interpreter, which renders HPGL/2 through a Postscript-like API.
Currently, it can render to eps and png files.
For rendering the scenery to pixel formats, a rendering engine has been coded,
which draws vector graphics into pixel buffers.

%package devel
Group:          Development/Libraries/Graphics
Summary:        Additional files needed for hpgs development
Requires:       %{name} = %{version} glibc-devel

%description devel
This package contains files required to develop applications using the
hpgs libraries.

%prep
%setup -q

%build
cd build/unix-shared
make prefix=/usr libsfx=%{_lib} slibsfx=%{_lib} COPT="$RPM_OPT_FLAGS"

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr/bin
mkdir -p $RPM_BUILD_ROOT/usr/include
mkdir -p $RPM_BUILD_ROOT/usr/%{_lib}
mkdir -p $RPM_BUILD_ROOT/usr/share/doc/packages/hpgs
cp -pr doc $RPM_BUILD_ROOT/usr/share/doc/packages/hpgs
cp -p INSTALL README LICENSE TODO ChangeLog $RPM_BUILD_ROOT/usr/share/doc/packages/hpgs

cd build/unix-shared
make install-devel prefix=$RPM_BUILD_ROOT/usr libsfx=%{_lib} slibsfx=%{_lib}

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)

/usr/bin/hpgs
/usr/%{_lib}/libhpgs.so.%{version}
/usr/%{_lib}/libhpgs.so.HPGS_MAJOR_VERSION.HPGS_MINOR_VERSION
/usr/share/locale/de/LC_MESSAGES/hpgs.mo
%doc /usr/share/doc/packages/hpgs

%files devel
%defattr(-,root,root)

/usr/%{_lib}/libhpgs.so
/usr/include/hpgs.h
/usr/include/hpgsplugin.h
/usr/include/hpgsmutex.h

%changelog
