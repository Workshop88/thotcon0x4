%define         docver 2012.11.12
%define         libver 2012.11.10
Name:           kicad
Version:        2012.11.15
Release:        1.r3804%{?dist}.PWR
Summary:        Schematic diagram and printed circuit board design

Group:          Applications/Engineering
License:        GPLv2+
URL:            https://launchpad.net/kicad

# Source files created from upstream's bazaar repository
# bzr export -r 3804 kicad-2012.11.15
# bzr export -r 114 kicad-libraries-2012.01.19
# bzr export -r 309 kicad-doc-2012.01.19

Source0:        %{name}-%{version}.tar.bz2
Source1:        %{name}-doc-%{docver}.tar.bz2
Source2:        %{name}-libraries-%{libver}.tar.bz2
Source3:        %{name}-ld.conf
Source4:        %{name}-2010.05.09.x-kicad-pcbnew.desktop
Source5:        pcbnew.desktop
Source6:        %{name}-icons.tar.bz2
Source7:        Epcos-MKT-1.0.tar.bz2

Patch10:        %{name}-%{version}-real-version.patch
Patch11:        kicad-use-system-boost.patch

BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:  desktop-file-utils
BuildRequires:  wxGTK-devel
BuildRequires:  boost-devel
BuildRequires:  cmake
BuildRequires:  doxygen

Requires:       electronics-menu
Requires:       kicad-components

%description
Kicad is EDA software to design electronic schematic
diagrams and printed circuit board artwork up to 16
layers.

Kicad is a set of four apps and a project manager:
- Eeschema: schematic entry
- Pcbnew: board editor
- Gerbview: GERBER viewer (photoplotter documents)
- Cvpcb: footprint selector for components used in the circuit design
- Kicad: project manager

%package        lib-default
Summary:        Standard component libraries for %{name}
Group:          Applications/Engineering
License:        GPLv2+
Requires:       %{name} = %{version}-%{release}
%if 0%{?fedora} >= 11
BuildArch:      noarch
%endif
Provides:       kicad-components

%description    lib-default
Standard component and foot print libraries supplied with KiCad.

%package        doc
Summary:        Documentation for kicad
Group:          Applications/Engineering
License:        GPLv2+
Requires:       %{name} = %{version}-%{release}
%if 0%{?fedora} >= 11
BuildArch:      noarch
%endif

%description    doc
Documentation and tutorials for kicad in English

%prep
%setup -q -a 1 -a 2 -a 6 -a 7

%patch10 -p1 -b .real-version
%patch11 -p1 -b .boost-sys

%ifarch x86_64 sparc64 ppc64 amd64 s390x
%{__sed} -i "s|KICAD_PLUGINS lib/kicad/plugins|KICAD_PLUGINS lib64/kicad/plugins|" CMakeLists.txt
%{__sed} -i "s|/usr/lib/kicad|/usr/lib64/kicad|" %{SOURCE3}
%endif


%build

# Add Epcos library
pushd Epcos-MKT-1.0
cp -pR library ../%{name}-libraries-%{libver}/
cp -pR modules ../%{name}-libraries-%{libver}/
popd

#
# Symbols libraries
#
pushd %{name}-libraries-%{libver}
%cmake -DKICAD_STABLE_VERSION=ON
%{__make} %{?_smp_mflags} VERBOSE=1
popd

#
# Core components
mkdir build
pushd build

%cmake   \
    -DKICAD_STABLE_VERSION=ON \
    -DBUILD_TESTING:BOOL=OFF \
    -DKICAD_KEEPCASE:BOOL=ON \
     ..
%{__make} %{?_smp_mflags} VERBOSE=1


%install
%{__rm} -rf %{buildroot}

pushd build
%{__make} INSTALL="install -p" DESTDIR=%{buildroot} install
popd

# install desktop
desktop-file-install \
  --dir %{buildroot}%{_datadir}/applications \
  --remove-category Development              \
  --delete-original                          \
  %{buildroot}%{_datadir}/applications/kicad.desktop

desktop-file-install \
  --dir %{buildroot}%{_datadir}/applications \
  --remove-category Development              \
  --delete-original                          \
  %{buildroot}%{_datadir}/applications/eeschema.desktop

