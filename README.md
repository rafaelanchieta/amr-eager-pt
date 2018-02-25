# amr-eager-pt
AMR-EAGER is a transition-based parser for Abstract Meaning Representation. For more details, visit https://github.com/mdtux89/amr-eager

<<<<<<< HEAD
## Trained Models
To download the trained models, run the following script
```
./download.sh
```
## Installation
- Install JAMR aligner (https://github.com/jflanigan/jamr) and set path in ```preprocessing-pt.sh```

=======
>>>>>>> 32c4ee9f25b2a9309d03ac27524c22461d66d838
## Dependencies
- PALAVRAS Parser (http://visl.sdu.dk/constraint_grammar.html)
- NLTK (http://www.nltk.org/)

## Parsing with Pre-Trained Model (Little Prince)

The input data format for parsing should be raw document with one sentence per line. See ```example/test.txt```

First, run preprocessing
```
<<<<<<< HEAD
python3 preprocessing-pt.py
=======
./preprocessing_pt.sh
>>>>>>> 32c4ee9f25b2a9309d03ac27524c22461d66d838
```
This will give you output files in the same directory with the prefix ```<sentences_file>``` and extensions ```.out``` and ```.sentences```.

Then, run
```
python preprocessing.py -f <sentences_file>
```
This will give you output files in the same directory with the prefix ```<sentences_file```and extensions ```.tokens.p``` and ```.dependencies.p```

Then, run the parser
```
python parser.py -f <file> -m <model_dir>
```
This will give you the parsed AMR file (.parsed) in the same directory as your input sentence file.
