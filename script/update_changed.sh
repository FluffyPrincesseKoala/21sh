FILE=changed_file.txt
git status | grep modifié | awk {'print $2'} > $FILE
