for i in {1..10000}
do
  echo "insert into mytest values ($i,'smallwang911_$i');"
  #printf "insert into table valus (%d,'hello','world');\n" $i
done
