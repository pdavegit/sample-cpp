gzip -dc input.json.gz | curl -v http://127.0.0.1:8001/json --data @- 
#cat input2.json | curl -v -XPOST http://127.0.0.1:8001/json --data @-

