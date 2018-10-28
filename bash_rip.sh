#/bin/bash
#Array variable declaration -g global name
declare -ag ARRAY
declare -ag PASS
declare -ag RESULTS
if [ "$1" != "" ] && [ "$2" != "" ]; then
while IFS=":" read USER ENCRYPT REMAIN; do                            #Read the shadow file and split on the ':' character. Only collect use and Crypt.
    IFS="$";                                                          #Change the Internal Field Separator to split ENCRYPT on "$"
    read -a ARRAY <<<"$ENCRYPT"                                       #Split ENCRYPT on "$" and store in array
    if [ ${#ARRAY[@]} -gt 1 ]; then                                   #Passwords which dont have hashes have only 1 field which is a * or !
        echo "[*]  $USER:$ENCRYPT";
        exec 3< $2                                                    #Open the wordlist file (second paramter on command line
        while read -u 3 TEST; do                                      #Read each word from wordlist
            PASS=( $(openssl passwd -1 -salt ${ARRAY[2]} $TEST;) )    #Compute the Hash using the salt from the shadow file and the test password
            if [ "${PASS[3]}" == "${ARRAY[3]}" ]; then                #If the computed hash matches the shadow hash  HOORAY!
                RESULTS+=( "[*]$USER>$TEST" );
            fi
        done
    fi;
    IFS=":"
done <$1
echo
echo
echo "[*]+++++++++++++"
echo "[*]+  RESULTS  +"
echo "[*]+++++++++++++"
for i in ${RESULTS[@]}; do
 echo $i
done
else 
echo "rip.sh provides a simple bash script to compute linux shadow hashes."
echo 
echo "USAGE        ./rip.sh PASS LIST"
echo 
echo "    PASS    Path to the password file"
echo
echo "    LIST    Path to the wordlist file."
fi
