The module cfeSupport.c contains two functions that are required to run the cFE on 
VxWorks in kernel mode:
- GetWrsKernelTextStart
- GetWrsKernelTextEnd
When you load the cFE Core using the dynamic loader and you see the above functions marked as unresolved, 
then the module has not been included with the VIP.

It can be included in the VIP by adding the file to the VxWorks Image Project. I use the following command,
assuming you are in the VIP directory and have copied this file into that directory:
vxprj vip file add cfeSupport.c

The module also has a helper function that can be used to load and start the cFS:
startCfeCore

This function can be called from the VxWorks kernel shell command line with the path to the cFE Core:
-> startCfeCore /romfs/cpu1/core-cpu1.exe

Note that the path "/romfs/cpu1/core-cpu1.exe" is the default and will be used if you just enter:
-> startCfeCore


