make clean all
#mcs -target:exe testribclient.cs ribclient.cs ribclientPINVOKE.cs
mcs -target:library ribclient.cs ribclientPINVOKE.cs
mcs -target:exe testribclient.cs -reference:ribclient.dll
mono testribclient.exe
