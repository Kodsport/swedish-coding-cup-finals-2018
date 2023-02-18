#!/bin/bash
mkdir -p attachments/
for A in {1..5}; do
	cp data/secret/group$A/00$A-c$A.in attachments/$A.in
done