desktop-file-install \
  --dir %{buildroot}%{_datadir}/applications \
  --remove-category Development              \
  %{SOURCE5}

#
# Symbols libraries
#
pushd %{name}-libraries-%{libver}/
%{__make} INSTALL="install -p" DESTDIR=%{buildroot} install
popd

# install template
install -d %{buildroot}%{_datadir}/%{name}/template
install -m 644 template/%{name}.pro %{buildroot}%{_datadir}/%{name}/template

# install new mime type
install -pm 644 %{SOURCE4} %{buildroot}%{_datadir}/mimelnk/application/x-%{name}-pcbnew.desktop

# install mimetype and application icons
install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/32x32/mimetypes/application-x-kicad-eeschema.png %{buildroot}%{_datadir}/icons/hicolor/32x32/mimetypes/application-x-kicad-eeschema.png
install -m 644 -D -p %{name}-icons/resources/linux/mime/icons/hicolor/32x32/apps/eeschema.png %{buildroot}%{_datadir}/icons/hicolor/32x32/apps/eeschema.png
install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/24x24/mimetypes/application-x-kicad-eeschema.png %{buildroot}%{_datadir}/icons/hicolor/24x24/mimetypes/application-x-kicad-eeschema.png
install -m 644 -D -p %{name}-icons/resources/linux/mime/icons/hicolor/24x24/apps/eeschema.png %{buildroot}%{_datadir}/icons/hicolor/24x24/apps/eeschema.png
install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/22x22/mimetypes/application-x-kicad-eeschema.png %{buildroot}%{_datadir}/icons/hicolor/22x22/mimetypes/application-x-kicad-eeschema.png
install -m 644 -D -p %{name}-icons/resources/linux/mime/icons/hicolor/22x22/apps/eeschema.png %{buildroot}%{_datadir}/icons/hicolor/22x22/apps/eeschema.png
install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/16x16/mimetypes/application-x-kicad-eeschema.png %{buildroot}%{_datadir}/icons/hicolor/16x16/mimetypes/application-x-kicad-eeschema.png
install -m 644 -D -p %{name}-icons/resources/linux/mime/icons/hicolor/16x16/apps/eeschema.png %{buildroot}%{_datadir}/icons/hicolor/16x16/apps/eeschema.png

install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/32x32/mimetypes/application-x-kicad-pcbnew.png %{buildroot}%{_datadir}/icons/hicolor/32x32/mimetypes/application-x-kicad-pcbnew.png
install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/32x32/apps/pcbnew.png %{buildroot}%{_datadir}/icons/hicolor/32x32/apps/pcbnew.png
install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/24x24/mimetypes/application-x-kicad-pcbnew.png %{buildroot}%{_datadir}/icons/hicolor/24x24/mimetypes/application-x-kicad-pcbnew.png
install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/24x24/apps/pcbnew.png %{buildroot}%{_datadir}/icons/hicolor/24x24/apps/pcbnew.png
install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/22x22/mimetypes/application-x-kicad-pcbnew.png %{buildroot}%{_datadir}/icons/hicolor/22x22/mimetypes/application-x-kicad-pcbnew.png
install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/22x22/apps/pcbnew.png %{buildroot}%{_datadir}/icons/hicolor/22x22/apps/pcbnew.png
install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/16x16/mimetypes/application-x-kicad-pcbnew.png %{buildroot}%{_datadir}/icons/hicolor/16x16/mimetypes/application-x-kicad-pcbnew.png
install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/16x16/apps/pcbnew.png %{buildroot}%{_datadir}/icons/hicolor/16x16/apps/pcbnew.png

install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/32x32/apps/kicad.png %{buildroot}%{_datadir}/icons/hicolor/32x32/apps/kicad.png
install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/24x24/apps/kicad.png %{buildroot}%{_datadir}/icons/hicolor/24x24/apps/kicad.png
install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/22x22/apps/kicad.png %{buildroot}%{_datadir}/icons/hicolor/22x22/apps/kicad.png
install -pm 644 %{name}-icons/resources/linux/mime/icons/hicolor/16x16/apps/kicad.png %{buildroot}%{_datadir}/icons/hicolor/16x16/apps/kicad.png


