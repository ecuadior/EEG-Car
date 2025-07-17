Buck converter that will be used to power the esp 32 board
9 to 3.3V
current max output: 300mA

WHile testing out the pcb for the buck converter it was found out there was no output volatge/current. Debugging was done with a multimeter testing whih component recive voltage and testing if there is any short circuirt by testing contiuity. 
During the test it was found there was no error short shirt becasue the contituty was acting cirrectly for all componet. While looking for components volatge it was found everything to the right of the IC was recing voltge but ervrything to the left wasnt recving volatge. I speculate it could be the EN pin connected to the voolatge divder, in which the path is to small that signal is not passing. More so, the data sheet for LMR36503 highlits that in some case the EN pin should be connected starigh to VIN. 

Another possible issue is the instalation of yhe inductor to the pcb it might have damage something because when testing the connectvity of where the inductor will be place there is no noise(indacting contiuity is good) but this was with testing on the pcb with no componet. Howeverm doing the same test with the pcb with componets continutyi was found beteern the two ends of the the inductor. 
Image below is version 1 of the buck converter
![IMG_2940](https://github.com/user-attachments/assets/bb2a5df2-f2a1-4a4d-9a2e-33d345717405)
