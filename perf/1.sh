while read -r line
do
#	 echo $line
     eval $line
done < test1.txt
