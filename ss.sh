
#!/bin/bash

echo "1. create the employee record"

echo "2. delete the employee"

echo "3. search the employee"

echo "4. display the employee"

echo "5. sort the employee"

echo "6. list the employee"

echo "7. exit"

echo -n "Enter the choice"
read c
case $c in
	1)read name
	 read phone
	 read id
	 if  grep -q "$id" employee.txt;  
	    then
		echo "employee already exit"
	 else
	  echo "$name:$id:$phone" >> employee.txt
	  echo "record created successfully"
	 fi
	;;

	2)read id
	 if  grep -q "$id" employee.txt;  
	    then
		grep -v "$id" employee.txt >> temp.txt
		mv temp.txt employee.txt
	 else
	  echo "record not exit"
	 fi
	;;

	3)
	  read id
	 if  grep -q "$id" employee.txt;  
	    then
		echo "employee already exit"
	 else
	  echo "not exit"
	 fi
	;;

	4)
	 read id
	 if  grep -q "$id" employee.txt;  
	    then
		grep "$id" employee.txt
	 else
	  echo "record not exist"
	 fi
	
	;;

	5)
	;;

	6)
	 cat employee.txt
	;;

	7) exit
	;;
	*) echo "wrong choice"
	;;
esac

