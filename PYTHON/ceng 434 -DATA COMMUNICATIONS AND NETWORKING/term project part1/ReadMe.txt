For our project configureR1.sh needs to be run in node R1 and configureR2.sh needs to be run in node R2.

There are 5 scripts in discovery scripts for discovery part of the project.

One discovery script will be run in each node with the name corresponding to that node such as:
d.py will run on D node, r3.py will run r3 on node, r2.py will run on r2 node, r1.py will run on r1 node, s.py will run on s node
to run the scripts use "python d.py" command.

Discovery Scripts needs to be run in the order of D,R3,R2,R1,S . Such that first we use "python d.py" in D then "python r3.py" in R3 and so on.
Scripts needs to be run one after another withouth waiting more than a few seconds or they will terminate because of socket timeouts we implemented.

After running discovery scripts required files will be created by scripts. Project can move on to experimental scripts.

To have the experiment 1 run configureR3.sh on R3 node then experimentalScripts will be executed.

Experimental scripts will run just as discovery script such as:
exper_d.py will run on D node, exper_r3.py will run on R3 node, exper_r2.py will run on R2 node, exper_r1.py will run on R1 node, exper_s.py will run on S node


Experimental Scripts needs to be run in the order of D,R3,R2,R1,S . Such that first we use "python exper_d.py" in D then "python exper_r3.py" in R3 and so on.
Scripts needs to be run one after another withouth waiting more than a few seconds or they will terminate because of socket timeouts we implemented.

After experimental scripts finish running. S node will print 50 end-to-end delays which can be used on this site:https://www.mathsisfun.com/data/confidence-interval-calculator.html  to calculate %95 confidence interval of the results. Doing this for every experiment.


Found confidence intervals can be shaped as :
x = [0,20,40,50]
y = [0.96,21.3,40.8,52]
err = [0.0784,0.809,0.843,0.965]
figure
errorbar(x,y,err)
grid on
xlabel('Network Emulation Delay (ms)')
ylabel('End-to-End Delay (ms)')
legend('Delay')

to create our End-to-end delay - delay emulation graph at https://octave-online.net/ site.
