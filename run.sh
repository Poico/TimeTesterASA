for i in {4000..7000..100};
	do echo $i;
		./gen_supermarble $i $i $i  > teste_$i.txt; done
