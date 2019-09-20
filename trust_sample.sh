#!/bin/bash

# echo "-------trust results (4,p,ns)-------" > trust.log
for (( i=1; i<=5; i++ ))
do
	# echo "This is the "${i}" round." >> trust.log
	sed -i "50 s/round1/round"${i}"/" ./sample.py
	node=50
	while (( ${node}<=500 ))
	do
		case ${node} in
			50)
				depth=3
				width=6
				;;
			100)
				depth=3
				width=7
				;;
			150)
				depth=3
				width=7
				;;
			200)
				depth=3
				width=8
				;;
			250)
				depth=3
				width=8
				;;
			300)
				depth=4
				width=6
				;;
			350)
				depth=4
				width=7
				;;
			400)
				depth=4
				width=7
				;;
			450)
				depth=4
				width=8
				;;
			500)
				depth=4
				width=8
				;;
		esac
		# echo "Sample size: "${node} >> trust.log 
		python3.6 sample.py -n ${node} -d ${depth} -w ${width} # >> trust.log
		next=`expr ${node} + 50`
		# ./waf --run trust-query-test >> trust.log
		# sed -i "17 s/"${node}"/"${next}"/" ./examples/trust-query-test.cc
		node=${next}
	done
	# sed -i "17 s/"${node}"/50/" ./examples/trust-query-test.cc
	sed -i "50 s/round"${i}"/round1/" ./sample.py
done