# Preparing for documentation pull-ups
%{__rm} -f  %{name}-doc-%{docver}/doc/help/CMakeLists.txt
%{__rm} -f  %{name}-doc-%{docver}/doc/help/makefile
%{__rm} -f  %{name}-doc-%{docver}/doc/tutorials/CMakeLists.txt
%{__rm} -rf %{name}-doc-%{docver}/internat
%{__rm} -rf %{name}-doc-%{docver}/presentations/ru

### for i in de es fr it pl ru; do
###     %{__rm} -rf %{name}-doc-%{docver}/doc/help/$i;
###     %{__rm} -rf %{name}-doc-%{docver}/doc/tutorials/$i;
### done
### 
### %{__rm} -rf %{name}-doc-%{docver}/doc/help/pt
### %{__rm} -rf %{name}-doc-%{docver}/doc/tutorials/hu
### %{__rm} -rf %{name}-doc-%{docver}/doc/tutorials/zh_CN

%{__mkdir_p} %{buildroot}%{_docdir}/%{name}/help/en
%{__mkdir_p} %{buildroot}%{_docdir}/%{name}/tutorials/en
%{__cp} -pr %{name}-doc-%{docver}/doc/help/en/*.pdf  %{buildroot}%{_docdir}/%{name}/help/en
%{__cp} -pr %{name}-doc-%{docver}/doc/help/en/docs_src/*.odg %{buildroot}%{_docdir}/%{name}/help/en/
%{__cp} -pr %{name}-doc-%{docver}/doc/help/file_formats/*.pdf %{buildroot}%{_docdir}/%{name}/help/en
%{__cp} -pr %{name}-doc-%{docver}/presentations/tdose-2009-jerry-jacobs/ \
            %{buildroot}%{_docdir}/%{name}/presentations/
%{__cp} -pr %{name}-doc-%{docver}/doc/contrib/*.pdf  %{buildroot}%{_docdir}/%{name}/tutorials/en
%{__cp} -pr %{name}-doc-%{docver}/doc/tutorials/en/*.pdf %{buildroot}%{_docdir}/%{name}/tutorials/en
%{__rm} -f  %{buildroot}%{_docdir}/%{name}/INSTALL.txt

%post
touch --no-create %{_datadir}/icons/hicolor || :
update-desktop-database &> /dev/null || :
update-mime-database %{_datadir}/mime &> /dev/null || :

/sbin/ldconfig

%postun
if [ $1 -eq 0 ]
then
  touch --no-create %{_datadir}/icons/hicolor || :
  %{_bindir}/gtk-update-icon-cache --quiet %{_datadir}/icons/hicolor || :
fi
update-desktop-database %{_datadir}/applications > /dev/null 2>&1 || :
update-mime-database %{_datadir}/mime &> /dev/null || :

/sbin/ldconfig


%posttrans
gtk-update-icon-cache %{_datadir}/icons/hicolor &>/dev/null || :


%clean
%{__rm} -rf %{buildroot}


%files
%defattr(-,root,root)
%doc %{_docdir}/%{name}/help/en/kicad.pdf
%dir %{_datadir}/%{name}/library
%dir %{_datadir}/%{name}/modules
%{_bindir}/*
%{_libdir}/%{name}/*
%{_datadir}/%{name}/
%{_datadir}/applications/*.desktop
%{_datadir}/icons/hicolor/*/mimetypes/application-x-%{name}-*.*
%{_datadir}/icons/hicolor/*/apps/*.*
%{_datadir}/mime/packages/%{name}.xml
%{_datadir}/mimelnk/application/x-%{name}-*.desktop
### %%config(noreplace) %%{_sysconfdir}/ld.so.conf.d/kicad.conf

%files lib-default
%defattr(-,root,root,-)
%{_datadir}/%{name}/library/*.dcm
%{_datadir}/%{name}/library/*.lib
%{_datadir}/%{name}/modules/*

%files doc
%defattr(-,root,root,-)
%dir %{_docdir}/%{name}
%dir %{_docdir}/%{name}/help/
%dir %{_docdir}/%{name}/presentations/
%dir %{_docdir}/%{name}/scripts/
%dir %{_docdir}/%{name}/tutorials/
%doc %{_docdir}/%{name}/help/en/*
%doc %{_docdir}/%{name}/presentations/*
%doc %{_docdir}/%{name}/scripts/*
%doc %{_docdir}/%{name}/tutorials/en/*

%changelog
* Tue Jan 9 2013 Paul Reich <reichp@att.net> 2012.11.15-2.r3804.PWR
- Split off component libraries into separate package.

* Sat Nov 17 2012 Paul Reich <reichp@att.net> 2012.11.15-1.r3804.PWR
- Packaged from upstream for FC16. Does not compile with LTO

* Sun Jan 29 2012 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2012.01.19-1.rev3256
- New upstream release
- Add doxygen as build requirement
- Add bulgarian language
- Add it and pl tutorials
- Update versioning patch
- Add patch to fix python syntax in bom-in-python (Gerd v. Egidy <gerd@egidy.de>)
- Add a new patch to fix a new link time error
- Fix a PS plotting scale bug
- Move junction button close to no connexion button
- Fix thermal relief gap calculation for circular pads in pcbnew
- Add undo/redo support for Pcbnew auto place, auto move, and auto route features.
- Make CvPcb correctly preview the selected component footprint if one has already been assigned.
- Fix a bug in pcb calculation
- Width tuning (width correction) for PS plotting of tracks, pads and vias

* Fri Jul 15 2011 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2011.07.12-2.rev3047
- Fix patch command 

* Mon Jul 12 2011 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2011.07.12-1.rev3047
- New upstream version
- Update versioning patch
- Add Polish documentation
- Add Epcos MKT capacitors library
- Fix localisation installation path

* Mon Apr  4 2011 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2011.01.28-3.rev2765
- Fix 3D viewer crash (BZ #693008)

* Wed Mar 23 2011 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2011.01.28-2.rev2765
- Add missing library

* Tue Mar 22 2011 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2011.01.28-1.rev2765
- New upstream version
- Update versioning patch, all others patches no more needed
- Patch to fix a link time error (with help from Kevin Kofler and Nikola Pajkovsky)

* Mon Feb 07 2011 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 2010.05.27-10.rev2363
- Rebuilt for https://fedoraproject.org/wiki/Fedora_15_Mass_Rebuild

* Sun Jan 30 2011 Dan Horák <dan@danny.cz> - 2010.05.27-9.rev2363
- Add s390x as 64-bit arch

* Sat Jan 29 2011 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.05.27-8.rev2363
- Fix 3D view crash with some graphics cards (BZ #664143).

* Wed Jul 14 2010 Dan Horák <dan@danny.cz> - 2010.05.27-7.rev2363
- rebuilt against wxGTK-2.8.11-2

* Tue Jun 15 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.05.27-6
- Fix some module edition issues (https://bugs.launchpad.net/kicad/+bug/593546,
  https://bugs.launchpad.net/kicad/+bug/593547)

* Fri Jun 11 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.05.27-5
- Fix a crash in searching string (https://bugs.launchpad.net/kicad/+bug/592566)

* Tue Jun  8 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.05.27-4
- Fix a focus issue (https://bugs.launchpad.net/kicad/+bug/587970)
- Fix an unwanted mouse cursor move when using the t hotkey in pcbnew
- Fix an issue on arcs draw in 3D viewer (https://bugs.launchpad.net/kicad/+bug/588882)

* Mon May 31 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.05.27-3
- Fix an undo-redo issue (https://bugs.launchpad.net/kicad/+bug/586032)

* Sun May 30 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.05.27-2
- Don't forget icons

* Sat May 29 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.05.27-1
- New packager version
- Update kicad version number patch
- Patch to fix https://bugs.launchpad.net/kicad/+bug/587175
- Patch to fix https://bugs.launchpad.net/kicad/+bug/587176

* Fri May 21 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.05.09-3
- Fix the kicad version number
- Fix a problem when trying to modify a footprint value in eeschema
  https://bugs.launchpad.net/kicad/+bug/583939

* Tue May 18 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.05.09-2
- No backup of patched files to delete
- Add noreplace flag to config macro

* Mon May 17 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.05.09-1
- New upstream version
- All previous patches no more needed
- Backward to cmake 2.6 requirement

* Sun May  9 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.05.05-1
- New upstream version
- All previous patches no more needed
- Fix url: KiCad move from SourceForge.net to LaunchPad.net
- Remove vendor tag from desktop-file-install
- Add x-kicad-pcbnew mimetype
- Add new icons for mimetype

* Mon May  3 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.04.06-9.rev2515
- Fix a minor bug that occurs when changing module orientation or side

* Mon May  3 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.04.06-8.rev2515
- Auto update 3D viewer: fix https://bugs.launchpad.net/kicad/+bug/571089
- Create png from screen (libedit): fix https://bugs.launchpad.net/kicad/+bug/573833

* Sun May  2 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.04.06-7.rev2515
- Rename COTATION class (french word) in DIMENSION and fix
  https://bugs.launchpad.net/kicad/+bug/568356 and https://bugs.launchpad.net/kicad/+bug/568357
- Some code cleaning ans enhancements + fix a bug about last netlist file used (LP #567902)

* Sat May  1 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.04.06-6.rev2515
- Make cleanup feature undoable, fix https://bugs.launchpad.net/kicad/+bug/564619
- Fix issues in SVG export, fix https://bugs.launchpad.net/kicad/+bug/565388
- Minor pcbnew enhancements
- Fix minor gerber problems, fix https://bugs.launchpad.net/kicad/+bug/567881

* Sat May  1 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.04.06-5.rev2515
- DRC have to use the local parameters clearance if specified,
  and NETCLASS value only if no local value specified. 

* Sat May  1 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.04.06-4.rev2514
- Fix https://bugs.launchpad.net/bugs/568896 and https://bugs.launchpad.net/bugs/569312

* Thu Apr 29 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.04.06-3.rev2514
- Fix a crash that happens sometimes when opening the design rule dialog

* Mon Apr 26 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.04.06-2.rev2514
- Fix https://bugs.launchpad.net/bugs/570074

* Mon Apr 12 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.04.06-1.rev2514
- New upstream version
- Patches no more needed

* Mon Apr  5 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.03.14-5.rev2463
- Add patch to fix SF #2981759

* Sat Apr  3 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.03.14-4.rev2463
- Apply upstream patch to fix inch/mm ratio
- Provide a source download URL

* Wed Mar 17 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.03.14-3.rev2463
- Patch with svn revision 2463 which fix 2 bugs
- Harmonize identation in %%changelog

* Tue Mar 16 2010 Tom "spot" Callaway <tcallawa@redhat.com> 2010.03.14-2.rev2462
- Link fixes. Really, these libraries should be linked properly so they don't need
  the executable linking calls to be explicitly correct, but cmake gives me a headache.
- Fix demo installation

* Mon Mar 15 2010 Alain Portal <alain.portal[AT]univ-montp2[DOT]fr> 2010.03.14-1.rev2462
- New upstream version

* Mon Aug 24 2009 Jon Ciesla <limb@jcomserv.net> - 2009.07.07-4.rev1863
- Multilib path correction, BZ 518916.

* Fri Jul 24 2009 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 2009.07.07-3.rev1863
- Rebuilt for https://fedoraproject.org/wiki/Fedora_12_Mass_Rebuild

* Wed Jul 08 2009 Jon Ciesla <limb@jcomserv.net> - 2009.07.07-2.rev1863
- Dropped eeschema desktop file.
- Moved English kicad.pdf to main rpm.
- Added ls.so.conf file and ldconfig to post, postun to fix libs issue.
- Dropped category Development from desktop file.

* Tue Jul 7 2009 Chitlesh Goorah <chitlesh [AT] fedoraproject DOT org> - 2009.07.07-1.rev1863
- svn rev 1863
- documentation splitted into multiple packages
- libraries are now taken directly from SVN rather than from older releases
- build changed to cmake based

* Wed Feb 25 2009 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 2007.07.09-5
- Rebuilt for https://fedoraproject.org/wiki/Fedora_11_Mass_Rebuild

