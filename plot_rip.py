import os, sys
from pylab import *

colors=['r','b','g','m','c','k']

if len(sys.argv) < 2:
	print 'usage: %s rips_result1.txt rips_result2.txt ...'%(sys.argv[0])
	sys.exit(0)

rips_result = sys.argv[1:]

xmin = 1e10
xmax = 0

for i in range(len(rips_result)):
	print 'loading ',rips_result[i]
	result = loadtxt(rips_result[i])
	f = 340*result[:,0]/2/pi
	semilogx(f, -10*log10(result[:,1]),color=colors[i],linestyle='-',lw=2)
	if f.min() < xmin:
		xmin = f.min()
	if f.max() > xmax:
		xmax = f.max()

xlim(xmin*0.95,xmax*1.05)
xlabel('f')

show()
