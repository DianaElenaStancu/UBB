SCRIPT_PATH=$1
RETRIES=10

RESULTS=()

for i in $(seq 1 $RETRIES); do
	result=$(./$SCRIPT_PATH)
  RESULTS+=($result)
done

total=0
sum=0
for i in "${RESULTS[@]}"
do
    sum=$(echo "$sum + $i" | bc)
    total=$((total + 1))
done

average=$(echo "scale=6; $sum / $total" | bc)
echo $average