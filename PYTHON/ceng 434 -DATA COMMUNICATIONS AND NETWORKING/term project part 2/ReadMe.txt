There are 5 scripts and 1 library file for part 2 of our project. Each script named by the node it belongs to such as s.py for the node S.
For node scripts in S and D "common.py" is imported. For scripts to works on S and D, common.py needs to added to those nodes to the same location as the scripts.(common.py shares the common checksum library)

For to run scripts for each experiment argument needs to be given at node S and D. 
For example at node D and S we want to run experiment 1:
"python d.py 1" need to be run at D
"python r3.py" need to be run at R3
"python s.py 1" need to be run at S
for experiment 2:
"python d.py 2" need to be run at D
"python r1.py" need to be run at R1
"python r2.py" need to be run at R2
"python s.py 2" need to be run at S

To get our operation time result correctly script at node S need to be run last. What is run before doesn't matter as long is S is last.
Scripts needs to be run in 20 seconds without delaying more since first script will receive timeout in 20 seconds if no data is sent to its way.
After we see the result at node S other scripts will close themselves in 20 seconds with a timeout. So wait 20 before running any other experiment.

For both experiments s.py will send input.txt that is in the same folder as the script.
For experiment 1 d.py will produce output.txt in the same folder
For experiment 2 d.py will produce output2.txt in the same folder

For testing ctrl+z can be used in multihoming scripts to down that interface capability of sending or receiving packets.(link down test made with this)

Results with the input.txt we've used for fast experiments can be found at input.txt and results.txt(also some copy paste of network emulations that are used in nodes)

https://www.mathsisfun.com/data/confidence-interval-calculator.html is used to calculate %95 confidence interval of the results. (pasting raw data from results.txt)
for graphs https://octave-online.net/ is used with the configuration in confidence_interval.txt.