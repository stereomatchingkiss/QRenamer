How to generate the installer for windows :

1 : download the pics from the mega link(https://mega.nz/#!UslFiYQJ!-eNluUhjH5S2XBlpep5RdZZ8aGYJwqgWDBXvxh5dmOA)
unzip it and place the icon "macro_names.ico" under the folder "installer/config"

2 : Install the Qt installer(version 2.0 or above)

3 : setup the environment path of Qt installer(ex : C:\Qt\QtIFW2.0.1\bin)

4 : create a "data" folder under "installer/packages/main.component"

5 : copy the QRenamer.exe under the folder "data"

6 : open command prompt and enter the command "windeployqt QRenamer.exe"(make sure you setup the path before)

7 : double click the "genInstaller.bat" under the folder "installer"

8 : done