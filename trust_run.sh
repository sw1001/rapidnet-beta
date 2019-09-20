#!/bin/bash

for (( i=1; i<=5; i++ ))
do
	echo "---trust result (4,p,ns)---" > ./data/prov/time_log/trust_round${i}.log
	sed -i "17 s/round1/round"${i}"/" ./examples/trust-query-test.cc
	node=50
	while (( ${node}<=500 ))
	do
		echo "Sample size: "${node} >> ./data/prov/time_log/trust_round${i}.log 
		# python3.6 sample.py -n ${node} -d ${depth} -w ${width} # >> trust.log
		next=`expr ${node} + 50`
		./waf --run trust-query-test >> ./data/prov/time_log/trust_round${i}.log
		sed -i "17 s/"${node}"/"${next}"/" ./examples/trust-query-test.cc
		node=${next}
	done
	sed -i "17 s/"${node}"/50/" ./examples/trust-query-test.cc
	sed -i "17 s/round"${i}"/round1/" ./examples/trust-query-test.cc
done

