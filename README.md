# OSC_to_Peavey_Xframe_88_Relay
 
 
This Project was built back in 2014 to pair newer technology with older technology.   

An Ipad was used with TouchOSC to send control commands via OSC Protocol to a Raspberry Pi so it can control the much older hardware, Peavey Xframe 88 Specifically, via a serial communication port.   This code currently runs the audio controls of several local bars in Las Vegas.    It has been extremly stable and never needed bug fixes.  I personally havent looked at the code in a few years and only had to send a full flash of the raspberry pi SD card with the software preinstalled a couple of times.   SD card corruption about once a year was the only problem this faced.   Code wasn't really the most abstracted / full featured and was done in a jam session for some extra operating cash.   

Some Notes:

The Full OSC standard wasn't implemented only what was necessariy to interprete the primary message and translate it to single string blurps that the xframe needed to function.

There was little to no documentation on peavey Xframe 88's serial communications,  this was a complete reverse-engineering task utilizing the original software, packet capture software and a lot of guess work based on datasets.    
