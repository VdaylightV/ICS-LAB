while read -r line
do
#	 echo $line
     eval $line
done < test2.txt
