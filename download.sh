#!/bin/bash

wget http://143.107.183.175:23580/models/model.zip
unzip model.zip
rm -f model.zip

wget http://143.107.183.175:23580/models/model_nlpnet.zip
unzip model_nlpnet.zip
rm -f model_nlpnet.zip

wget http://143.107.183.175:23580/models/stanford-corenlp-full-2017-06-09.zip
unzip stanford-corenlp-full-2017-06-09.zip
rm -f stanford-corenlp-full-2017-06-09.zip

wget http://143.107.183.175:23580/models/stanford-parser-2010-11-30.zip
unzip stanford-parser-2010-11-30.zip
rm -f stanford-parser-2010-11-30.zip

wget http://143.107.183.175:23580/models-earger/resources.zip
unzip resources.zip
rm -f resources.zip

wget http://143.107.183.175:23580/models-earger/stanford-corenlp-full-2015-12-09.zip
unzip stanford-corenlp-full-2015-12-09.zip
rm -f stanford-corenlp-full-2015-12-09.zip

wget http://143.107.183.175:23580/models-earger/model-amr-earger.zip
unzip model-amr-earger.zip
rm -f model-amr-earger.zip

wget https://github.com/redpony/cdec/archive/master.zip
unzip master.zip
rm -f master.zip