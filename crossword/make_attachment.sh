mkdir -p attachments/
for A in {1..5}; do
	cp data/secret/group$A/$A.in attachments/$A.in
done
