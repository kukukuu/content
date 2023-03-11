for i in $(seq 16)
do
	file="my_work.cc"
	name="zxw${i}"
       echo "cd ~/content/lqcd_mc" > ${name}.sh
       echo "mpic++ ${file} -o ${name} && mpirun -np ${i} ${name}" >> ${name}.sh
done
for i in $(seq 16)
do
	file="my_example.cc"
	name="zxe${i}"
       echo "cd ~/content/lqcd_mc" > ${name}.sh
       echo "mpic++ ${file} -o ${name} && mpirun -np ${i} ${name}" >> ${name}.sh
done
