
Debian
====================
This directory contains files used to package nodebased/nodebase-qt
for Debian-based Linux systems. If you compile nodebased/nodebase-qt yourself, there are some useful files here.

## nodebase: URI support ##


nodebase-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install nodebase-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your nodebaseqt binary to `/usr/bin`
and the `../../share/pixmaps/nodebase128.png` to `/usr/share/pixmaps`

nodebase-qt.protocol (KDE)

