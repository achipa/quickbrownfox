cd src
fakeroot qmake
make distclean
rm *.o -f
rm moc_* -f
rm debian/quickbrownfox.substvars
cd ..
dpkg-buildpackage -rfakeroot -I.svn -S -sa
